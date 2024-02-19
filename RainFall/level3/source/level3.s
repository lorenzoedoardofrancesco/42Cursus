    ;-- v:
    0x080484a4      55             push ebp
    0x080484a5      89e5           mov ebp, esp
    0x080484a7      81ec18020000   sub esp, 0x218
    0x080484ad      a160980408     mov eax, dword [obj.stdin]  ; obj.stdin__GLIBC_2.0
                                                                ; [0x8049860:4]=0
    0x080484b2      89442408       mov dword [esp + 8], eax
    0x080484b6      c74424040002.  mov dword [esp + 4], 0x200  ; [0x200:4]=-1 ; 512
    0x080484be      8d85f8fdffff   lea eax, [ebp - 0x208]
    0x080484c4      890424         mov dword [esp], eax
    0x080484c7      e8d4feffff     call sym.imp.fgets
    0x080484cc      8d85f8fdffff   lea eax, [ebp - 0x208]
    0x080484d2      890424         mov dword [esp], eax
    0x080484d5      e8b6feffff     call sym.imp.printf
    0x080484da      a18c980408     mov eax, dword [obj.m]      ; [0x804988c:4]=0
    0x080484df      83f840         cmp eax, 0x40               ; 64
┌─< 0x080484e2      7534           jne 0x8048518
│   0x080484e4      a180980408     mov eax, dword [obj.stdout] ; obj.stdout__GLIBC_2.0
│                                                              ; [0x8049880:4]=0
│   0x080484e9      89c2           mov edx, eax
│   0x080484eb      b800860408     mov eax, str.Wait_what___n  ; 0x8048600 ; "Wait what?!\n"
│   0x080484f0      8954240c       mov dword [esp + 0xc], edx
│   0x080484f4      c74424080c00.  mov dword [esp + 8], 0xc    ; [0xc:4]=-1 ; 12
│   0x080484fc      c74424040100.  mov dword [esp + 4], 1
│   0x08048504      890424         mov dword [esp], eax
│   0x08048507      e8a4feffff     call sym.imp.fwrite
│   0x0804850c      c704240d8604.  mov dword [esp], str._bin_sh ; [0x804860d:4]=0x6e69622f ; "/bin/sh"
│   0x08048513      e8a8feffff     call sym.imp.system
└─> 0x08048518      c9             leave
    0x08048519      c3             ret
    ;-- main:
    0x0804851a      55             push ebp
    0x0804851b      89e5           mov ebp, esp
    0x0804851d      83e4f0         and esp, 0xfffffff0
    0x08048520      e87fffffff     call sym.v
    0x08048525      c9             leave
    0x08048526      c3             ret