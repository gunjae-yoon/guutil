#include <guutil/thread/sharedmutex.h>

#if defined(__linux__)
#include <unistd.h>
#endif

using namespace guutil;

int conditiontest(int argc, char* argv[]);
int sharedmutextest(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	conditiontest(argc, argv);
	//sharedmutextest(argc, argv);
	return 0;
}

Condition* cond;
Mutex* mut;
int32_t iValue;

void* producer(void* arg) {
	for(size_t iSize = 0; iSize < 1000; iSize++) {
		mut->lock();
		iValue++;
		printf("producer: %d\n", iValue);
		mut->unlock();
	}
}

void* consumer(void* arg) {
	for(size_t iSize = 0; iSize < 1000; iSize++) {
		mut->lock();
		iValue--;
		printf("consumer: %d\n", iValue);
		mut->unlock();
	}
}

int conditiontest(int argc, char* argv[]) {
	cond = Condition::createInstance();
	mut = Mutex::createInstance();
	iValue = 0;

	pthread_t threadP;
	pthread_t threadC;

	pthread_create(&threadP, NULL, producer, NULL);
	pthread_create(&threadC, NULL, consumer, NULL);


	usleep(1000 * 1000 * 10);

	return 0;
}

int sharedmutextest(int argc, char* argv[]) {
	SharedMutex* sm = SharedMutex::createInstance("test");
	for(size_t iTest = 0; iTest < 200; iTest++) {
		if(iTest % 100 == 0) {
			sm->lock();
		}
		else if(iTest % 100 == 99) {
			sm->unlock();
		}
		else {
			printf("[%5d] %d\n", iTest, getpid());
		}
		usleep(1000*10);
	}
	delete sm;
	return 0;
}
