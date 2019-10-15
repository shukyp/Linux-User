#
# How depedency rule components are referred
#
# all: a.cpp b.cpp
# $@ mean to 'all' (the target)
# $< a.cpp
# $^ a.cpp b.cpp
#
# ------------------------
#
# debug make file 
# make --debug[=flags]
#	no flags is like using -d
#	b basic debugging
# 	v verbose basic debugging
#	i show implicit rules
#	j detailed debug info
#	m show info while remaking makefile
#
# see: https://linux.die.net/man/1/make
#
#

# Variable

# true | false
dbginfo = true

ifeq ($(dbginfo),true)
	DBG=-ggdb
else
	DBG= 
endif

CC_FLAG := -v -Wall $(DBG) -c
CC_TOOL := gcc

MAIN_INCL  := 	./incl/
INFRA_INCL := 	./us_infra/
INCL_PATH  := 	-I$(MAIN_INCL) -I$(INFRA_INCL)

EXEC_DIR := 	obj

#LIBS :=
#LPATH :=

MAIN_SRC  := 	.
INFRA_SRC := 	./us_infra

HDRS := 	$(wildcard $(MAIN_INCL)/*.h $(INFRA_INCL)/*.h)
SRCS := 	$(wildcard $(MAIN_SRC)/*.c $(INFRA_SRC)/*.c)
OBJS := 	$(SRCS:.c=.o)

EXEC := 	./$(EXEC_DIR)/exec

.PHONY: all 

# main target
all: $(EXEC_DIR) $(EXEC)

$(EXEC_DIR):
	@if [ ! -d ./$(EXEC_DIR) ]; then mkdir ./$(EXEC_DIR); fi;

$(EXEC): $(OBJS) Makefile
	$(CC_TOOL) $(OBJS) -o $(EXEC)

# target: header files dependecny
.c.o: *.c $(HDRS) Makefile
	$(CC_TOOL) $(CC_FLAG) $(INCL_PATH) $< -o $@

.PHONY: clean 
clean:
	rm $(OBJS)
	rm $(EXEC)



