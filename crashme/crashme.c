/*

  Example code to show a behaviour of openssl where missing
  error checks could result in crashes.

  compile with
    gcc crashme.c -o crashme -lssl -lcrypto

*/

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	unsigned char buf[4096];
	FILE *f;
	int r;
	SSL_CTX *sctx;
	SSL *server;
	BIO *sinbio,*soutbio;

	SSL_library_init();
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();

	if(!(sctx = SSL_CTX_new(TLSv1_method()))) return 1;
	if(!(server = SSL_new(sctx)) ) return 1;

	sinbio=BIO_new(BIO_s_mem());
	soutbio=BIO_new(BIO_s_mem());
	SSL_set_bio(server,sinbio,soutbio);
	SSL_set_accept_state(server);

	f = fopen("ssl3-packet", "rb");
	r = fread(buf,1,4096,f);
	BIO_write(sinbio,buf,r);

	SSL_do_handshake(server);
	ERR_print_errors_fp(stderr);

	SSL_do_handshake(server);

	return 0;
}
