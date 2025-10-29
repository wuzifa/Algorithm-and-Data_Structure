
main:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 8a 2f 00 00    	push   0x2f8a(%rip)        # 3fb0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 8c 2f 00 00    	jmp    *0x2f8c(%rip)        # 3fb8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nopl   0x0(%rax)
    1030:	f3 0f 1e fa          	endbr64
    1034:	68 00 00 00 00       	push   $0x0
    1039:	e9 e2 ff ff ff       	jmp    1020 <_init+0x20>
    103e:	66 90                	xchg   %ax,%ax
    1040:	f3 0f 1e fa          	endbr64
    1044:	68 01 00 00 00       	push   $0x1
    1049:	e9 d2 ff ff ff       	jmp    1020 <_init+0x20>
    104e:	66 90                	xchg   %ax,%ax
    1050:	f3 0f 1e fa          	endbr64
    1054:	68 02 00 00 00       	push   $0x2
    1059:	e9 c2 ff ff ff       	jmp    1020 <_init+0x20>
    105e:	66 90                	xchg   %ax,%ax

Disassembly of section .plt.got:

0000000000001060 <__cxa_finalize@plt>:
    1060:	f3 0f 1e fa          	endbr64
    1064:	ff 25 8e 2f 00 00    	jmp    *0x2f8e(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    106a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001070 <__stack_chk_fail@plt>:
    1070:	f3 0f 1e fa          	endbr64
    1074:	ff 25 46 2f 00 00    	jmp    *0x2f46(%rip)        # 3fc0 <__stack_chk_fail@GLIBC_2.4>
    107a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001080 <strtol@plt>:
    1080:	f3 0f 1e fa          	endbr64
    1084:	ff 25 3e 2f 00 00    	jmp    *0x2f3e(%rip)        # 3fc8 <strtol@GLIBC_2.2.5>
    108a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001090 <__printf_chk@plt>:
    1090:	f3 0f 1e fa          	endbr64
    1094:	ff 25 36 2f 00 00    	jmp    *0x2f36(%rip)        # 3fd0 <__printf_chk@GLIBC_2.3.4>
    109a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

Disassembly of section .text:

00000000000010a0 <_start>:
    10a0:	f3 0f 1e fa          	endbr64
    10a4:	31 ed                	xor    %ebp,%ebp
    10a6:	49 89 d1             	mov    %rdx,%r9
    10a9:	5e                   	pop    %rsi
    10aa:	48 89 e2             	mov    %rsp,%rdx
    10ad:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    10b1:	50                   	push   %rax
    10b2:	54                   	push   %rsp
    10b3:	45 31 c0             	xor    %r8d,%r8d
    10b6:	31 c9                	xor    %ecx,%ecx
    10b8:	48 8d 3d eb 00 00 00 	lea    0xeb(%rip),%rdi        # 11aa <main>
    10bf:	ff 15 13 2f 00 00    	call   *0x2f13(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    10c5:	f4                   	hlt
    10c6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    10cd:	00 00 00 

00000000000010d0 <deregister_tm_clones>:
    10d0:	48 8d 3d 39 2f 00 00 	lea    0x2f39(%rip),%rdi        # 4010 <__TMC_END__>
    10d7:	48 8d 05 32 2f 00 00 	lea    0x2f32(%rip),%rax        # 4010 <__TMC_END__>
    10de:	48 39 f8             	cmp    %rdi,%rax
    10e1:	74 15                	je     10f8 <deregister_tm_clones+0x28>
    10e3:	48 8b 05 f6 2e 00 00 	mov    0x2ef6(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    10ea:	48 85 c0             	test   %rax,%rax
    10ed:	74 09                	je     10f8 <deregister_tm_clones+0x28>
    10ef:	ff e0                	jmp    *%rax
    10f1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10f8:	c3                   	ret
    10f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001100 <register_tm_clones>:
    1100:	48 8d 3d 09 2f 00 00 	lea    0x2f09(%rip),%rdi        # 4010 <__TMC_END__>
    1107:	48 8d 35 02 2f 00 00 	lea    0x2f02(%rip),%rsi        # 4010 <__TMC_END__>
    110e:	48 29 fe             	sub    %rdi,%rsi
    1111:	48 89 f0             	mov    %rsi,%rax
    1114:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1118:	48 c1 f8 03          	sar    $0x3,%rax
    111c:	48 01 c6             	add    %rax,%rsi
    111f:	48 d1 fe             	sar    $1,%rsi
    1122:	74 14                	je     1138 <register_tm_clones+0x38>
    1124:	48 8b 05 c5 2e 00 00 	mov    0x2ec5(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    112b:	48 85 c0             	test   %rax,%rax
    112e:	74 08                	je     1138 <register_tm_clones+0x38>
    1130:	ff e0                	jmp    *%rax
    1132:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1138:	c3                   	ret
    1139:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001140 <__do_global_dtors_aux>:
    1140:	f3 0f 1e fa          	endbr64
    1144:	80 3d c5 2e 00 00 00 	cmpb   $0x0,0x2ec5(%rip)        # 4010 <__TMC_END__>
    114b:	75 2b                	jne    1178 <__do_global_dtors_aux+0x38>
    114d:	55                   	push   %rbp
    114e:	48 83 3d a2 2e 00 00 	cmpq   $0x0,0x2ea2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1155:	00 
    1156:	48 89 e5             	mov    %rsp,%rbp
    1159:	74 0c                	je     1167 <__do_global_dtors_aux+0x27>
    115b:	48 8b 3d a6 2e 00 00 	mov    0x2ea6(%rip),%rdi        # 4008 <__dso_handle>
    1162:	e8 f9 fe ff ff       	call   1060 <__cxa_finalize@plt>
    1167:	e8 64 ff ff ff       	call   10d0 <deregister_tm_clones>
    116c:	c6 05 9d 2e 00 00 01 	movb   $0x1,0x2e9d(%rip)        # 4010 <__TMC_END__>
    1173:	5d                   	pop    %rbp
    1174:	c3                   	ret
    1175:	0f 1f 00             	nopl   (%rax)
    1178:	c3                   	ret
    1179:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001180 <frame_dummy>:
    1180:	f3 0f 1e fa          	endbr64
    1184:	e9 77 ff ff ff       	jmp    1100 <register_tm_clones>

0000000000001189 <plus>:
    1189:	f3 0f 1e fa          	endbr64
    118d:	48 8d 04 37          	lea    (%rdi,%rsi,1),%rax
    1191:	c3                   	ret

0000000000001192 <sumstore>:
    1192:	f3 0f 1e fa          	endbr64
    1196:	53                   	push   %rbx
    1197:	48 89 d3             	mov    %rdx,%rbx
    119a:	48 63 f6             	movslq %esi,%rsi
    119d:	48 63 ff             	movslq %edi,%rdi
    11a0:	e8 e4 ff ff ff       	call   1189 <plus>
    11a5:	48 89 03             	mov    %rax,(%rbx)
    11a8:	5b                   	pop    %rbx
    11a9:	c3                   	ret

00000000000011aa <main>:
    11aa:	f3 0f 1e fa          	endbr64
    11ae:	41 54                	push   %r12
    11b0:	55                   	push   %rbp
    11b1:	53                   	push   %rbx
    11b2:	48 83 ec 10          	sub    $0x10,%rsp
    11b6:	48 89 f3             	mov    %rsi,%rbx
    11b9:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    11c0:	00 00 
    11c2:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
    11c7:	31 c0                	xor    %eax,%eax
    11c9:	48 8b 7e 08          	mov    0x8(%rsi),%rdi
    11cd:	ba 0a 00 00 00       	mov    $0xa,%edx
    11d2:	be 00 00 00 00       	mov    $0x0,%esi
    11d7:	e8 a4 fe ff ff       	call   1080 <strtol@plt>
    11dc:	89 c5                	mov    %eax,%ebp
    11de:	4c 63 e0             	movslq %eax,%r12
    11e1:	48 8b 7b 10          	mov    0x10(%rbx),%rdi
    11e5:	ba 0a 00 00 00       	mov    $0xa,%edx
    11ea:	be 00 00 00 00       	mov    $0x0,%esi
    11ef:	e8 8c fe ff ff       	call   1080 <strtol@plt>
    11f4:	89 c6                	mov    %eax,%esi
    11f6:	48 63 d8             	movslq %eax,%rbx
    11f9:	48 89 e2             	mov    %rsp,%rdx
    11fc:	89 ef                	mov    %ebp,%edi
    11fe:	e8 8f ff ff ff       	call   1192 <sumstore>
    1203:	4c 8b 04 24          	mov    (%rsp),%r8
    1207:	48 89 d9             	mov    %rbx,%rcx
    120a:	4c 89 e2             	mov    %r12,%rdx
    120d:	48 8d 35 f0 0d 00 00 	lea    0xdf0(%rip),%rsi        # 2004 <_IO_stdin_used+0x4>
    1214:	bf 02 00 00 00       	mov    $0x2,%edi
    1219:	b8 00 00 00 00       	mov    $0x0,%eax
    121e:	e8 6d fe ff ff       	call   1090 <__printf_chk@plt>
    1223:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
    1228:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    122f:	00 00 
    1231:	75 0e                	jne    1241 <main+0x97>
    1233:	b8 00 00 00 00       	mov    $0x0,%eax
    1238:	48 83 c4 10          	add    $0x10,%rsp
    123c:	5b                   	pop    %rbx
    123d:	5d                   	pop    %rbp
    123e:	41 5c                	pop    %r12
    1240:	c3                   	ret
    1241:	e8 2a fe ff ff       	call   1070 <__stack_chk_fail@plt>

Disassembly of section .fini:

0000000000001248 <_fini>:
    1248:	f3 0f 1e fa          	endbr64
    124c:	48 83 ec 08          	sub    $0x8,%rsp
    1250:	48 83 c4 08          	add    $0x8,%rsp
    1254:	c3                   	ret
