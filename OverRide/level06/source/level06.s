auth(int32_t arg_4h, int32_t arg_8h);
; var int32_t var_28h @ stack - 0x28
; var int32_t var_24h @ stack - 0x24
; var int32_t var_20h @ stack - 0x20
; var int32_t var_18h @ stack - 0x18
; var int32_t var_14h @ stack - 0x14
; var int32_t var_10h @ stack - 0x10
; arg int32_t arg_4h @ stack + 0x4
; arg int32_t arg_8h @ stack + 0x8
0x08048748      push    ebp
0x08048749      mov     ebp, esp
0x0804874b      sub     esp, 0x28
0x0804874e      mov     dword [var_28h], 0x8048a63
0x08048756      mov     eax, dword [arg_4h]
0x08048759      mov     dword [esp], eax
0x0804875c      call    strcspn    ; sym.imp.strcspn ; size_t strcspn(const char *s1, const char *s2)
0x08048761      add     eax, dword [arg_4h]
0x08048764      mov     byte [eax], 0
0x08048767      mov     dword [var_28h], 0x20 ; 32
0x0804876f      mov     eax, dword [arg_4h]
0x08048772      mov     dword [esp], eax
0x08048775      call    strnlen    ; sym.imp.strnlen
0x0804877a      mov     dword [var_10h], eax
0x0804877d      push    eax
0x0804877e      xor     eax, eax
0x08048780      je      0x8048785
0x08048782      add     esp, 4
0x08048785      pop     eax
0x08048786      cmp     dword [var_10h], 5
0x0804878a      jg      0x8048796
0x0804878c      mov     eax, 1
0x08048791      jmp     0x8048877
0x08048796      mov     dword [var_20h], 0
0x0804879e      mov     dword [var_24h], 1
0x080487a6      mov     dword [var_28h], 0
0x080487ae      mov     dword [esp], 0
0x080487b5      call    ptrace     ; sym.imp.ptrace ; long ptrace(void *ptrace_request, pid_t pid, void *addr, void *data)
0x080487ba      cmp     eax, 0xffffffff
0x080487bd      jne     0x80487ed
0x080487bf      mov     dword [esp], str.32m.___________________________. ; 0x8048a68
0x080487c6      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080487cb      mov     dword [esp], str.31m_____TAMPERING_DETECTED ; 0x8048a8c
0x080487d2      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080487d7      mov     dword [esp], str.32m ; 0x8048ab0
0x080487de      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080487e3      mov     eax, 1
0x080487e8      jmp     0x8048877
0x080487ed      mov     eax, dword [arg_4h]
0x080487f0      add     eax, 3
0x080487f3      movzx   eax, byte [eax]
0x080487f6      movsx   eax, al
0x080487f9      xor     eax, 0x1337
0x080487fe      add     eax, 0x5eeded
0x08048803      mov     dword [var_14h], eax
0x08048806      mov     dword [var_18h], 0
0x0804880d      jmp     0x804885b
0x0804880f      mov     eax, dword [var_18h]
0x08048812      add     eax, dword [arg_4h]
0x08048815      movzx   eax, byte [eax]
0x08048818      cmp     al, 0x1f   ; 31
0x0804881a      jg      0x8048823
0x0804881c      mov     eax, 1
0x08048821      jmp     0x8048877
0x08048823      mov     eax, dword [var_18h]
0x08048826      add     eax, dword [arg_4h]
0x08048829      movzx   eax, byte [eax]
0x0804882c      movsx   eax, al
0x0804882f      mov     ecx, eax
0x08048831      xor     ecx, dword [var_14h]
0x08048834      mov     edx, 0x88233b2b
0x08048839      mov     eax, ecx
0x0804883b      mul     edx
0x0804883d      mov     eax, ecx
0x0804883f      sub     eax, edx
0x08048841      shr     eax, 1
0x08048843      add     eax, edx
0x08048845      shr     eax, 0xa
0x08048848      imul    eax, eax, 0x539
0x0804884e      mov     edx, ecx
0x08048850      sub     edx, eax
0x08048852      mov     eax, edx
0x08048854      add     dword [var_14h], eax
0x08048857      add     dword [var_18h], 1
0x0804885b      mov     eax, dword [var_18h]
0x0804885e      cmp     eax, dword [var_10h]
0x08048861      jl      0x804880f
0x08048863      mov     eax, dword [arg_8h]
0x08048866      cmp     eax, dword [var_14h]
0x08048869      je      0x8048872
0x0804886b      mov     eax, 1
0x08048870      jmp     0x8048877
0x08048872      mov     eax, 0
0x08048877      leave
0x08048878      ret

