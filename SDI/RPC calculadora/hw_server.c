#include <rpc/rpc.h>

// Interface gerada pelo RPCGen a partir da IDL (hw.x) especificada
#include "hw.h"

int * somar_1_svc(struct calculadora * param, struct svc_req *req) {
     static int soma = 0;
     soma = param->num1 + param->num2;
     return (&soma);
}

int * subtrair_1_svc(struct calculadora * param, struct svc_req *req) {
     static int subtracao = 0;
     subtracao = param->num1 - param->num2;
     return (&subtracao);
}

int * dividir_1_svc(struct calculadora * param, struct svc_req *req) {
     static int divisao = 0;
     divisao = param->num1 / param->num2;
     return (&divisao);
}

int * multiplicar_1_svc(struct calculadora * param, struct svc_req *req) {
     static int multiplicacao = 0;
     multiplicacao = param->num1 * param->num2;
     return (&multiplicacao);
}
