#lec 3 SPOC Discussion

##**提前准备**
（请在周一上课前完成）

 - 完成lec3的视频学习和提交对应的在线练习
 - git pull ucore_os_lab, v9_cpu, os_course_spoc_exercises  　in github repos。这样可以在本机上完成课堂练习。
 - 仔细观察自己使用的计算机的启动过程和linux/ucore操作系统运行后的情况。搜索“80386　开机　启动”
 - 了解控制流，异常控制流，函数调用,中断，异常(故障)，系统调用（陷阱）,切换，用户态（用户模式），内核态（内核模式）等基本概念。思考一下这些基本概念在linux, ucore, v9-cpu中的os*.c中是如何具体体现的。
 - 思考为什么操作系统需要处理中断，异常，系统调用。这些是必须要有的吗？有哪些好处？有哪些不好的地方？
 - 了解在PC机上有啥中断和异常。搜索“80386　中断　异常”
 - 安装好ucore实验环境，能够编译运行lab8的answer
 - 了解Linux和ucore有哪些系统调用。搜索“linux 系统调用", 搜索lab8中的syscall关键字相关内容。在linux下执行命令: ```man syscalls```
 - 会使用linux中的命令:objdump，nm，file, strace，man, 了解这些命令的用途。
 - 了解如何OS是如何实现中断，异常，或系统调用的。会使用v9-cpu的dis,xc, xem命令（包括启动参数），分析v9-cpu中的os0.c, os2.c，了解与异常，中断，系统调用相关的os设计实现。阅读v9-cpu中的cpu.md文档，了解汇编指令的类型和含义等，了解v9-cpu的细节。
 - 在piazza上就lec3学习中不理解问题进行提问。

## 第三讲 启动、中断、异常和系统调用-思考题

## 3.1 BIOS
 1. 比较UEFI和BIOS的区别。
 > UEFI和BIOS区别

/|UEFI | BIOS 
-|-|-|
开机模式|保护模式 | 16位实模式
开机时寻址空间 | | 16bit，$2^{16} = 64KB$
语言 | C 语言 | 组合语言 
扩充方式 | 载入驱动程序 | 结合中断向量
可扩展性 | 好 | 较差
输出 | 用EFI Byte Code（EFI字节代码）编写而成的，需要解释 | 由直接运行在CPU上的代码组成 

> 流程对比

步骤 | UEFI | BIOS|
-|-|-
1 | 系统开机 - 上电自检（Power On Self Test 或 POST）。|系统开机 - 上电自检（Power On Self Test 或 POST）。
2 |UEFI 固件被加载，并由它初始化启动要用的硬件。 | POST过后初始化用于启动的硬件（磁盘、键盘控制器等）。
3 | 固件读取其引导管理器以确定从何处（比如，从哪个硬盘及分区）加载哪个 UEFI 应用。| BIOS会运行BIOS磁盘启动顺序中第一个磁盘的首440bytes（MBR启动代码区域）内的代码。
4| 固件按照引导管理器中的启动项目，加载UEFI 应用。| 启动引导代码从BIOS获得控制权，然后引导启动下一阶段的代码（如果有的话）（一般是系统的启动引导代码）。
5|已启动的 UEFI 应用还可以启动其他应用（对应于 UEFI shell 或 rEFInd 之类的引导管理器的情况）或者启动内核及initramfs（对应于GRUB之类引导器的情况），这取决于 UEFI 应用的配置。| 再次被启动的代码（二阶段代码）（即启动引导）会查阅支持和配置文件。
6 | / | 根据配置文件中的信息，启动引导程序会将内核和initramfs文件载入系统的RAM中，然后开始启动内核。

