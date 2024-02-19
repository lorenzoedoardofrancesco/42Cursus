store_number(int32_t arg_4h);
; var int32_t var_14h @ stack - 0x14
; var int32_t var_10h @ stack - 0x10
; arg int32_t arg_4h @ stack + 0x4
0x08048630      push    ebp
0x08048631      mov     ebp, esp
0x08048633      sub     esp, 0x28
0x08048636      mov     dword [var_14h], 0
0x0804863d      mov     dword [var_10h], 0
0x08048644      mov     eax, str.Number: ; 0x8048ad3
0x08048649      mov     dword [esp], eax
0x0804864c      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x08048651      call    get_unum   ; sym.get_unum
0x08048656      mov     dword [var_14h], eax
0x08048659      mov     eax, str.Index: ; 0x8048add
0x0804865e      mov     dword [esp], eax
0x08048661      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x08048666      call    get_unum   ; sym.get_unum
0x0804866b      mov     dword [var_10h], eax
0x0804866e      mov     ecx, dword [var_10h]
0x08048671      mov     edx, 0xaaaaaaab
0x08048676      mov     eax, ecx
0x08048678      mul     edx
0x0804867a      shr     edx, 1
0x0804867c      mov     eax, edx
0x0804867e      add     eax, eax
0x08048680      add     eax, edx
0x08048682      mov     edx, ecx
0x08048684      sub     edx, eax
0x08048686      test    edx, edx
0x08048688      je      0x8048697
0x0804868a      mov     eax, dword [var_14h]
0x0804868d      shr     eax, 0x18
0x08048690      cmp     eax, 0xb7  ; 183
0x08048695      jne     0x80486c2
0x08048697      mov     dword [esp], str.ERROR ; 0x8048ae6
0x0804869e      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080486a3      mov     dword [esp], str.This_index_is_reserved_for_wil ; 0x8048af8
0x080486aa      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080486af      mov     dword [esp], str.ERROR ; 0x8048ae6
0x080486b6      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080486bb      mov     eax, 1
0x080486c0      jmp     0x80486d5
0x080486c2      mov     eax, dword [var_10h]
0x080486c5      shl     eax, 2
0x080486c8      add     eax, dword [arg_4h]
0x080486cb      mov     edx, dword [var_14h]
0x080486ce      mov     dword [eax], edx
0x080486d0      mov     eax, 0
0x080486d5      leave
0x080486d6      ret

read_number(int32_t arg_4h);
; var int32_t var_28h @ stack - 0x28
; var int32_t var_24h @ stack - 0x24
; var int32_t var_10h @ stack - 0x10
; arg int32_t arg_4h @ stack + 0x4
0x080486d7      push    ebp
0x080486d8      mov     ebp, esp
0x080486da      sub     esp, 0x28
0x080486dd      mov     dword [var_10h], 0
0x080486e4      mov     eax, str.Index: ; 0x8048add
0x080486e9      mov     dword [esp], eax
0x080486ec      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x080486f1      call    get_unum   ; sym.get_unum
0x080486f6      mov     dword [var_10h], eax
0x080486f9      mov     eax, dword [var_10h]
0x080486fc      shl     eax, 2
0x080486ff      add     eax, dword [arg_4h]
0x08048702      mov     edx, dword [eax]
0x08048704      mov     eax, str.Number_at_data__u__is__u ; 0x8048b1b
0x08048709      mov     dword [var_24h], edx
0x0804870d      mov     edx, dword [var_10h]
0x08048710      mov     dword [var_28h], edx
0x08048714      mov     dword [esp], eax
0x08048717      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x0804871c      mov     eax, 0
0x08048721      leave
0x08048722      ret

