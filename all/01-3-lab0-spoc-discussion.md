# lab0 SPOC思考题

## 个人思考题

---

能否读懂ucore中的AT&T格式的X86-32汇编语言？请列出你不理解的汇编语言。
- [x]  

>  - http://www.imada.sdu.dk/Courses/DM18/Litteratur/IntelnATT.htm
> - 最困难的地方在于，名称跟曾经的习惯用法不一样，尤其是涉及到特殊寄存器的指令，以及特权指令等。
> 

虽然学过计算机原理和x86汇编（根据THU-CS的课程设置），但对ucore中涉及的哪些硬件设计或功能细节不够了解？
- [x]  

> - 中断寄存器和非通用寄存器等。
> - 内存的layout


哪些困难（请分优先级）会阻碍你自主完成lab实验？
- [x]  

> - 调试工具简陋，尤其进行完本次SPOC课之后，xem和hexedit功能很少，非常不利于大型软件的调试！做lab时会有更好的工具吗？
> - 阅读源码的能力
>   - 很多不知所云的位运算
>   - 嵌入汇编，看到讲义上还有嵌入汇编的特殊用法？？

如何把一个在gdb中或执行过程中出现的物理/线性地址与你写的代码源码位置对应起来？
- [x]  

> 1. 在gdb中通过break加行号得到物理地址，list加*物理地址得到行号。
> 2. 用nm, objdump工具可以看到

了解函数调用栈对lab实验有何帮助？
- [x]  

> 出了错可以调试 
> 对于函数的调用过程和程序的运行过程有更好的理解。
> 便于调试以及检查。 

你希望从lab中学到什么知识？
- [x]  

> 更好的理解os
> improve programming skills

---

## 小组讨论题

---

搭建好实验环境，请描述碰到的困难和解决的过程。
- [x]  

> - 困难：工具上手需要时间
> - 解决：先把最基本的功能掌握，在试验中慢慢上手。

熟悉基本的git命令行操作命令，从github上
的 http://www.github.com/chyyuu/ucore_lab 下载
ucore lab实验
- [x]  

> clone 仓库 
> gitclone http://www.github.com/chyyuu/ucore_lab

尝试用qemu+gdb（or ECLIPSE-CDT）调试lab1
- [x]   

> 清除文件夹：make clean 
> 编译lab1：make 
> 调出debug命令行：make debug

对于如下的代码段，请说明”：“后面的数字是什么含义
```
 /* Gate descriptors for interrupts and traps */
 struct gatedesc {
    unsigned gd_off_15_0 : 16;        // low 16 bits of offset in segment
    unsigned gd_ss : 16;            // segment selector
    unsigned gd_args : 5;            // # args, 0 for interrupt/trap gates
    unsigned gd_rsv1 : 3;            // reserved(should be zero I guess)
    unsigned gd_type : 4;            // type(STS_{TG,IG32,TG32})
    unsigned gd_s : 1;                // must be 0 (system)
    unsigned gd_dpl : 2;            // descriptor(meaning new) privilege level
    unsigned gd_p : 1;                // Present
    unsigned gd_off_31_16 : 16;        // high bits of offset in segment
 };
 ```

- [x]  

> 每一个filed(域，成员变量)在struct(结构)中所占的位数; 也称“位域”，用于表示这个成员变量占多少位(bit)。

对于如下的代码段，
```
#define SETGATE(gate, istrap, sel, off, dpl) {            \
    (gate).gd_off_15_0 = (uint32_t)(off) & 0xffff;        \
    (gate).gd_ss = (sel);                                \
    (gate).gd_args = 0;                                    \
    (gate).gd_rsv1 = 0;                                    \
    (gate).gd_type = (istrap) ? STS_TG32 : STS_IG32;    \
    (gate).gd_s = 0;                                    \
    (gate).gd_dpl = (dpl);                                \
    (gate).gd_p = 1;                                    \
    (gate).gd_off_31_16 = (uint32_t)(off) >> 16;        \
}
```
如果在其他代码段中有如下语句，
```
unsigned intr;
intr=8;
SETGATE(intr, 0,1,2,3);
```
请问执行上述指令后， intr的值是多少？

- [x]  0x10002

> https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab0/lab0_ex3.c

请分析 [list.h](https://github.com/chyyuu/ucore_lab/blob/master/labcodes/lab2/libs/list.h)内容中大致的含义，并能include这个文件，利用其结构和功能编写一个数据结构链表操作的小C程序
- [x]  

> 

---

## 开放思考题

---

是否愿意挑战大实验（大实验内容来源于你的想法或老师列好的题目，需要与老师协商确定，需完成基本lab，但可不参加闭卷考试），如果有，可直接给老师email或课后面谈。
- [x]  

>  

## v9-cpu相关题目
---

### 提前准备
```
sudo apt-get install hexedit
cd YOUR v9-cpu DIR
git pull v9-cpu 
cd YOUR os_course_spoc_exercise DIR
git pull os_course_spoc_exercise
```

分析和实验funcall.c，需要完成的内容包括： 
-[X]

 - 修改代码，可正常显示小组两位同学的学号（用字符串） 
 > 完成https://github.com/JudyYe/v9-cpu/blob/master/root/usr/funcall.c
 - 生成funcall.c的汇编码，理解其实现并给汇编码写注释
 > v9-cpu/funcall.txt https://github.com/JudyYe/v9-cpu/blob/master/funcall.txt
 - 尝试用xem的简单调试功能单步调试代码
 > ./xem -g funcall

 - 回答如下问题：
   - funcall中的堆栈有多大？是内核态堆栈还是用户态堆栈
 > 并不知道上限在哪里啊???写一个爆栈的程序？;内核态
   - funcall中的全局变量ret放在内存中何处？如何对它寻址？
 > 通过SG，反汇编，找到global_address + 0，
   - funcall中的字符串放在内存中何处？如何对它寻址？
 > 运行到2c的时候，看a的值，就是string s存放的内存地址。
 > 
 >结果：根据此方法，找到地址：0x90 - 0x93处内存是（'2''0''1''3')即字符串的位置。

   - 局部变量i在内存中的何处？如何对它寻址？
  > 方法：运行到4c处，查看local sp + 4 
   >
