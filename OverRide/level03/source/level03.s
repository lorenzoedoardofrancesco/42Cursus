decrypt(int32_t arg_4h);
; var int32_t var_30h @ stack - 0x30
; var int32_t var_2ch @ stack - 0x2c
; var int32_t var_28h @ stack - 0x28
; var int32_t var_21h @ stack - 0x21
; var int32_t var_1dh @ stack - 0x1d
; var int32_t var_19h @ stack - 0x19
; var int32_t var_15h @ stack - 0x15
; var int32_t var_11h @ stack - 0x11
; var int32_t var_10h @ stack - 0x10
; arg int32_t arg_4h @ stack + 0x4
0x08048660      push    ebp
0x08048661      mov     ebp, esp
0x08048663      push    edi
0x08048664      push    esi
0x08048665      sub     esp, 0x40
0x08048668      mov     eax, dword gs:[0x14]
0x0804866e      mov     dword [var_10h], eax
0x08048671      xor     eax, eax
0x08048673      mov     dword [var_21h], 0x757c7d51 ; 'Q}|u'
0x0804867a      mov     dword [var_1dh], 0x67667360 ; '`sfg'
0x08048681      mov     dword [var_19h], 0x7b66737e ; '~sf{'
0x08048688      mov     dword [var_15h], 0x33617c7d ; '}|a3'
0x0804868f      mov     byte [var_11h], 0
0x08048693      push    eax
0x08048694      xor     eax, eax
0x08048696      je      0x804869b
0x08048698      add     esp, 4
0x0804869b      pop     eax
0x0804869c      lea     eax, [var_21h]
0x0804869f      mov     dword [var_30h], 0xffffffff ; -1
0x080486a6      mov     edx, eax
0x080486a8      mov     eax, 0
0x080486ad      mov     ecx, dword [var_30h]
0x080486b0      mov     edi, edx
0x080486b2      repne   scasb al, byte es:[edi]
0x080486b4      mov     eax, ecx
0x080486b6      not     eax
0x080486b8      sub     eax, 1
0x080486bb      mov     dword [var_28h], eax
0x080486be      mov     dword [var_2ch], 0
0x080486c5      jmp     0x80486e5
0x080486c7      lea     eax, [var_21h]
0x080486ca      add     eax, dword [var_2ch]
0x080486cd      movzx   eax, byte [eax]
0x080486d0      mov     edx, eax
0x080486d2      mov     eax, dword [arg_4h]
0x080486d5      xor     eax, edx
0x080486d7      mov     edx, eax
0x080486d9      lea     eax, [var_21h]
0x080486dc      add     eax, dword [var_2ch]
0x080486df      mov     byte [eax], dl
0x080486e1      add     dword [var_2ch], 1
0x080486e5      mov     eax, dword [var_2ch]
0x080486e8      cmp     eax, dword [var_28h]
0x080486eb      jb      0x80486c7
0x080486ed      lea     eax, [var_21h]
0x080486f0      mov     edx, eax
0x080486f2      mov     eax, str.Congratulations ; 0x80489c3
0x080486f7      mov     ecx, 0x11  ; 17
0x080486fc      mov     esi, edx
0x080486fe      mov     edi, eax
0x08048700      repe    cmpsb byte [esi], byte ptr es:[edi]
0x08048702      seta    dl
0x08048705      setb    al
0x08048708      mov     ecx, edx
0x0804870a      sub     cl, al
0x0804870c      mov     eax, ecx
0x0804870e      movsx   eax, al
0x08048711      test    eax, eax
0x08048713      jne     0x8048723
0x08048715      mov     dword [esp], str.bin_sh ; 0x80489d4
0x0804871c      call    system     ; sym.imp.system ; int system(const char *string)
0x08048721      jmp     0x804872f
0x08048723      mov     dword [esp], str.Invalid_Password ; 0x80489dc
0x0804872a      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x0804872f      mov     esi, dword [var_10h]
0x08048732      xor     esi, dword gs:[0x14]
0x08048739      je      0x8048740
0x0804873b      call    __stack_chk_fail ; sym.imp.__stack_chk_fail ; void __stack_chk_fail(void)
0x08048740      add     esp, 0x40
0x08048743      pop     esi
0x08048744      pop     edi
0x08048745      pop     ebp
0x08048746      ret

