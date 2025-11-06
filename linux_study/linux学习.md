# 常用指令

```shell
在visual studio里面改完记得build一下才会把vs里面改好的东西同步到linux中projects文件夹下

cd /mnt/c/Users/wuzif/source/repos/everyday_homework/linux_study：切换到这个目录

ls：查看当前目录下文件 -a查看所有东西(包括隐藏文件)，-l查看详细信息，-r/R递归进行(对目录进行操作一般用到)

cat:查看文件内容

tac: 倒过来逐行输出文件内容

touch:创建文件

pwd:查看当前所在目录

~: 当前用户的主目录

.:当前所在目录

..:当前目录上一级目录

mkdir dir_name: 创建目录    

mkdir (-p) grandparent/parent/child: 如果没有有-p,只创建末级目录，如果末级目录的祖先目录不存在会报错,如果有-p，最终目的也是创建末级目录，但是如果末级目录的祖先目录不存在会自动创建

rm -r dir_name: 递归删除dir_name下的所有内容，并且回收站也找不回，慎用！！！！！！！！！

gcc -Og(优化选项，还有-O1/-O2) source.c(源文件) -S(生成的文件类型) (生成的文件名)

objdump -d main > main_objdump.d：把main(目标文件反汇编并重定向(可覆盖原文件，>>是不覆盖)输出到
main_objdump.d，后面半部分可选，)

gdb (obj文件/源文件)：开始用gdb调试该文件

disassemble (函数/文件)：反汇编这部分，但是不会像objdump显示每个字节，只显示每个指令

x/14xb 函数名(也可以是任何地址)：显示从该函数地址开始的14个字节

windows cd命令不能跨盘符，输入"D:"先切换到D盘

```



# Machine level programming-Basic

寄存器用来存放临时变量，用哪个寄存器存储有专门的算法，这个不用关心



