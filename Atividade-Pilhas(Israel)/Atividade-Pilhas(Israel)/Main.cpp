#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <queue>
#include <list>

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
    bool is_operator(const std::string& token) {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }

    double avalia_expressao_npr(const std::string& expressao) {
        std::stack<double> pilha2;

        std::istringstream iss(expressao);
        std::string token;
        while (iss >> token) {
            if (!is_operator(token)) {
                // Se o token n�o � um operador, converte para double e empilha
                double numero;
                std::istringstream(token) >> numero;
                pilha2.push(numero);
            }
            else {
                // Se o token � um operador, desempilha dois n�meros, aplica a opera��o e empilha o resultado
                double op2 = pilha2.top();
                pilha2.pop();
                double op1 = pilha2.top();
                pilha2.pop();

                double resultado;
                if (token == "+") {
                    resultado = op1 + op2;
                }
                else if (token == "-") {
                    resultado = op1 - op2;
                }
                else if (token == "*") {
                    resultado = op1 * op2;
                }
                else if (token == "/") {
                    resultado = op1 / op2;
                }
                pilha2.push(resultado);
            }
        }

        // O resultado final � o elemento restante na pilha
        return pilha2.top();
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







    int main() 
    {
        std::string expressao;
        std::cout << "Digite a expressao a ser verificada: ";
        std::getline(std::cin, expressao);

        if (verifica_balanceamento(expressao)) {
            std::cout << "Os parenteses, colchetes e chaves estao balanceados." << std::endl;
        }
        else {
            std::cout << "Os parenteses, colchetes e chaves NAO estao balanceados." << std::endl;
        }


        //////////////////////////////////////////////////////////////////
        //Programa NPR
        std::string expressao2;
        std::cout << "Digite a expressao em Notacao Polonesa Reversa (NPR): ";
        std::getline(std::cin, expressao2);

        double resultado = avalia_expressao_npr(expressao2);
        std::cout << "O resultado da expressao e: " << resultado << std::endl;



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
        std::cout << "\nTrabalhos Concluidos:\n";
        for (const Trabalho& trabalho : trabalhos_concluidos) {
            std::cout << trabalho.nome << std::endl;
        }


        return 0;
    }