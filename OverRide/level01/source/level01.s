verify_user_name();
0x08048464      push    ebp
0x08048465      mov     ebp, esp
0x08048467      push    edi
0x08048468      push    esi
0x08048469      sub     esp, 0x10
0x0804846c      mov     dword [esp], str.verifying_username.... ; 0x8048690
0x08048473      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x08048478      mov     edx, a_user_name ; 0x804a040
0x0804847d      mov     eax, str.dat_wil ; 0x80486a8
0x08048482      mov     ecx, 7
0x08048487      mov     esi, edx
0x08048489      mov     edi, eax
0x0804848b      repe    cmpsb byte [esi], byte ptr es:[edi]
0x0804848d      seta    dl
0x08048490      setb    al
0x08048493      mov     ecx, edx
0x08048495      sub     cl, al
0x08048497      mov     eax, ecx
0x08048499      movsx   eax, al
0x0804849c      add     esp, 0x10
0x0804849f      pop     esi
0x080484a0      pop     edi
0x080484a1      pop     ebp
0x080484a2      ret

verify_user_pass(int32_t arg_4h);
; arg int32_t arg_4h @ stack + 0x4
0x080484a3      push    ebp
0x080484a4      mov     ebp, esp
0x080484a6      push    edi
0x080484a7      push    esi
0x080484a8      mov     eax, dword [arg_4h]
0x080484ab      mov     edx, eax
0x080484ad      mov     eax, str.admin ; 0x80486b0
0x080484b2      mov     ecx, 5
0x080484b7      mov     esi, edx
0x080484b9      mov     edi, eax
0x080484bb      repe    cmpsb byte [esi], byte ptr es:[edi]
0x080484bd      seta    dl
0x080484c0      setb    al
0x080484c3      mov     ecx, edx
0x080484c5      sub     cl, al
0x080484c7      mov     eax, ecx
0x080484c9      movsx   eax, al
0x080484cc      pop     esi
0x080484cd      pop     edi
0x080484ce      pop     ebp
0x080484cf      ret

int main(int argc, char **argv, char **envp);
; var int32_t var_68h @ stack - 0x68
; var int32_t var_64h @ stack - 0x64
; var int32_t var_50h @ stack - 0x50
; var int32_t var_10h @ stack - 0x10
; var int32_t var_ch @ stack - 0xc
0x080484d0      push    ebp
0x080484d1      mov     ebp, esp
0x080484d3      push    edi
0x080484d4      push    ebx
0x080484d5      and     esp, 0xfffffff0
0x080484d8      sub     esp, 0x60
0x080484db      lea     ebx, [var_50h]
0x080484df      mov     eax, 0
0x080484e4      mov     edx, 0x10  ; 16
0x080484e9      mov     edi, ebx
0x080484eb      mov     ecx, edx
0x080484ed      rep     stosd dword es:[edi], eax
0x080484ef      mov     dword [var_10h], 0
0x080484f7      mov     dword [esp], str.ADMIN_LOGIN_PROMPT ; 0x80486b8
0x080484fe      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x08048503      mov     eax, str.Enter_Username: ; 0x80486df
0x08048508      mov     dword [esp], eax
0x0804850b      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x08048510      mov     eax, dword stdin ; obj.stdin__GLIBC_2.0
                                   ; 0x804a020
0x08048515      mov     dword [var_64h], eax
0x08048519      mov     dword [var_68h], 0x100 ; 256
0x08048521      mov     dword [esp], a_user_name ; 0x804a040
0x08048528      call    fgets      ; sym.imp.fgets ; char *fgets(char *s, int size, FILE *stream)
0x0804852d      call    verify_user_name ; sym.verify_user_name
0x08048532      mov     dword [var_10h], eax
0x08048536      cmp     dword [var_10h], 0
0x0804853b      je      0x8048550
0x0804853d      mov     dword [esp], str.nope__incorrect_username... ; 0x80486f0
0x08048544      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x08048549      mov     eax, 1
0x0804854e      jmp     0x80485af
0x08048550      mov     dword [esp], str.Enter_Password: ; 0x804870d
0x08048557      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x0804855c      mov     eax, dword stdin ; obj.stdin__GLIBC_2.0
                                   ; 0x804a020
0x08048561      mov     dword [var_64h], eax
0x08048565      mov     dword [var_68h], 0x64 ; 'd' ; 100
0x0804856d      lea     eax, [var_50h]
0x08048571      mov     dword [esp], eax
0x08048574      call    fgets      ; sym.imp.fgets ; char *fgets(char *s, int size, FILE *stream)
0x08048579      lea     eax, [var_50h]
0x0804857d      mov     dword [esp], eax
0x08048580      call    verify_user_pass ; sym.verify_user_pass
0x08048585      mov     dword [var_10h], eax
0x08048589      cmp     dword [var_10h], 0
0x0804858e      je      0x8048597
0x08048590      cmp     dword [var_10h], 0
0x08048595      je      0x80485aa
0x08048597      mov     dword [esp], str.nope__incorrect_password... ; 0x804871e
0x0804859e      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080485a3      mov     eax, 1
0x080485a8      jmp     0x80485af
0x080485aa      mov     eax, 0
0x080485af      lea     esp, [var_ch]
0x080485b2      pop     ebx
0x080485b3      pop     edi
0x080485b4      pop     ebp
0x080485b5      ret
0x080485b6      nop
0x080485b7      nop
0x080485b8      nop
0x080485b9      nop
0x080485ba      nop
0x080485bb      nop
0x080485bc      nop
0x080485bd      nop
0x080485be      nop
0x080485bf      nop