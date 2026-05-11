NVCC = nvcc
SRC = src
INC = include
BUILD = build

all:
	mkdir -p build
	$(NVCC) -I$(INC) $(SRC)/main.cu $(SRC)/kernel.cu $(SRC)/util.cu -o build/cracker

clean:
	rm -rf build/*