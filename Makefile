###########################################################
#	Makefile for libjoseph :) 
#
#
#
###########################################################

CC := gcc
DEBUG := -g -DDEBUG
WARM := -Wall -Wno-unused-variable \
			 -Wno-unused-but-set-variable \
			 -Wno-format-contains-nul
ARCH := -DX86=1
ENABLE := -DJPERF_ENABLE=1 #\
				 -DWITH_ZMQ=1
J_CXXFLAGS := -I. -I/usr/local/include \
							-pthread -fPIC #-std=c++11
CFLAGS := $(ARCH) $(ENABLE) \
				 $(DEBUG) $(WARM) \
				 $(J_CXXFLAGS)
#LDFLAGS = -lzmq
RM := rm -f
SRC := $(wildcard src/*.c) 
OBJ := $(patsubst %.c, %.o, $(SRC))
LIBRARIES := libjoseph.so
EXECUTABLE := libjoseph_test

.PHONY: all $(EXECUTABLE) clean dir 
.PHONY: $(LIBRARIES) install

all: dir $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	    $(CC) $(OBJ) -o $@ $(LDFLAGS)
			$(RM) $(OBJ) *~

libjoseph.so: $(OBJ)
			$(CC) $(OBJ) -shared -o $@ $(LDFLAGS)
			$(RM) $(OBJ) *~

install: .libinstall .hdrinstall

.libinstall: $(LIBRARIES)
	install libjoseph.so /usr/local/lib/
	# -touch .libinstall

.hdrinstall: include/libjoseph.h
	install include/joseph_common.h /usr/local/include/
	install include/joseph_struct.h /usr/local/include/
	install include/joseph_utils.h /usr/local/include/
	install include/joseph_net.h /usr/local/include/
	install include/joseph_perf.h /usr/local/include/
	# -touch .hdrinstall

clean: 
	$(RM) $(OBJ) $(EXECUTABLE) $(LIBRARIES) *~
	rm -rf /tmp/joseph

dir: 
	if [ ! -d /tmp/joseph ] ; \
	then \
		mkdir /tmp/joseph ; \
	fi;
	echo 123 > /tmp/joseph/int_test
	echo \"This is test message\" > /tmp/joseph/string_test
	echo 123.456 > /tmp/joseph/double_test
	echo 123.45 > /tmp/joseph/float_test
