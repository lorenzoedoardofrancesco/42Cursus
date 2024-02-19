;-- n:
0x08048454      55             push ebp
0x08048455      89e5           mov ebp, esp
0x08048457      83ec18         sub esp, 0x18
0x0804845a      c70424b08504.  mov dword [esp], str._bin_cat__home_user_level7_.pass ; [0x80485b0:4]=0x6e69622f ; "/bin/cat /home/user/level7/.pass"
0x08048461      e80affffff     call sym.imp.system
0x08048466      c9             leave
0x08048467      c3             ret
;-- m:
0x08048468      55             push ebp
0x08048469      89e5           mov ebp, esp
0x0804846b      83ec18         sub esp, 0x18
0x0804846e      c70424d18504.  mov dword [esp], str.Nope   ; [0x80485d1:4]=0x65706f4e ; "Nope"
0x08048475      e8e6feffff     call sym.imp.puts
0x0804847a      c9             leave
0x0804847b      c3             ret
;-- main:
0x0804847c      55             push ebp
0x0804847d      89e5           mov ebp, esp
0x0804847f      83e4f0         and esp, 0xfffffff0
0x08048482      83ec20         sub esp, 0x20
0x08048485      c70424400000.  mov dword [esp], 0x40       ; '@'
                                                            ; [0x40:4]=-1 ; 64
0x0804848c      e8bffeffff     call sym.imp.malloc
0x08048491      8944241c       mov dword [esp + 0x1c], eax
0x08048495      c70424040000.  mov dword [esp], 4
0x0804849c      e8affeffff     call sym.imp.malloc
0x080484a1      89442418       mov dword [esp + 0x18], eax
0x080484a5      ba68840408     mov edx, sym.m              ; 0x8048468 ;
0x080484ae      8910           mov dword [eax], edx
0x080484b0      8b450c         mov eax, dword [ebp + 0xc]
0x080484b3      83c004         add eax, 4
0x080484b6      8b00           mov eax, dword [eax]
0x080484b8      89c2           mov edx, eax
0x080484ba      8b44241c       mov eax, dword [esp + 0x1c]
0x080484be      89542404       mov dword [esp + 4], edx
0x080484c2      890424         mov dword [esp], eax
0x080484c5      e876feffff     call sym.imp.strcpy
0x080484ca      8b442418       mov eax, dword [esp + 0x18]
0x080484ce      8b00           mov eax, dword [eax]
0x080484d0      ffd0           call eax
0x080484d2      c9             leave
0x080484d3      c3             ret