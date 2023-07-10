#include "Stdafx.h"
#include "Assert.h"
/* ������������� main.cpp ģ�飬��ģ�����ñ������� include header �ļ���ʹ�� extern ���� */
extern QString s_applicationName;

int Assertion::CheckPointerInternal(const char* exprStr, void* exprResult)
{
	if (exprResult != nullptr)
	{
		return 0;
	}

	assert(s_assertHandler != nullptr && "Assert handler is nullptr");
	m_assertionContext->m_exprStr = exprStr;

	/* ��Ϣ��ʽ�� */
	static char msgBuf[512] = { 0 };
	::sprintf(msgBuf, ">>> Null pointer exception occurred. \nPointer name: %s\n Function: %s\n", m_assertionContext->m_exprStr, m_assertionContext->m_function);

	m_assertionContext->m_assertFailMsg = msgBuf;

	int ret = s_assertHandler(m_assertionContext);

	return ret;
}

int Assertion::MakeSureInternal(const char* exprStr, bool exprResult, const char* reason)
{
	if (exprResult)
	{
		return 0;
	}

	assert(s_assertHandler != nullptr && "Assert handler is nullptr");
	m_assertionContext->m_exprStr = exprStr;

	/* ��Ϣ��ʽ�� */
	static char msgBuf[512] = { 0 };
	::sprintf(msgBuf, ">>> Assertion failed because of %s.\nExpression: %s\n Function: %s\n", reason, m_assertionContext->m_exprStr, m_assertionContext->m_function);

	m_assertionContext->m_assertFailMsg = msgBuf;

	int ret = s_assertHandler(m_assertionContext);

	return ret;
}


int Assertion::DefaultAssertionHandler(std::unique_ptr<AssertionContext>& assertContext)
{
	/* ���ö��������ʽΪ ���� */
	int reportMode = ::_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
	::_CrtSetReportMode(_CRT_ERROR, reportMode);

	/* ���� crt assertion ������� */
	int ret = ::_CrtDbgReport(_CRT_ERROR, assertContext->m_file, assertContext->m_line, s_applicationName.toLatin1(), assertContext->m_assertFailMsg);

	/* 0��ʾ���ˡ���ֹ����1��ʾ���ˡ����ԡ� */
	return ret;
}

