CC = gcc
CFLAGS = -Wall -Wextra -I./pt -I./pt/parse -fPIC
LDFLAGS = -shared

SRCS = $(shell find src -name "*.c")
OBJS = $(SRCS:.c=.o)

LIB_NAME = libpt
OUT_DIR = out
LOCAL_INC = /usr/local/include/pt
LOCAL_LIB = /usr/local/lib

all: prep static dynamic clean_objs

prep:
	mkdir -p out/lib
	mkdir -p out/include/pt/parse

static: $(OBJS)
	ar rcs out/lib/$(LIB_NAME).a $(OBJS)

dynamic: $(OBJS)
	$(CC) $(LDFLAGS) -o out/lib/$(LIB_NAME).so $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean_objs:
	rm -f $(OBJS)

install: all
	@echo "[*] Installing to system directories..."
	mkdir -p $(LOCAL_INC)/parse
	cp pt/*.h $(LOCAL_INC)/
	cp pt/parse/*.h $(LOCAL_INC)/parse/
	cp out/lib/$(LIB_NAME).a $(LOCAL_LIB)/
	cp out/lib/$(LIB_NAME).so $(LOCAL_LIB)/
	@echo "[+] Installation complete. Run 'ldconfig' to refresh dynamic linker cache."

clean:
	rm -rf out $(OBJS)

.PHONY: all prep static dynamic clean clean_objs install
