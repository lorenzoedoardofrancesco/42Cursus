int main(int argc, char **argv, char **envp);
; var int32_t var_20h @ stack - 0x20
; var int32_t var_8h @ stack - 0x8
0x08048494      push    ebp
0x08048495      mov     ebp, esp
0x08048497      and     esp, 0xfffffff0
0x0804849a      sub     esp, 0x20
0x0804849d      mov     dword [esp], str. ; 0x80485f0 ; const char *s
0x080484a4      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080484a9      mov     dword [esp], str.Level00 ; 0x8048614 ; const char *s
0x080484b0      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080484b5      mov     dword [esp], str. ; 0x80485f0 ; const char *s
0x080484bc      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080484c1      mov     eax, str.Password: ; 0x804862c
0x080484c6      mov     dword [esp], eax ; const char *format
0x080484c9      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x080484ce      mov     eax, data.08048636 ; 0x8048636
0x080484d3      lea     edx, [var_8h]
0x080484d7      mov     dword [var_20h], edx
0x080484db      mov     dword [esp], eax ; const char *format
0x080484de      call    __isoc99_scanf ; sym.imp.__isoc99_scanf ; int scanf(const char *format)
0x080484e3      mov     eax, dword [var_8h]
0x080484e7      cmp     eax, 0x149c
0x080484ec      jne     0x804850d
0x080484ee      mov     dword [esp], str.Authenticated ; 0x8048639 ; const char *s
0x080484f5      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080484fa      mov     dword [esp], str.bin_sh ; 0x8048649 ; const char *string
0x08048501      call    system     ; sym.imp.system ; int system(const char *string)
0x08048506      mov     eax, 0
0x0804850b      jmp     0x804851e
0x0804850d      mov     dword [esp], str.Invalid_Password ; 0x8048651 ; const char *s
0x08048514      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x08048519      mov     eax, 1
0x0804851e      leave
0x0804851f      ret