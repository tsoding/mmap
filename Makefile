EXE=01-allocating-memory 02-reading-files 03-ipc 04-exec 04-payload

.PHONY: all
all: $(EXE)

04-payload: 04-payload.asm
	nasm -o 04-payload 04-payload.asm

%: %.c
	gcc -Wall -ggdb -o $@ $<

.PHONY: clean
clean:
	rm -rfv $(EXE)
