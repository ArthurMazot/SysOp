#include "IO.hpp" 
 

 /* Função para add uma nova requisição I/O */
void IOGerenciamento::adicionaReq(PCB* pcb, IOType tipo, int address){
    unique_lock<mutex> lock(IOMutex);
    filaRequisicoes.push( {pcb->id, tipo, address});
    filaBloqueados.push(pcb);
    pcb->state = ProcessState::BLOCKED;
    cout << "Requição de IO add ao processo.!" << pcb->id << endl;
    cvNewRequesicao.notify_one();
    }

void IOGerenciamento::threadIO(){
    cout << "[IO] threadIO iniciada e aguardando requisições...\n";
    while(true){
        unique_lock<mutex> lock(IOMutex);
        cvNewRequesicao.wait(lock, [&]() { return !filaRequisicoes.empty(); });

        IO req = filaRequisicoes.front();
        filaRequisicoes.pop();

        PCB* pcb = filaBloqueados.front();
        filaBloqueados.pop();

        reqAtual = req;
        reqPendente = true;

        if(reqAtual.tipo == LEITURA){
            cout << "Processo " << reqAtual.pid << "esperando  de entrada.!" << endl;
            cout << reqAtual.pid << endl;
        }else{
            int valor = sistema->mem->pos[reqAtual.address].p;
            cout << "Processo " << reqAtual.pid << endl;
            cout << "SAIDA: " << valor << endl;
            gerarInterrupcao();
            }
        cvInterrupcaoFinalizada.wait(lock, [&] (){ return !reqPendente;});
    }
}
    
void IOGerenciamento::valorDeEntrada(int pid, int valor){
    unique_lock<mutex> lock(IOMutex);
    if(reqPendente && reqAtual.pid == pid && reqAtual.tipo == LEITURA){
        sistema->mem->pos[reqAtual.address].p = valor;
        cout << "Entrada adquirida para o processo " << pid << ": " << valor << endl;
        gerarInterrupcao();
    }
}

void IOGerenciamento::InterrupcaoFinalizada(){
    unique_lock<mutex> lock (IOMutex);
    PCB* pcb = nullptr;
    queue<PCB*> temp;

    while(!filaBloqueados.empty()){
        PCB* atual = filaBloqueados.front();
        filaBloqueados.pop();
        if(atual->id == reqAtual.pid){
            pcb = atual;
            break;
        }else{
            temp.push(atual);
        }
    }

    while(!temp.empty()){
        filaBloqueados.push(temp.front());
        temp.pop();
    }
    if(pcb){
        pcb->state = ProcessState::READY;
        sistema->so->esc->addExec(pcb);
        cout << "Processo " << pcb->id << "foi movido para fila de prontos " << endl; 
    }
    reqPendente = false;
    cvInterrupcaoFinalizada.notify_one();
}

void IOGerenciamento::gerarInterrupcao(){
    cout << "[IO] gerarInterrupcao() chamada\n";
    sistema->so->ih->handle(Interrupts::IOInterrupt);
}