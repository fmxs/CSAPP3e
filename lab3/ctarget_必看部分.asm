.text:004017a8 <getbuf>:
  # 栈的生长方向向下。在向下生长的栈中，栈顶位于内存地址最低的位置，新数据会被添加到栈顶，导致栈的内存地址向下增长。
                           .text:004017a8 48 83 ec 28                      sub    $0x28,%rsp; 申请0x28字节的空间
                           .text:004017ac 48 89 e7                         mov    %rsp,%rdi; rdi = rsp
                           .text:004017af e8 8c 02 00 00                   callq  0x00401a40 <Gets>
                           .text:004017b4 b8 01 00 00 00                   mov    $0x1,%eax
                           .text:004017b9 48 83 c4 28                      add    $0x28,%rsp
                           .text:004017bd c3                               retq   
                           .text:004017be 90                               nop
                           .text:004017bf 90                               nop

.text:004017c0 <touch1>:
  # void touch1(){  // writeup给出了touch代码
  #     vlevel = 1; /* Part of validation protocol */
  #     printf("Touch1!: You called touch1()\n");
  #     validate(1);
  #     exit(0);
  # }
                           .text:004017c0 48 83 ec 08                      sub    $0x8,%rsp
                           .text:004017c4 c7 05 0e 2d 20 00 01 00 00 00    movl   $0x1,0x202d0e(%rip)        # 0x006044dc <vlevel>
                           .text:004017ce bf c5 30 40 00                   mov    $0x4030c5,%edi
                           .text:004017d3 e8 e8 f4 ff ff                   callq  0x00400cc0
                           .text:004017d8 bf 01 00 00 00                   mov    $0x1,%edi
                           .text:004017dd e8 ab 04 00 00                   callq  0x00401c8d <validate>
                           .text:004017e2 bf 00 00 00 00                   mov    $0x0,%edi
                           .text:004017e7 e8 54 f6 ff ff                   callq  0x00400e40

.text:004017ec <touch2>:
  # void touch2(unsigned val) {
  #     vlevel = 2; /* Part of validation protocol */
  #    _if (val == cookie) {//这里cookie是服务器给我们的一个数值，存放在cookie.txt文件中
  #         printf("Touch2!: You called touch2(0x%.8x)\n", val);
  #         validate(2);
  #     } else {
  #         printf("Misfire: You called touch2(0x%.8x)\n", val);
  #         fail(2);
  #     }
  #     exit(0);
  # }
                           .text:004017ec 48 83 ec 08                      sub    $0x8,%rsp; 申请8个字节空间
                           # 将保存在 edi 的输入值移动到 edx 
                           .text:004017f0 89 fa                            mov    %edi,%edx; edx = edi
                           .text:004017f2 c7 05 e0 2c 20 00 02 00 00 00    movl   $0x2,0x202ce0(%rip)        # 0x006044dc <vlevel>
                           .text:004017fc 3b 3d e2 2c 20 00                cmp    0x202ce2(%rip),%edi        # 0x006044e4 <cookie>
                           .text:00401802 75 20                            jne    0x00401824
                           .text:00401804 be e8 30 40 00                   mov    $0x4030e8,%esi
                           .text:00401809 bf 01 00 00 00                   mov    $0x1,%edi
                           .text:0040180e b8 00 00 00 00                   mov    $0x0,%eax
                           .text:00401813 e8 d8 f5 ff ff                   callq  0x00400df0
                           .text:00401818 bf 02 00 00 00                   mov    $0x2,%edi
                           .text:0040181d e8 6b 04 00 00                   callq  0x00401c8d <validate>
                           .text:00401822 eb 1e                            jmp    0x00401842
                           .text:00401824 be 10 31 40 00                   mov    $0x403110,%esi
                           .text:00401829 bf 01 00 00 00                   mov    $0x1,%edi
                           .text:0040182e b8 00 00 00 00                   mov    $0x0,%eax
                           .text:00401833 e8 b8 f5 ff ff                   callq  0x00400df0
                           .text:00401838 bf 02 00 00 00                   mov    $0x2,%edi
                           .text:0040183d e8 0d 05 00 00                   callq  0x00401d4f <fail>
                           .text:00401842 bf 00 00 00 00                   mov    $0x0,%edi
                           .text:00401847 e8 f4 f5 ff ff                   callq  0x00400e40

