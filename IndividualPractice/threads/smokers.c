// Assume a cigarette requires three ingredients to make and smoke: tobacco, paper, and matches. There are three smokers around a table, each of whom has an infinite supply of one of the three ingredients — one smoker has an infinite supply of tobacco, another has paper, and the third has matches.
//
// There is also a non-smoking agent who enables the smokers to make their cigarettes by arbitrarily (non-deterministically) selecting two of the supplies to place on the table. The smoker who has the third supply should remove the two items from the table, using them (along with their own supply) to make a cigarette, which they smoke for a while. Once the smoker has finished his cigarette, the agent places two new random items on the table. This process continues forever.


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

pthread_cond_t tobacco, paper, matches, finish;
pthread_mutex_t mtx;
//pthread_rwlock_t rwl;
char turn = 'a';

void* smoker1(void* a){    // smoker 1 has matches
	while(1){
		pthread_mutex_lock(&mtx);
		//		pthread_rwlock_rdlock(&rwl);

		//		if(turn == 's'){
		pthread_cond_wait(&paper, &mtx);
		pthread_cond_wait(&tobacco, &mtx);

		printf("Smoker 1 got paper and tobacco and smokes..............\n");
		sleep(3);
		printf("Smoker 1 finished\n");
		pthread_cond_signal(&finish);
		//			turn = 'a';
		//		}
		pthread_mutex_unlock(&mtx);
		//		pthread_rwlock_unlock(&rwl);
	}

	return NULL;
}

void* smoker2(void* a){    // smoker 2 has paper
	while(1){
		pthread_mutex_lock(&mtx);
		//		pthread_rwlock_rdlock(&rwl);

		//		if(turn == 's'){
		pthread_cond_wait(&tobacco, &mtx);
		pthread_cond_wait(&matches, &mtx);

		printf("Smoker 2 got matches and tobacco and smokes..............\n");
		sleep(3);
		printf("Smoker 2 finished\n");
		pthread_cond_signal(&finish);
		//			turn = 'a';
		//		}
		pthread_mutex_unlock(&mtx);
		//		pthread_rwlock_unlock(&rwl);
	}


	return NULL;
}

void* smoker3(void* a){    // smoker 3 has tobacco
	while(1){
		pthread_mutex_lock(&mtx);
		//		pthread_rwlock_rdlock(&rwl);
		//		if(turn == 's'){

		pthread_cond_wait(&matches, &mtx);
		pthread_cond_wait(&paper, &mtx);

		printf("Smoker 3 got matches and paper and smokes..............\n");
		sleep(3);
		printf("Smoker 3 finished\n");
		pthread_cond_signal(&finish);
		//			turn = 'a';
		//		}
		pthread_mutex_unlock(&mtx);
		//		pthread_rwlock_unlock(&rwl);
	}

	return NULL;
}

void* agent(void* a){
	while(1){

		pthread_mutex_lock(&mtx);
		//		pthread_rwlock_wrlock(&rwl);
		//		if(turn == 'a'){

		int n = rand()%3+1;
		if(n==1){
			printf("Agent offered tobacco and paper.\n");
			pthread_cond_signal(&paper);
			pthread_cond_signal(&tobacco);

		}else if(n==2){
			printf("Agent offered tobacco and matches.\n");
			pthread_cond_signal(&tobacco);
			pthread_cond_signal(&matches);

		}else if(n==3){
			printf("Agent offered matches and paper.\n");
			pthread_cond_signal(&matches);
			pthread_cond_signal(&paper);
		}
		pthread_cond_wait(&finish, &mtx);
		//			turn = 's';
		//		}
		pthread_mutex_unlock(&mtx);
		//		pthread_rwlock_unlock(&rwl);
	}
}


int main(){
	pthread_t sm1, sm2, sm3, ag;

	pthread_cond_init(&tobacco, NULL);
	pthread_cond_init(&paper, NULL);
	pthread_cond_init(&matches, NULL);
	pthread_cond_init(&finish, NULL);
	pthread_mutex_init(&mtx, NULL);
	//	pthread_rwlock_init(&rwl, NULL);	


	pthread_create(&sm1, NULL, smoker1, NULL);
	pthread_create(&sm2, NULL, smoker2, NULL);
	pthread_create(&sm3, NULL, smoker3, NULL);
	pthread_create(&ag, NULL, agent, NULL);


	pthread_join(sm1, NULL);
	pthread_join(sm2, NULL);
	pthread_join(sm3, NULL);
	pthread_join(ag, NULL);

	pthread_cond_destroy(&tobacco);
	pthread_cond_destroy(&paper);
	pthread_cond_destroy(&matches);
	pthread_cond_destroy(&finish);
	pthread_mutex_destroy(&mtx);
	//	pthread_rwlock_destroy(&rwl);

	return 0;

}
