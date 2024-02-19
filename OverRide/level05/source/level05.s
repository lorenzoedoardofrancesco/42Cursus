int main(int argc, char **argv, char **envp);
; var int32_t var_98h @ stack - 0x98
; var int32_t var_94h @ stack - 0x94
; var int32_t var_80h @ stack - 0x80
; var int32_t var_74h @ stack - 0x74
; var int32_t var_10h @ stack - 0x10
0x08048444      push    ebp
0x08048445      mov     ebp, esp
0x08048447      push    edi
0x08048448      push    ebx
0x08048449      and     esp, 0xfffffff0
0x0804844c      sub     esp, 0x90
0x08048452      mov     dword [var_10h], 0
0x0804845d      mov     eax, dword stdin ; loc.__bss_start
                                   ; 0x80497f0
0x08048462      mov     dword [var_94h], eax
0x08048466      mov     dword [var_98h], 0x64 ; 'd' ; 100
0x0804846e      lea     eax, [var_74h]
0x08048472      mov     dword [esp], eax
0x08048475      call    fgets      ; sym.imp.fgets ; char *fgets(char *s, int size, FILE *stream)
0x0804847a      mov     dword [var_10h], 0
0x08048485      jmp     0x80484d3
0x08048487      lea     eax, [var_74h]
0x0804848b      add     eax, dword [var_10h]
0x08048492      movzx   eax, byte [eax]
0x08048495      cmp     al, 0x40   ; 64
0x08048497      jle     0x80484cb
0x08048499      lea     eax, [var_74h]
0x0804849d      add     eax, dword [var_10h]
0x080484a4      movzx   eax, byte [eax]
0x080484a7      cmp     al, 0x5a   ; 90
0x080484a9      jg      0x80484cb
0x080484ab      lea     eax, [var_74h]
0x080484af      add     eax, dword [var_10h]
0x080484b6      movzx   eax, byte [eax]
0x080484b9      mov     edx, eax
0x080484bb      xor     edx, 0x20  ; 32
0x080484be      lea     eax, [var_74h]
0x080484c2      add     eax, dword [var_10h]
0x080484c9      mov     byte [eax], dl
0x080484cb      add     dword [var_10h], 1
0x080484d3      mov     ebx, dword [var_10h]
0x080484da      lea     eax, [var_74h]
0x080484de      mov     dword [var_80h], 0xffffffff ; -1
0x080484e6      mov     edx, eax
0x080484e8      mov     eax, 0
0x080484ed      mov     ecx, dword [var_80h]
0x080484f1      mov     edi, edx
0x080484f3      repne   scasb al, byte es:[edi]
0x080484f5      mov     eax, ecx
0x080484f7      not     eax
0x080484f9      sub     eax, 1
0x080484fc      cmp     ebx, eax
0x080484fe      jb      0x8048487
0x08048500      lea     eax, [var_74h]
0x08048504      mov     dword [esp], eax
0x08048507      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x0804850c      mov     dword [esp], 0
0x08048513      call    exit       ; sym.imp.exit ; void exit(int status)
0x08048518      nop
0x08048519      nop
0x0804851a      nop
0x0804851b      nop
0x0804851c      nop
0x0804851d      nop
0x0804851e      nop
0x0804851f      nop