.text:0040184c <hexmatch>:
  # /* Compare string to hex represention of unsigned value */
  # int hexmatch(unsigned val, char *sval) {
  #     char cbuf[110];
  #     /* Make position of check string unpredictable */
  #     char *s = cbuf + random() % 100;
  #     sprintf(s, "%.8x", val);
  #     return strncmp(sval, s, 9) == 0;
  # }
                           .text:0040184c 41 54                            push   %r12
                           .text:0040184e 55                               push   %rbp
                           .text:0040184f 53                               push   %rbx
                           .text:00401850 48 83 c4 80                      add    $0xffffffffffffff80,%rsp
                           .text:00401854 41 89 fc                         mov    %edi,%r12d
                           .text:00401857 48 89 f5                         mov    %rsi,%rbp
                           .text:0040185a 64 48 8b 04 25 28 00 00 00       mov    %fs:0x28,%rax
                           .text:00401863 48 89 44 24 78                   mov    %rax,0x78(%rsp)
                           .text:00401868 31 c0                            xor    %eax,%eax
                           .text:0040186a e8 41 f5 ff ff                   callq  0x00400db0
                           .text:0040186f 48 89 c1                         mov    %rax,%rcx
                           .text:00401872 48 ba 0b d7 a3 70 3d 0a d7 a3    movabs $0xa3d70a3d70a3d70b,%rdx
                           .text:0040187c 48 f7 ea                         imul   %rdx
                           .text:0040187f 48 01 ca                         add    %rcx,%rdx
                           .text:00401882 48 c1 fa 06                      sar    $0x6,%rdx
                           .text:00401886 48 89 c8                         mov    %rcx,%rax
                           .text:00401889 48 c1 f8 3f                      sar    $0x3f,%rax
                           .text:0040188d 48 29 c2                         sub    %rax,%rdx
                           .text:00401890 48 8d 04 92                      lea    (%rdx,%rdx,4),%rax
                           .text:00401894 48 8d 04 80                      lea    (%rax,%rax,4),%rax
                           .text:00401898 48 c1 e0 02                      shl    $0x2,%rax
                           .text:0040189c 48 29 c1                         sub    %rax,%rcx
                           .text:0040189f 48 8d 1c 0c                      lea    (%rsp,%rcx,1),%rbx
                           .text:004018a3 45 89 e0                         mov    %r12d,%r8d
                           .text:004018a6 b9 e2 30 40 00                   mov    $0x4030e2,%ecx
                           .text:004018ab 48 c7 c2 ff ff ff ff             mov    $0xffffffffffffffff,%rdx
                           .text:004018b2 be 01 00 00 00                   mov    $0x1,%esi
                           .text:004018b7 48 89 df                         mov    %rbx,%rdi
                           .text:004018ba b8 00 00 00 00                   mov    $0x0,%eax
                           .text:004018bf e8 ac f5 ff ff                   callq  0x00400e70
                           .text:004018c4 ba 09 00 00 00                   mov    $0x9,%edx
                           .text:004018c9 48 89 de                         mov    %rbx,%rsi
                           .text:004018cc 48 89 ef                         mov    %rbp,%rdi
                           .text:004018cf e8 cc f3 ff ff                   callq  0x00400ca0
                           .text:004018d4 85 c0                            test   %eax,%eax
                           .text:004018d6 0f 94 c0                         sete   %al
                           .text:004018d9 0f b6 c0                         movzbl %al,%eax
                           .text:004018dc 48 8b 74 24 78                   mov    0x78(%rsp),%rsi
                           .text:004018e1 64 48 33 34 25 28 00 00 00       xor    %fs:0x28,%rsi
                           .text:004018ea 74 05                            je     0x004018f1
                           .text:004018ec e8 ef f3 ff ff                   callq  0x00400ce0
                           .text:004018f1 48 83 ec 80                      sub    $0xffffffffffffff80,%rsp
                           .text:004018f5 5b                               pop    %rbx
                           .text:004018f6 5d                               pop    %rbp
                           .text:004018f7 41 5c                            pop    %r12
                           .text:004018f9 c3                               retq   

