struct operandos {
    int x;
    int y;
    int z;
};
program PROG {
    version VERSAO {
        int ADD(operandos) = 1;
        int SUB(operandos) = 2;
        int MUL(operandos) = 3;
        double DIVI(operandos) = 4;
    } = 100;
} = 55555555;