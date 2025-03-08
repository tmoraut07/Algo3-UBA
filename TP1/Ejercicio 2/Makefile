CC = g++
CPPFLAGS = -g -std=c++11 -Wall -O3
OUTPUT_PATH := bin

.PHONY: all valgrind gdb clean

all: benchmark

# tests
benchmark: app
	@time $(OUTPUT_PATH)/app < tests/test1.txt
	@time $(OUTPUT_PATH)/app < tests/test2.txt

# target para correr con valgrind
valgrind: app
	@valgrind --leak-check=full $(OUTPUT_PATH)/app < tests/test2.txt

# target para correr con gdb
gdb: app
	@gdb $(OUTPUT_PATH)/app

# target para correr con lldb (para macOS)
lldb: app
	@lldb $(OUTPUT_PATH)/app

# compilar app
app: main.cpp
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(CPPFLAGS) $< -o $(OUTPUT_PATH)/app

clean:
	rm -f *.o
	rm -rf $(OUTPUT_PATH)