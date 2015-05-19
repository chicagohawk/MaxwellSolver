/* signature */
#ifndef SIG_POLYCLASS

  #include "polyclass.h"

#endif

#define SIG_POLYLIB "polylib.h"

/* ----------------------------------------------------------
   Polynomial library
   ---------------------------------------------------------- */

typedef POLYNOMIAL (*POLYPNT)[5];

/*
  buildpolylib

    build polynomial library by constructing the polynomials from coefficients

  Parameters:

    polylib : address (pointer) of pointer to a polynomial array (library)

    (*polylib)[n][i] = P^n_i as defined in the documentation

  Return Value:

    NONE

  Syntax:

    POLYPNT POLYLIB;

    buildpolylib( & POLYLIB );

    POLYLIB[p][i].print();

  Alert:
    
    Access to (e.g.) P^n_i = P^2_3 is invalid, although memory is

    allocated as [5][5] 2-dim polynomial array.
*/
void buildpolylib( POLYPNT * polylib )
{

  /* coefficient tables
     TAB_Pi : coefficients for p = i order accuracy */

  double TAB_P0[1][1] = { { 1. } };
  
  double TAB_P1[2][2] = { { 1. },
                          { 0., 1. } };
  
  double TAB_P2[3][3] = { { 1. },
                          { 0., 2.},
                          { 0., -1., 2.} };
  
  double TAB_P3[4][4] = { { 1. },
                          { 0., 3. },
                          { 0., -3./2., 9./2. },
                          { 0., 1., -9./2., 9./2. } };
  
  double TAB_P4[5][5] = { { 1. },
                          { 0., 4. },
                          { 0., -2., 8. },
                          { 0., 4./3., -8., 32./3. },
                          { 0., -1., 22./3., -16., 32./3. } };


  *polylib = new POLYNOMIAL[5][5]; 

  /* polynomial library construction */
  
  (*polylib)[0][0].set(TAB_P0[0], 0);

  for (int i=0; i<=1; i++)
    (*polylib)[1][i].set(TAB_P1[i], i);

  for (int i=0; i<=2; i++)
    (*polylib)[2][i].set(TAB_P2[i], i);

  for (int i=0; i<=3; i++)
    (*polylib)[3][i].set(TAB_P3[i], i);

  for (int i=0; i<=4; i++)
    (*polylib)[4][i].set(TAB_P4[i], i);

  return;

}



