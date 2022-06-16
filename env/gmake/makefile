# init #

## basic

NAME	:=gametool
VERS	:=1x0x0

## fdirs

ROOT	:=../..

DSRC	:=$(ROOT)/src
DOBJ	:=$(ROOT)/obj
DBIN	:=$(ROOT)/bin

## lists

LSRC	:=$(wildcard $(DSRC)/*.cpp $(DSRC)/**/*.cpp)
LOBJ	:=$(patsubst $(DSRC)/%.cpp,$(DOBJ)/%.obj,$(LSRC))
LBIN	:=$(DBIN)/$(NAME).exe

## build

CMAKER	:=gcc -c -o
CFLAGS	:= -O2
LMAKER	:=gcc -o
LFLAGS	:=

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
	.$(SLASH)$(LBIN)
	$(info ========)
	$(info done start)
#start

build:	$(LOBJ) $(LBIN)
	$(info ========)
	$(info done build)
#build

clean:
	$(RM) $(LOBJ) $(LBIN)
	$(info ========)
	$(info done clean)
#clean

# rule #

$(DSRC)$(SLASH)%.cpp:	$(DSRC)$(SLASH)%.hpp
	$(info [header]=$^;[source]=$@;)
## source
$(DOBJ)$(SLASH)%.obj:	$(DSRC)$(SLASH)%.cpp
	$(info [source]=$^;[object]=$@;)
	$(CMAKER) $@ $^ $(CFLAGS)
## object
$(DBIN)$(SLASH)%.exe:	$(LOBJ)
	$(info [object]=$^;[binary]=$@;)
	$(LMAKER) $@ $^ $(LFLAGS)
## binary

# endf #