#lec 3 SPOC Discussion

## 第三讲 启动、中断、异常和系统调用-思考题

## 3.1 BIOS
 1. 比较UEFI和BIOS的区别。
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
 1. 举例说明Linux中有哪些中断，哪些异常？
 1. Linux的系统调用有哪些？大致的功能分类有哪些？  (w2l1)

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
  ex1.md的提示不是很懂
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
 
