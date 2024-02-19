int main(int argc, char **argv, char **envp);
; var const void *s2 @ stack - 0x40
; var size_t n @ stack - 0x3c
; var void *s1 @ stack - 0x30
; var unsigned long var_8h @ stack - 0x8
; arg char **envp @ stack + 0x8
; arg int32_t arg_ch @ stack + 0xc
0x08048424      push    ebp
0x08048425      mov     ebp, esp
0x08048427      and     esp, 0xfffffff0
0x0804842a      sub     esp, 0x40
0x0804842d      mov     eax, dword [envp]
0x08048430      add     eax, 4
0x08048433      mov     eax, dword [eax]
0x08048435      mov     dword [esp], eax ; const char *str
0x08048438      call    atoi       ; sym.imp.atoi ; int atoi(const char *str)
0x0804843d      mov     dword [var_8h], eax
0x08048441      cmp     dword [var_8h], 9
0x08048446      jle     0x804844f
0x08048448      mov     eax, 1
0x0804844d      jmp     0x80484a3
0x0804844f      mov     eax, dword [var_8h]
0x08048453      lea     ecx, [eax*4]
0x0804845a      mov     eax, dword [envp]
0x0804845d      add     eax, 8
0x08048460      mov     eax, dword [eax]
0x08048462      mov     edx, eax
0x08048464      lea     eax, [s1]
0x08048468      mov     dword [n], ecx ; size_t n
0x0804846c      mov     dword [s2], edx ; const void *s2
0x08048470      mov     dword [esp], eax ; void *s1
0x08048473      call    memcpy     ; sym.imp.memcpy ; void *memcpy(void *s1, const void *s2, size_t n)
0x08048478      cmp     dword [var_8h], 0x574f4c46
0x08048480      jne     0x804849e
0x08048482      mov     dword [arg_ch], 0
0x0804848a      mov     dword [s2], data.08048580 ; 0x8048580
0x08048492      mov     dword [esp], str.bin_sh ; 0x8048583
0x08048499      call    execl      ; sym.imp.execl
0x0804849e      mov     eax, 0
0x080484a3      leave
0x080484a4      ret