> 结果：栈指向 07bfffd8，+4，位置即为 07bfffdc，发现与i的值吻合（从21开始递减）
   - 当前系统是处于中断使能状态吗？
  > iena = 0 中断不使能

   - funcall中的函数参数是如何传递的？函数返回值是如何传递的？
  > 参数列表从右到左压栈，返回值放到a中
   - 分析并说明funcall执行文件的格式和内容
  > 方法：使用hexedit查看funcall的二进制文件,对照汇编码
  > 
  > 结果：发现汇编码中的0000-008c放到了执行文件的0010-009c处，这一段是代码段，00A0 - 00A3是全局data段，00A4 - 是local data段。如下表


地址段 | 布局
-|-
0000 - 0009 | 未知 
   0010 - 009F | code 段
   00A0 - 00A3 | global data 段
   00A4 - end | local data 段

　

分析和实验os0.c，需要完成的内容包括： 
-[X]

 - 生成os0.c的汇编码，理解其实现并给汇编码写注释
 > 
 - 尝试用xem的简单调试功能单步调试代码
 - 回答如下问题：
   - 何处设置的中断使能？   
 > STI 设置中断使能为1
   - 系统何时处于中断屏蔽状态？
 > 开始处理timeout中断的时候，em.c使中断屏蔽

   - 如果系统处于中断屏蔽状态，如何让其中断使能？
 > RTI命令后，如果全部中断处理完，开中断。
   - 系统产生中断后，CPU会做哪些事情？（在没有软件帮助的情况下）
 > 1. 切换状态：当在用户态时，保存当前环境，并切换到内核态
> 2. 保存PC到栈中 ``` *(uint *)((xsp ^ p) & -8) = (uint)xpc - tpc;```
> 3. 跳转到中断向量，即设置pc ```xpc = (int *)(ivec + tpc);```
> 4. 执行中断（运行以后的指令）
> 总之，就是把当前状态存到栈中，然后跳转到中断向量表的位置。

   - CPU执行RTI指令的具体完成工作是哪些？
 > 1. return from interrupt, 
> 2. set pc, sp, may switch user/kernel mode; 
> 3. if has pending interrupt, process the interrupt


[HARD]分析和实验os1/os3.c，需要完成的内容包括： 
-[X]
 
 - os1中的task1和task2的堆栈的起始和终止地址是什么？
 > 注：堆栈的起始和终止地址指，运行时的栈，不是最大可以使用的栈。
| \ | task0 | task1|
| - | - | - |
|起始 | 函数调用时的sp = 07bffff8 | task1_stack + 50|
|终止 | 中断发生时的sp | 中断发生时的sp |


 - os1是如何实现任务切换的？
> 在trap中交换task0和task1的sp，使得恢复中断的时候，跳转到交换后的函数状态。

 - os3中的task1和task2的堆栈的起始和终止地址是什么？
> task0/1_stack的地址。

```task0_sp -= 2; *task0_sp = &task0_stack[1000];
task0_sp -= 2; *task0_sp = &trapret;```

 - os3是如何实现任务切换的？
 
| 名称 | 功能 | 
|-|-|
|task0_stack/task1_stack | 处于用户态时的栈，usp指向他们 
|task0_kstack/task1_kstack| 核心态时的栈
> 在核心态中，维护两个栈task0/1_kstack，当发生一个timeout中断的时候，交换task0_sp和task1_sp两个栈顶指针，在task0_sp栈顶的第一个RTI时，会首先跳转到trapret，在trapret中，利用实现存在task0/1_stack中的栈元素，设置到用户态，然后再次跳转到task0/1，此时运行task0/1就处于用户态运行。
> 与os1的不同之处在于，task0 / 1是运行在用户态中的，输出write利用系统调用sys_write完成。```trap = FSYS```

 - os3的用户态task能够破坏内核态的系统吗？
 > 可以。

 > 方法1：在write()中，改变asm(TRAP, S_write)为asm(TRAP, $随便的值)
 
 >方法2：在task0中调用自己写的read函数，read是一个未定义中断号
 
 >方法3：参考陈文潇，```就是fc不是syscall也不是timer，可以看到alltraps里面是从PSHA开始的，那么在这之前PUSH一个奇怪的数作为fc，使得跳入unknown interrupt即可。```