.text:004018fa <touch3>:
  # //需要传入touch3的参数是一个字符串的首地址，这个地址指向的字符串需要与cookie的字符串表示相同。
  # //这里cookie的字符串表示是cookie:0x59b997fa的ASCII表示的字符串：35 39 62 39 39 37 66 61 00。
  # void touch3(char *sval) {
  #     vlevel = 3; /* Part of validation protocol */
  #    `if (hexmatch(cookie, sval)) {
  #         printf("Touch3!: You called touch3(\"%s\")\n", sval);
  #         validate(3);
  #     } else {
  #         printf("Misfire: You called touch3(\"%s\")\n", sval);
  #         fail(3);
  #     }
  #     exit(0);
  # }
                           .text:004018fa 53                               push   %rbx
                           .text:004018fb 48 89 fb                         mov    %rdi,%rbx
                           .text:004018fe c7 05 d4 2b 20 00 03 00 00 00    movl   $0x3,0x202bd4(%rip)        # 0x006044dc <vlevel>
                           .text:00401908 48 89 fe                         mov    %rdi,%rsi
                           .text:0040190b 8b 3d d3 2b 20 00                mov    0x202bd3(%rip),%edi        # 0x006044e4 <cookie>
                           .text:00401911 e8 36 ff ff ff                   callq  0x0040184c <hexmatch>
                           .text:00401916 85 c0                            test   %eax,%eax
                           .text:00401918 74 23                            je     0x0040193d
                           .text:0040191a 48 89 da                         mov    %rbx,%rdx
                           .text:0040191d be 38 31 40 00                   mov    $0x403138,%esi
                           .text:00401922 bf 01 00 00 00                   mov    $0x1,%edi
                           .text:00401927 b8 00 00 00 00                   mov    $0x0,%eax
                           .text:0040192c e8 bf f4 ff ff                   callq  0x00400df0
                           .text:00401931 bf 03 00 00 00                   mov    $0x3,%edi
                           .text:00401936 e8 52 03 00 00                   callq  0x00401c8d <validate>
                           .text:0040193b eb 21                            jmp    0x0040195e
                           .text:0040193d 48 89 da                         mov    %rbx,%rdx
                           .text:00401940 be 60 31 40 00                   mov    $0x403160,%esi
                           .text:00401945 bf 01 00 00 00                   mov    $0x1,%edi
                           .text:0040194a b8 00 00 00 00                   mov    $0x0,%eax
                           .text:0040194f e8 9c f4 ff ff                   callq  0x00400df0
                           .text:00401954 bf 03 00 00 00                   mov    $0x3,%edi
                           .text:00401959 e8 f1 03 00 00                   callq  0x00401d4f <fail>
                           .text:0040195e bf 00 00 00 00                   mov    $0x0,%edi
                           .text:00401963 e8 d8 f4 ff ff                   callq  0x00400e40

.text:00401968 <test>:
                           .text:00401968 48 83 ec 08                      sub    $0x8,%rsp
                           .text:0040196c b8 00 00 00 00                   mov    $0x0,%eax
                           .text:00401971 e8 32 fe ff ff                   callq  0x004017a8 <getbuf>
                           .text:00401976 89 c2                            mov    %eax,%edx
                           .text:00401978 be 88 31 40 00                   mov    $0x403188,%esi
                           .text:0040197d bf 01 00 00 00                   mov    $0x1,%edi
                           .text:00401982 b8 00 00 00 00                   mov    $0x0,%eax
                           .text:00401987 e8 64 f4 ff ff                   callq  0x00400df0
                           .text:0040198c 48 83 c4 08                      add    $0x8,%rsp
                           .text:00401990 c3                               retq   
                           .text:00401991 90                               nop
                           .text:00401992 90                               nop
                           .text:00401993 90                               nop
                           .text:00401994 90                               nop
                           .text:00401995 90                               nop
                           .text:00401996 90                               nop
                           .text:00401997 90                               nop
                           .text:00401998 90                               nop
                           .text:00401999 90                               nop
                           .text:0040199a 90                               nop
                           .text:0040199b 90                               nop
                           .text:0040199c 90                               nop
                           .text:0040199d 90                               nop
                           .text:0040199e 90                               nop
                           .text:0040199f 90                               nop
