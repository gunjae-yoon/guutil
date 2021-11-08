#ifndef __guutil_version_h__
#define __guutil_version_h__

#define GUUT_MAJOR_VERSION		1
#define GUUT_MINOR_VERSION		0
#define GUUT_MICRO_VERSION		0
#define GUUT_REVISION			6747ac2
#define GUUT_REVISION_DATETIME	2021/11/08 14:09:54

#define QUOTE_(x)	#x
#define QUOTE(x)	QUOTE_(x)

#define GUUT_VERSION	QUOTE(GUUT_MAJOR_VERSION.GUUT_MINOR_VERSION.GUUT_MICRO_VERSION(Rev GUUT_REVISION - GUUT_REVISION_DATETIME))

#endif
