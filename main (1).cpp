#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Aluno {
    string nome;
    int matricula;
    float notas[2];  
};

struct Disciplina {
    string nome;
    string codigo;
    string professorResponsavel;
};

struct Turma {
    Disciplina disciplina;
    int quantidadeAlunos;
    Aluno alunos[40];
    float notas[40][2];
};

const Aluno alunoFim = {"", 0, {0, 0}};
const Disciplina disciplinaFim = {"", "", ""};
const Turma turmaFim = {disciplinaFim, 0, {alunoFim}, {{0, 0}}};

void cadastrarAlunos(Aluno alunos[], int &quantidadeAlunos) {
    int i = quantidadeAlunos;
    char continuar;

    do {
        if (i >= 999) {
            cout << "Limite de alunos atingido." << endl;
            break;
        }

        cout << "Digite o nome do aluno(a): ";
        cin >> alunos[i].nome;

        if (alunos[i].nome.empty()) 
            break;

        alunos[i].matricula = i + 1; // Matrícula automática

        i++;

        cout << "Deseja adicionar outro aluno? (s/n): ";
        cin >> continuar;
    } while (continuar == 's' || continuar == 'S');

    quantidadeAlunos = i;
    alunos[i] = alunoFim;
}

void cadastrarDisciplina(Turma turmas[], int &quantidadeTurmas) {
    cout << "Digite o nome da disciplina: ";
    cin >> turmas[quantidadeTurmas].disciplina.nome;
    if (turmas[quantidadeTurmas].disciplina.nome.empty()) 
        return;

    cout << "Digite o nome do professor responsável: ";
    cin >> turmas[quantidadeTurmas].disciplina.professorResponsavel;

    cout << "Digite o código da disciplina: ";
    cin >> turmas[quantidadeTurmas].disciplina.codigo;

    turmas[quantidadeTurmas].quantidadeAlunos = 0;

    quantidadeTurmas++;
}

void exibirAlunos(const Aluno alunos[]) {
    int i = 0;
    while (alunos[i].nome != "") {
        cout << "Nome: " << alunos[i].nome << ", Matrícula: " << alunos[i].matricula << endl;
        i++;
    }
}

void exibirDisciplinas(const Turma turmas[], int quantidadeTurmas) {
    for (int i = 0; i < quantidadeTurmas; i++) {
        cout << "Nome da disciplina: " << turmas[i].disciplina.nome << endl;
        cout << "Professor responsável: " << turmas[i].disciplina.professorResponsavel << endl;
        cout << "Código da disciplina: " << turmas[i].disciplina.codigo << endl;
        cout << "Quantidade de alunos: " << turmas[i].quantidadeAlunos << endl;
    }
}

void adicionarAlunoDisciplina(Aluno alunos[], int quantidadeAlunos, Turma turmas[], int &quantidadeTurmas) {
    int indiceAluno, indiceDisciplina;

    cout << "Selecione o aluno para adicionar à disciplina:" << endl;
    exibirAlunos(alunos);
    cout << "Digite o número da matrícula do aluno: ";
    cin >> indiceAluno;

    if (indiceAluno < 1 || indiceAluno > quantidadeAlunos) {
        cout << "Aluno não encontrado." << endl;
        return;
    }

    cout << "Selecione a disciplina desejada:" << endl;
    exibirDisciplinas(turmas, quantidadeTurmas);
    cout << "Digite o índice da disciplina: ";
    cin >> indiceDisciplina;

    if (indiceDisciplina < 0 || indiceDisciplina >= quantidadeTurmas) {
        cout << "Disciplina não encontrada." << endl;
        return;
    }

    if (turmas[indiceDisciplina].quantidadeAlunos >= 40) {
        cout << "Turma cheia." << endl;
        return;
    }

    turmas[indiceDisciplina].alunos[turmas[indiceDisciplina].quantidadeAlunos] = alunos[indiceAluno - 1];
    turmas[indiceDisciplina].quantidadeAlunos++;
}

