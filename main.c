#include <stdio.h>

typedef struct {
    int ancho;
    int alto;
    int (*area)(struct Rectangulo*);
    int (*perimetro)(struct Rectangulo*);
} Rectangulo;

int area(Rectangulo *self) {
    return self->ancho * self->alto;
}

int perimetro(Rectangulo *self) {
    return 2 * (self->ancho + self->alto);
}


int main() {
    Rectangulo rect = {10, 5, area, perimetro};
    printf("Area: %d\n", rect.area(&rect));
    printf("Perimetro: %d\n", rect.perimetro(&rect));
    return 0;
}