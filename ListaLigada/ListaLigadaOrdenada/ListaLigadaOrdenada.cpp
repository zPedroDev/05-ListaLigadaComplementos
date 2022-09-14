#include <iostream>
using namespace std;

// definicao de tipo
struct NO {
	int valor;
	NO* prox;
};

NO* primeiro = NULL;
NO* ultimo = NULL;


// headers
void menu();
void inicializar();
void exibirQuantidadeElementos();
void exibirElementos();
void inserirElemento();
void excluirElemento();
void buscarElemento();
NO* posicaoElemento(int numero);
//--------------------------


int main()
{
	menu();
}

void menu()
{
	int op = 0;
	while (op != 7) {
		system("cls"); // somente no windows
		cout << "Menu Lista Ligada";
		cout << endl << endl;
		cout << "1 - Inicializar Lista \n";
		cout << "2 - Exibir quantidade de elementos \n";
		cout << "3 - Exibir elementos \n";
		cout << "4 - Buscar elemento \n";
		cout << "5 - Inserir elemento \n";
		cout << "6 - Excluir elemento \n";
		cout << "7 - Sair \n\n";

		cout << "Opcao: ";
		cin >> op;

		switch (op)
		{
		case 1: inicializar();
			break;
		case 2: exibirQuantidadeElementos();
			break;
		case 3: exibirElementos();
			break;
		case 4: buscarElemento();
			break;
		case 5: inserirElemento();
			break;
		case 6: excluirElemento();
			break;
		case 7:
			return;
		default:
			break;
		}

		system("pause"); // somente no windows
	}
}

void inicializar()
{
	// se a lista já possuir elementos
// libera a memoria ocupada
	NO* aux = primeiro;
	while (aux != NULL) {
		NO* paraExcluir = aux;
		aux = aux->prox;
		free(paraExcluir);
	}

	primeiro = NULL;
	cout << "Lista inicializada \n";

}

void exibirQuantidadeElementos() {

	int nElementos = 0;
	NO* aux = primeiro;
	while (aux != NULL) {
		nElementos++;
		aux = aux->prox;
	}
	cout << "Quantidade de elementos: " << nElementos << endl;

}

void exibirElementos()
{
	if (primeiro == NULL) {
		cout << "Lista vazia \n";
		return;
	}
	else {
		cout << "Elementos: \n";
		NO* aux = primeiro;
		while (aux != NULL) {
			cout << aux->valor << endl;
			aux = aux->prox;
		}
	}
}

void inserirElemento()
{
	// aloca memoria dinamicamente para o novo elemento
	NO* novo = (NO*)malloc(sizeof(NO));
	if (novo == NULL) //verifica se tem espaço na memória
	{
		cout << "Sem espaco na memoria";
		return;
	}

	cout << "Digite o elemento: ";
	cin >> novo->valor;
	novo->prox = NULL;

	NO* encontrado = posicaoElemento(novo->valor);
	if (encontrado) {
		cout << "Nao e permitido a insercao de valores repetidos na lista.";
		inserirElemento();
	}

	if (primeiro == NULL)
	{
		primeiro = novo;
		ultimo = novo;
		cout << "Elemento inserido com sucesso!\n\n";
		return;
	}

	NO* valoresSeguintes;
	NO* aux = primeiro;

	if (novo->valor < primeiro->valor) {
		NO* atual = aux;
		NO* novaEstrutura = NULL;
		novaEstrutura = novo;
		novaEstrutura->prox = atual;
		aux = NULL;
		aux = novaEstrutura;
		primeiro = novo;
		cout << "Elemento inserido com sucesso!\n\n";
		return;
	}

	// procura o final da lista
	while (aux->prox != NULL) {
		if (novo->valor < aux->prox->valor) {
			valoresSeguintes = aux->prox;
			novo->prox = valoresSeguintes;
			aux->prox = novo;
			cout << "Elemento inserido com sucesso!\n\n";
			return;
		}
		aux = aux->prox;
	}
	aux->prox = novo;
	ultimo = novo;
}

void excluirElemento()
{
	int elemento = -1;
	NO* aux = primeiro;
	cout << "Insira o elemento a ser excluido: ";
	cin >> elemento;
	NO* posicao = posicaoElemento(elemento);

	if (elemento < primeiro->valor || elemento > ultimo->valor) {
		cout << "Elemento nao encontrado\n\n";
		return;
	}

	if (posicao == primeiro) {
		primeiro = primeiro->prox;
		free(posicao);
		cout << "Elemento excluido!\n";
		return;
	}

	if (posicao == ultimo) {
		while (aux != NULL) {
			if (aux->prox == posicao) {
				ultimo = aux;
				aux->prox = NULL;
				free(posicao);
				cout << "Elemento excluido!\n";
				return;
			}
			aux = aux->prox;
		}
		
	}

	while (aux != NULL) {
		if (aux->prox == posicao) {
			aux->prox = posicao->prox;
			free(posicao);
			cout << "Elemento excluido com sucesso!\n\n";
			return;
		}
		aux = aux->prox;
	}


}


void buscarElemento()
{
	int valor;
	cout << "Digite o elemento: ";
	cin >> valor;
	NO* elementoExistente = posicaoElemento(valor);

	if (valor < primeiro->valor || valor > ultimo->valor) {
		cout << "Valor nao incluso na lista\n";
		return;
	}

	if (valor == primeiro->valor || valor == ultimo->valor) {
		cout << "Elemento existente na lista";
		return;
	}
		
	if (elementoExistente) {
		cout << "Elemento Encontrado\n\n";
	} 
	else {
		cout << "Elemento nao Encontrado\n\n";
	}
	
}

NO* posicaoElemento(int numero)
{
	NO* aux = primeiro;

	if (primeiro->valor == numero) return primeiro;

	if (ultimo->valor == numero) return ultimo;

	while (aux != NULL) {
		if (aux->valor == numero)
		{
			break;
		}
		aux = aux->prox;
	}
	return aux;
}
