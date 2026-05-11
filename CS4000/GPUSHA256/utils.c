#include <string.h>

void ix_to_password(char *alphabet,
                    int len,
                    unsigned long long ix,
                    char *out)
{
    int base = strlen(alphabet);

    for (int i = len - 1; i >= 0; i--)
    {
        out[i] = alphabet[ix % base];
        ix /= base;
    }

    out[len] = '\0';
}