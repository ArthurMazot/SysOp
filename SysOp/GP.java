package SysOp;

import SysOp.Sistema.Word;

public class GP {
    PCB[] processos;
    Word[] mem;
    private GM gm;

    public GP(Word[] m, int tamPag){
        processos = new PCB[m.length/tamPag]; //Não sei o tamanho
        for(int i = 0; i < processos.length; i++)
            processos[i] = null;
        gm = new GM(m.length, tamPag);
        mem = m;}

    boolean criaProcesso(Word[] prog){
        int[] tabPag = null;
        if(!gm.aloca(prog.length, tabPag)) return false; //verifica se tem espaço na memoria
        for(int i = 0; i < processos.length; i++) //coloca na lista de processos
            if(processos[i] == null){
                processos[i] = new PCB(i, tabPag);
                break;}
        return true;}

    void desalocaProcesso(int id){
        gm.desaloca(processos[id].tabPag);
        processos[id] = null;  //aparentemente não existe um delete
    }
}
