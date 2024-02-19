    ;-- main:
    0x08048ec0      55             push ebp
    0x08048ec1      89e5           mov ebp, esp
    0x08048ec3      83e4f0         and esp, 0xfffffff0
    0x08048ec6      83ec20         sub esp, 0x20
    0x08048ec9      8b450c         mov eax, dword [ebp + 0xc]
    0x08048ecc      83c004         add eax, 4
    0x08048ecf      8b00           mov eax, dword [eax]
    0x08048ed1      890424         mov dword [esp], eax
    0x08048ed4      e837080000     call sym.atoi
    0x08048ed9      3da7010000     cmp eax, 0x1a7                ; compares eax(atoi(av[1])) to 423
┌─< 0x08048ede      7578           jne 0x8048f58                 ; if false, jump
│   0x08048ee0      c7042448530c.  mov dword [esp], str._bin_sh  ; [0x80c5348:4]=0x6e69622f ; "/bin/sh"
│   0x08048ee7      e8047d0000     call sym.__strdup
│   0x08048eec      89442410       mov dword [esp + 0x10], eax
│   0x08048ef0      c74424140000.  mov dword [esp + 0x14], 0
│   0x08048ef8      e883b70000     call sym.getegid
│   0x08048efd      8944241c       mov dword [esp + 0x1c], eax
│   0x08048f01      e86ab70000     call sym.geteuid
│   0x08048f06      89442418       mov dword [esp + 0x18], eax
│   0x08048f0a      8b44241c       mov eax, dword [esp + 0x1c]
│   0x08048f0e      89442408       mov dword [esp + 8], eax
│   0x08048f12      8b44241c       mov eax, dword [esp + 0x1c]
│   0x08048f16      89442404       mov dword [esp + 4], eax
│   0x08048f1a      8b44241c       mov eax, dword [esp + 0x1c]
│   0x08048f1e      890424         mov dword [esp], eax
│   0x08048f21      e8dab70000     call sym.__setresgid
│   0x08048f26      8b442418       mov eax, dword [esp + 0x18]
│   0x08048f2a      89442408       mov dword [esp + 8], eax
│   0x08048f2e      8b442418       mov eax, dword [esp + 0x18]
│   0x08048f32      89442404       mov dword [esp + 4], eax
│   0x08048f36      8b442418       mov eax, dword [esp + 0x18]
│   0x08048f3a      890424         mov dword [esp], eax
│   0x08048f3d      e84eb70000     call sym.setresuid
│   0x08048f42      8d442410       lea eax, [esp + 0x10]
│   0x08048f46      89442404       mov dword [esp + 4], eax
│   0x08048f4a      c7042448530c.  mov dword [esp], str._bin_sh ; [0x80c5348:4]=0x6e69622f ; "/bin/sh"
│   0x08048f51      e8eab60000     call sym.execv
┌──< 0x08048f56      eb28           jmp 0x8048f80
│└─> 0x08048f58      a170e10e08     mov eax, dword [obj.stderr] ; obj._IO_stderr
│                                                               ; [0x80ee170:4]=0x80ee7a0 obj._IO_2_1_stderr_
│    0x08048f5d      89c2           mov edx, eax
│    0x08048f5f      b850530c08     mov eax, str.No___n         ; 0x80c5350 ; "No !\n"
│    0x08048f64      8954240c       mov dword [esp + 0xc], edx
│    0x08048f68      c74424080500.  mov dword [esp + 8], 5
│    0x08048f70      c74424040100.  mov dword [esp + 4], 1
│    0x08048f78      890424         mov dword [esp], eax
│    0x08048f7b      e8b0120000     call sym._IO_fwrite
└──> 0x08048f80      b800000000     mov eax, 0
    0x08048f85      c9             leave
    0x08048f86      c3             ret