CC=gcc

hellomake: tat.c 
	$(CC) -o tat tat.c -lX11 -lXtst `pkg-config --cflags --libs gtk+-2.0` -g -Wimplicit-function-declaration
