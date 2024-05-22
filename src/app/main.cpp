#include <guutil/thread/sharedmutex.h>
#include <guutil/memory/memorymanager.h>

#if defined(__linux__)
#include <unistd.h>
#endif

using namespace guutil;

int conditiontest(int argc, char* argv[]);
int sharedmutextest(int argc, char* argv[]);
int memorymanagertest(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	//conditiontest(argc, argv);
	//sharedmutextest(argc, argv);
	memorymanagertest(argc, argv);
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
			printf("[%5lu] %d\n", iTest, getpid());
		}
		usleep(1000*10);
	}
	delete sm;
	return 0;
}

int memorymanagertest(int argc, char* argv[]) {
	MemoryManager* mm = MemoryManager::createInstance(MemoryManagerKind::BUDDY);
	if(mm == NULL) {
		printf("ERROR: cannot create memory manager\n");
	}

	intptr_t arr[10] = {};
	int arridx = 0;
	arr[0] = (intptr_t)mm->alloc(256 * 1);
	arr[1] = (intptr_t)mm->alloc(256 * 2);
	arr[2] = (intptr_t)mm->alloc(256 * 3);
	arr[3] = (intptr_t)mm->alloc(256 * 4);
	arr[4] = (intptr_t)mm->alloc(256 * 5);
	arr[5] = (intptr_t)mm->alloc(256 * 6);
	arr[6] = (intptr_t)mm->alloc(256 * 7);
	arr[7] = (intptr_t)mm->alloc(256 * 8);
	arr[8] = (intptr_t)mm->alloc(256 * 9);
	arr[9] = (intptr_t)mm->alloc(256 * 10);

	for(size_t iArr = 0; iArr < 10; iArr++) {
		printf("[%2lu] address: %ld\n", iArr, arr[iArr]);
	}

	return 0;
}
