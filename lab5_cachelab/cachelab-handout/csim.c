#include "cachelab.h"
#include <unistd.h>
#include <getopt.h>

int s = 0, E = 0, b = 0;
char fileName[];
bool print_msg = false;
/// @brief 1.解析输入参数：解析命令行参数，获取缓存的相关参数，比如缓存的大小、缓存块的大小、缓存映射方式等。
/// @param argc 命令行总的参数个数
/// @param argv 保存了argc个参数，第0个参数是程序全名，之后参数是用户输入的参数。参数以空格分割开，空格不会被读取到argv数组里
void decode(int argc, char *argv[])
{ /* looping over arguments */
    for (int i = 1; i < argc; i++)
    {
        char c[] = argv[i]; // 依次保存每个输入的参数
        // 如果参数是操作符
        if (c[0] == '-')
        {
            switch (c[1])
            {
            case 'v': // 表示开启详细输出模式，输出模拟过程中的详细信息。
                print_msg = true;
                break;
            case 's': // 表示设置缓存的组数
                s = atoi(argv[++i]);
                break;
            case 'E': // 表示设置每个组中的行数
                E = atoi(argv[++i]);
                break;
            case 'b': // 表示设置缓存块的大小
                b = atoi(argv[++i]);
                break;
            case 't': // 表示指定要模拟的输入文件路径
                strcpy(fileName, argv[++i]);
                break;
            default:
                break;
            }
        }
    }
}

/**
 * Each	cache_line	has:
 * § Valid	bit
 * § Tag
 * § LRU counter(only if you are not using a queue)
 */
typedef struct
{
    uint32_t valid;     // 合法位
    uint32_t tag;       // 存储缓存行对应的内存地址
    uint64_t timeStamp; // 时间戳
} cache_line;

cache_line **virtual_cache;

/// @brief 2.初始化缓存：根据解析到的参数，初始化缓存的结构。
void init(int s, int E)
{
    uint32_t sets = 1 << s;
    // 分配一维数组
    virtual_cache = (cache_line **)malloc(sizeof(cache_line *) * sets);
    if (virtual_cache == NULL)
    {
        printf("分配一维数组失败!");
        return;
    }
    // 分配每一维的内存空间
    for (int i = 0; i < sets; i++)
    {
        virtual_cache[i] = (cache_line *)malloc(sizeof(cache_line) * E);
        if (virtual_cache[i] == NULL)
        {
            printf("分配第二维数组失败!");
            return;
        }
    }
}

/// @brief 在使用完 malloc 分配的内存空间后，一定要记得使用 free
void freeCache()
{
    int sets = 1 << s;
    for (int i = 0; i < sets; i++)
    {
        free(virtual_cache[i]);
        virtual_cache[i] = NULL;
    }
    free(virtual_cache);
    virtual_cache = NULL;
}

#define U64MAX ~0ULL // unsigned long long 类型的最大值ffffffffffffffff，所有位都为1

// uint32_t 是 unsigned int 的缩写，表示 32 位无符号整数。
// 注意：uint32_t 只能在 C99 或更高版本的 C 语言中使用，如果使用旧版的 C 语言，需要使用 unsigned int 替代 uint32_t。

