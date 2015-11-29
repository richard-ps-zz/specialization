#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define VECSIZE 16
#define NTHREADS 4

int tmp[NTHREADS];
int vector_a[VECSIZE];
int vector_b[VECSIZE];
int sum = 0;

struct config {
	int id;
    int begin;
    int end;
};

void *func_thread(void *args) {
	struct config *cfg = args;

	for(int i=cfg->begin; i <= cfg->end; i++)
		tmp[cfg->id-1] += vector_a[i] * vector_b[i];

	char *msg = "Thread %d calculou de %d a %d: produto escalar parcial = %d\n";

	printf(msg, cfg->id, cfg->begin, cfg->end, tmp[cfg->id-1]);
	
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

	int rest = VECSIZE % NTHREADS;
	int slice = (VECSIZE/NTHREADS);

	init_vector(vector_a, "A");
	init_vector(vector_b, "B");

	struct config *cfg;

	for(int i=1; i < NTHREADS+1; i++) {
		cfg = malloc(sizeof(struct config));
        (*cfg).id = i;
        (*cfg).begin = (i-1) * slice;
        (*cfg).end = ((i-1) * slice) + slice-1;

		pthread_create(&threads[i-1], NULL, func_thread, (void *)cfg);
	}

	for(int i=0; i < NTHREADS; i++) {
		pthread_join(threads[i], NULL);
		sum += tmp[i];
	}

	printf("Produto escalar = %d\n", sum);

	return 0;
}

