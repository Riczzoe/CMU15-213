/*
 * @param[in] in The first number entered by the user is stored in register edi. 
 * @param[in] n1 Stored in register esi.
 * @param[in] n2 Stored in register edx.
 */
int func4(int in, int n1, int n2) {
    /* mov  %edx, %eax              */
    /* sub  %esi, %eax              */
    /* res stored in register eax   */
    int res = n2 - n1;
    /* mov  %eax, %ecx              */
    /* shr  $0x1f, %ecx             */
    /* c stored in register ecx     */
    /* if n2 >= n1 ==> res >= 0 ==> c = 0  */
    /*    n2 < n1  ==> res < 0  ==> c = 1  */
    int c = res >>> 31;
    /* add  %ecx, %eax              */
    /* sar  %eax                    */
    res = (res + c) >> 1;
    /* lea  (%rax,%rsi,1),%ecx      */
    c = res + n1;

    /* cmp  %edi, %ecx              */
    /* jge  <func4+0x39>            */
    if (c == in) {
        /* mov  $0x0, %eax          */
        /* lea  0x1(%rax, %rax, 1), %eax    */
        return 0;
    } 

    /* cmp  %edi, %ecx              */
    /* jle  <func4+0x24>            */
    else if (c > in) 
    {
        return 2 * func4(in, c - 1, n2);
    } 

    /* c < in                           */
    return 1 + 2 * func4(in, c + 1, n2);

}
