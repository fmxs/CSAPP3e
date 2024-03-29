# 实验介绍
# 1 简介
这项实验的目的是优化内存密集型代码，而“图像处理”为我们提供了许多优化函数的例子：
1. 旋转，将图像逆时针旋转90度。
2.  平滑，将图像“平滑”或者“模糊”。
## 1.1 旋转
在这个实验中，我们会把图像表示为一个二维矩阵M，其中Mij 表示矩阵M第(i,j)个像素的值，而像素值是由红，绿，蓝（RGB）组成的。
我们只考虑方形图像，这样只需要用一个字母N就可以表示图像的行数/列数。行和列的编号范围从 0 到 N - 1 。

鉴于以上的表示方式，对图像的旋转操作其实可以抽象为对矩阵的如下操作：
1. 矩阵的转置。将 M(i,j) 和 M(j,i) 交换。
2. 行交换。将第 i 行和第 N - 1 - i 行进行交换

我们用一张图来说明这两种矩阵操作。
![在这里插入图片描述](https://img-blog.csdnimg.cn/bee6f21121094ed4861aa8b384a2da49.png)

从这张图可以看到，如果我们想旋转某张图片，就可以抽象为先对矩阵进行转置，再对矩阵做行交换。
## 1.2 平滑
平滑操作简单来说是取一个像素点，再计算出以它为中心周围 3 乘 3 像素的像素平均值，再将像素平均值赋值给这 3 乘 3 区域中的的每一个像素。

![在这里插入图片描述](https://img-blog.csdnimg.cn/5124237412604539a8dc211aefef4db3.png)
# 2 数据结构
1个像素点由3种颜色组成，结构定义如下：

![在这里插入图片描述](https://img-blog.csdnimg.cn/7db247444855423683c42e2ac27aebd9.png)

可以看出，RGB值有16位表示（"16位颜色"）。一个图像I被表示为像素的一维数组，其中第（i，j）个像素是 I[RIDX(i,j,n)]。n是图像矩阵的尺寸。

RIDX是一个定义如下的宏。代码在defs.h中
![在这里插入图片描述](https://img-blog.csdnimg.cn/d2123d2cb89341c6ab62d6b3e1fe074a.png)

# 3 提示与支持
**唯一要修改的源文件是kernels.c**
## 3.1 版本管理
由于需要写好几个版本的旋转、平滑实现代码，为了比较各个版本的性能，实验提供了一个“注册”函数

![在这里插入图片描述](https://img-blog.csdnimg.cn/c679af2f204c46d5adc6a570e7e86f11.png)

在这个 add_rotate_function 函数中，第一个参数表示函数名，第二个参数表示用来描述函数作用的字符串。

## 3.2 驱动程序
我们写好的源代码将和实验提供的代码链接成一个二进制驱动文件。每次创建该文件都需要执行一次命令：

![在这里插入图片描述](https://img-blog.csdnimg.cn/d1c6282663124f19918f0187c9ddc041.png)

如果想运行这个文件，需要执行以下命令：

![在这里插入图片描述](https://img-blog.csdnimg.cn/3cfb4e325c9149b387a31bc24cda240f.png)

讲义提示一共有4种运行模式：

|  模式| 含义 |
|--|--|
| 默认模式 | 把写好的所有版本都在这个模式下运行 |
| Autograder模式 | 只运行rotate()和smooth()函数。是老师评分时的模式 |
| 文件模式 | 只运行.txt文件里写的指定版本 |
| 转储模式 | 每个版本的描述字符串会被存到一个.txt中，你可以编辑这个.txt，只保留你想要文件模式去测试的版本 |

如果运行这个驱动文件时没有写上任何参数，那么驱动文件就会以默认模式启动。其他模式和选项可以通过命令行参数来指定。
|参数|含义  |
|--|--|
| -g |Autograder模式，只运行rotate()和smooth()  |
| -f < funcfile> |文件模式，只执行< funcfile>中指定的版本  |
| -d < dumpfile> |转储模式，将所有版本名称转储到名字为< dumpfile>的.txt的文件里 |
| -q |将版本名称转储到转储文件后就退出。要与-d一起用。比如，要在打印完转储文件后立即退出，请输入：./driver -qd dumpfile  |
| -h|帮助，打印命令行的用法  |
# 4 两个任务
## 4.1 优化旋转
在这一部分需要优化旋转，并使CPE尽可能的低。

**样例版本**

我们可以使用./driver去运行样例版本，来查看运行结果。

在命令行中输入：

![在这里插入图片描述](https://img-blog.csdnimg.cn/de422da8ffcd43ffaf3dca9b145285ea.png)

**输出结果：**

![在这里插入图片描述](https://img-blog.csdnimg.cn/ed3128a0184340648331f303e909c8c0.png)

## 4.2 优化平稳
在这一部分需要优化平滑，实现尽可能低的CPE

我们可以使用./driver去运行样例版本，来查看运行结果。

在命令行中输入：

![在这里插入图片描述](https://img-blog.csdnimg.cn/492ab5d33516430d8a9a075eb804aa2b.png)

**得到运行结果：**

![在这里插入图片描述](https://img-blog.csdnimg.cn/f3fa07d3f94e40fbbbf5e9fd0dc5ce60.png)
## 4.3 建议
讲义建议我们：
- 看旋转和平滑生成的汇编代码，
- 使用课堂/书本上讲到的优化技巧，
- 始终专注于优化内部循环（在一个循环中被重复执行的代码）。
- 与旋转函数相比，平滑函数的计算量更大，对内存的敏感度更低，所以优化方式也有一些不同。
# 5 编码规则
- 必须是ANSI C语言，不能使用任何嵌入式汇编语言语句。
- 不能干扰时间测量机制。代码不能打印出任何不相干的信息。
- 只能修改**kernels.c**中的代码，允许在这些文件中定义宏、额外的全局变量和其他在这些文件中的程序。
