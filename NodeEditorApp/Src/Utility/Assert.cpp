#include "Stdafx.h"
#include "Assert.h"
/* 这个变量定义在 main.cpp 模块，跨模块引用变量而不 include header 文件，使用 extern 进行 */
extern QString s_applicationName;

int Assertion::CheckPointerInternal(const char* exprStr, void* exprResult)
{
	if (exprResult != nullptr)
	{
		return 0;
	}

	assert(s_assertHandler != nullptr && "Assert handler is nullptr");

	m_assertionContext->m_exprStr = exprStr;
	int ret = s_assertHandler(m_assertionContext);

	return ret;
}

int Assertion::DefaultAssertionHandler(std::unique_ptr<AssertionContext>& assertContext)
{
	/* 消息格式化 */
	static char msgBuf[512] = { 0 };
	::sprintf(msgBuf, ">>> Null pointer exception occurred. \nPointer name: %s\n Function: %s\n", assertContext->m_exprStr, assertContext->m_function);

	/* 设置断言输出形式为 窗口 */
	int reportMode = ::_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
	::_CrtSetReportMode(_CRT_ERROR, reportMode);

	/* 调用 crt assertion 窗口输出 */
	int ret = ::_CrtDbgReport(_CRT_ERROR, assertContext->m_file, assertContext->m_line, s_applicationName.toLatin1(), msgBuf);

	/* 0表示点了“中止”，1表示点了“重试” */
	return ret;
}

