# mysql-pbkdf2
Exposes OpenSSL's PKCS5_PBKDF2_HMAC as a MySQL function. Currently this only uses SHA-512.

To build + install on Ubuntu:
	1. install `libmysqlclient-dev`, and `libssl-dev`
	2. run `build.sh`
	3. copy the resulting `libmysql-pbkdf2.so` to `/usr/lib/mysql/plugin`
	4. Run `CREATE FUNCTION PBKDF2_SHA512 RETURNS STRING SONAME 'libmysql-pbkdf2.so'` in your db;
