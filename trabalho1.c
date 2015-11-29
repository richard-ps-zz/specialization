#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define VECSIZE 18
#define NTHREADS 4

int tmp[NTHREADS];
int vector_a[VECSIZE];
int vector_b[VECSIZE];
int sum = 0;

int slice = (VECSIZE/NTHREADS);
int rest = VECSIZE % NTHREADS;

struct config {
	int id;
};

void *func_thread(void *args) {
	struct config *cfg = args;

	int id = cfg->id;
    int begin = (id-1) * slice;
    int end = 0;

    if (id == NTHREADS) {
    	end = ((id-1) * slice) + slice-1 + rest;
    } else {
    	end = ((id-1) * slice) + slice-1;
    }

	for(int i=begin; i <= end; i++)
		tmp[id-1] += vector_a[i] * vector_b[i];

	char *msg = "Thread %d calculou de %d a %d: produto escalar parcial = %d\n";

	printf(msg, id, begin, end, tmp[id-1]);
	
	return 0;
}

void init_vector(int vector[], char *vector_name) {
	printf("%c = ", *vector_name);

	for (int i=0; i < VECSIZE-1; i++)  {
		vector[i] = rand() % 10;
		printf("%d,", vector[i]);
	}

	vector[VECSIZE-1] = rand() % 10;
	printf("%d\n", vector[VECSIZE-1]);

}

int main(int argc, char **argv) {
	srand(time(NULL));
	pthread_t threads[NTHREADS];

	if (NTHREADS > VECSIZE) {
		printf("Número de threads maior que o tamanho do vetor de dados!\n");
		return 1;
	} 

	init_vector(vector_a, "A");
	init_vector(vector_b, "B");

	struct config *cfg;

	for(int i=1; i < NTHREADS+1; i++) {
		cfg = malloc(sizeof(struct config));
        (*cfg).id = i;
		pthread_create(&threads[i-1], NULL, func_thread, (void*) cfg);
	}

	for(int i=0; i < NTHREADS; i++) {
		pthread_join(threads[i], NULL);
		sum += tmp[i];
	}

	printf("Produto escalar = %d\n", sum);

	return 0;
}

