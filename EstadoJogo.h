#ifndef ESTADOJOGO_H
#define ESTADOJOGO_H

#include "GameState.h"
#include <vector>
#include <string>

// Estrutura que representa um nó da árvore de estados
struct NoEstado {
    GameState estado;           
    char pecaMovida;           
    int xOrigem, yOrigem;      
    int xDestino, yDestino;    
    int numeroJogada;          
    NoEstado* pai;             // Ponteiro para o estado pai (jogada anterior)
    vector<NoEstado*> filhos;  // Lista dos estados filhos (próximas jogadas)
    
    
    NoEstado(GameState est, char peca, int xO, int yO, int xD, int yD, int numJog, NoEstado* p = nullptr);
    
    ~NoEstado();
};

class ArvoreEstados {
private:
    NoEstado* raiz;           
    NoEstado* estadoAtual;    
    int contadorJogadas;      
    
public:
    
    ArvoreEstados(GameState estadoInicial);
    
    ~ArvoreEstados();
    
    void adicionarEstado(GameState novoEstado, char peca, int xO, int yO, int xD, int yD);
    
    bool voltarJogada();

    void mostrarArvore();
    
    GameState getEstadoAtual();
    
private:
    
    void mostrarArvoreRecursivo(NoEstado* no, int nivel);
    
    
    void limparArvore(NoEstado* no);
};

#endif