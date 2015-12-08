#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

#define MAX_KEY_LENGTH 20
#define MAX_REGEX_LENGTH 16

int main(int argc, char **argv) {
	unsigned char digest[MD5_DIGEST_LENGTH];
	char digest_str[MD5_DIGEST_LENGTH * 2];
	
	char regex_str[MAX_REGEX_LENGTH];
	regex_t regex;
	int reti;

	char *key = argv[1];
	char *num_zeros = argv[2];
	char buffer[MAX_KEY_LENGTH];
	
	int i;
	int number = 1;

	MD5_CTX context;

	snprintf(regex_str, MAX_REGEX_LENGTH, "^0\\{%s\\}", num_zeros);

	reti = regcomp(&regex, regex_str, 0);

	if (reti) {
		printf("Something is wrong with your regex: %s", regex_str);
	}

	while (true) {
		snprintf(buffer, MAX_KEY_LENGTH, "%s%d", key, number);
		
		MD5_Init(&context);
		MD5_Update(&context, buffer, strlen(buffer));
		MD5_Final(digest, &context);

		for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
			sprintf(&digest_str[i * 2], "%02x", digest[i]);
		}
	
		reti = regexec(&regex, digest_str, 0, NULL, 0);
		if (!reti) {
			printf("Digest: %s\n", digest_str);
			break;
		}

		number++;
	}

	printf("Value: %d\n", number);

	regfree(&regex);

	return 0;
}
