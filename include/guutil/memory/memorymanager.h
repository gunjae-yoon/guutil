#ifndef __guutil_memorymanager_h__
#define __guutil_memorymanager_h__

namespace guutil {

	class MemoryManager {
	public:
		virtual ~MemoryManager(void);

		virtual void* alloc(size_t aSize) = 0;
		virtual void free(void* ptr) = 0;
	};

}

#endif
