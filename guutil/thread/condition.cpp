#include <guutil/thread/condition_impl.h>

namespace guutil {

	Condition::Condition(void) {
	}

	Condition::~Condition(void) {
	}

	void Condition::init(void) {
	}

	void Condition::wait(int32_t usec) {
	}

	void Condition::signal(void) {
	}

	Condition* Condition::createInstance(void) {
		ConditionImpl* newInstance = new ConditionImpl();
		newInstance->init();
		return newInstance;
	}
}
