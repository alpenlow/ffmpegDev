#############################################################
# Copyright (c) 2020, alpenlow
#############################################################

# ===============================================================
# 1. Global Variables
# ===============================================================
CC  = gcc
AR  = ar
CXX = g++
TOPDIR := $(shell pwd)


# ===============================================================
# 2. CFLAGS
# ===============================================================
W_CFLAGS +=  -Wreturn-type -Wsign-compare  -Wcomment -Wunused-variable -Wunused-parameter -Wunused-but-set-variable 
CFLAGS += -Wall -Wstrict-prototypes -fno-stack-protector -g $(W_CFLAGS) -std=gnu99 -fgnu89-inline 
CXXFLAGS += -Wall -std=c++11 $(W_CFLAGS)


# ===============================================================
# 3. Objects and Includes
# ===============================================================
INCS := inc \
	 += ffmpeg/libffmpeg_ubuntu_x86_64/include/

CDIR    := $(TOPDIR)/src
CSRCS   := $(shell find $(CDIR) -name "*.c")
CXXSRCS := $(shell find $(CDIR) -name "*.cpp")
COBJS   := $(CSRCS:.c=.o) 
CXXOBJS := $(CXXSRCS:.cpp=.ox)
OBJS    := $(COBJS)

TARDIR ?= .
TARGET ?= app


# ===============================================================
# 4. Rules
# ===============================================================
all: $(TARGET)

$(TARGET): $(COBJS) $(CXXOBJS)
	$(CC) -g  $(CFLAGS)  $^ -o $(TARDIR)/$@ $(LDFLAGS) $(LIBS)

.PHONY: all clean distclean 

%.o: %.c
	$(CC) -g $(CFLAGS) $(INCS:%='-I%') -MD -c $< -o $@
%.ox: %.cpp
	$(CXX) -g $(CXXFLAGS) $(INCS:%='-I%') -MD -c $< -o $@

DEPS := $(OBJS:.o=.d) $(CXXOBJS:.ox=.d)

clean:
	rm -f $(OBJS) $(CXXOBJS) $(DEPS)

distclean: clean
	find . -name "*.o" -exec rm -f {} \;
	find . -name "*.d" -exec rm -f {} \;
