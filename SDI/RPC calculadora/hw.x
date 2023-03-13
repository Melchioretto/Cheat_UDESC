struct calculadora {
	int num1;
	int num2;
};

program PROG {
	version VERS {
		int somar(calculadora) = 1;
		int subtrair(calculadora) = 2;
		int dividir(calculadora) = 3;
		int multiplicar(calculadora) = 4;
	} = 1;
} = 0x30009999;
