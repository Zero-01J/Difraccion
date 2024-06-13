#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define D 1.895e-6
#define PI 3.141592653589793


double radianes_a_grados(double radianes) {
    return radianes * 180.0 / PI;
}


double angulo(double long_onda, int orden) {
    double seno = (orden * long_onda) / D;

    if (seno < -1.0 || seno > 1.0) {
        return -1.0;
    }
    return asin(seno);
}

int main() {
    int orden;

    double longitudes_onda[] = {410, 470, 545, 580, 605, 670};
    const char* colores[] = {"Violeta", "Azul", "Verde", "Amari", "Anaran", "Rojo"};
    int num_colores = sizeof(longitudes_onda) / sizeof(longitudes_onda[0]);


    printf("Introduce el orden de difraccion (m): ");
    scanf("%d", &orden);
    if (orden <= 0) {
        fprintf(stderr, "El orden de difraccion se considerara como un entero positivo .\n");
        return 1;
    }


    printf("Color\t\tLong de onda (nm)\tAngulo de difr (grad)\n");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < num_colores; i++) {
        double longitud_onda_nm = longitudes_onda[i];
        double longitud_onda_m = longitud_onda_nm * 1e-9;
        double angulo_radianes = angulo(longitud_onda_m, orden);
        if (angulo_radianes < 0) {
            printf("%s\t\t%.2f\t\t(No es posible calcular un angulo valido)\n", colores[i], longitud_onda_nm);
        } else {
            double angulo_grados = radianes_a_grados(angulo_radianes);
            printf("%s\t\t%.2f\t\t\t%.6f\n", colores[i], longitud_onda_nm, angulo_grados);
        }
    }

    return 0;
}
