# init #

## basic

NAME	:=glfw
VERS	:=y22m06d17
TYPE	:=lib # exe/lib/dll

## fdirs

ROOT	:=../..

DSRC	:=$(ROOT)/src
DOBJ	:=$(ROOT)/obj
DBIN	:=$(ROOT)/bin

## lists

LSRC	:=$(wildcard $(DSRC)/*.c $(DSRC)/**/*.c)
LOBJ	:=$(patsubst $(DSRC)/%.c,$(DOBJ)/%.o,$(LSRC))
LBIN	:=$(DBIN)/$(NAME).$(TYPE)

## build

CMAKER	:=gcc -c -o
CFLAGS	:= -std=c99 -w -O2
CFLAGS	+= -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
CFLAGS	+= 	-Wfatal-errors
CFLAGS	+= -Wextra
CFLAGS	+= -Wshadow
CFLAGS	+= -Wsign-compare
CFLAGS	+= -Wundef
CFLAGS	+= -Wwrite-strings
CFLAGS	+= -Wredundant-decls
CFLAGS	+= -Wdisabled-optimization
CFLAGS	+= -Wdouble-promotion
CFLAGS	+= -Wmissing-declarations
CFLAGS	+= -Wlogical-op
CFLAGS	+= -Wno-aggressive-loop-optimizations
CFLAGS	+= -Wdeclaration-after-statement
CFLAGS	+= -Wmissing-prototypes
CFLAGS	+= -Wnested-externs
CFLAGS	+= -Wstrict-prototypes
CFLAGS	+= -Wc++-compat
CFLAGS	+= -Wold-style-definition
LMAKER	:=ar rc
LFLAGS	:= -lm,dl,readline,Dwmapi

ifeq ($(TYPE),)
else ifeq ($(TYPE),exe)
else ifeq ($(TYPE),lib)
else ifeq ($(TYPE),dll)
endif

## shell

ifeq ($(OS),Windows_NT)

	RM	:=del /Q /F
	CP	:=copy /Y

	SLASH	:=\\

	DSRC	:=$(subst /,$(SLASH),$(DSRC))
	DOBJ	:=$(subst /,$(SLASH),$(DOBJ))
	DBIN	:=$(subst /,$(SLASH),$(DBIN))
	LSRC	:=$(subst /,$(SLASH),$(LSRC))
	LOBJ	:=$(subst /,$(SLASH),$(LOBJ))
	LBIN	:=$(subst /,$(SLASH),$(LBIN))

ifdef ComSpec
	SHELL	:=$(ComSpec)
endif
ifdef COMSPEC
	SHELL	:=$(ComSpec)
endif

else

	RM	:=rm -riv
	CP	:=cp -riv

endif

# work #

all:	build
#all

print:
	$(info ========)
	$(info basic)
	$(info ========)
	$(info [NAME]=$(NAME))
	$(info [VERS]=$(VERS))
	$(info ========)
	$(info fdirs)
	$(info ========)
	$(info [DSRC]=$(DSRC))
	$(info [DOBJ]=$(DOBJ))
	$(info [DBIN]=$(DBIN))
	$(info ========)
	$(info lists)
	$(info ========)
	$(info [LSRC]=$(LSRC))
	$(info [LOBJ]=$(LOBJ))
	$(info [LBIN]=$(LBIN))
	$(info ========)
	$(info build)
	$(info ========)
	$(info [CMAKER]=$(CMAKER))
	$(info [CFLAGS]=$(CFLAGS))
	$(info [LMAKER]=$(LMAKER))
	$(info [LFLAGS]=$(LFLAGS))
	$(info ========)
	$(info shell)
	$(info ========)
	$(info [SHELL]=$(SHELL))
	$(info [RM]=$(RM))
	$(info [CP]=$(CP))
	$(info ========)
	$(info done print)
#print

start:	build
	$(info ========)
	$(info done start)
#start

build:	$(LOBJ) $(LBIN)
	ranlib $(LBIN)
	$(info ========)
	$(info done build)
#build

clean:
	$(RM) $(LOBJ) $(LBIN)
	$(info ========)
	$(info done clean)
#clean

# rule #

$(DOBJ)$(SLASH)%.o:	$(DSRC)$(SLASH)%.c
	$(info [source]=$^;[object]=$@;)
	$(CMAKER) $@ $^ $(CFLAGS)
## object
$(DBIN)$(SLASH)%:	$(LOBJ)
	$(info [object]=$^;[binary]=$@;)
	$(LMAKER) $@ $^ $(LFLAGS)
## binary

# endf #