void registrarNotas(Turma turmas[], int quantidadeTurmas) {
    int indiceAluno, indiceDisciplina;
    float nota;
    int notaIndex;

    cout << "Selecione a disciplina para registrar as notas:" << endl;
    exibirDisciplinas(turmas, quantidadeTurmas);
    cout << "Digite o índice da disciplina: ";
    cin >> indiceDisciplina;

    if (indiceDisciplina < 0 || indiceDisciplina >= quantidadeTurmas) {
        cout << "Disciplina não encontrada." << endl;
        return;
    }

    cout << "Selecione o aluno para atribuir a nota:" << endl;
    for (int i = 0; i < turmas[indiceDisciplina].quantidadeAlunos; i++) {
        cout << "Índice: " << i << " - Nome: " << turmas[indiceDisciplina].alunos[i].nome << endl;
    }
    cout << "Digite o índice do aluno: ";
    cin >> indiceAluno;

    if (indiceAluno < 0 || indiceAluno >= turmas[indiceDisciplina].quantidadeAlunos) {
        cout << "Aluno não encontrado." << endl;
        return;
    }

    cout << "Digite a qual nota deseja atribuir (0 ou 1): ";
    cin >> notaIndex;

    if (notaIndex < 0 || notaIndex > 1) {
        cout << "Índice de nota inválido." << endl;
        return;
    }

    cout << "Digite a nota do aluno (0-10): ";
    cin >> nota;

    turmas[indiceDisciplina].notas[indiceAluno][notaIndex] = nota;
    cout << "Nota registrada com sucesso!" << endl;
}

void salvarDados(Aluno alunos[], int quantidadeAlunos, Turma turmas[], int quantidadeTurmas) {
    ofstream arquivoAlunos("alunos.txt");
    for (int i = 0; i < quantidadeAlunos; i++) {
        arquivoAlunos << alunos[i].nome << " " << alunos[i].matricula << " " << alunos[i].notas[0] << " " << alunos[i].notas[1] << endl;
    }
    arquivoAlunos.close();

    ofstream arquivoTurmas("turmas.txt");
    for (int i = 0; i < quantidadeTurmas; i++) {
        arquivoTurmas << turmas[i].disciplina.nome << " " << turmas[i].disciplina.codigo << " " << turmas[i].disciplina.professorResponsavel << " " << turmas[i].quantidadeAlunos << endl;
        for (int j = 0; j < turmas[i].quantidadeAlunos; j++) {
            arquivoTurmas << turmas[i].alunos[j].nome << " " << turmas[i].alunos[j].matricula << " " << turmas[i].notas[j][0] << " " << turmas[i].notas[j][1] << endl;
        }
    }
    arquivoTurmas.close();
}

void carregarDados(Aluno alunos[], int &quantidadeAlunos, Turma turmas[], int &quantidadeTurmas) {
    ifstream arquivoAlunos("alunos.txt");
    quantidadeAlunos = 0;
    while (arquivoAlunos >> alunos[quantidadeAlunos].nome >> alunos[quantidadeAlunos].matricula >> alunos[quantidadeAlunos].notas[0] >> alunos[quantidadeAlunos].notas[1]) {
        quantidadeAlunos++;
    }
    arquivoAlunos.close();

    ifstream arquivoTurmas("turmas.txt");
    quantidadeTurmas = 0;
    while (arquivoTurmas >> turmas[quantidadeTurmas].disciplina.nome >> turmas[quantidadeTurmas].disciplina.codigo >> turmas[quantidadeTurmas].disciplina.professorResponsavel >> turmas[quantidadeTurmas].quantidadeAlunos) {
        for (int j = 0; j < turmas[quantidadeTurmas].quantidadeAlunos; j++) {
            arquivoTurmas >> turmas[quantidadeTurmas].alunos[j].nome >> turmas[quantidadeTurmas].alunos[j].matricula >> turmas[quantidadeTurmas].notas[j][0] >> turmas[quantidadeTurmas].notas[j][1];
        }
        quantidadeTurmas++;
    }
    arquivoTurmas.close();
}

