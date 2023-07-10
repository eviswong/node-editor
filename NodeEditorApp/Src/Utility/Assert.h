#pragma once
#include <type_traits>

template <typename T>
struct AddReference { using Result = T&; };

template <typename T>
struct AddReference<T&> { using Result = T&; };

template <typename From, typename To>
class ImplicitlyConvertible
{
private:
	using ReturnTypeSizeOfTwoBytes = char[2];
	using ReturnTypeSizeOfOneByte  = char;

	static typename AddReference<From>::Result MakeFrom();

	static char Helper(To);
	static ReturnTypeSizeOfTwoBytes& Helper(...);

public:
	static const bool Value = (sizeof(Helper(MakeFrom())) == 1);
};

template <bool Cond>
struct EnableIf;

template <>
struct EnableIf<true>
{
	using Result = void;
};

struct AssertionContext
{
	const char* m_exprStr;
	const char* m_assertFailMsg;
	const char* m_file;
	const char* m_function;
	int         m_line;
};

#define __is_implicitly_convertible_to_boolean(type)    \
    typename EnableIf<ImplicitlyConvertible<type, bool>::Value>::Result* enabler = nullptr

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

	// Ϊʲô�� template ? 
	// ���Խ����κ����͵�ָ����������ֱ���� void* ���������ܣ�ʹ������Ҫ�ȶ�ָ��ת�� (void*)(ptr)��
	template <typename T>
	int CheckPointer(const char* exprStr, T* exprResult)
	{
		return CheckPointerInternal(exprStr, (void*)(exprResult));
	}

	// ��Ϊģ���ṩ�ߣ��㲢��֪���Է������д��apiιʲô���������� MakeSure() ��˵�� exprResult ���ܻᱻ����ʹ��
	// MakeSure(1 == 1)  # �� bool  ���Ͳ���
	// 
	// const char* str = MakeStringBuffer();
	// MakeSure(str)      # �� const char* ���Ͳ���, �û�������ȷ���ַ�����Ϊ��
	// 
	// std::string res = GetName();
	// MakeSure(res);     # �� std::string ���Ͳ������û�������ȷ���ַ�����Ϊ��
	// 
	// ��Ϊģ���ṩ�ߣ�����뱣֤ exprResult ���Ա�ת��Ϊ bool ���͡������ԣ�һ�����󲢲���ֱ�ӱ�ǿתΪ bool ���͡�
	// Ҳ����˵������Ҫ����� ģ����� T ��Լ����
	// 
	// __is_implicitly_convertible_to_boolean() �õ� SFINAE, һ�����Ͳ���Լ�����ɡ�������û��ϵ��
	//
	template <typename T>
	int MakeSure(const char* exprStr, T exprResult, const char* reason, __is_implicitly_convertible_to_boolean(T)) 
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


#ifdef _DEBUG /* ֻ���ڿ���ģʽ�£�debug���ſ���ʹ�� assertion ���ܡ��� release ģʽ�£�assertion ��Ч�� */
#  define __check_pointer __check_pointer_impl
#  define __make_sure     __make_sure_impl
#else
#  define __check_pointer     /* empty */
#  define __make_sure
#endif