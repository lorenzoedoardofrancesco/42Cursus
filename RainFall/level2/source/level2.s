    ;-- p:
    0x080484d4      55             push ebp
    0x080484d5      89e5           mov ebp, esp
    0x080484d7      83ec68         sub esp, 0x68
    0x080484da      a160980408     mov eax, dword [obj.stdout] ; obj.stdout__GLIBC_2.0
                                                                ; [0x8049860:4]=0
    0x080484df      890424         mov dword [esp], eax
    0x080484e2      e8c9feffff     call sym.imp.fflush
    0x080484e7      8d45b4         lea eax, [ebp - 0x4c]
    0x080484ea      890424         mov dword [esp], eax
    0x080484ed      e8cefeffff     call sym.imp.gets
    0x080484f2      8b4504         mov eax, dword [ebp + 4]
    0x080484f5      8945f4         mov dword [ebp - 0xc], eax
    0x080484f8      8b45f4         mov eax, dword [ebp - 0xc]
    0x080484fb      25000000b0     and eax, 0xb0000000
    0x08048500      3d000000b0     cmp eax, 0xb0000000
┌─< 0x08048505      7520           jne 0x8048527
│   0x08048507      b820860408     mov eax, str.__p__n         ; 0x8048620 ; "(%p)\n"
│   0x0804850c      8b55f4         mov edx, dword [ebp - 0xc]
│   0x0804850f      89542404       mov dword [esp + 4], edx
│   0x08048513      890424         mov dword [esp], eax
│   0x08048516      e885feffff     call sym.imp.printf
│   0x0804851b      c70424010000.  mov dword [esp], 1
│   0x08048522      e8a9feffff     call sym.imp._exit
└─> 0x08048527      8d45b4         lea eax, [ebp - 0x4c]
    0x0804852a      890424         mov dword [esp], eax
    0x0804852d      e8befeffff     call sym.imp.puts
    0x08048532      8d45b4         lea eax, [ebp - 0x4c]
    0x08048535      890424         mov dword [esp], eax
    0x08048538      e8a3feffff     call sym.imp.strdup
    0x0804853d      c9             leave
    0x0804853e      c3             ret
    ;-- main:
    0x0804853f      55             push ebp
    0x08048540      89e5           mov ebp, esp
    0x08048542      83e4f0         and esp, 0xfffffff0
    0x08048545      e88affffff     call sym.p
    0x0804854a      c9             leave
    0x0804854b      c3             ret