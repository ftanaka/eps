#include <stdio.h>
#include <stdlib.h>

#include "input.h"

int le_dimensao ( FILE *arq ) {
   int dimensao;

   dimensao = -1;

   if ( arq != NULL ){
      fscanf ( arq, "%d", &dimensao );
      if ( dimensao <= 0 )
         fprintf ( stderr, "ERROR: invalid dimension value:le_dimensao\n" );
   } else
      fprintf ( stderr, "ERROR: can not read file.\n" );

   return dimensao;
}

double **destroi_matriz ( int dimensao, double **matriz ) {
   int i;

   if ( matriz != NULL ) {
      for ( i = 0; i < dimensao; i++ )
         if ( matriz[i] != NULL )
            free ( matriz[i] );
      free ( matriz );
   }

   return NULL;
}

double **cria_matriz ( FILE *arq, int dimensao ){
   int i, j, cont;
   double valor, **A;

   i = j = cont = -1;
   valor = -1;
   A   = NULL;

   if ( arq == NULL )
      fprintf ( stderr, "ERROR: can not read file: cria_matriz.\n" );
   else {
      A = malloc ( dimensao * sizeof ( double ** ) );
      if ( A == NULL )
         fprintf ( stderr, "ERROR: malloc (1) failed: cria_matriz\n" );
      else {
         for ( cont = 0; cont < dimensao; cont++ ) {
            A[cont] = malloc ( dimensao * sizeof ( double * ) );
            if ( A[cont] == NULL ) {
               fprintf ( stderr, "ERROR: malloc (2) failed: cria_matriz\n" );
               A = destroi_matriz ( dimensao, A );
            }
         }
      }

      for ( cont = 0; cont < dimensao * dimensao; cont ++ ) {
         fscanf ( arq, "%d %d %lf", &i, &j, &valor );
         
         if ( i < 0 || i >= dimensao || j < 0 || j >= dimensao ) {
            fprintf ( stderr, "ERROR: invalid input: cria_matriz\n" );
            A = destroi_matriz ( dimensao, A );
            break;
         } else
            A[i][j] = valor;
      }
   }

   return A;
}

void imprime_matriz ( int dimensao, double **matriz ) {
   int i, j;

   for ( i = 0; i < dimensao; i++ ) {
      for ( j = 0; j < dimensao; j++ )
         fprintf ( stdout, "%f ", matriz[i][j] );
      fprintf ( stdout, "\n" );
   }
}

double *destroi_b ( double *b ) {
   if ( b != NULL )
      free ( b );

   return NULL;
}

double *cria_b ( FILE *arq, int dimensao ) {
   int cont;
   double valor, *b;

   cont = -1;
   valor = -1;
   b = NULL;

   if ( arq == NULL )
      fprintf ( stderr, "ERROR: can not read file: cria_b\n" );
   else {
      b = malloc ( dimensao * sizeof ( double ) );
      if ( b == NULL ) {
         fprintf ( stderr, "ERROR: malloc failed: cria_b\n" );
         b = destroi_b ( b );
      } else {
         for ( cont = 0; cont < dimensao; cont++ ) {
            fscanf ( arq, "%lf", &valor );
            b[cont] = valor;
         }
      }
   }

   return b;
}

void imprime_b ( int dimensao, double *b ) {
   int i;

   for ( i = 0; i < dimensao; i++ )
      fprintf ( stdout, "%f\n", b[i] );
}
