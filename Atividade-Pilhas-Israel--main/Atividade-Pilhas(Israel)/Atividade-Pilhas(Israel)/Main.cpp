#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <queue>
#include <list>
#include <vector>
#include <stack>


    bool verifica_balanceamento(const std::string & expressao) {
        std::stack<char> pilha;

        for (char c : expressao) {
            if (c == '(' || c == '[' || c == '{') {
                pilha.push(c);
            }
            else if (c == ')' || c == ']' || c == '}') {
                if (pilha.empty()) {
                    return false;
                }
                char topo = pilha.top();
                pilha.pop();
                if ((c == ')' && topo != '(') || (c == ']' && topo != '[') || (c == '}' && topo != '{')) {
                    return false;
                }
            }
        }

        return pilha.empty();
    }




    //////////////////////////////////////////////////////////////////
    //Programa NPR

    bool isOperator(const std::string& token) {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }

    double avaliaExpressaoNPR(const std::string& expressao) {
        std::istringstream iss(expressao);
        std::stack<double> pilha;

        std::string token;
        while (iss >> token) {
            if (!isOperator(token)) {
                double operando;
                std::istringstream(token) >> operando;
                pilha.push(operando);
            }
            else {
                if (pilha.size() < 2) {
                    std::cerr << "Erro: Operandos insuficientes para o operador " << token << std::endl;
                    return NAN; // Not a Number
                }

                double operando2 = pilha.top();
                pilha.pop();
                double operando1 = pilha.top();
                pilha.pop();

                double resultado;
                if (token == "+") {
                    resultado = operando1 + operando2;
                }
                else if (token == "-") {
                    resultado = operando1 - operando2;
                }
                else if (token == "*") {
                    resultado = operando1 * operando2;
                }
                else if (token == "/") {
                    if (operando2 == 0) {
                        std::cerr << "Erro: Divisao por zero" << std::endl;
                        return NAN;
                    }
                    resultado = operando1 / operando2;
                }
                pilha.push(resultado);
            }
        }

        if (pilha.size() != 1) {
            std::cerr << "Erro: Expressao invalida" << std::endl;
            return NAN;
        }

        return pilha.top();
    }



    ////////////////////////////////////////////////////////////////
    //Exerc�cio das tarefas

    struct Trabalho {
        std::string nome;
        int prioridade;
        Trabalho(const std::string& n, int p) : nome(n), prioridade(p) {}
    };

    // Fun��o para comparar trabalhos com base em prioridade (usada na fila de prioridade)
    struct ComparadorPrioridade {
        bool operator()(const Trabalho& t1, const Trabalho& t2) {
            return t1.prioridade < t2.prioridade;
        }
    };