test(int32_t arg_4h, int32_t arg_8h);
; var int32_t var_10h @ stack - 0x10
; arg int32_t arg_4h @ stack + 0x4
; arg int32_t arg_8h @ stack + 0x8
0x08048747      push    ebp
0x08048748      mov     ebp, esp
0x0804874a      sub     esp, 0x28
0x0804874d      mov     eax, dword [arg_4h]
0x08048750      mov     edx, dword [arg_8h]
0x08048753      mov     ecx, edx
0x08048755      sub     ecx, eax
0x08048757      mov     eax, ecx
0x08048759      mov     dword [var_10h], eax
0x0804875c      cmp     dword [var_10h], 0x15
0x08048760      ja      0x804884a
0x08048766      mov     eax, dword [var_10h]
0x08048769      shl     eax, 2
0x0804876c      add     eax, 0x80489f0
0x08048771      mov     eax, dword [eax]
0x08048773      jmp     eax
0x08048775      mov     eax, dword [ebp - 0xc]
0x08048778      mov     dword [esp], eax
0x0804877b      call    decrypt    ; sym.decrypt
0x08048780      jmp     0x8048858  ; sym.test+0x111
0x08048785      mov     eax, dword [ebp - 0xc]
0x08048788      mov     dword [esp], eax
0x0804878b      call    decrypt    ; sym.decrypt
0x08048790      jmp     0x8048858  ; sym.test+0x111
0x08048795      mov     eax, dword [ebp - 0xc]
0x08048798      mov     dword [esp], eax
0x0804879b      call    decrypt    ; sym.decrypt
0x080487a0      jmp     0x8048858  ; sym.test+0x111
0x080487a5      mov     eax, dword [ebp - 0xc]
0x080487a8      mov     dword [esp], eax
0x080487ab      call    decrypt    ; sym.decrypt
0x080487b0      jmp     0x8048858  ; sym.test+0x111
0x080487b5      mov     eax, dword [ebp - 0xc]
0x080487b8      mov     dword [esp], eax
0x080487bb      call    decrypt    ; sym.decrypt
0x080487c0      jmp     0x8048858  ; sym.test+0x111
0x080487c5      mov     eax, dword [ebp - 0xc]
0x080487c8      mov     dword [esp], eax
0x080487cb      call    decrypt    ; sym.decrypt
0x080487d0      jmp     0x8048858  ; sym.test+0x111
0x080487d5      mov     eax, dword [ebp - 0xc]
0x080487d8      mov     dword [esp], eax
0x080487db      call    decrypt    ; sym.decrypt
0x080487e0      jmp     0x8048858  ; sym.test+0x111
0x080487e2      mov     eax, dword [ebp - 0xc]
0x080487e5      mov     dword [esp], eax
0x080487e8      call    decrypt    ; sym.decrypt
0x080487ed      jmp     0x8048858  ; sym.test+0x111
0x080487ef      mov     eax, dword [ebp - 0xc]
0x080487f2      mov     dword [esp], eax
0x080487f5      call    decrypt    ; sym.decrypt
0x080487fa      jmp     0x8048858  ; sym.test+0x111
0x080487fc      mov     eax, dword [ebp - 0xc]
0x080487ff      mov     dword [esp], eax
0x08048802      call    decrypt    ; sym.decrypt
0x08048807      jmp     0x8048858  ; sym.test+0x111
0x08048809      mov     eax, dword [ebp - 0xc]
0x0804880c      mov     dword [esp], eax
0x0804880f      call    decrypt    ; sym.decrypt
0x08048814      jmp     0x8048858  ; sym.test+0x111
0x08048816      mov     eax, dword [ebp - 0xc]
0x08048819      mov     dword [esp], eax
0x0804881c      call    decrypt    ; sym.decrypt
0x08048821      jmp     0x8048858  ; sym.test+0x111
0x08048823      mov     eax, dword [ebp - 0xc]
0x08048826      mov     dword [esp], eax
0x08048829      call    decrypt    ; sym.decrypt
0x0804882e      jmp     0x8048858  ; sym.test+0x111
0x08048830      mov     eax, dword [ebp - 0xc]
0x08048833      mov     dword [esp], eax
0x08048836      call    decrypt    ; sym.decrypt
0x0804883b      jmp     0x8048858  ; sym.test+0x111
0x0804883d      mov     eax, dword [ebp - 0xc]
0x08048840      mov     dword [esp], eax
0x08048843      call    decrypt    ; sym.decrypt
0x08048848      jmp     0x8048858  ; sym.test+0x111
0x0804884a      call    rand       ; sym.imp.rand ; int rand(void)
0x0804884f      mov     dword [esp], eax
0x08048852      call    decrypt    ; sym.decrypt
0x08048857      nop
0x08048858      leave
0x08048859      ret

int main(int argc, char **argv, char **envp);
; var int32_t var_20h @ stack - 0x20
; var int32_t var_1ch @ stack - 0x1c
; var int32_t var_8h @ stack - 0x8
; var int32_t var_4h @ stack - 0x4
0x0804885a      push    ebp
0x0804885b      mov     ebp, esp
0x0804885d      and     esp, 0xfffffff0
0x08048860      sub     esp, 0x20
0x08048863      push    eax
0x08048864      xor     eax, eax
0x08048866      je      0x804886b
0x08048868      add     esp, 4
0x0804886b      pop     eax
0x0804886c      mov     dword [esp], 0
0x08048873      call    time       ; sym.imp.time ; time_t time(time_t *timer)
0x08048878      mov     dword [esp], eax
0x0804887b      call    srand      ; sym.imp.srand ; void srand(int seed)
0x08048880      mov     dword [esp], 0x8048a48
0x08048887      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x0804888c      mov     dword [esp], str.level03 ; 0x8048a6c
0x08048893      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x08048898      mov     dword [esp], 0x8048a48
0x0804889f      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080488a4      mov     eax, str.Password: ; 0x8048a7b
0x080488a9      mov     dword [esp], eax
0x080488ac      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x080488b1      mov     eax, 0x8048a85
0x080488b6      lea     edx, [var_8h]
0x080488ba      mov     dword [var_20h], edx
0x080488be      mov     dword [esp], eax
0x080488c1      call    __isoc99_scanf ; sym.imp.__isoc99_scanf ; int scanf(const char *format)
0x080488c6      mov     eax, dword [var_8h]
0x080488ca      mov     dword [var_20h], 0x1337d00d
0x080488d2      mov     dword [esp], eax
0x080488d5      call    test       ; sym.test
0x080488da      mov     eax, 0
0x080488df      leave
0x080488e0      ret
0x080488e1      nop
0x080488e2      nop
0x080488e3      nop
0x080488e4      nop
0x080488e5      nop
0x080488e6      nop
0x080488e7      nop
0x080488e8      nop
0x080488e9      nop
0x080488ea      nop
0x080488eb      nop
0x080488ec      nop
0x080488ed      nop
0x080488ee      nop
0x080488ef      nop