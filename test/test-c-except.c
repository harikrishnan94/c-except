#include <c-except/trycatch.h>
#include <stdio.h>

int main()
{
	CEXCEPT_TRY()
	{
		printf("Called1\n");
		CExceptThrow("Thrown 1");
		printf("Called2\n");
	}
	CEXCEPT_CATCH() { printf("Caught Exception: %s\n", exception_data->message); }
	CEXCEPT_FINALLY() { printf("Final\n"); }
	CEXCEPT_ENDTRY();

#ifdef CEXCEPT_BLOCKS
	printf("\n");

	CEXCEPT_TRY()
	{
		printf("Called3\n");
		CExceptThrow("Thrown 2");
		printf("Called4\n");
	}
	CEXCEPT_CATCH() { printf("Caught Exception: %s\n", exception_data->message); }
	CEXCEPT_ENDTRY();
#endif
}