/////Exerc�cio do editor de texto

    struct Node {
        char data;
        Node* prev;
        Node* next;
    };

    class TextEditor {
    private:
        Node* head;
        Node* tail;
        Node* cursor;

    public:
        TextEditor() {
            head = nullptr;
            tail = nullptr;
            cursor = nullptr;
        }

        // Insere um caractere na posi��o atual do cursor
        void insert(char c) {
            Node* newNode = new Node;
            newNode->data = c;
            newNode->prev = nullptr;
            newNode->next = nullptr;

            if (head == nullptr) {
                head = newNode;
                tail = newNode;
                cursor = newNode;
            }
            else {
                if (cursor == nullptr) {
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;
                }
                else {
                    newNode->prev = cursor;
                    newNode->next = cursor->next;
                    if (cursor->next != nullptr)
                        cursor->next->prev = newNode;
                    else
                        tail = newNode;
                    cursor->next = newNode;
                }
            }
            cursor = newNode;
        }

        // Remove o caractere na posi��o atual do cursor
        void erase() {
            if (cursor == nullptr) return;

            Node* toDelete = cursor;
            if (cursor->prev != nullptr) {
                cursor->prev->next = cursor->next;
            }
            else {
                head = cursor->next;
            }
            if (cursor->next != nullptr) {
                cursor->next->prev = cursor->prev;
            }
            else {
                tail = cursor->prev;
            }
            cursor = cursor->prev;
            delete toDelete;
        }

        // Move o cursor para a esquerda
        void moveLeft() {
            if (cursor != nullptr && cursor->prev != nullptr)
                cursor = cursor->prev;
        }

        // Move o cursor para a direita
        void moveRight() {
            if (cursor != nullptr && cursor->next != nullptr)
                cursor = cursor->next;
        }

        // Exibe o texto atual
        void display() {
            Node* current = head;
            while (current != nullptr) {
                std::cout << current->data;
                current = current->next;
            }
            std::cout << std::endl;
        }
    };



    ///Exerc�cio do server
    // Defini��o da estrutura de um n� da lista duplamente ligada
    struct Server {
        int id;
        int tasksProcessed;

        Server() : id(0), tasksProcessed(0) {}

        Server(int _id) : id(_id), tasksProcessed(0) {}
    };

    class LoadBalancer {
    private:
        Server* servers;
        int numServers;
        std::queue<int> taskQueue;

    public:
        LoadBalancer(int _numServers) : numServers(_numServers) {
            servers = new Server[numServers];
            for (int i = 0; i < numServers; ++i) {
                servers[i] = Server(i);
            }
        }

        ~LoadBalancer() {
            delete[] servers;
        }

        // Adiciona uma tarefa � fila
        void addTask(int taskId) {
            taskQueue.push(taskId);
            balanceLoad();
        }

        // Prot�tipo da fun��o balanceLoad
        void balanceLoad();

    };

    // Defini��o da fun��o balanceLoad
    void LoadBalancer::balanceLoad() {
        while (!taskQueue.empty()) {
            // Encontra o servidor com menos tarefas processadas
            int minTasks = servers[0].tasksProcessed;
            int minIndex = 0;
            for (int i = 1; i < numServers; ++i) {
                if (servers[i].tasksProcessed < minTasks) {
                    minTasks = servers[i].tasksProcessed;
                    minIndex = i;
                }
            }

            // Atribui a pr�xima tarefa ao servidor encontrado
            int taskId = taskQueue.front();
            taskQueue.pop();
            servers[minIndex].tasksProcessed++;
            std::cout << "Task " << taskId << " assimildada para o Server " << servers[minIndex].id << std:: endl;
        }
    }



    ////Exerc�cio undo/endo
    class TextEditor2 {
    private:
        std::string text;
        std::stack<std::string> undoStack;
        std::stack<std::string> redoStack;

    public:
        TextEditor2() {
            text = "";
        }

        // Insere texto no editor
        void insertText(const std::string& newText) {
            undoStack.push(text);
            text += newText;
            redoStack = std::stack<std::string>(); // Limpa a pilha de redo
        }

        // Deleta texto do editor
        void deleteText(int numChars) {
            if (numChars >= text.length()) {
                undoStack.push(text);
                text = "";
            }
            else {
                undoStack.push(text);
                text.erase(text.length() - numChars, numChars);
            }
            redoStack = std::stack<std::string>(); // Limpa a pilha de redo
        }

        // Desfaz a �ltima a��o
        void undo() {
            if (!undoStack.empty()) {
                redoStack.push(text);
                text = undoStack.top();
                undoStack.pop();
            }
        }

        // Refaz a �ltima a��o desfeita
        void redo() {
            if (!redoStack.empty()) {
                undoStack.push(text);
                text = redoStack.top();
                redoStack.pop();
            }
        }

        // Retorna o texto atual
        std::string getText() const {
            return text;
        }
    };








    int main() 
    {
        std::string expressao;
        std::cout << "2.a) Digite a expressao a ser verificada: " ;
        std::getline(std::cin, expressao);

        if (verifica_balanceamento(expressao)) {
            std::cout << "Os parenteses, colchetes e chaves estao balanceados." << std::endl;
        }
        else {
            std::cout << "Os parenteses, colchetes e chaves NAO estao balanceados." << std::endl;
        }
        std::cout << " " << std::endl;


        //////////////////////////////////////////////////////////////////
        //Programa NPR
        std::string notacao;
        std::cout << "Digite a expressao em Notacao Polonesa Reversa (NPR): ";
        std::getline(std::cin, notacao);

        double resultado = avaliaExpressaoNPR(notacao);
        if (!std::isnan(resultado)) {
            std::cout << "Resultado: " << resultado << std::endl;
        }
        std::cout << " " << std::endl;


        ////////////////////////////////////////////////////////////////
        //Exerc�cio das tarefas

        // Fila de prioridade para gerenciar os trabalhos
        std::priority_queue<Trabalho, std::vector<Trabalho>, ComparadorPrioridade> fila_trabalhos;

        // Lista ligada para manter os trabalhos conclu�dos
        std::list<Trabalho> trabalhos_concluidos;

        // Simula��o de alguns trabalhos
        fila_trabalhos.push(Trabalho("Documento1", 2));
        fila_trabalhos.push(Trabalho("Apresentacao", 1));
        fila_trabalhos.push(Trabalho("Planilha", 3));

        std::cout << "\n2.c)Trabalhos Concluidos:\n";
        // Processamento dos trabalhos
        while (!fila_trabalhos.empty()) {
            // Obtem o pr�ximo trabalho da fila de prioridade
            Trabalho proximo_trabalho = fila_trabalhos.top();
            fila_trabalhos.pop();

            // Simula o processamento do trabalho (aqui estamos apenas imprimindo)
            std::cout << "Imprimindo: " << proximo_trabalho.nome << std::endl;

            // Adiciona o trabalho conclu�do � lista ligada de trabalhos conclu�dos
            trabalhos_concluidos.push_back(proximo_trabalho);
        }

        // Exibe os trabalhos conclu�dos

        
        for (const Trabalho& trabalho : trabalhos_concluidos) {
            std::cout << trabalho.nome << std::endl;
        }
        std::cout << " " << std::endl;


        /////////////////////////////
        //Exerc�cio de editor de texto

        std::cout << "4.a)Editor de texto: \n";
        TextEditor editor;
        editor.insert('H');
        editor.insert('e');
        editor.insert('l');
        editor.insert('l');
        editor.insert('o');
        editor.display(); // Sa�da: "Hello"

        editor.erase();
        editor.display(); // Sa�da: "Hell"

        editor.moveRight();
        editor.insert('!');
        editor.display(); // Sa�da: "Hell!"
        std::cout << " " << std::endl;


        LoadBalancer balancer(3);

        // Adiciona algumas tarefas
        std::cout << "4.b)Atribui��o de tasks para server:\n";
        balancer.addTask(1);
        balancer.addTask(2);
        balancer.addTask(3);
        balancer.addTask(4);
        balancer.addTask(5);
        balancer.addTask(6);
        balancer.addTask(7);
        balancer.addTask(8);
        balancer.addTask(9);
        std::cout << " " << std::endl;


        TextEditor2 editor2;

        std::cout << "4.c)Editor undo/endo:\n";
        editor2.insertText("Hello ");
        std::cout << editor2.getText() << std::endl; // Sa�da: "Hello "

        editor2.insertText("World!");
        std::cout << editor2.getText() << std::endl; // Sa�da: "Hello World!"

        editor2.deleteText(6);
        std::cout << editor2.getText() << std::endl; // Sa�da: "Hello "

        editor2.undo();
        std::cout << editor2.getText() << std::endl; // Sa�da: "Hello World!"

        editor2.redo();
        std::cout << editor2.getText() << std::endl; // Sa�da: "Hello "

        return 0;
    }