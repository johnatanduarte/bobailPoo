#include "EstadoJogo.h"
#include <iostream>
#include <iomanip>

using namespace std;

NoEstado::NoEstado(GameState est, char peca, int xO, int yO, int xD, int yD, int numJog, NoEstado* p) {
    estado = est;
    pecaMovida = peca;
    xOrigem = xO;
    yOrigem = yO;
    xDestino = xD;
    yDestino = yD;
    numeroJogada = numJog;
    pai = p;
    // O vetor filhos já é inicializado vazio automaticamente
}

NoEstado::~NoEstado() {
    
    for (size_t i = 0; i < filhos.size(); i++) {
        delete filhos[i];
    }

    filhos.clear();
}

ArvoreEstados::ArvoreEstados(GameState estadoInicial) {
    
    raiz = new NoEstado(estadoInicial, ' ', -1, -1, -1, -1, 0, nullptr); //quais caracteristicas foram movidas? nenhuma
    estadoAtual = raiz;  
    contadorJogadas = 0;
    
    cout << "=== Arvore de Estados Inicializada ===" << endl;
}

ArvoreEstados::~ArvoreEstados() {
    limparArvore(raiz);
}

void ArvoreEstados::adicionarEstado(GameState novoEstado, char peca, int xO, int yO, int xD, int yD) {
    contadorJogadas++;
    
    NoEstado* novoNo = new NoEstado(novoEstado, peca, xO, yO, xD, yD, contadorJogadas, estadoAtual);//o estadoAtual é o nó pai, ou seja, a jogada anterior.
    
    estadoAtual->filhos.push_back(novoNo);
    
    estadoAtual = novoNo;
    
    cout << "--- Jogada " << contadorJogadas << " adicionada: " << peca 
         << " de (" << xO << "," << yO << ") para (" << xD << "," << yD << ") ---" << endl;
}

bool ArvoreEstados::voltarJogada() {

    if (estadoAtual->pai == nullptr) {
        cout << "--- Nao e possivel voltar: ja esta no inicio do jogo ---" << endl;
        return false;
    }
    
    estadoAtual = estadoAtual->pai;
    contadorJogadas--;
    
    cout << "--- Voltou para jogada " << estadoAtual->numeroJogada << " ---" << endl;
    return true;
}

void ArvoreEstados::mostrarArvore() {
    cout << "\n========== ARVORE COMPLETA DE JOGADAS ==========" << endl;
    cout << "Legenda: [Jogada] Peca: origem -> destino" << endl;
    cout << "===============================================" << endl;
    
    mostrarArvoreRecursivo(raiz, 0);
    
    cout << "===============================================" << endl;
    cout << "Total de jogadas realizadas: " << contadorJogadas << endl;
}

void ArvoreEstados::mostrarArvoreRecursivo(NoEstado* no, int nivel) {
    if (no == nullptr) {
        return;
    }
    
    // Cria indentação baseada no nível da árvore
    string indentacao = "";
    for (int i = 0; i < nivel; i++) {
        indentacao += "  ";  
    }
    
    if (no->numeroJogada == 0) {
        cout << indentacao << "[INICIO] Estado inicial do jogo";
    } else {
        cout << indentacao << "[" << no->numeroJogada << "] " 
             << no->pecaMovida << ": (" << no->xOrigem << "," << no->yOrigem 
             << ") -> (" << no->xDestino << "," << no->yDestino << ")";
    }
    
    if (no == estadoAtual) {
        cout << " <- fim da arvore (estado atual)";
    }
    cout << endl;
    
    for (size_t i = 0; i < no->filhos.size(); i++) { 
        mostrarArvoreRecursivo(no->filhos[i], nivel + 1);
    }

}

GameState ArvoreEstados::getEstadoAtual() {
    return estadoAtual->estado;
}

void ArvoreEstados::limparArvore(NoEstado* no) {
    if (no != nullptr) {
        
        for (size_t i = 0; i < no->filhos.size(); i++) {
            limparArvore(no->filhos[i]);
        }

        delete no;
    }
}