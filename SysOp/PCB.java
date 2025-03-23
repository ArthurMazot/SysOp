package SysOp;

public class PCB {
    public int id;
    public int[] tabPag;
    public boolean rodando;
    public int pc;

    public PCB(int i, int[] tab){
        id = i;
        tabPag = tab;
        rodando = false;
        pc = 0;}
}
