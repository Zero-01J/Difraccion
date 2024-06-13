#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define N_LINEAS 14300.0
#define PI 3.141592653589793

double grados_a_radianes(double grados) {
    return grados * PI / 180.0;
}


double calcular_longitud_onda(double angulo, int orden) {
    double d = 1.0 / N_LINEAS;
    double angulo_radianes = grados_a_radianes(angulo);
    double seno = sin(angulo_radianes);
    if (fabs(seno) < 1e-6) {
        return -1.0;
    }
    return (d * seno) / orden;
}


double calcular_ensanchamiento(double angulo, int orden, double delta_theta_grados) {
    double d = 1.0 / N_LINEAS;
    double angulo_radianes = grados_a_radianes(angulo);
    double delta_theta = grados_a_radianes(delta_theta_grados);
    double coseno = cos(angulo_radianes);
    if (fabs(coseno) < 1e-6) {
        return -1.0;
    }
    return (d * coseno * delta_theta) / orden;
}

int main() {
    int orden, num_maximos;
    double delta_theta_grados;


    printf("Orden de difraccion (m): ");
    scanf("%d", &orden);
    if (orden <= 0) {
        fprintf(stderr, "Orden de difraccion invalido. Debe ser mayor que 0.\n");
        return 1;
    }


    printf("Numero de angulos para el orden %d: ", orden);
    scanf("%d", &num_maximos);
    if (num_maximos <= 0) {
        fprintf(stderr, "Numero de angulos invalido. Debe ser mayor que 0.\n");
        return 1;
    }


    printf("Variacion angular estimada (delta_theta en grados): ");
    scanf("%lf", &delta_theta_grados);


    double* angulos = (double*)malloc(num_maximos * sizeof(double));
    double* longitudes_aproximadas = (double*)malloc(num_maximos * sizeof(double));
    if (angulos == NULL || longitudes_aproximadas == NULL) {
        fprintf(stderr, "Error al asignar memoria.\n");
        return 1;
    }

    for (int i = 0; i < num_maximos; i++) {
        printf("Angulo del maximo %d en grados: ", i + 1);
        scanf("%lf", &angulos[i]);
        printf("Longitud de onda aproximada del maximo %d en nm: ", i + 1);
        scanf("%lf", &longitudes_aproximadas[i]);
    }


    FILE *file = fopen("espectro_difraccion.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error abriendo el archivo\n");
        free(angulos);
        free(longitudes_aproximadas);
        return 1;
    }


    fprintf(file, "Orden: %d\n", orden);
    fprintf(file, "Angulo (grad)\tLong de onda cal (nm)\tLong de onda aprox (nm)\tEnsanchamiento (nm)\n");
    for (int i = 0; i < num_maximos; i++) {
        double lambda_metros = calcular_longitud_onda(angulos[i], orden);
        if (lambda_metros < 0) {
            fprintf(file, "%f\t(Valor invalido)\t%f\t(Valor invalido)\n", angulos[i], longitudes_aproximadas[i]);
        } else {
            double lambda_nm = lambda_metros * 1e9;
            double ensanchamiento_nm = calcular_ensanchamiento(angulos[i], orden, delta_theta_grados) * 1e9;
            fprintf(file, "%f\t%f\t%f\t%f\n", angulos[i], lambda_nm, longitudes_aproximadas[i], ensanchamiento_nm);
        }
    }

    fclose(file);
    free(angulos);
    free(longitudes_aproximadas);
    printf("Longitudes de onda y ensanchamiento calculados en 'espectro_difraccion.txt'\n");

    return 0;
}
