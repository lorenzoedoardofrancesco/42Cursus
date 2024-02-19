;-- o:
0x080484a4      55             push ebp
0x080484a5      89e5           mov ebp, esp
0x080484a7      83ec18         sub esp, 0x18
0x080484aa      c70424f08504.  mov dword [esp], str._bin_sh ; [0x80485f0:4]=0x6e69622f ; "/bin/sh"
0x080484b1      e8fafeffff     call sym.imp.system
0x080484b6      c70424010000.  mov dword [esp], 1
0x080484bd      e8cefeffff     call sym.imp._exit
;-- n:
0x080484c2      55             push ebp
0x080484c3      89e5           mov ebp, esp
0x080484c5      81ec18020000   sub esp, 0x218
0x080484cb      a148980408     mov eax, dword [obj.stdin]  ; loc.__bss_start
                                                            ; [0x8049848:4]=0
0x080484d0      89442408       mov dword [esp + 8], eax
0x080484d4      c74424040002.  mov dword [esp + 4], 0x200  ; [0x200:4]=-1 ; 512
0x080484dc      8d85f8fdffff   lea eax, [ebp - 0x208]
0x080484e2      890424         mov dword [esp], eax
0x080484e5      e8b6feffff     call sym.imp.fgets
0x080484ea      8d85f8fdffff   lea eax, [ebp - 0x208]
0x080484f0      890424         mov dword [esp], eax
0x080484f3      e888feffff     call sym.imp.printf
0x080484f8      c70424010000.  mov dword [esp], 1
0x080484ff      e8ccfeffff     call sym.imp.exit
;-- main:
0x08048504      55             push ebp
0x08048505      89e5           mov ebp, esp
0x08048507      83e4f0         and esp, 0xfffffff0
0x0804850a      e8b3ffffff     call sym.n
0x0804850f      c9             leave
0x08048510      c3             ret

;-- _GLOBAL_OFFSET_TABLE_:
0x08049818      dec     esp        ; [22] -rw- section size 40 named .got.plt
0x08049819      xchg    edi, eax
0x0804981a      add     al, 8
0x0804981c      add     byte [eax], al
0x0804981e      add     byte [eax], al
0x08049820      add     byte [eax], al
0x08049822      add     byte [eax], al
;-- printf:
0x08049824      .dword 0x08048386  ; RELOC 32 printf
;-- _exit:
0x08049828      .dword 0x08048396  ; RELOC 32 _exit
;-- fgets:
0x0804982c      .dword 0x080483a6  ; RELOC 32 fgets
;-- system:
0x08049830      .dword 0x080483b6  ; RELOC 32 system
;-- __gmon_start__:
0x08049834      .dword 0x080483c6  ; RELOC 32 __gmon_start__
;-- exit:
0x08049838      .dword 0x080483d6  ; RELOC 32 exit
;-- __libc_start_main:
0x0804983c      .dword 0x080483e6  ; RELOC 32 __libc_start_main