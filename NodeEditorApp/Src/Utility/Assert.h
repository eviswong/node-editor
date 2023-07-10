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

#define __is_implicitly_convertible_to_boolean(type)    \
    typename std::enable_if<std::is_convertible<type, bool>::value>::type* enabler = nullptr

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

	// 为什么用 template ? 
	// 可以接受任何类型的指针变量。如果直接用 void* 做参数接受，使用者需要先对指针转型 (void*)(ptr)。
	template <typename T>
	int CheckPointer(const char* exprStr, T* exprResult)
	{
		return CheckPointerInternal(exprStr, (void*)(exprResult));
	}

	// 作为模块提供者，你并不知道使用者会给api喂什么参数。对于 MakeSure() 来说， exprResult 可能会被如下使用
	// MakeSure(1 == 1)  # 接 bool  类型参数
	// 

	// 
	// std::string res = GetName();
	// MakeSure(res);     # 接 std::string 类型参数，用户可能想确保字符串不为空
	// 
	// 作为模块提供者，你必须保证 exprResult 可以被转换为 bool 类型。很明显，一个对象并不能直接被强转为 bool 类型。
	// 也就是说，你需要对这个 模板参数 T 做约束。
	// 
	// __is_implicitly_convertible_to_boolean() 用到 SFINAE, 一种类型参数约束技巧。看不懂没关系。
	//
	template <typename T>
	int MakeSure(const char* exprStr,T exprResult, const char* reason, __is_implicitly_convertible_to_boolean(T))
	{
		return MakeSureInternal(exprStr, (bool)exprResult, reason);
	}

	int CheckPointerInternal(const char* exprStr, void* exprResult);

	int MakeSureInternal(const char* exprStr, bool exprResult, const char* reason);

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