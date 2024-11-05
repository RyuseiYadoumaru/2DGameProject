#pragma once

#include <windows.h>


#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <unordered_map>
#include <string>
#include <string_view>

#include <memory>

#include <fstream>
#include <sstream>

using namespace std;

using TypeID = size_t;

#define  PROHIBIT_COPY_AND_ASSIN(CLASS)		 \
CLASS(const CLASS&) = delete;				 \
CLASS& operator=(const CLASS&) = delete;	 \

/**
 * ポインタをデリートする
 */
#define SAFE_DELETE(value)	\
if(value != nullptr){		\
	delete value;			\
	value = nullptr;		\
}							\

#define SAFE_DELETE_ARRAY(value)	\
if(value != NULL){					\
	delete[] value;					\
	value = NULL;					\
}									


/**
 * アラインメント
 */
#define ALIGN(N) _declspec(align(N))
#define ALIGN16 ALIGN(16)