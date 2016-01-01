CC=gcc
DEBUG = -g -DDEBUG
WARM = -Wall -Wno-unused-variable \
			 -Wno-unused-but-set-variable \
			 -Wno-format-contains-nul
ARCH = -DX86=1
ENABLE = -DJPERF_ENABLE=1 #\
				 -DWITH_ZMQ=1
CFLAGS = $(ARCH) $(ENABLE) \
				 $(DEBUG) $(WARM)
#LDFLAGS = -lzmq
RM = rm -f
SRC = $(wildcard src/*.c) 
OBJ = $(patsubst %.c, %.o, $(SRC))
EXECUTABLE=libjoseph

.PHONY: all $(EXECUTABLE) clean dir

all: dir $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	    $(CC) $(OBJ) -o $@ $(LDFLAGS)
			$(RM) $(OBJ) *~

clean: 
	$(RM) $(OBJ) $(EXECUTABLE) *~
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
