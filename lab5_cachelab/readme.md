# Part A: cache simulator 第一部分：缓存模拟器
# 目标
cachelab 模拟器这部分给了一个参考程序 `csim-ref`，我们需要实现的缓存模拟器**要和参考程序 `csim-ref` 一模一样**。
# 测试用例
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

# 解析测试用例
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
            t = atoi(argv[++i]);
            break;
        default:
            break;
        }
    }
}
```
代码第一行中声明了一个for循环，由于数组中第一个值是程序名称，没什么用，所以循环范围就跳过了0，从1开始，到10时就结束，这样就能遍历所有有用的参数。

第3行声明了一个`c[]`，这是一个字符数组，可以包含两个字符，比如`char c[] = "-t";`就包含了 '-' 和 't' 两个字符，其中c[0] = '-'，c[1] = 't'。

第5行使用了`if`判断，判断如果c[0]等于'-'，说明c[1]必然是一个操作符，于是进入下面的`switch`。

在第7行使用了一个`switch`结构，对不同的操作符执行不同的操作。

这时就用到了上一节的知识，比如操作符`v`就是表示开启详细输出模式，操作符's'表示设置缓存的组数，等等。

在`case 'b'`中使用到了C语言函数库里的一个函数`atoi`,它能把字符串转换为一个整数。比如`atoi('5')`返回值就是int型的 `5`
