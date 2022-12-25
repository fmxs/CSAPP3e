# 从start_farm开始，到end_farm为止，寻找需要的gadget
.text:00401994 <start_farm>:
                           .text:00401994 b8 01 00 00 00                   mov    $0x1,%eax
                           .text:00401999 c3                               retq   

.text:0040199a <getval_142>:
                           .text:0040199a b8 fb 78 90 90                   mov    $0x909078fb,%eax
                           .text:0040199f c3                               retq   

.text:004019a0 <addval_273>:
    # 48 89 c7 表示 movq %rax,%rdi 可为我们所用

    # movq 和 movl 区别：movq是移动64位数据(quadword)的指令，movl是移动32位数据(long)的指令
    # 它们都用于在寄存器和内存之间移动数据
    # 例子：MOVL $0x12345678, %EAX，这个指令将数值0x12345678存储在EAX寄存器中。
    # 例子：MOVQ $0x1234567812345678, %RAX，这个指令将数值0x1234567812345678存储在RAX寄存器中。
                           .text:004019a0 8d 87 48 89 c7 c3                lea    -0x3c3876b8(%rdi),%eax
                           .text:004019a6 c3                               retq   

.text:004019a7 <addval_219>:
    # 58 表示 popq %rax 可为我们所用
                           .text:004019a7 8d 87 51 73 58 90                lea    -0x6fa78caf(%rdi),%eax
                           .text:004019ad c3                               retq   

.text:004019ae <setval_237>:
                           .text:004019ae c7 07 48 89 c7 c7                movl   $0xc7c78948,(%rdi)
                           .text:004019b4 c3                               retq   

.text:004019b5 <setval_424>:
                           .text:004019b5 c7 07 54 c2 58 92                movl   $0x9258c254,(%rdi)
                           .text:004019bb c3                               retq   

.text:004019bc <setval_470>:
                           .text:004019bc c7 07 63 48 8d c7                movl   $0xc78d4863,(%rdi)
                           .text:004019c2 c3                               retq   

.text:004019c3 <setval_426>:
                           .text:004019c3 c7 07 48 89 c7 90                movl   $0x90c78948,(%rdi)
                           .text:004019c9 c3                               retq   

.text:004019ca <getval_280>:
                           .text:004019ca b8 29 58 90 c3                   mov    $0xc3905829,%eax
                           .text:004019cf c3                               retq   

.text:004019d0 <mid_farm>:
                           .text:004019d0 b8 01 00 00 00                   mov    $0x1,%eax
                           .text:004019d5 c3                               retq   

.text:004019d6 <add_xy>:
    # rsi 和 esi 的区别：rsi是64位指针寄存器，在64位操作系统中使用。而esi是32位指针寄存器，在32位操作系统中使用。
    # rsi称为源指针寄存器，esi称为扩展源指针寄存器，它们都指向源字符串中正在处理的字符的地址
                           .text:004019d6 48 8d 04 37                      lea    (%rdi,%rsi,1),%rax
                           .text:004019da c3                               retq   

.text:004019db <getval_481>:
                           .text:004019db b8 5c 89 c2 90                   mov    $0x90c2895c,%eax
                           .text:004019e0 c3                               retq   

.text:004019e1 <setval_296>:
                           .text:004019e1 c7 07 99 d1 90 90                movl   $0x9090d199,(%rdi)
                           .text:004019e7 c3                               retq   

.text:004019e8 <addval_113>:
                           .text:004019e8 8d 87 89 ce 78 c9                lea    -0x36873177(%rdi),%eax
                           .text:004019ee c3                               retq   

.text:004019ef <addval_490>:
                           .text:004019ef 8d 87 8d d1 20 db                lea    -0x24df2e73(%rdi),%eax
                           .text:004019f5 c3                               retq   

.text:004019f6 <getval_226>:
                           .text:004019f6 b8 89 d1 48 c0                   mov    $0xc048d189,%eax
                           .text:004019fb c3                               retq   

.text:004019fc <setval_384>:
                           .text:004019fc c7 07 81 d1 84 c0                movl   $0xc084d181,(%rdi)
                           .text:00401a02 c3                               retq   

.text:00401a03 <addval_190>:
                           .text:00401a03 8d 87 41 48 89 e0                lea    -0x1f76b7bf(%rdi),%eax
                           .text:00401a09 c3                               retq   

.text:00401a0a <setval_276>:
                           .text:00401a0a c7 07 88 c2 08 c9                movl   $0xc908c288,(%rdi)
                           .text:00401a10 c3                               retq   

.text:00401a11 <addval_436>:
                           .text:00401a11 8d 87 89 ce 90 90                lea    -0x6f6f3177(%rdi),%eax
                           .text:00401a17 c3                               retq   

.text:00401a18 <getval_345>:
                           .text:00401a18 b8 48 89 e0 c1                   mov    $0xc1e08948,%eax
                           .text:00401a1d c3                               retq   

