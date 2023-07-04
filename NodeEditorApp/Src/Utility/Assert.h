#pragma once
#define ASSERT(...) assert(__VA_ARGS__);
#define CHECK_PTR(ptr, errMsg) Q_ASSERT_X(ptr != nullptr, __FUNCTION__, errMsg)