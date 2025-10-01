#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

void denaaaaani(unsigned char *ai, size_t len) {
    for (size_t i = 0; i < len; i++) {
        unsigned char c = ai[i];
        c = ((c >> 1) | (c << 7)) & 0xFF; // 1비트 오른쪽 회전
        ai[i] = c ^ 0x55;
    }
}

unsigned char *base64_decode(const char *input, int length, int *out_len) {
    BIO *b64, *bmem;
    unsigned char *buffer = (unsigned char *)malloc(length);
    memset(buffer, 0, length);

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL); // 개행 제거
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);

    *out_len = BIO_read(bmem, buffer, length);
    BIO_free_all(bmem);

    return buffer;
}

int main() {
    char b64_input[256];
    printf("Base64 encoded encrypted command? ");
    if (!fgets(b64_input, sizeof(b64_input), stdin)) {
        printf("Input error\n");
        return 1;
    }
    b64_input[strcspn(b64_input, "\n")] = 0;

    int decoded_len;
    unsigned char *decoded = base64_decode(b64_input, strlen(b64_input), &decoded_len);

    denaaaaani(decoded, decoded_len);
    decoded[decoded_len] = '\0';

    printf("Decrypted command: %s\n", decoded);

    system((char *)decoded);

    free(decoded);
    return 0;
}

