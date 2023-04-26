typdedf syruct {
    long offset;        /* Offset of the reference to replace */
    long type:32,       /* Relocation type */
         symbol:32;     /* Symbol table idnex */
    long addend;        /* Constant part of relocation expression */
} Elf64_Rela;

/* Pseudocode for relocation algorithm */
foreach section s in sections {
    foreach relocation entry r in s {
        refptr = s + r.offset;      /* ptr to reference to be relocation    */
        
        /* Relocate a PC-relative reference */
        if (r.type == R_X86_64_PC_32) {
            refaddr = ADDR(S) + r.offset;   /* ref's run-time address   */
            *refptr = (unsigned) (ADDR(r.symbol) + r.addend - refaddr);
        }

        /* Relocate an absolute reference   */
        if (r.type == R_X86_64_32) 
            *refptr = (unsigned) (ADDR(r.symbol) + r.addend);
    }
}
