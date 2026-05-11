all:
	nvcc main.c utils.c gpu_kernel.cu -O3 -Xcompiler -fopenmp -o hash_cracker

clean:
	rm -f hash_cracker