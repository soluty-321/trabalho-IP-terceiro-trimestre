#include <stdio.h>
#include <string.h>
#include "monte.h"

static Carta carta(int id, const char *nome) {
    Carta c;
    memset(&c, 0, sizeof(c));
    c.id = id;
    snprintf(c.nome, sizeof(c.nome), "%s", nome);
    return c;
}

int main(void) {
    Monte m = { .tam = 0 };
    Carta out;

    if (enfileirar(&m, carta(1, "A")) != 0) return 1;
    if (enfileirar(&m, carta(2, "B")) != 0) return 2;
    if (desenfileirar(&m, &out) != 0) return 3;
    printf("%d %s\n", out.id, out.nome);
    if (desenfileirar(&m, &out) != 0) return 4;
    printf("%d %s\n", out.id, out.nome);
    printf("tam=%d\n", m.tam);

    return 0;
}