.text:00401a1e <addval_479>:
                           .text:00401a1e 8d 87 89 c2 00 c9                lea    -0x36ff3d77(%rdi),%eax
                           .text:00401a24 c3                               retq   

.text:00401a25 <addval_187>:
                           .text:00401a25 8d 87 89 ce 38 c0                lea    -0x3fc73177(%rdi),%eax
                           .text:00401a2b c3                               retq   

.text:00401a2c <setval_248>:
                           .text:00401a2c c7 07 81 ce 08 db                movl   $0xdb08ce81,(%rdi)
                           .text:00401a32 c3                               retq   

.text:00401a33 <getval_159>:
                           .text:00401a33 b8 89 d1 38 c9                   mov    $0xc938d189,%eax
                           .text:00401a38 c3                               retq   

.text:00401a39 <addval_110>:
                           .text:00401a39 8d 87 c8 89 e0 c3                lea    -0x3c1f7638(%rdi),%eax
                           .text:00401a3f c3                               retq   

.text:00401a40 <addval_487>:
                           .text:00401a40 8d 87 89 c2 84 c0                lea    -0x3f7b3d77(%rdi),%eax
                           .text:00401a46 c3                               retq   

.text:00401a47 <addval_201>:
                           .text:00401a47 8d 87 48 89 e0 c7                lea    -0x381f76b8(%rdi),%eax
                           .text:00401a4d c3                               retq   

.text:00401a4e <getval_272>:
                           .text:00401a4e b8 99 d1 08 d2                   mov    $0xd208d199,%eax
                           .text:00401a53 c3                               retq   

.text:00401a54 <getval_155>:
                           .text:00401a54 b8 89 c2 c4 c9                   mov    $0xc9c4c289,%eax
                           .text:00401a59 c3                               retq   

.text:00401a5a <setval_299>:
                           .text:00401a5a c7 07 48 89 e0 91                movl   $0x91e08948,(%rdi)
                           .text:00401a60 c3                               retq   

.text:00401a61 <addval_404>:
                           .text:00401a61 8d 87 89 ce 92 c3                lea    -0x3c6d3177(%rdi),%eax
                           .text:00401a67 c3                               retq   

.text:00401a68 <getval_311>:
                           .text:00401a68 b8 89 d1 08 db                   mov    $0xdb08d189,%eax
                           .text:00401a6d c3                               retq   

.text:00401a6e <setval_167>:
                           .text:00401a6e c7 07 89 d1 91 c3                movl   $0xc391d189,(%rdi)
                           .text:00401a74 c3                               retq   

.text:00401a75 <setval_328>:
                           .text:00401a75 c7 07 81 c2 38 d2                movl   $0xd238c281,(%rdi)
                           .text:00401a7b c3                               retq   

.text:00401a7c <setval_450>:
                           .text:00401a7c c7 07 09 ce 08 c9                movl   $0xc908ce09,(%rdi)
                           .text:00401a82 c3                               retq   

.text:00401a83 <addval_358>:
                           .text:00401a83 8d 87 08 89 e0 90                lea    -0x6f1f76f8(%rdi),%eax
                           .text:00401a89 c3                               retq   

.text:00401a8a <addval_124>:
                           .text:00401a8a 8d 87 89 c2 c7 3c                lea    0x3cc7c289(%rdi),%eax
                           .text:00401a90 c3                               retq   

.text:00401a91 <getval_169>:
                           .text:00401a91 b8 88 ce 20 c0                   mov    $0xc020ce88,%eax
                           .text:00401a96 c3                               retq   

.text:00401a97 <setval_181>:
                           .text:00401a97 c7 07 48 89 e0 c2                movl   $0xc2e08948,(%rdi)
                           .text:00401a9d c3                               retq   

.text:00401a9e <addval_184>:
                           .text:00401a9e 8d 87 89 c2 60 d2                lea    -0x2d9f3d77(%rdi),%eax
                           .text:00401aa4 c3                               retq   

.text:00401aa5 <getval_472>:
                           .text:00401aa5 b8 8d ce 20 d2                   mov    $0xd220ce8d,%eax
                           .text:00401aaa c3                               retq   

.text:00401aab <setval_350>:
                           .text:00401aab c7 07 48 89 e0 90                movl   $0x90e08948,(%rdi)
                           .text:00401ab1 c3                               retq   

.text:00401ab2 <end_farm>:
                           .text:00401ab2 b8 01 00 00 00                   mov    $0x1,%eax
                           .text:00401ab7 c3                               retq   
                           .text:00401ab8 90                               nop
                           .text:00401ab9 90                               nop
                           .text:00401aba 90                               nop
                           .text:00401abb 90                               nop
                           .text:00401abc 90                               nop
                           .text:00401abd 90                               nop
                           .text:00401abe 90                               nop
                           .text:00401abf 90                               nop
