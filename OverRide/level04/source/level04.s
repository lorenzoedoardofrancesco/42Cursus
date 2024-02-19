int main(int argc, char **argv, char **envp);
; var int32_t var_b8h @ stack - 0xb8
; var int32_t var_b4h @ stack - 0xb4
; var int32_t var_b0h @ stack - 0xb0
; var int32_t var_a8h @ stack - 0xa8
; var int32_t var_a0h @ stack - 0xa0
; var int32_t var_9ch @ stack - 0x9c
; var int32_t var_90h @ stack - 0x90
; var int32_t var_1ch @ stack - 0x1c
; var int32_t var_18h @ stack - 0x18
; var int32_t var_14h @ stack - 0x14
; var int32_t var_10h @ stack - 0x10
; var int32_t var_ch @ stack - 0xc
0x080486c8      push    ebp
0x080486c9      mov     ebp, esp
0x080486cb      push    edi
0x080486cc      push    ebx
0x080486cd      and     esp, 0xfffffff0
0x080486d0      sub     esp, 0xb0
0x080486d6      call    fork       ; sym.imp.fork
0x080486db      mov     dword [var_10h], eax
0x080486e2      lea     ebx, [var_9ch]
0x080486e6      mov     eax, 0
0x080486eb      mov     edx, 0x20  ; 32
0x080486f0      mov     edi, ebx
0x080486f2      mov     ecx, edx
0x080486f4      rep     stosd dword es:[edi], eax
0x080486f6      mov     dword [var_14h], 0
0x08048701      mov     dword [var_a0h], 0
0x08048709      cmp     dword [var_10h], 0
0x08048711      jne     0x8048769
0x08048713      mov     dword [var_a8h], 1
0x0804871b      mov     dword [esp], 1
0x08048722      call    prctl      ; sym.imp.prctl ; int prctl(int option, unsigned long v2, unsigned long v3, unsigned long v4, unsigned long v5)
0x08048727      mov     dword [var_b0h], 0
0x0804872f      mov     dword [var_b4h], 0
0x08048737      mov     dword [var_b8h], 0
0x0804873f      mov     dword [esp], 0
0x08048746      call    ptrace     ; sym.imp.ptrace ; long ptrace(void *ptrace_request, pid_t pid, void *addr, void *data)
0x0804874b      mov     dword [esp], str.Give_me_some_shellcode__k ; 0x8048903
0x08048752      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x08048757      lea     eax, [var_9ch]
0x0804875b      mov     dword [esp], eax
0x0804875e      call    gets       ; sym.imp.gets ; char *gets(char *s)
0x08048763      jmp     0x804881a
0x08048768      nop
0x08048769      lea     eax, [var_a0h]
0x0804876d      mov     dword [esp], eax
0x08048770      call    wait       ; sym.imp.wait ; pid_t wait(int *wstatus)
0x08048775      mov     eax, dword [var_a0h]
0x08048779      mov     dword [var_1ch], eax
0x08048780      mov     eax, dword [var_1ch]
0x08048787      and     eax, 0x7f  ; 127
0x0804878a      test    eax, eax
0x0804878c      je      0x80487ac
0x0804878e      mov     eax, dword [var_90h]
0x08048792      mov     dword [var_18h], eax
0x08048799      mov     eax, dword [var_18h]
0x080487a0      and     eax, 0x7f  ; 127
0x080487a3      add     eax, 1
0x080487a6      sar     al, 1
0x080487a8      test    al, al
0x080487aa      jle     0x80487ba
0x080487ac      mov     dword [esp], str.child_is_exiting... ; 0x804891d
0x080487b3      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080487b8      jmp     0x804881a
0x080487ba      mov     dword [var_b0h], 0
0x080487c2      mov     dword [var_b4h], 0x2c ; ',' ; 44
0x080487ca      mov     eax, dword [var_10h]
0x080487d1      mov     dword [var_b8h], eax
0x080487d5      mov     dword [esp], 3
0x080487dc      call    ptrace     ; sym.imp.ptrace ; long ptrace(void *ptrace_request, pid_t pid, void *addr, void *data)
0x080487e1      mov     dword [var_14h], eax
0x080487e8      cmp     dword [var_14h], 0xb
0x080487f0      jne     0x8048768
0x080487f6      mov     dword [esp], str.no_exec___for_you ; 0x8048931
0x080487fd      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x08048802      mov     dword [var_b8h], 9
0x0804880a      mov     eax, dword [var_10h]
0x08048811      mov     dword [esp], eax
0x08048814      call    kill       ; sym.imp.kill ; int kill(pid_t pid, int sig)
0x08048819      nop
0x0804881a      mov     eax, 0
0x0804881f      lea     esp, [var_ch]
0x08048822      pop     ebx
0x08048823      pop     edi
0x08048824      pop     ebp
0x08048825      ret
0x08048826      nop
0x08048827      nop
0x08048828      nop
0x08048829      nop
0x0804882a      nop
0x0804882b      nop
0x0804882c      nop
0x0804882d      nop
0x0804882e      nop
0x0804882f      nop