> PXE ，网络启动，大致启动流程 
1. POST
2. 发送一个动态获得IP地址的广播包（请求FIND帧）到网络上。
3. DHCP服务器在收到该广播包后，发送给客户端分配IP地址的DHCP回应包。内容包括客户端的IP地址，TFTP服务器的IP地址（DHCP服务器的066选项），预设通讯通道，及开机启动文件（DHCP服务器的067选项）。该文件应该是一种由PXE启动规范规定的固定格式的可执行文. XP正常启动时显示多重启动菜单之前的启动代码。 
4. 客户面收到DHCP回应后，则会响应一个FRAME，以请求传送启动文件。之后，服务端将和客户机再进行一系列应答，以决定启动的一些参数。
5. 客户端通过TFTP通讯协议从服务器下载开机启动文件。启动文件接收完成后，将控制权转交给启动块，完成PXE启动。客户端通过这个开机影像文件开机，这个开机文件可以只是单纯的开机程式也可以是操作系统。如果是用3Com Boot Image Editor编辑的启动文件，系统将根据PXE文件中的代码决定是显示选择菜单还是直接下载预设的镜像文件启动电脑。
接下来的工作就由相应的镜像文件来完成了。
> 参考资料：https://www.microsoft.com/resources/documentation/WindowsServ/2003/all/ADS/en-us/nbs_boot_policy_overview.mspx?mfr=true

 1. 描述PXE的大致启动流程。

## 3.2 系统启动流程
 1. 了解NTLDR的启动流程。
 
```
 1. NTLDR把计算机的微处理器从实模式转换为32位平面内存模式
 2. NTLDR执行适当的小型文件系统驱动程序并加载Boot.ini文件
 3. NTLDR通过Boot.ini文件获得要启动的操作系统
 4. NTLDR进行硬件检测，检测结束后进行配置选择
```
 1. 了解GRUB的启动流程。

```
 1. 装载第二引导装载程序
 2. 显示启动菜单和提供用户交互接口，并根据用户选择或默认配置加载操作系统内核
 3. 根据grub.conf显示启动菜单，提供同用户交互界面
 4. 根据用户选择或默认配置和grub.conf的内核配置加载相应的内核程序，把控制权交给内核程序
```
 1. 比较NTLDR和GRUB的功能有差异。

```
 1.NTLDR只能引导windows系统，只能安装在硬盘
 2.GRUB可以引导任意系统，可以安装在U盘，硬盘，光盘等
 
```
 1. 了解u-boot的功能。

```
* 系统引导支持NFS挂载、RAMDISK(压缩或非压缩)形式的根文件系统；支持NFS挂载、从FLASH中引导压缩或非压缩系统内核；
* 基本辅助功能强大的操作系统接口功能；可灵活设置、传递多个关键参数给操作系统，适合系统在不同开发阶段的调试要求与产品发布，尤以Linux支持最为强劲；支持目标板环境参数多种存储方式，如FLASH、NVRAM、EEPROM；
* CRC32校验可校验FLASH中内核、RAMDISK镜像文件是否完好；
* 设备驱动串口、SDRAM、FLASH、以太网、LCD、NVRAM、EEPROM、键盘、USB、PCMCIA、PCI、RTC等驱动支持；
* 上电自检功能SDRAM、FLASH大小自动检测；SDRAM故障检测；CPU型号；
* 特殊功能XIP内核引导；
  主要用于嵌入式操作系统的装载与引导。
  开放源码，支持多种嵌入式操作系统内核，支持多个处理器系列，具有较高的可靠性和稳定性。
```

