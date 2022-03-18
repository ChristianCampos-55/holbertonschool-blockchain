CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -ggdb3  -ftrapv -Wconversion -Wunreachable-code --std=gnu90
LIBS = -I. -lssl -lcrypto
T0 = sha256
T1 = ec_create
T2 = ec_to_pub
T3 = ec_from_pub
T4 = ec_save
T5 = ec_load
T6 = ec_sign
T7 = ec_verify
LIB = libhblk_crypto.a
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(LIB)

$(LIB): $(OBJ)
	ar ru $@ $^
	ranlib $@

$(T7): $(T7).c test/$(T7)-main.c $(T6).c $(T5).c $(T4).c $(T3).c $(T2).c $(T1).c provided/_print_hex_buffer.c
	$(CC) $(CFLAGS) -o $@  $^ $(LIBS)

$(T6): $(T6).c test/$(T6)-main.c $(T5).c $(T4).c $(T3).c $(T2).c $(T1).c provided/_print_hex_buffer.c
	$(CC) $(CFLAGS) -o $@  $^ $(LIBS)

$(T5): $(T5).c test/$(T5)-main.c $(T4).c $(T3).c $(T2).c $(T1).c provided/_print_hex_buffer.c
	$(CC) $(CFLAGS) -o $@  $^ $(LIBS)

$(T4): $(T4).c test/$(T4)-main.c $(T3).c $(T2).c $(T1).c provided/_print_hex_buffer.c
	$(CC) $(CFLAGS) -o $@  $^ $(LIBS)

$(T3): $(T3).c test/$(T3)-main.c $(T2).c $(T1).c provided/_print_hex_buffer.c
	$(CC) $(CFLAGS) -o $@  $^ $(LIBS)

$(T2): $(T2).c test/$(T2)-main.c $(T1).c provided/_print_hex_buffer.c
	$(CC) $(CFLAGS) -o $@  $^ $(LIBS)

$(T1): $(T1).c test/$(T1)-main.c provided/_print_hex_buffer.c
	$(CC) $(CFLAGS) -o $@  $^ $(LIBS)

$(T0): $(T0).c test/$(T0)-main.c provided/_print_hex_buffer.c
	$(CC) $(CFLAGS) -o $@  $^ $(LIBS)

.PHONY: clean, check

clean:
	rm $(OBJ) $(T0) $(T1) $(T2) $(T3) $(T4) $(T5) $(T6) $(T7)

check:
	betty *.c *.h
