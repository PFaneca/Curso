CC :=gcc
CFLAGS := -lncurses -lpthread

all:JogoUI motor bot 

JogoUI: JogoUI.c
	$(CC) JogoUI.c -o JogoUI $(CFLAGS)

motor:motor.c
	$(CC) motor.c  -o motor -lpthread

bot:bot.c
	$(CC) bot.c -o bot 

	
clean:
	rm -f JogoUI motor bot variaveis.sh