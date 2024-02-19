    ;-- p:
    0x08048444      55             push ebp
    0x08048445      89e5           mov ebp, esp
    0x08048447      83ec18         sub esp, 0x18
    0x0804844a      8b4508         mov eax, dword [ebp + 8]
    0x0804844d      890424         mov dword [esp], eax
    0x08048450      e8ebfeffff     call sym.imp.printf
    0x08048455      c9             leave
    0x08048456      c3             ret
    ;-- n:
    0x08048457      55             push ebp
    0x08048458      89e5           mov ebp, esp
    0x0804845a      81ec18020000   sub esp, 0x218
    0x08048460      a104980408     mov eax, dword [obj.stdin]  ; loc.__bss_start
                                                                ; [0x8049804:4]=0
    0x08048465      89442408       mov dword [esp + 8], eax
    0x08048469      c74424040002.  mov dword [esp + 4], 0x200  ; [0x200:4]=-1 ; 512
    0x08048471      8d85f8fdffff   lea eax, [ebp - 0x208]
    0x08048477      890424         mov dword [esp], eax
    0x0804847a      e8d1feffff     call sym.imp.fgets
    0x0804847f      8d85f8fdffff   lea eax, [ebp - 0x208]
    0x08048485      890424         mov dword [esp], eax
    0x08048488      e8b7ffffff     call sym.p
    0x0804848d      a110980408     mov eax, dword [obj.m]      ; [0x8049810:4]=0
    0x08048492      3d44550201     cmp eax, 0x1025544
┌─< 0x08048497      750c           jne 0x80484a5
│   0x08048499      c70424908504.  mov dword [esp], str._bin_cat__home_user_level5_.pass ; [0x8048590:4]=0x6e69622f ; "/bin/cat /home/user/level5/.pass"
│   0x080484a0      e8bbfeffff     call sym.imp.system
└─> 0x080484a5      c9             leave
    0x080484a6      c3             ret
    ;-- main:
    0x080484a7      55             push ebp
    0x080484a8      89e5           mov ebp, esp
    0x080484aa      83e4f0         and esp, 0xfffffff0
    0x080484ad      e8a5ffffff     call sym.n
    0x080484b2      c9             leave
    0x080484b3      c3             ret

    ;-- m:                                               XREF[2]:     Entry Point(*), n:0804848d(R)  
    0x08049810      int              00000000h