#pragma once
#define ASSERT(...) assert(__VA_ARGS__);
#define CHECK_PTR(ptr, errMsg) Q_ASSERT_X(ptr != nullptr, __FUNCTION__, errMsg)


struct AssertionContext
{
	const char* m_exprStr;
	const char* m_file;
	const char* m_function;
	int         m_line;
};

class Assertion
{
public:
	typedef int(*AssertHandler)(std::unique_ptr<AssertionContext>& assertContext);



	Assertion(const char* file, const char* function, int line)
	{
		m_assertionContext = std::make_unique<AssertionContext>();

		m_assertionContext->m_file = file;
		m_assertionContext->m_function = function;
		m_assertionContext->m_line = line;
	}

	template <typename T>
	int CheckPointer(const char* exprStr, T* exprResult)
	{
		return CheckPointerInternal(exprStr, (void*)(exprResult));
	}

	int CheckPointerInternal(const char* exprStr, void* exprResult);

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

#ifdef _DEBUG /* 只有在开发模式下（debug）才可以使用 assertion 功能。在 release 模式下，assertion 无效。 */
#  define __check_pointer __check_pointer_impl
#else
#  define __check_pointer     /* empty */
#endif