int main(int argc, char **argv, char **envp);
; var int32_t var_1dch @ stack - 0x1dc
; var int32_t var_1d8h @ stack - 0x1d8
; var int32_t var_1cch @ stack - 0x1cc
; var int32_t var_1c8h @ stack - 0x1c8
; var int32_t var_1c4h @ stack - 0x1c4
; var int32_t var_1bch @ stack - 0x1bc
; var int32_t var_2ch @ stack - 0x2c
; var int32_t var_28h @ stack - 0x28
; var int32_t var_24h @ stack - 0x24
; var int32_t var_20h @ stack - 0x20
; var int32_t var_1ch @ stack - 0x1c
; var int32_t var_18h @ stack - 0x18
; var int32_t var_14h @ stack - 0x14
; var int32_t var_10h @ stack - 0x10
; arg char **envp @ stack + 0x8
; arg int32_t arg_ch @ stack + 0xc
0x08048723      push    ebp
0x08048724      mov     ebp, esp
0x08048726      push    edi
0x08048727      push    esi
0x08048728      push    ebx
0x08048729      and     esp, 0xfffffff0
0x0804872c      sub     esp, 0x1d0
0x08048732      mov     eax, dword [envp]
0x08048735      mov     dword [var_1c4h], eax
0x08048739      mov     eax, dword [arg_ch]
0x0804873c      mov     dword [var_1c8h], eax
0x08048740      mov     eax, dword gs:[0x14]
0x08048746      mov     dword [var_14h], eax
0x0804874d      xor     eax, eax
0x0804874f      mov     dword [var_2ch], 0
0x0804875a      mov     dword [var_28h], 0
0x08048765      mov     dword [var_24h], 0
0x08048770      mov     dword [var_20h], 0
0x0804877b      mov     dword [var_1ch], 0
0x08048786      mov     dword [var_18h], 0
0x08048791      lea     ebx, [var_1bch]
0x08048795      mov     eax, 0
0x0804879a      mov     edx, 0x64  ; 'd' ; 100
0x0804879f      mov     edi, ebx
0x080487a1      mov     ecx, edx
0x080487a3      rep     stosd dword es:[edi], eax
0x080487a5      jmp     0x80487ea
0x080487a7      mov     eax, dword [var_1c4h]
0x080487ab      mov     eax, dword [eax]
0x080487ad      mov     dword [var_1cch], 0xffffffff ; -1
0x080487b5      mov     edx, eax
0x080487b7      mov     eax, 0
0x080487bc      mov     ecx, dword [var_1cch]
0x080487c0      mov     edi, edx
0x080487c2      repne   scasb al, byte es:[edi]
0x080487c4      mov     eax, ecx
0x080487c6      not     eax
0x080487c8      lea     edx, [eax - 1]
0x080487cb      mov     eax, dword [var_1c4h]
0x080487cf      mov     eax, dword [eax]
0x080487d1      mov     dword [var_1d8h], edx
0x080487d5      mov     dword [var_1dch], 0
0x080487dd      mov     dword [esp], eax
0x080487e0      call    memset     ; sym.imp.memset ; void *memset(void *s, int c, size_t n)
0x080487e5      add     dword [var_1c4h], 4
0x080487ea      mov     eax, dword [var_1c4h]
0x080487ee      mov     eax, dword [eax]
0x080487f0      test    eax, eax
0x080487f2      jne     0x80487a7
0x080487f4      jmp     0x8048839
0x080487f6      mov     eax, dword [var_1c8h]
0x080487fa      mov     eax, dword [eax]
0x080487fc      mov     dword [var_1cch], 0xffffffff ; -1
0x08048804      mov     edx, eax
0x08048806      mov     eax, 0
0x0804880b      mov     ecx, dword [var_1cch]
0x0804880f      mov     edi, edx
0x08048811      repne   scasb al, byte es:[edi]
0x08048813      mov     eax, ecx
0x08048815      not     eax
0x08048817      lea     edx, [eax - 1]
0x0804881a      mov     eax, dword [var_1c8h]
0x0804881e      mov     eax, dword [eax]
0x08048820      mov     dword [var_1d8h], edx
0x08048824      mov     dword [var_1dch], 0
0x0804882c      mov     dword [esp], eax
0x0804882f      call    memset     ; sym.imp.memset ; void *memset(void *s, int c, size_t n)
0x08048834      add     dword [var_1c8h], 4
0x08048839      mov     eax, dword [var_1c8h]
0x0804883d      mov     eax, dword [eax]
0x0804883f      test    eax, eax
0x08048841      jne     0x80487f6
0x08048843      mov     dword [esp], str.Welcome_to_wil_s_crappy_number_storage_service___________________________________________________________Commands:_______________________________________________store___store_a_number_into_the_data_storage_________read____read_a_number_from_the_data_storage__________quit____exit_the_program_________________________________________________________________________________wil_has_reserved_some_storage_: ; 0x8048b38
0x0804884a      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x0804884f      mov     eax, str.Input_command: ; 0x8048d4b
0x08048854      mov     dword [esp], eax
0x08048857      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x0804885c      mov     dword [var_2ch], 1
0x08048867      mov     eax, dword stdin ; obj.stdin__GLIBC_2.0
                                   ; 0x804a040
