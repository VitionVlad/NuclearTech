CPP=g++
PROG_NAME=NuclearTechVk

SRC_FILES = main.cpp

all: $(PROG_NAME)

$(PROG_NAME): $(SRC_FILES)
	@$(CPP) $^ -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -g -O0 -o $@
	@echo "Run..."
	@./$(PROG_NAME)

clean:
	@rm -f *.o $(PROG_NAME)
	@echo "Clean done!"
