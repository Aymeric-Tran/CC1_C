# -Wall: Enable all common warnings
# -Wextra: Enable extra warnings
# -pedantic: Enforce strict ANSI/ISO C compliance
# -g: Generate debug information
# -O2: Optimize the code for speed while maintaining reasonable compile times
# -D_FORTIFY_SOURCE=2: Enhance buffer overflow detection
# -fstack-protector-strong: Protect against stack buffer overflows

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -O2 -D_FORTIFY_SOURCE=2 -fstack-protector-strong 
SRC = main.c btree.c fp_open.c repl.c
TARGET = CC_1_DB
OBJS = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
