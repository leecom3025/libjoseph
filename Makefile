CC=gcc
DEBUG = -g -DDEBUG
WARM = -Wall -Wno-unused-variable \
			 -Wno-unused-but-set-variable \
			 -Wno-format-contains-nul
ARCH = -DX86=1
ENABLE = -DJPERF_ENABLE=1
CFLAGS = $(ARCH) $(ENABLE) \
				 $(DEBUG) $(WARM)
LDFLAGS =
RM= rm -f
SRC = $(wildcard *.c) 
OBJ= $(patsubst %.c, %.o, $(SRC))
EXECUTABLE=libjoseph

.PHONY: clean $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	    $(CC) $(LDFLAGS) $(OBJ) -o $@
			$(RM) $(OBJ) *~
#			if [ -f /tmp/joseph ] ; \
			then \
				rm -rf  /tmp/joseph ; \
			fi;
			mkdir /tmp/joseph
			echo 123 > /tmp/joseph/int_test
			echo \"This is test message\" > /tmp/joseph/string_test
			echo 123.456 > /tmp/joseph/double_test
			echo 123.45 > /tmp/joseph/float_test

clean:
	     $(RM) $(OBJ) $(EXECUTABLE) *~
			 rm -rf /tmp/joseph
