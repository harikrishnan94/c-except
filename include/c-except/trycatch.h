#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	const char* message;
} CExceptExceptionData;

void CExceptThrow(const char* message);

// Clang and BlockRuntime based Exceptions
#ifdef CEXCEPT_BLOCKS

void CExceptTryCatchFinally(
	void (^try_block)(), void (^catch_block)(const CExceptExceptionData*), void (^finally_block)());

#define CEXCEPT_TRY()                                                                              \
	do                                                                                             \
	{                                                                                              \
		void (^finally_block)() = ^{};                                                             \
	void (^try_block)() = ^

#define CEXCEPT_CATCH()                                                                            \
	;                                                                                              \
	void (^catch_block)() = ^(const CExceptExceptionData* exception_data)

#define CEXCEPT_FINALLY()                                                                          \
	;                                                                                              \
	finally_block = ^()

#define CEXCEPT_ENDTRY()                                                                           \
	;                                                                                              \
	CExceptTryCatchFinally(try_block, catch_block, finally_block);                                 \
	}                                                                                              \
	while (0)

#elif defined(CEXCEPT_NESTED_FUNCTIONS)
#endif

#ifdef __cplusplus
}
#endif