# init #

## basic

NAME	:=gametool
VERS	:=1x0x0
TYPE	:=exe

## fdirs

ROOT	:=../..

DSRC	:=$(ROOT)/src
DOBJ	:=$(ROOT)/obj
DBIN	:=$(ROOT)/bin
DLIB	:=$(ROOT)/lib

## lists

LSRC	:=$(wildcard $(DSRC)/*.cpp $(DSRC)/**/*.cpp)
LOBJ	:=$(patsubst $(DSRC)/%.cpp,$(DOBJ)/%.obj,$(LSRC))
LBIN	:=$(DBIN)/$(NAME).$(TYPE)
LLIB	:=$(notdir $(wildcard $(DLIB)/*))
LLIB	:=$(filter-out qt6 glm imgui,$(LLIB))

## build

CMAKER	:=gcc -c -o
CFLAGS	:= -O2 -g -w -fno-threadsafe-statics
CFLAGS	+= $(addprefix -I$(DLIB)/,$(addsuffix /src,$(LLIB)))
CFLAGS	+= -D_GLFW_WIN32
LMAKER	:=gcc -o
LFLAGS	:= $(addprefix -L$(DLIB)/,$(addsuffix /bin,$(LLIB))) $(addprefix -l,$(LLIB))
LFLAGS	+= -l opengl32 -l gdi32 -l Dwmapi -l stdc++

ifeq ($(TYPE),)
else ifeq ($(TYPE),exe)
	CFLAGS	+= -DGT_BUILD_EXE
else ifeq ($(TYPE),lib)
	CFLAGS	+= -DGT_BUILD_LIB
else ifeq ($(TYPE),dll)
	CFLAGS	+= -DGT_BUILD_DLL
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

all:	$(addprefix all_,$(LLIB)) build
#all
all_%:	$(DLIB)/%/env/gmake
	$(MAKE) -C $^ all
#all_%

print:	$(addprefix print_,$(LLIB))
	$(info ========)
	$(info basic)
	$(info ========)
	$(info [NAME]=$(NAME))
	$(info [VERS]=$(VERS))
	$(info [TYPE]=$(TYPE))
	$(info ========)
	$(info fdirs)
	$(info ========)
	$(info [DSRC]=$(DSRC))
	$(info [DOBJ]=$(DOBJ))
	$(info [DBIN]=$(DBIN))
	$(info [DBIN]=$(DLIB))
	$(info ========)
	$(info lists)
	$(info ========)
	$(info [LSRC]=$(LSRC))
	$(info [LOBJ]=$(LOBJ))
	$(info [LBIN]=$(LBIN))
	$(info [LLIB]=$(LLIB))
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
print_%:	$(DLIB)/%/env/gmake
	$(MAKE) -C $^ print
#print_%

start:	build
	.$(SLASH)$(LBIN)
	$(info ========)
	$(info done start)
#start

build:	$(addprefix build_,$(LLIB)) $(LOBJ) $(LBIN)
	$(info ========)
	$(info done build)
#build
build_%:	$(DLIB)/%/env/gmake
	$(MAKE) -C $^ build
#build_%

clean:	$(addprefix clean_,$(LLIB)) $(LOBJ) $(LBIN)
	$(RM) $(LOBJ) $(LBIN)
	$(info ========)
	$(info done clean)
#clean
clean_%:	$(DLIB)/%/env/gmake
	$(MAKE) -C $^ clean
#clean_%

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