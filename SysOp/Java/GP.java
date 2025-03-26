package SysOp.Java;

import SysOp.Java.Sistema.Word;

public class GP {
    private int tamPag;
    private PCB[] processosProntos;
    private Word[] mem;
    private GM gm;

    public GP(Word[] m, int tamP){
        processosProntos = new PCB[m.length/tamP]; //Não sei o tamanho
        tamPag = tamP;
        for(int i = 0; i < processosProntos.length; i++)
            processosProntos[i] = null;
        gm = new GM(m.length, tamP);
        mem = m;}

    boolean criaProcesso(Word[] prog){
        int[] tabPag = null;
        if(!gm.aloca(prog.length, tabPag)) //verifica se tem espaço na memoria
            return false;

        for(int i = 0; i < tamPag; i++) //colaca o programa nas paginas alocadas
            for(int j = 0; j < tamPag; j++)
                mem[tabPag[i]*tamPag + j] = prog[i*tamPag + j]; //se tiver reclamando que tabPag pode ser null, não vai ser pq no gm.aloca se não encontrar espaço na memoria ele entra no if e retonra falso;

        for(int i = 0; i < processosProntos.length; i++) //coloca na lista de processos
            if(processosProntos[i] == null){
                processosProntos[i] = new PCB(i, tabPag);
                break;}
        return true;}

    void desalocaProcesso(int id){
        gm.desaloca(processosProntos[id].tabPag);
        processosProntos[id] = null;}  //aparentemente não existe um delete
}
