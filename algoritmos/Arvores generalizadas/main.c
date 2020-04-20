#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MALLOC(t) (t*)malloc(sizeof(t))

typedef struct _funcionario{
	char *nome;
	float salario;
	char *nif;
}Funcionario;

typedef struct _tree{
	struct _tree* children[10];
	Funcionario *funcionario;	
}Tree;

Funcionario *cria_funcionario(char *n, float s, char *nifiscal)
{
	Funcionario *func = MALLOC(Funcionario);
	func->nome = strdup(n);
	func->nif = strdup(nifiscal);
	func->salario = s;
	return func;
}

Tree* insere_funcionario_aux(Tree* tree, Funcionario* func, char* path)
{
	if(tree==NULL)
	{
		tree = MALLOC(Tree);
		for(int i = 0; i < 10; i++) tree->children[i] = NULL;
		tree->funcionario = NULL;
	}
	if(*path == '\0'){
		tree->funcionario = func;
	}
	else{
		/* *path == '5'
			'5' - '0' = 5
			por ausa dos valores ASCII
			*/
		int pos = *path - '0';
		tree->children[pos] = insere_funcionario_aux(tree->children[pos], func, path+1);
	}
	return tree;
}

Tree* insere_funcionario(Tree* tree, Funcionario* func)
{
	return insere_funcionario_aux(tree, func, func->nif);
}

void mostra_funcionarios(Tree* tree){
	if(tree){
		if(tree->funcionario){
			printf("%20s %5.2f %8s\n", tree->funcionario->nome, 
			tree->funcionario->salario, 
			tree->funcionario->nif);
		}
		for(int i=0; i<10;i++){
			mostra_funcionarios(tree->children[i]);
		}
	}
}

int main()
{
	Tree *tree = NULL;

	tree = insere_funcionario(tree,
		cria_funcionario("Joaquim", 1003.3,"34872432"));
	tree = insere_funcionario(tree,
		cria_funcionario("Maria", 1003.3,"34172"));
	tree = insere_funcionario(tree,
		cria_funcionario("Madalena", 1003.3,"34172432"));
	tree = insere_funcionario(tree,
		cria_funcionario("Jose", 1003.3,"12345678"));
		mostra_funcionarios(tree);

	return 0;
}