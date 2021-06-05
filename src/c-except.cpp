#include <cstring>
#include <memory>

#include "c-except/trycatch.h"

void CExceptThrow(const char* message)
{
	const auto len = std::strlen(message);
	auto excpet_message = std::make_unique<char[]>(len + 1);

	std::memcpy(excpet_message.get(), message, len);
	throw CExceptExceptionData{ excpet_message.release() }; // NOLINT
}

#ifdef CEXCEPT_BLOCKS
struct scope_exit // NOLINT
{
	void (^block)(); // NOLINT
	~scope_exit() { block(); }
};

void CExceptTryCatchFinally(
	void (^try_block)(), void (^catch_block)(const CExceptExceptionData*), void (^finally_block)())
{
	scope_exit se{ finally_block };

	try
	{
		try_block();
	}
	catch (const CExceptExceptionData& except_data)
	{
		scope_exit se{ ^{
		  std::unique_ptr<char[]>(const_cast<char*>(except_data.message)); // NOLINT
		} };
		catch_block(&except_data);
	}
}
#elif defined(CEXCEPT_NESTED_FUNCTIONS)

template <typename Finalizer> struct scope_exit // NOLINT
{
	Finalizer finally; // NOLINT
	~scope_exit() { finally(); }
};

void CExceptTryCatchFinally(
	void (*try_block)(), void (*catch_block)(const CExceptExceptionData*), void (*finally_block)())
{
	scope_exit<decltype(finally_block)> se{ finally_block };

	try
	{
		try_block();
	}
	catch (const CExceptExceptionData& except_data)
	{
		auto deleter = [&] {
			std::unique_ptr<char[]>(const_cast<char*>(except_data.message)); // NOLINT
		};
		scope_exit<decltype(deleter)> se{ deleter };
		catch_block(&except_data);
	}
}
#endif