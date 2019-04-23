CC=gcc
CFLAGS=-Wall -g -O2

SpaceWar : principal.o view.o model.o controller.o xwc.o
	${CC} ${CFLAGS} -o $@ $^ -lm -lXpm -lX11 


ifndef NOXPM
principal.o : principal.c
	${CC} ${CFLAGS} -c $< -lm -lXpm -lX11 

view.o : view.c 
	${CC} ${CFLAGS} -c $< -lm -lXpm -lX11 

controller.o : controller.c
	${CC} ${CFLAGS} -c $< -lm -lXpm -lX11 

else
principal.o : 
	echo Este programa só funciona com a biblioteca Xpm instalada

view.o : 
	echo Este programa só funciona com a biblioteca Xpm instalada

controller.o :
	echo Este programa só funciona com a biblioteca Xpm instalada
endif

model.o : model.c 
	${CC} ${CFLAGS} -c $<

xwc.o : xwc.c

clean :
	rm *.o
