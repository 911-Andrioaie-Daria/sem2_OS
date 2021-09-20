// Assume a cigarette requires three ingredients to make and smoke: tobacco, paper, and matches. There are three smokers around a table, each of whom has an infinite supply of one of the three ingredients — one smoker has an infinite supply of tobacco, another has paper, and the third has matches.
//
// There is also a non-smoking agent who enables the smokers to make their cigarettes by arbitrarily (non-deterministically) selecting two of the supplies to place on the table. The smoker who has the third supply should remove the two items from the table, using them (along with their own supply) to make a cigarette, which they smoke for a while. Once the smoker has finished his cigarette, the agent places two new random items on the table. This process continues forever.


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

pthread_cond_t ready, consumed;
int tobacco = 0, matches = 0, paper = 0;
pthread_mutex_t mtx;

void* smoker1(void* a){    // smoker 1 has matches
	pthread_mutex_lock(&mtx);
	while(1){
		while(tobacco == 0 || paper == 0)
			pthread_cond_wait(&ready, &mtx);
		printf("Smoker 1 got paper and tobacco and smokes..............\n");
                sleep(1);
                printf("Smoker 1 finished\n\n");
		tobacco = 0;
		paper  = 0;
                pthread_cond_signal(&consumed);

	}
	pthread_mutex_unlock(&mtx);


	return NULL;
}

void* smoker2(void* a){    // smoker 2 has paper
	pthread_mutex_lock(&mtx);
        while(1){
                while(tobacco == 0 || matches == 0)
                        pthread_cond_wait(&ready, &mtx);
                printf("Smoker 2 got matches and tobacco and smokes..............\n");
                sleep(1);
                printf("Smoker 2 finished\n\n");
                tobacco = 0;
                matches = 0;
                pthread_cond_signal(&consumed);

        }
        pthread_mutex_unlock(&mtx);



	return NULL;
}

void* smoker3(void* a){    // smoker 3 has tobacco
	pthread_mutex_lock(&mtx);
        while(1){
                while(paper == 0 || matches == 0)
                        pthread_cond_wait(&ready, &mtx);
                printf("Smoker 3 got matches and paper and smokes..............\n");
                sleep(1);
                printf("Smoker 3 finished\n\n");
                paper = 0;
                matches = 0;
                pthread_cond_signal(&consumed);

        }
        pthread_mutex_unlock(&mtx);


	return NULL;
}

void* agent(void* a){
	pthread_mutex_lock(&mtx);
	while(1){
		while(tobacco == 1 || matches == 1 || paper == 1)
			pthread_cond_wait(&consumed, &mtx);

		int n = rand()%3+1;

		if(n==1){
			printf("Agent offered paper and tobacco.\n");
			tobacco = 1;
			paper = 1;
			pthread_cond_broadcast(&ready);

		}else if(n==2){
			printf("Agent offered matches and tobacco.\n");
			tobacco = 1;
			matches = 1;
			pthread_cond_broadcast(&ready);

		}else if(n==3){
			printf("Agent offered matches and paper.\n");
			matches = 1;
			paper = 1;
			pthread_cond_broadcast(&ready);
		}
	}
	pthread_mutex_unlock(&mtx);
}


int main(){
	pthread_t sm1, sm2, sm3, ag;

	pthread_cond_init(&consumed, NULL);
	pthread_cond_init(&ready, NULL);
	pthread_mutex_init(&mtx, NULL);


	pthread_create(&sm1, NULL, smoker1, NULL);
	pthread_create(&sm2, NULL, smoker2, NULL);
	pthread_create(&sm3, NULL, smoker3, NULL);
	pthread_create(&ag, NULL, agent, NULL);


	pthread_join(sm1, NULL);
	pthread_join(sm2, NULL);
	pthread_join(sm3, NULL);
	pthread_join(ag, NULL);

	pthread_cond_destroy(&ready);
	pthread_cond_destroy(&consumed);
	pthread_mutex_destroy(&mtx);

	return 0;

}
