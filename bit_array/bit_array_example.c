#include <stdio.h>
#include "bit_array.h"

void print_bits(uint8_t x)
{
    int i;
    for(i=8*sizeof(x)-1; i>=0; i--) {
        (x & (1 << i)) ? putchar('1') : putchar('0');
    }
    printf("\n");
}

int main(void) {
    bit_array *ba;
    ba = bit_array_create(8);
    printf("%d\n", bit_array_set(ba, 6));
    printf("%d\n", bit_array_set(ba, 6));
    // print_bits(ba->bits[0]);

    return 0;
}