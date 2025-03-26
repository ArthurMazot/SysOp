package SysOp.Java;

public class GM {
    private int tamPag;
    private boolean[] pags;

    public GM(int tamM, int tamP){
        tamPag = tamP;
        pags = new boolean[tamM/tamPag];
        for(int i = 0; i < pags.length; i++) pags[i] = false;}

    boolean aloca(int numPalvaras, int[] tabPag){
        int tam = (numPalvaras/tamPag) + (((numPalvaras % tamPag) > 0) ? 1 : 0); //quantas paginas o programa precisa
        int count = tam;

        for(int i = 0; (i < pags.length) && (count > 0); i++) //verfica se tem todas as paginas necessarias
            if(!pags[i]) 
                count--;

        if(count != 0) return false;

        tabPag = new int[tam];
        for(int i = 0 ; count < tabPag.length; i++) //coloca as paginas alocadas no tabPag;
            if(!pags[i]){
                pags[i] = true;
                tabPag[count++] = i;}
        return true;}

    void desaloca(int[] tabPag){
        for(int i = 0; i < tabPag.length; i++)
            pags[tabPag[i]] = false;}
}
