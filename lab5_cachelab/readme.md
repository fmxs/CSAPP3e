# Part A: cache simulator 第一部分：缓存模拟器
# 目标
cachelab 模拟器这部分给了一个参考程序 csim-ref，我们需要实现的缓存模拟器要和这个参考程序 csim-ref 一模一样。
# 测试用例
测试用例是一行 linux 命令，比如像这样：

linux> ./csim-ref -v -s 3 -E 2 -b 4 -t traces/example.trace

这行命令用于运行参考程序 csim-ref, 这个命令包含了以下参数：

-v：表示开启详细输出模式，输出模拟过程中的详细信息。

-s 3：表示设置缓存的组数为 3。

-E 2：表示设置每个组中的行数为 2。

-b 4：表示设置缓存块的大小为 4 字节。

-t traces/example.trace：表示指定要模拟的输入文件路径为 traces/example.trace。

在执行这条命令后，csim-ref 会按照指定的参数模拟 CPU 缓存的工作过程，并输出模拟结果。
