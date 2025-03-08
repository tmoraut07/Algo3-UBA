CC = g++
CPPFLAGS = -g -std=c++14 -O3
OUTPUT_PATH := bin

.PHONY: all valgrind gdb lldb clean

# target por defecto
all: clean app

# target para correr
run: app
	./$(OUTPUT_PATH)/app

# target para correr los tests con valgrind
valgrind: app
	@valgrind --leak-check=full $(OUTPUT_PATH)/app < tests/test1.txt
	@valgrind --leak-check=full $(OUTPUT_PATH)/app < tests/test2.txt
	
# target para correr con gdb
gdb: app
	@gdb $(OUTPUT_PATH)/app

# target para correr con lldb
lldb: app
	@lldb $(OUTPUT_PATH)/app

# target para correr los tests
tests: app
	@time $(OUTPUT_PATH)/app < tests/test1.txt
	@time $(OUTPUT_PATH)/app < tests/test2.txt
	
# compilacion
app: main.cpp									
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(CPPFLAGS) $< -o $(OUTPUT_PATH)/app

clean:
	rm -f *.o
	rm -rf $(OUTPUT_PATH)
