#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>
bool PBKDF2_SHA512_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
	initid->max_length = 64; //64 bites for a SHA-512 checksum
	if (args->arg_count != 4)
	{
		strcpy(message,"PBKDF2_SHA512() requires three arguments");
		return 1;
	}

	if (args->arg_type[0] != STRING_RESULT)
	{
		strcpy(message,"PBKDF2_SHA512(): Bad argument #1, string expected.");
		return 1;
	}
	if (args->arg_type[1] != STRING_RESULT)
	{
		strcpy(message,"PBKDF2_SHA512(): Bad argument #2, string expected.");
		return 1;
	}
	if (args->arg_type[2] != INT_RESULT)
	{
		strcpy(message,"PBKDF2_SHA512(): Bad argument #3, int expected.");
		return 1;
	}
	return 0;
}

void PBKDF2_SHA512_deinit(UDF_INIT *initid)
{
}

void PBKDF2_SHA512_reset(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
}

void PBKDF2_SHA512_clear(UDF_INIT *initid, char *is_null, char *error)
{
}

void PBKDF2_SHA512_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
}

// PBKDF2_SHA512(string pass, string salt, int iterations)
char *PBKDF2_SHA512(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
	int hashStatus = PKCS5_PBKDF2_HMAC(
		(const unsigned char *)(args->args[0]),
		args->lengths[0],
		(const unsigned char *)(args->args[1]),
		args->lengths[1],
		*(int*) args->args[2],
		EVP_sha512(),
		64,
		result
	);
	if(hashStatus){
		*length = 64;
	}else{
		*error = 1;
	}
	return result;
}
