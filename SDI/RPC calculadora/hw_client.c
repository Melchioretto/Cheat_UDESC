#include <stdio.h>
#include <rpc/rpc.h>

// Interface gerada pelo RPCGen a partir da IDL (hw.x) especificada
#include "hw.h"

int main (int argc, char *argv[]) {
	if (argc != 2) {
		printf("ERRO: ./client <hostname>\n");
		exit(1);
	}

	CLIENT *cl;
	cl = clnt_create(argv[1], PROG, VERS, "tcp");
	if (cl == NULL) {
		clnt_pcreateerror(argv[1]);
		exit(1);
	}

	int num1, num2;
	char op;

	while (scanf("%d %d %c", &num1, &num2, &op) != EOF) {
		struct calculadora params;
		params.num1 = num1;
		params.num2 = num2;
		int * resultado;

		switch (op) {
			case '+': resultado = somar_1(&params, cl); break;
			case '-': resultado = subtrair_1(&params, cl); break;
			case '/': resultado = dividir_1(&params, cl); break;
			case '*': resultado = multiplicar_1(&params, cl); break;
			default: printf("Operação inválida\n"); exit(1);
		}

		if (resultado == NULL) {
			clnt_perror(cl, argv[1]);
			exit(1);
		}
		printf("%d%c%d=%d\n", num1, op, num2, *resultado);
	}

	clnt_destroy(cl);
	return 0;
}
