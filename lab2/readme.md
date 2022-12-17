# 参考链接
https://hansimov.gitbook.io/csapp/labs/bomb-lab/writeup#1.-jie-shao
https://zhuanlan.zhihu.com/p/458788706

# 使用到的工具
- ODA，可以反汇编文件。https://onlinedisassembler.com/odaweb/S3t8BvPF
![image](https://user-images.githubusercontent.com/65701532/208233954-a10433b4-58f3-4372-a484-0ab54326b288.png)
- VS Code 的 x86 and x86_64 Assembly插件，可以高亮汇编代码
![image](https://user-images.githubusercontent.com/65701532/208233948-1e0e4f29-871a-4469-b8e0-09c8ee0a8997.png)
- gdb，linux调试工具，要在Ubuntu系统用
- ChatAPI，可以帮助解释汇编代码，汇编代码复制粘贴进去就行 https://gpt.chatapi.art/

# 文件说明
- bomb.asm

这是将文件夹中的bomb反汇编后得到的文件，反汇编工具是ODA，地址在上面一节写着。

该文件对6个炸弹函数给出了详细的注释。

参考链接包括：
https://www.viseator.com/2017/06/21/CS_APP_BombLab/

https://wdxtub.com/csapp/thick-csapp-lab-2/2016/04/16/