void exibirMenuPrincipal() {
    cout << "--------------------------------------" << endl;
    cout << "        SISTEMA ACADÊMICO            " << endl;
    cout << "--------------------------------------" << endl << endl;

    cout << "1. Gerenciar Alunos" << endl;
    cout << "2. Gerenciar Disciplinas" << endl;
    cout << "3. Gerenciar Turmas" << endl;
    cout << "4. Registrar Notas" << endl;
    cout << "5. Salvar e Sair" << endl << endl;

    cout << "--------------------------------------" << endl;
}

void exibirMenuAlunos() {
    cout << "--------------------------------------" << endl;
    cout << "        GERENCIAR ALUNOS             " << endl;
    cout << "--------------------------------------" << endl << endl;

    cout << "1. Cadastrar aluno" << endl;
    cout << "2. Listar alunos" << endl;
    cout << "3. Voltar" << endl << endl;

    cout << "--------------------------------------" << endl;
}

void exibirMenuDisciplinas() {
    cout << "--------------------------------------" << endl;
    cout << "     GERENCIAR DISCIPLINAS            " << endl;
    cout << "--------------------------------------" << endl << endl;

    cout << "1. Cadastrar disciplina" << endl;
    cout << "2. Listar disciplinas" << endl;
    cout << "3. Voltar" << endl << endl;

    cout << "--------------------------------------" << endl;
}

void exibirMenuTurmas() {
    cout << "--------------------------------------" << endl;
    cout << "        GERENCIAR TURMAS             " << endl;
    cout << "--------------------------------------" << endl << endl;

    cout << "1. Adicionar Aluno a uma Turma" << endl;
    cout << "2. Listar Turmas" << endl;
    cout << "3. Voltar" << endl << endl;

    cout << "--------------------------------------" << endl;
}

int main() {
    Aluno alunos[999];
    int quantidadeAlunos = 0;
    Turma turmas[100];
    int quantidadeTurmas = 0;

    carregarDados(alunos, quantidadeAlunos, turmas, quantidadeTurmas);

    int opcaoPrincipal, opcaoSecundaria;

    do {
        exibirMenuPrincipal();
        cout << "Digite a opção desejada: ";
        cin >> opcaoPrincipal;

        switch (opcaoPrincipal) {
            case 1:
                do {
                    exibirMenuAlunos();
                    cout << "Digite a opção desejada: ";
                    cin >> opcaoSecundaria;

                    switch (opcaoSecundaria) {
                        case 1:
                            cadastrarAlunos(alunos, quantidadeAlunos);
                            break;
                        case 2:
                            exibirAlunos(alunos);
                            break;
                        case 3:
                            break;
                        default:
                            cout << "Opção inválida!" << endl;
                    }
                } while (opcaoSecundaria != 3);
                break;

            case 2:
                do {
                    exibirMenuDisciplinas();
                    cout << "Digite a opção desejada: ";
                    cin >> opcaoSecundaria;

                    switch (opcaoSecundaria) {
                        case 1:
                            cadastrarDisciplina(turmas, quantidadeTurmas);
                            break;
                        case 2:
                            exibirDisciplinas(turmas, quantidadeTurmas);
                            break;
                        case 3:
                            break;
                        default:
                            cout << "Opção inválida!" << endl;
                    }
                } while (opcaoSecundaria != 3);
                break;

            case 3:
                do {
                    exibirMenuTurmas();
                    cout << "Digite a opção desejada: ";
                    cin >> opcaoSecundaria;

                    switch (opcaoSecundaria) {
                        case 1:
                            adicionarAlunoDisciplina(alunos, quantidadeAlunos, turmas, quantidadeTurmas);
                            break;
                        case 2:
                            exibirDisciplinas(turmas, quantidadeTurmas);
                            break;
                        case 3:
                            break;
                        default:
                            cout << "Opção inválida!" << endl;
                    }
                } while (opcaoSecundaria != 3);
                break;

            case 4:
                registrarNotas(turmas, quantidadeTurmas);
                break;

            case 5:
                salvarDados(alunos, quantidadeAlunos, turmas, quantidadeTurmas);
                cout << "Dados salvos. Encerrando o sistema..." << endl;
                break;

            default:
                cout << "Opção inválida!" << endl;
        }
    } while (opcaoPrincipal != 5);

    return 0;
}
