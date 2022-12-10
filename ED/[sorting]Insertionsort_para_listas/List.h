// Lista duplamente encadeada circular com node sentinela
#ifndef LIST_H
#define LIST_H
#include "Node.h"

class List {
private:
    Node *m_head {nullptr}; // ponteiro para o node sentinela
    int m_size {0}; // numero de elementos na lista atualmente

public:
    // Construtor default: cria uma lista vazia, ou sejaaa, 
    // com o ponteiro m_head apontando para o node sentinela
    List() { // O(1)
        m_head = new Node(0, nullptr, nullptr);
        m_head->prev = m_head->next = m_head;
    }

    // insere um elemento no final da lista
    void push_back(const int& val) { // O(1)
        Node *aux = new Node(val, m_head->prev, m_head);
        aux->prev->next = aux;
        m_head->prev = aux;
        m_size++;
    }

    // retorna o numero de elementos na lista
    int size() const { // O(1)
        return m_size;
    }

    // retorna true se e somente se lista eh vazia
    bool empty() const { // O(1)
        return m_size == 0;
    }

    // deixa a lista vazia novamente, liberando memoria
    void clear() { // O(n)
        Node *aux = m_head->prev;
        while(aux != m_head) {
            Node *temp = aux;
            aux = aux->prev;
            delete temp;
        }
        m_head->prev = m_head->next = m_head;
        m_size = 0;
    }

    // Destrutor
    ~List() { // O(n)
        clear();
        delete m_head;
    }

    // iterador para a lista
    class iterator {
    private:
        Node *pointer {nullptr};
    public:
        iterator(Node *ptr) {
            pointer = ptr;
        }
        iterator& operator++() {
            pointer = pointer->next;
            return *this;
        }
        bool operator!=(const iterator& it) {
            return this->pointer != it.pointer;
        }
        int& operator*() {
            return pointer->value;
        }
    };

    // retorna um iterador para o primeiro elemento da lista
    iterator begin() {
        return iterator(m_head->next);
    }

    // retorna um iterador para uma posicao apos o ultimo elemento
    iterator end() {
        return iterator(m_head);
    }

    /**
     * Funcao que ordena os elementos da lista em ordem crescente.
     * Esta funcao ordena a lista usando o algoritmo insertionsort.
     * Para implementar esta funcao, voce deve satisfazer as 
     * seguintes restricoes:
     * 1 - Nao eh permitido usar arrays ou outras estruturas de
     *     dados auxiliares, inclusive, nao eh permitido instanciar
     *     nodes adicionais. Voce pode declarar variaveis ponteiro
     *     auxiliares para te ajudar.
     * 2 - Seu algoritmo deve ter complexidade de pior caso O(n^2), 
     *     assim como a versao original dele para vetores.
     * 3 - Nao eh permitido usar funcoes auxiliares. 
     *     Da para fazer tudo dentro da funcao insertionsort.
     */
    void insertionsort() {
        Node *aux1 = m_head->next; //cria node auxiliar que comeca apontando para o primeiro elemento da arraylist
        int size = m_size; //pega o tamanho atual do arraylist
        int cont = 0; //contagem auxiliar para rodar mais vezes no for mais esterno
        for(int i = 1; i < size; i++) {
            cont++; //sempre que rodar uma vez no for, cont aumenta para guardar o numero de vezes rodadas totalmente
            Node *au = aux1; //um node auxiliar para que aux1 não perca a primeira posicao do arraylist
            Node *aux2 = aux1->next; //node auxiliar que aponta para a proxima posicao do arraylsit 
            int v = aux2->value; //int que guarda o valor do aux2
            int j = i - 1; //int j que guarda um a menos que i
            while(v < au->value && j >= 0) { //compara se v é menor que o valor guardado em au
                au->next->value = au->value; //faz o seguinte ao au receber o valor de au
                au->value = v; //faz au receber v
                v = aux2->value; //faz v acompanhar a mudanca de valor de aux2
                --j; //diminui j
                au = au->next; //faz au apontar para a posicao seguinte
            }
            aux1 = aux1->next; //faz aux1 apontar para a posicao seguinte
            if(i+1 == m_size && cont < size*(size-3)) { //if complementar para ver se os valores de i e cont já chegaram no maximo
                i = 1;                                  //se so o i tiver atingido o limite, significa que o programa ainda precisa 
                aux1 = m_head->next;                    //rodar, entao, i volta pra zero e aux1 volta a apontar para a primeira 
                                                        //posicao do arraylist, se cont tambem tiver atingido o limite, significa 
            }                                           //que o codigo chegou no seu final, e tudo esta ordenado. Assim o for termina
        }
    }
};

#endif