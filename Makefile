BUILD = build/main
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))

all: build/main

$(BUILD): $(OBJ)
	gcc $(OBJ) -Iinclude -o $(BUILD)

build/%.o: src/%.c
	gcc -c $< -Iinclude -o $@

cleanObj:
	rm $(OBJ)

cleanall:
	rm $(BUILD) $(OBJ) 
	
run:
	./$(BUILD) $(FLAGS)

.PHONY: $(BUILD) 