int main(int argc, char **argv, char **envp);
; var int32_t var_50h @ stack - 0x50
; var int32_t var_4ch @ stack - 0x4c
; var int32_t var_48h @ stack - 0x48
; var int32_t var_38h @ stack - 0x38
; var int32_t var_2ch @ stack - 0x2c
; var int32_t var_28h @ stack - 0x28
; var int32_t var_24h @ stack - 0x24
; var int32_t var_8h @ stack - 0x8
; arg char **envp @ stack + 0x8
0x08048879      push    ebp
0x0804887a      mov     ebp, esp
0x0804887c      and     esp, 0xfffffff0
0x0804887f      sub     esp, 0x50
0x08048882      mov     eax, dword [envp]
0x08048885      mov     dword [var_38h], eax
0x08048889      mov     eax, dword gs:[0x14]
0x0804888f      mov     dword [var_8h], eax
0x08048893      xor     eax, eax
0x08048895      push    eax
0x08048896      xor     eax, eax
0x08048898      je      0x804889d
0x0804889a      add     esp, 4
0x0804889d      pop     eax
0x0804889e      mov     dword [esp], str. ; 0x8048ad4
0x080488a5      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080488aa      mov     dword [esp], str.level06 ; 0x8048af8
0x080488b1      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080488b6      mov     dword [esp], str. ; 0x8048ad4
0x080488bd      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080488c2      mov     eax, str.Enter_Login: ; 0x8048b08
0x080488c7      mov     dword [esp], eax
0x080488ca      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x080488cf      mov     eax, dword stdin ; obj.stdin__GLIBC_2.0
                                   ; 0x804a060
0x080488d4      mov     dword [var_4ch], eax
0x080488d8      mov     dword [var_50h], 0x20 ; 32
0x080488e0      lea     eax, [var_28h]
0x080488e4      mov     dword [esp], eax
0x080488e7      call    fgets      ; sym.imp.fgets ; char *fgets(char *s, int size, FILE *stream)
0x080488ec      mov     dword [esp], str. ; 0x8048ad4
0x080488f3      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080488f8      mov     dword [esp], str.NEW_ACCOUNT_DETECTED ; 0x8048b1c
0x080488ff      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x08048904      mov     dword [esp], str. ; 0x8048ad4
0x0804890b      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x08048910      mov     eax, str.Enter_Serial: ; 0x8048b40
0x08048915      mov     dword [esp], eax
0x08048918      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x0804891d      mov     eax, 0x8048a60
0x08048922      lea     edx, [var_2ch]
0x08048926      mov     dword [var_50h], edx
0x0804892a      mov     dword [esp], eax
0x0804892d      call    __isoc99_scanf ; sym.imp.__isoc99_scanf ; int scanf(const char *format)
0x08048932      mov     eax, dword [var_2ch]
0x08048936      mov     dword [var_50h], eax
0x0804893a      lea     eax, [var_28h]
0x0804893e      mov     dword [esp], eax
0x08048941      call    auth       ; sym.auth
0x08048946      test    eax, eax
0x08048948      jne     0x8048969
0x0804894a      mov     dword [esp], str.Authenticated ; 0x8048b52
0x08048951      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x08048956      mov     dword [esp], str.bin_sh ; 0x8048b61
0x0804895d      call    system     ; sym.imp.system ; int system(const char *string)
0x08048962      mov     eax, 0
0x08048967      jmp     0x804896e
0x08048969      mov     eax, 1
0x0804896e      mov     edx, dword [var_8h]
0x08048972      xor     edx, dword gs:[0x14]
0x08048979      je      0x8048980
0x0804897b      call    __stack_chk_fail ; sym.imp.__stack_chk_fail ; void __stack_chk_fail(void)
0x08048980      leave
0x08048981      ret
0x08048982      nop
0x08048983      nop
0x08048984      nop
0x08048985      nop
0x08048986      nop
0x08048987      nop
0x08048988      nop
0x08048989      nop
0x0804898a      nop
0x0804898b      nop
0x0804898c      nop
0x0804898d      nop
0x0804898e      nop
0x0804898f      nop