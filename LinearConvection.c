#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define FLOAT float
#define c 1.0

void initCondition( FLOAT * u, FLOAT * x0, int n_x );
void updateFunc( FLOAT * u, FLOAT * x0, int n_x, FLOAT dx, FLOAT dt);

int main(int argc, char **argv){

  // Archivo para imprimir las evolucion de u
  FILE *data = fopen("LinearConvection.dat", "w");
  
  // Numero de iteraciones en espacio y tiempo y sus respectivos dt, dx
  int n_x = atoi(argv[1]);
  int n_t = atoi(argv[2]);
  FLOAT dx = 2.0/(n_x-1);
  printf("%f\n",dx);
  FLOAT dt = 0.001;
    
  
  // Condicion inicial
  FLOAT *x0 = malloc(n_x*sizeof(FLOAT));
  int j;
  for( j = 0; j < n_x; j++){
    x0[j] = j*dx;
  }
 
  // Vector de evolucion de la velocidad u del fluido
  FLOAT *u = malloc(n_x *sizeof(FLOAT));
  int i;
  u = malloc(n_x*sizeof(FLOAT));
  for( j = 0; j < n_x; j++ ){
    u[j] = 1.0;
  }
  
  // Inicializa las condiciones iniciales en el vector u
  initCondition(u,x0,n_x);

  // Imprime el primer valor de u
  for( i = 0; i < n_x-1; i++){
    fprintf(data, "%f ", (float) u[i]);
  }
  fprintf(data, "%f\n", (float) u[i]);

  // Actualiza la funcion u
  for( j= 0; j < n_t; j++){
    updateFunc(u,x0,n_x,dx,dt);
    // Imprime la funcion u
    for( i = 0; i < n_x-1; i++){
      fprintf(data, "%f ", (float) u[i]);
    }
    fprintf(data, "%f\n", (float) u[i]);
   }
  return 0;
}


/*
 * Inicializa las condiciones iniciales
 */
void initCondition( FLOAT * u, FLOAT * x0, int n_x){
  
  int i;
  FLOAT limInf = 0.75;
  FLOAT limSup = 1.25;
  FLOAT val = 2.0;
  for( i = 0; i < n_x; i++){
    if( (x0[i] > limInf) && (x0[i] < limSup) ){
      u[i] = val;
    }
  }
}

void updateFunc( FLOAT * u, FLOAT *x0, int n_x, FLOAT dx, FLOAT dt ){
  // Copia los valores (sin apuntar) del vector u
  FLOAT * upast = malloc(n_x*sizeof(FLOAT));
  memcpy( upast, u, n_x*sizeof(FLOAT));
  int i;
  for( i = 1; i < n_x-1 ; i++){
    //printf("%f\n", upast[i]);
    u[i] = upast[i] - c*(dt/dx)*(upast[i] - upast[i-1]);
  }
  // Libera memoria
  free(upast);

}