## 3.3 中断、异常和系统调用比较
 1. 什么是中断、异常和系统调用？
 2. 中断、异常和系统调用的处理流程有什么异同？
 2. 举例说明Linux中有哪些中断，哪些异常？
 3. 以ucore lab8的answer为例，uCore的时钟中断处理流程。
 1. Linux的系统调用有哪些？大致的功能分类有哪些？  (w2l1)

 ```
 1. 举例说明Linux中有哪些中断，哪些异常？
> Linux中把中断描述符分为五类：

| 门|功能 |
|-|-|
|中断门（interrupt gate）| 用户态的进程不能访问Intel中断门（门的DPL字段为0）。所有的Linux中断处理程序都通过中断门激活，并全部限制在内核态。
|系统门（system gate）|用户态的进程可以访问Intel陷阱门（门的DPL字段为3）。通过系统门来激活三个Linux异常处理程序|
|系统中断门（system interrupt gate）| 能够被用户态进程访问的Intel中断门（门的DPL字段为3）。与向量3相关的异常处理程序是由系统中断门激活的
|陷阱门（trap gate）| 用户态的进程不能访问的一个Intel陷阱门（门的DPL字段为0）。大部分Linux异常处理程序都通过陷阱门来激活。
|任务门（task gate）| 不能被用户态进程访问的Intel任务门（门的DPL字段为0）。Linux对“Double fault”异常的处理程序是由任务门激活的。|
 > 查看全部中断，可以查看linux 的中断向量表。中断举例： 时钟中断，键盘输入中断等。
> 异常举例：除零错，page fault 等

 1. Linux的系统调用有哪些？大致的功能分类有哪些？  (w2l1)

 > 具体可以查阅 syscall table http://docs.cs.up.ac.za/programming/asm/derick_tut/syscalls.html
 提供将近两百个系统调用，大致分类可以查看系统调用所在的文件，根据文件名推测大概类型，比如，与时间相关，输入输出设备相关的read_write，io_ctrl，与进程调度相关的sched等

```
  + 采分点：说明了Linux的大致数量（上百个），说明了Linux系统调用的主要分类（文件操作，进程管理，内存管理等）
  - 答案没有涉及上述两个要点；（0分）
  - 答案对上述两个要点中的某一个要点进行了正确阐述（1分）
  - 答案对上述两个要点进行了正确阐述（2分）
  - 答案除了对上述两个要点都进行了正确阐述外，还进行了扩展和更丰富的说明（3分）
 ```
 
 1. 以ucore lab8的answer为例，uCore的系统调用有哪些？大致的功能分类有哪些？(w2l1)
 
 ```
  + 采分点：说明了ucore的大致数量（二十几个），说明了ucore系统调用的主要分类（文件操作，进程管理，内存管理等）
  - 答案没有涉及上述两个要点；（0分）
  - 答案对上述两个要点中的某一个要点进行了正确阐述（1分）
  - 答案对上述两个要点进行了正确阐述（2分）
  - 答案除了对上述两个要点都进行了正确阐述外，还进行了扩展和更丰富的说明（3分）
 ```
 
## 3.4 linux系统调用分析
 1. 通过分析[lab1_ex0](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab1/lab1-ex0.md)了解Linux应用的系统调用编写和含义。(w2l1)
 
 ```
  objdump : 对二进制程序进行反编译，得到汇编源码。 -S参数命令是尽可能反汇编出源代码。
  nm : 用于显示关于指定 File 中符号的信息，得到符号的地址及类型。
  file : 是检测文件类型的命令。例如可以检测出ex0.exe为32位i386的ELF文件，使用了动态链接和ld-linux的解释器。
  系统调用 :  通过将SYS_write放入eax，STDOUT放入ebx，字符串的位置放入ecx， 字符串的长度放入edx。
  之后通过int 0x80来实现系统调用，通过这几个放入寄存器的参数来实现功能。
 ```

 ```
  + 采分点：说明了objdump，nm，file的大致用途，说明了系统调用的具体含义
  - 答案没有涉及上述两个要点；（0分）
  - 答案对上述两个要点中的某一个要点进行了正确阐述（1分）
  - 答案对上述两个要点进行了正确阐述（2分）
  - 答案除了对上述两个要点都进行了正确阐述外，还进行了扩展和更丰富的说明（3分）
 
 ```
 
 1. 通过调试[lab1_ex1](https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab1/lab1-ex1.md)了解Linux应用的系统调用执行过程。(w2l1)
 
 ```
  strace : 用于用来跟踪进程执行时的系统调用和所接收的信号。-f参数显示了跟踪由fork调用所产生的子进程。-c参数可以统计每一系统调用的所执行的时间,次数和出错的次数等。
  通过strace的追踪，可以看到在linux应用调用中，ex1依次调用了execve新建进程, access检查文件, open打开文件, fstat查看文件, read读取文件, mmap将文件载入内存, mprotect设置内存访问权限, 最后调用write函数输出hello world。
 ```

 ```
  + 采分点：说明了strace的大致用途，说明了系统调用的具体执行过程（包括应用，CPU硬件，操作系统的执行过程）
  - 答案没有涉及上述两个要点；（0分）
  - 答案对上述两个要点中的某一个要点进行了正确阐述（1分）
  - 答案对上述两个要点进行了正确阐述（2分）
  - 答案除了对上述两个要点都进行了正确阐述外，还进行了扩展和更丰富的说明（3分）
 ```
 
## 3.5 ucore系统调用分析
 1. ucore的系统调用中参数传递代码分析。
 1. 以getpid为例，分析ucore的系统调用中返回结果的传递代码。
 1. 以ucore lab8的answer为例，分析ucore 应用的系统调用编写和含义。
 > - 在ucore中的trap.c中，通过trapframe的结构传递参数。调用trap（trapframe），trap中调用trap_dispatch(trapframe),在trap_dispatch()中检查中断类型trapframe tf->trapno,如果是系统调用T_SYS，则调用syscall().
> - 进入syscall()中，在trapframe中有tf_reg，tf_reg的eax传递系统调用号，参数有ebx, ecx, edi,esi传递。

 1. ucore的系统调用中返回结果的传递代码分析。
> 恢复syscall存储在trapframe中的调用trap之前的CPU状态，清除trap number，error code，iret，从中断中返回。
找到 /kern/trap/trapentry.S中的.globl __trapret

    ```
