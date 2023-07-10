#pragma once
#include <type_traits>

struct AssertionContext
{
	const char* m_exprStr;
	const char* m_assertFailMsg;
	const char* m_file;
	const char* m_function;
	int         m_line;
};

class Assertion
{
public:
	typedef int(*AssertHandler)(std::unique_ptr<AssertionContext>& assertContext);

	Assertion(const char* file, const char* function, int line);

	// 为什么用 template ? 
	// 可以接受任何类型的指针变量。如果直接用 void* 做参数接受，使用者需要先对指针转型 (void*)(ptr)。
	template <typename T>
	int CheckPointer(const char* exprStr, T* exprResult)
	{
		return CheckPointerInternal(exprStr, (void*)(exprResult));
	}

	int CheckPointerInternal(const char* exprStr, void* exprResult);

	int MakeSure(const char* exprStr, bool exprResult, const char* reason);

	static int DefaultAssertionHandler(std::unique_ptr<AssertionContext>& assertContext);

	static void InstallAssertHandler(AssertHandler assertHandler)
	{
		s_assertHandler = assertHandler;
	}

private:
	std::unique_ptr<AssertionContext> m_assertionContext;

	inline static AssertHandler s_assertHandler{ nullptr };
};

#define __check_pointer_impl(pointer)                                                     \
{                                                                                         \
	int ret = Assertion(__FILE__, __FUNCTION__, __LINE__).CheckPointer(#pointer, pointer);\
    if (ret == 1)                                                                         \
    {                                                                                     \
    	_CrtDbgBreak();                                                                   \
    	std::abort();                                                                     \
    }                                                                                     \
}


#define __make_sure_impl(condition)                                                                                  \
{                                                                                                                    \
	int ret = Assertion(__FILE__, __FUNCTION__, __LINE__).MakeSure(#condition, condition, "unknown log verbosity");  \
	if (ret == 1)                                                                                                    \
	{                                                                                                                \
		_CrtDbgBreak();                                                                                              \
		std::abort();                                                                                                \
	}                                                                                                                \
}


#ifdef _DEBUG /* 只有在开发模式下（debug）才可以使用 assertion 功能。在 release 模式下，assertion 无效。 */
#  define __check_pointer __check_pointer_impl
#  define __make_sure     __make_sure_impl
#else
#  define __check_pointer     /* empty */
#  define __make_sure
#endif