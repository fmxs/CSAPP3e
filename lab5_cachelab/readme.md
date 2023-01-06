# Part A: cache simulator 第一部分：缓存模拟器
# 目标
cachelab 模拟器这部分给了一个参考程序 `csim-ref`，我们需要实现的缓存模拟器**要和参考程序 `csim-ref` 一模一样**。
# 前置知识：熟悉测试用例
测试用例是一行 linux 命令，比如像这样：
`linux> ./csim-ref -v -s 3 -E 2 -b 4 -t traces/example.trace`

这行命令用于运行参考程序 `csim-ref`, 这个命令包含了以下参数，每个参数以空格分割：

`./csim-ref`: 表示程序名

`-v`：表示开启详细输出模式，输出模拟过程中的详细信息。

`-s 3`：表示设置缓存的组数为 3。

`-E 2`：表示设置每个组中的行数为 2。

`-b 4`：表示设置缓存块的大小为 4 字节。

`-t traces/example.trace`：表示指定要模拟的输入文件路径为 traces/example.trace。

在执行这条命令后，`csim-ref` 会按照指定的参数模拟 CPU 缓存的工作过程，并输出模拟结果。

# 1.解析输入参数
我们使用C语言程序的入口函数`main`将测试用例中的各项参数读取到程序里，标准的`main`函数如下所示：
```
int main(int argc, char *argv[])
{
  // 程序的主体
  return 0;
}
```
`argc`： 表示输入的参数总数。

在测试用例`./csim-ref -v -s 3 -E 2 -b 4 -t traces/example.trace`中，每个参数都以空格分割开，一共有10个参数。所以这里`argc`就等于 10。

`argv`: 保存了每个输入的参数。

在测试用例`./csim-ref -v -s 3 -E 2 -b 4 -t traces/example.trace`中，`argv`的长度为10，`argv[0]`保存了`./csim-ref`，`argv[1]`保存了`-v`，依次类推。

因此，我们可以在main函数中写一个`for`循环，从而遍历argv数组中的参数。

```
/// @brief 解析输入参数：解析命令行参数，获取缓存的相关参数，比如缓存的大小、缓存块的大小、缓存映射方式等。
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
int s, E, b;
char fileName[];
bool print_msg;
```
代码第一行中声明了一个for循环，由于数组中第一个值是程序名称，没什么用，所以循环范围就跳过了0，从1开始，到10时就结束，这样就能遍历所有有用的参数。

第3行声明了一个`c[]`，这是一个字符数组，可以包含两个字符，比如`char c[] = "-t";`就包含了 '-' 和 't' 两个字符，其中c[0] = '-'，c[1] = 't'。

第5行使用了`if`判断，判断如果c[0]等于'-'，说明c[1]必然是一个操作符，于是进入下面的`switch`。

在第7行使用了一个`switch`结构，对不同的操作符执行不同的操作。

这时就用到了上一节的知识，比如操作符`v`就是表示开启详细输出模式，操作符's'表示设置缓存的组数，等等。

在`case 'b'`中使用到了C语言函数库里的一个函数`atoi`,它能把字符串转换为一个整数。比如`atoi('5')`返回值就是int型的 `5`

# 2.初始化缓存
![image](https://user-images.githubusercontent.com/65701532/210950939-adb9e857-05ad-4306-ae0a-9725a8118bfb.png)

上图是自学讲义的第17页，它提示我们3个信息：
- 第一点，缓存就是一个由 `缓存行` 组成的二维数组，这个二维数组一共有`S`组`E`行的`缓存组`。
- 第二点，`S = 2^s` 表示缓存的组数是 2 的 s 次方，即有 `S` 个组。
- 第三点，`E`是每组中的行数

缓存的组是一个抽象的概念，每个组中通常有一定数量的行，每行又有一定数量的块。我们用一个例子来解释组、行、块的概念。

![image](https://user-images.githubusercontent.com/65701532/210953147-7c0e12e3-ff7c-4ab2-a0c1-c4a49a8751a7.png)

在上图中，我们定义了一个缓存，这个缓存一共有4个组。每个组的结构都有一样数量的行，一样数量的块。这里以组1为例继续深入：

![image](https://user-images.githubusercontent.com/65701532/210953992-a04abde8-55ea-44d2-90bd-86626b046526.png)

在上图中，我们看到组1里一共有3行，分别叫做`cache line 1, cache line 2, cache line 3`。

现在我们接着再往每个`cache line` 里看。

![image](https://user-images.githubusercontent.com/65701532/210955785-73d9cf04-c730-4fd5-8d9d-c7392cfcc6ee.png)

如上图，`cache line 1`中一共有4个`块`（block），分别叫做block1, block 2, block 3, block 4。

例如，如果 `S = 2^s = 4`，那么这个缓存就有 `4` 个组，每个组中可能有若干行，每行又可能有若干块。

每一个`cache line`有3部分组成：

- valid bit，表示合法位
- tag，表示这个块所在的缓存行对应的内存地址
- timestamp，表示时间戳

翻译成C语言的话，我们可以将`cache line`定义成一个结构体，里面存放3个变量：
```
/**
 * Each	cache_line	has:
 * § Valid	bit
 * § Tag
 * § LRU counter(only if you are not using a queue)
 */
typedef struct
{
    int validBit;  // 合法位
    int tag;       // 存储缓存行对应的内存地址
    int timeStamp; // 时间戳
} cache_line;
```

接着再用结构体`cache_line`去定义`缓存`。**注意，讲义提示我们：缓存就是由`cache_line`组成的二维数组**。
```
cache_line **virtual_cache;
```

自学讲义中提示我们使用 `malloc` 函数去给缓存动态地分配内存空间。

在C语言中，如果要使用 `malloc` 函数分配二维数组，可以先分配一维数组，然后再分配每一维的内存空间。

```
/// @brief 初始化缓存：根据解析到的参数，初始化缓存的结构。
void init(int s, int E)
{
    int sets = 1 << s;
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
```
到这里我们就成功的进行了缓存的初始化。不过别忘记malloc分配的内存还需要手动释放：
```
/// @brief 在使用完 malloc 分配的内存空间后，一定要记得使用 free
void freeCache()
{
    int sets = 1 << s;
    for (int i = 0; i < sets; i++)
    {
        free(virtual_cache[i]);
    }
}
```