__trapret:
    # restore registers from stack
    popal

    # restore %ds, %es, %fs and %gs
    popl %gs
    popl %fs
    popl %es
    popl %ds

    # get rid of the trap number and error code
    addl $0x8, %esp
    iret
    ```
 1. 以ucore lab8的answer为例，分析ucore应用的系统调用编写和含义。
  > 程序员通过user/libs/syscall.c中的函数调用系统调用。如
    
    ```
int
sys_wait(int pid, int *store) {
    return syscall(SYS_wait, pid, store);
}
    ```
> syscall()函数中，通过压栈，和内联函数调用传入参数.内联函数可以在kernel/syscall.c中找到对应的使用，见1

    ```
    syscall(int num, ...) {
    va_list ap;
    va_start(ap, num);
    uint32_t a[MAX_ARGS];
    int i, ret;
    for (i = 0; i < MAX_ARGS; i ++) {
        a[i] = va_arg(ap, uint32_t);
    }
    va_end(ap);

    asm volatile (
        "int %1;"
        : "=a" (ret)
        : "i" (T_SYSCALL),
          "a" (num),
          "d" (a[0]),
          "c" (a[1]),
          "b" (a[2]),
          "D" (a[3]),
          "S" (a[4])
        : "cc", "memory");
    return ret;
}
    ```


 1. 以ucore lab8的answer为例，尝试修改并运行ucore OS kernel代码，使其具有类似Linux应用工具`strace`的功能，即能够显示出应用程序发出的系统调用，从而可以分析ucore应用的系统调用执行过程。
 
## 3.6 请分析函数调用和系统调用的区别
 1. 请从代码编写和执行过程来说明。
   1. 说明`int`、`iret`、`call`和`ret`的指令准确功能
   
   ```
    系统调用使用的是int和iret
    函数调用使用的是call ret
    int 和 iret 调用的时候会从用户态切换到内核态，在用户堆栈和内核栈之间进行切换。
   ```
 

## v9-cpu相关题目
---

### 提前准备
```
cd YOUR v9-cpu DIR
git pull 
cd YOUR os_course_spoc_exercise DIR
git pull 
```

### v9-cpu系统调用实现
  1. v9-cpu中os4.c的系统调用中参数传递代码分析。
  1. v9-cpu中os4.c的系统调用中返回结果的传递代码分析。
  1. 理解v9-cpu中os4.c的系统调用编写和含义。