0x0804886c      mov     dword [var_1d8h], eax
0x08048870      mov     dword [var_1dch], 0x14 ; 20
0x08048878      lea     eax, [var_28h]
0x0804887f      mov     dword [esp], eax
0x08048882      call    fgets      ; sym.imp.fgets ; char *fgets(char *s, int size, FILE *stream)
0x08048887      lea     eax, [var_28h]
0x0804888e      mov     dword [var_1cch], 0xffffffff ; -1
0x08048896      mov     edx, eax
0x08048898      mov     eax, 0
0x0804889d      mov     ecx, dword [var_1cch]
0x080488a1      mov     edi, edx
0x080488a3      repne   scasb al, byte es:[edi]
0x080488a5      mov     eax, ecx
0x080488a7      not     eax
0x080488a9      sub     eax, 1
0x080488ac      sub     eax, 1
0x080488af      mov     byte [esp + eax + 0x1b8], 0
0x080488b7      lea     eax, [var_28h]
0x080488be      mov     edx, eax
0x080488c0      mov     eax, str.store ; 0x8048d5b
0x080488c5      mov     ecx, 5
0x080488ca      mov     esi, edx
0x080488cc      mov     edi, eax
0x080488ce      repe    cmpsb byte [esi], byte ptr es:[edi]
0x080488d0      seta    dl
0x080488d3      setb    al
0x080488d6      mov     ecx, edx
0x080488d8      sub     cl, al
0x080488da      mov     eax, ecx
0x080488dc      movsx   eax, al
0x080488df      test    eax, eax
0x080488e1      jne     0x80488f8
0x080488e3      lea     eax, [var_1bch]
0x080488e7      mov     dword [esp], eax
0x080488ea      call    store_number ; sym.store_number
0x080488ef      mov     dword [var_2ch], eax
0x080488f6      jmp     0x8048965
0x080488f8      lea     eax, [var_28h]
0x080488ff      mov     edx, eax
0x08048901      mov     eax, str.read ; 0x8048d61
0x08048906      mov     ecx, 4
0x0804890b      mov     esi, edx
0x0804890d      mov     edi, eax
0x0804890f      repe    cmpsb byte [esi], byte ptr es:[edi]
0x08048911      seta    dl
0x08048914      setb    al
0x08048917      mov     ecx, edx
0x08048919      sub     cl, al
0x0804891b      mov     eax, ecx
0x0804891d      movsx   eax, al
0x08048920      test    eax, eax
0x08048922      jne     0x8048939
0x08048924      lea     eax, [var_1bch]
0x08048928      mov     dword [esp], eax
0x0804892b      call    read_number ; sym.read_number
0x08048930      mov     dword [var_2ch], eax
0x08048937      jmp     0x8048965
0x08048939      lea     eax, [var_28h]
0x08048940      mov     edx, eax
0x08048942      mov     eax, str.quit ; 0x8048d66
0x08048947      mov     ecx, 4
0x0804894c      mov     esi, edx
0x0804894e      mov     edi, eax
0x08048950      repe    cmpsb byte [esi], byte ptr es:[edi]
0x08048952      seta    dl
0x08048955      setb    al
0x08048958      mov     ecx, edx
0x0804895a      sub     cl, al
0x0804895c      mov     eax, ecx
0x0804895e      movsx   eax, al
0x08048961      test    eax, eax
0x08048963      je      0x80489cf
0x08048965      cmp     dword [var_2ch], 0
0x0804896d      je      0x8048989
0x0804896f      mov     eax, str.Failed_to_do__s_command ; 0x8048d6b
0x08048974      lea     edx, [var_28h]
0x0804897b      mov     dword [var_1dch], edx
0x0804897f      mov     dword [esp], eax
0x08048982      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x08048987      jmp     0x80489a1
0x08048989      mov     eax, str.Completed__s_command_successfully ; 0x8048d88
0x0804898e      lea     edx, [var_28h]
0x08048995      mov     dword [var_1dch], edx
0x08048999      mov     dword [esp], eax
0x0804899c      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x080489a1      lea     eax, [var_28h]
0x080489a8      mov     dword [eax], 0
0x080489ae      mov     dword [eax + 4], 0
0x080489b5      mov     dword [eax + 8], 0
0x080489bc      mov     dword [eax + 0xc], 0
0x080489c3      mov     dword [eax + 0x10], 0
0x080489ca      jmp     0x804884f
0x080489cf      nop
0x080489d0      mov     eax, 0
0x080489d5      mov     esi, dword [var_14h]
0x080489dc      xor     esi, dword gs:[0x14]
0x080489e3      je      0x80489ea
0x080489e5      call    __stack_chk_fail ; sym.imp.__stack_chk_fail ; void __stack_chk_fail(void)
0x080489ea      lea     esp, [var_10h]
0x080489ed      pop     ebx
0x080489ee      pop     esi
0x080489ef      pop     edi
0x080489f0      pop     ebp
0x080489f1      ret
0x080489f2      nop
0x080489f3      nop
0x080489f4      nop
0x080489f5      nop
0x080489f6      nop
0x080489f7      nop
0x080489f8      nop
0x080489f9      nop
0x080489fa      nop
0x080489fb      nop
0x080489fc      nop
0x080489fd      nop
0x080489fe      nop
0x080489ff      nop