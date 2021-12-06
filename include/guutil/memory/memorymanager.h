#ifndef __guutil_memorymanager_h__
#define __guutil_memorymanager_h__

#include <stdint.h>
#include <guutil/dllexport.h>

#if defined(__linux__)
#include <cstddef>
#endif

namespace guutil {

	enum class DLL_EXPORT MemoryManagerKind {
		BUDDY,
	};

	class DLL_EXPORT MemoryManager {
	protected:
		MemoryManager(void);

	public:
		virtual ~MemoryManager(void);

		virtual bool initialize(void);

		virtual void* alloc(size_t aSize);
		virtual void* realloc(void* aMem, size_t aSize);
		virtual void free(void* aMem);

		virtual size_t getMaxSize(void);

		static MemoryManager* createInstance(MemoryManagerKind kind);
	};

}

#endif
