PROG=proj 

.PATH: ${.CURDIR}/game_state/
.PATH: ${.CURDIR}/load/
.PATH: ${.CURDIR}/macros/
.PATH: ${.CURDIR}/devices/
.PATH: ${.CURDIR}/Images/


SRCS = proj.c game.c graphics.c keyboard.c menu.c view.c timer_proj.c level.c mouse.c pause.c gameover.c spawner.c rtc.c

#IPATHS=-I./libs/graph/ -I./libs/kbc/ -I./libs/rtc/ -I./libs/timer/ -I./libs/keyboard/ -I./libs/mouse/  -I./libs/mouse/ 

CFLAGS += -pedantic -D_LCOM_OPTIMIZED_ 


DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

.include <minix.lcom.mk>
