PROG=proj 

.PATH: ${.CURDIR}/game_state/
.PATH: ${.CURDIR}/load/
.PATH: ${.CURDIR}/macros/
.PATH: ${.CURDIR}/devices/
.PATH: ${.CURDIR}/Images/


# source code files to be compiled
SRCS = proj.c game.c graphics.c keyboard.c menu.c view.c timer_proj.c level.c

#IPATHS=-I./libs/graph/ -I./libs/kbc/ -I./libs/rtc/ -I./libs/timer/ -I./libs/keyboard/ -I./libs/mouse/  -I./libs/mouse/ 
# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_ 


# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
