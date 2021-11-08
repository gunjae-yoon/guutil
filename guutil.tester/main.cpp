#include <guutil/thread/sharedmutex.h>

#if defined(__linux__)
#include <unistd.h>
#endif

using namespace guutil;

int sharedmutextest(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	sharedmutextest(argc, argv);
	return 0;
}

int sharedmutextest(int argc, char* argv[]) {
	SharedMutex* sm = SharedMutex::createSharedMutex("test");
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