/// @brief 3.读入输入文件：读取指定的输入文件，获取要模拟的操作序列。
/// @param line
void loadOperation(char *line)
{
    char op;
    uint64_t addr = 0;
    uint32_t dataBytes = 0;
    // %c：一个字符  %lx：十六进制数字  %u：无符号数字
    sscanf(line, " %c %lx,%u", &op, &addr, &dataBytes);
    switch (op)
    {
    case 'L':
    case 'M':
    case 'S':
        break;
    default:
        return;
    }
    if (print_msg)
    {
        printf("fmxs:\n");
        printf("%c %lx,%u ", op, addr, dataBytes);
    }

    // 总结：计算缓存中的组号（将地址转换为缓存中的组号）
    // 1. (addr >> b) 将地址addr右移b位，去除地址中的块号，只保留组号
    // 2. (~(U64MAX << s)) 将一个全1的数字U64MAX左移，最低位就保留了s个0。再进行取反，就得到一个最低s位全1，其余全0的数字。
    // 将1和2得到的结果相与，就能得到组号。
    uint32_t set = (addr >> b) & (~(U64MAX << s));

    // 总结：计算缓存中的标记位
    // 1.(b+s)表示地址中的块号和组号所占的长度
    // 2.将addr右移(b+s)位后，就得到标记位
    uint32_t tag = addr >> (b + s);

    // 4.模拟操作：对于输入文件中的每一条操作，在缓存中查找是否存在对应的缓存行。如果存在，就称这次访问为缓存命中；如果不存在，就称这次访问为缓存未命中。根据操作的类型（Load 或 Modify）和缓存命中情况，更新缓存的状态。
    bool isFindCache = false;
    int empty_line = -1;
    for (int i = E - 1; i > 0; i--)
    {
        if (virtual_cache[set][i].valid)
        {
            if (virtual_cache[set][i].tag == tag)
            {
                isFindCache = true;
                virtual_cache[set][i].timeStamp = ticks;
                break;
            }
        }
        else
        {
            empty_line = 1;
        }
    }

    // 如果是修改指令，由于有写回操作，需要+1
    if (op == 'M')
    {
        hits++;
    }
    if (isFindCache)
    {
        hits++;
        if (print_msg)
        {
            printf("hit ");
        }
    }
    else
    {
        miss++;
        if (print_msg)
        {
            printf("miss ");
        }
        if (empty_line == -1) // 如果未命中且没有空行，就需要LRU替换
        {
            evictions++;
            empty_line = LRU(set);
            if (print_msg)
            {
                printf("eviction ");
            }
        }

        // 未命中后需要更新缓存
        virtual_cache[set][empty_line].valid = 1;
        virtual_cache[set][empty_line].tag = tag;
        virtual_cache[set][empty_line].timeStamp = ticks;
    }

    if (op == 'M' && print_msg)
    {
        printf("hit ");
    }
    if (print_msg)
    {
        printf("\n");
    }
}

#define MAX_LEN 100 // 读取的最大字符数（包括结尾的换行符）
char line[MAX_LEN];
void cmd_parsing(char *fileName)
{
    // r:只读。以“只读”方式打开当前目录下的 fileName 文件，并使 fp 指向该文件，这样就可以通过 fp 来操作 demo.txt 了。fp 通常被称为文件指针。
    FILE *fp = fopen(fileName, "r");
    while (!feof(fp) && !ferror(fp))
    {
        strcpy(line, "\n");
        fgets(line, MAX_LEN, fp); // 从文件中读取一行字符串
        loadOperation(line);
        ticks++;
    }
    fclose(fp);
}

uint8_t LRU(uint8_t set)
{
    int replace = 0;
    // 寻找timeStamp值最小的缓存；timeStamp值越小，说明距离现在越久
    for (int i = 1; i < E; i++)
    {
        if (virtual_cache[set][i].timeStamp < virtual_cache[set][replace].timeStamp)
        {
            replace = i;
        }
    }
    return replace;
}

int hits = 0, miss = 0, evictions = 0;
#define file "test-csim"
#define ticks __TIME__
int main(int argc, char *argv[])
{

    /**
     * 1.解析输入参数：解析命令行参数，获取缓存的相关参数，比如缓存的大小、缓存块的大小、缓存映射方式等。
     *
     * 2.初始化缓存：根据解析到的参数，初始化缓存的结构。
     *
     * 3.读入输入文件：读取指定的输入文件，获取要模拟的操作序列。
     *
     * 4.模拟操作：对于输入文件中的每一条操作，在缓存中查找是否存在对应的缓存行。如果存在，就称这次访问为缓存命中；如果不存在，就称这次访问为缓存未命中。根据操作的类型（Load 或 Modify）和缓存命中情况，更新缓存的状态。
     *
     * 5.输出统计信息：输出缓存命中次数、缓存未命中次数以及缓存替换次数等信息。
     */
    decode(argc, argv);

    init(s, E);

    cmd_parsing(file);

    loadOperation(line);

    printSummary(hits, miss, evictions);

    freeCache();

    return 0;
}
