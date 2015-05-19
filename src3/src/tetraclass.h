/* signature */
#ifndef SIG_POLYVECTOR

  #include "polyvector.h"

#endif

#define SIG_TETRACLASS "tetraclass.h"

/* ----------------------------------------------
   Tetrahedron class
   
     geometric properties of individual tetrahedron

   Functional:

     1. tetra volume       
     2. areas (twiced)
     3. coordinate matrix & F matrix
     4. tangent edge vector (not normalized)
     5. edge lengths
     6. tetrahedron type
     7. unit normal outward vectors
     8. zero-order basis vectors
     9. curl of zero basis vectors

   Syntax:

     TETRA tet;

     tet.definematrix( & mesh.nodecords, mesh.elevertex.at(0) );

     tet.tanvecgen( & mesh.nodecords, mesh.elevertex.at(0) );

     tet.areasgen();

     tet.unitnormvecgen();

     tet.zerobasisgen();

     tet.zerobasiscurlgen();
   ---------------------------------------------- */

class TETRA{

  public:

    /* ------ data storage ------ */

    // matrix A
    gsl_matrix *A;

    // matrix F
    gsl_matrix *F;

    // tetrahedron volume
    double volume;

    // tetrahedron type ( 1 or -1 )
    int type;

    // tangent vectors (not normalized)
    vector<double> tanvec [4][4];

    // tangent vector lengths
    double tanveclen [4][4];

    // twice the opposite triangle areas
    vector<double> areas;

    // unit outward normal vectors
    vector<double> unitnormvec [4];

    // zero-order basis vectors
    COMPVEC zerobasis [4][4];

    // curl of zero-order basis vectors
    COMPVEC zerobasiscurl [4][4];

    /* ------ tools ------ */

    // compute A & F, set volume and type
    void definematrix( vector<double*> *, int * );

    // generate tangent vectors
    void tanvecgen( vector<double*> *, int * );

    // generate triangle areas
    void areasgen();

    // generate unit normal vectors
    void unitnormvecgen();

    // generate zero-order basis vectors
    void zerobasisgen();

    // generate curl of zero-order basis vectors
    void zerobasiscurlgen();

  private:

    // tetrahedron rotational index
    static const int tetra_index [4][4];

    // cross product
    vector<double> crossproduct( vector<double>, vector<double> );

    // vector L-2 norm
    double vecnorm( vector<double> );

};


/*
  TETRA::tetra_index
    define tetrahedron rotational index
*/
const int TETRA::tetra_index [4][4] ={ {0, 1, 2, 3},
                                       {1, 2, 3, 0},
                                       {2, 3, 0, 1},
                                       {3, 0, 1, 2} };


/*
  TETRA::definematrix
    1. compute matrices A & F
    2. set tetra volume
    3. set tetra type
  Parameters:
    nodecords_pnt : pointer to MESH::nodecords
    vertices : an entry in MESH::elevertex
  Return Value:
    NONE
  Syntax:
    TETRA ele;
    ele.definematrix( & mesh.nodecords, mesh.elevertex.at(0) );
*/
void TETRA::definematrix( vector<double*> * nodecords_pnt, int* vertices )
{

  int signum;
  
  double detA;

  A = gsl_matrix_calloc( 4, 4 );

  F = gsl_matrix_calloc( 4, 4 );

  for( int i=0; i<4; i++ ){

    gsl_matrix_set( A, 0, i, 1.0 );

  }// end for

  for( int i=0; i<4; i++ ){

    for( int j=0; j<3; j++ ){

      gsl_matrix_set( A, j+1, i, (*nodecords_pnt).at( vertices[i] ) [j] );

    }// end for j

  }// end for i

  // set tetra volume and type
  gsl_matrix* Alu = gsl_matrix_calloc( 4, 4 );

  gsl_matrix_memcpy( Alu, A );

  gsl_permutation* p = gsl_permutation_alloc( 4 );

  gsl_linalg_LU_decomp( Alu, p, &signum );

  detA = gsl_linalg_LU_det( Alu, signum );

  if( detA > 0 )  type = 1;

  else type = -1;

  volume = abs( detA ) / 6.;

  gsl_matrix_free( Alu );

  gsl_permutation_free( p );

  gsl_matrix_memcpy( F, A );

  gsl_matrix_scale( F, 1./detA );

}


/*
  TETRA::tanvecgen
    1. generate tangent vectors (not normalized), fill in TETRA::tanvec
    2. generate tangent vector lengths, fill in tanveclen
  Parameters:
    nodecords_pnt : pointer to MESH::nodecords
    vertices : an entry in MESH::elevertex
  Return Value:
    NONE
  Syntax:
    TETRA::tanvecgen( & mesh.nodecords, mesh.elevertex.at(i) );
    TETRA::tanvec[i][j].at(k)
*/
void TETRA::tanvecgen( vector<double*> * nodecords_pnt, int* vertices)
{

  int indI, indJ;

  double *xi, *xj;

  for(int i=0; i<4; i++){

    indI = vertices[i];

    xi = (*nodecords_pnt).at(indI);

    for(int j=0; j<4; j++){

      indJ = vertices[j];

      xj = (*nodecords_pnt).at(indJ);

      for(int k=0; k<3; k++){

        tanvec[i][j].push_back( xj[k] - xi[k] );

      }// for k

      tanveclen[i][j] = vecnorm( tanvec[i][j] );

    }// end for j

  }// end for i

}


/*
  TETRA::crossproduct
    vc = va times vb
  Parameters:
    va, vb : size 3 vectors
  Return Value:
    vc : size 3 vector
*/
inline vector<double> TETRA::crossproduct( vector<double> va, vector<double> vb )
{

  assert( va.size()==3 && vb.size()==3 );

  vector<double> vc (3);

  vc.at(0) = va.at(1) * vb.at(2) - va.at(2) * vb.at(1);

  vc.at(1) = va.at(2) * vb.at(0) - va.at(0) * vb.at(2);

  vc.at(2) = va.at(0) * vb.at(1) - va.at(1) * vb.at(0);

  return vc;

}


/*
  TETRA::vecnorm
    compute vector L-2 norm
  Parameters:
    vec : size 3 vector
  Return Value:
    L-2 norm
*/
inline double TETRA::vecnorm( vector<double> vec )
{

  assert( vec.size()==3 );

  return sqrt( pow( vec.at(0), 2 ) + pow( vec.at(1), 2 ) + pow( vec.at(2), 2 ) );

}



/*
  TETRA::areasgen
    generate twice the opposite triangle areas,
    fill in TETRA::areas
  Parameters:
    NONE
  Return Value:
    NONE
  Alert:
    must be called after tanvecgen()
*/
void TETRA::areasgen()
{

  for(int i=0; i<4; i++){

    areas.push_back(

      vecnorm(

        crossproduct( 

          tanvec [ tetra_index[i][1] ] [ tetra_index[i][2] ] ,

          tanvec [ tetra_index[i][1] ] [ tetra_index[i][3] ] 

        )// crossproduct

      )// vecnorm

    );// push_back

  }// end for i

}


/*
  TETRA::unitnormvecgen
    generate unit normal outward vectors, fill in unitnormvec
  Alert:
    must be called after definematrix and areasgen
*/
void TETRA::unitnormvecgen()
{

  int signum;

  gsl_permutation* p = gsl_permutation_alloc( 4 );

  gsl_matrix* Flu = gsl_matrix_calloc( 4, 4 );

  gsl_matrix* Finv = gsl_matrix_calloc( 4, 4 );

  gsl_matrix_memcpy( Flu, F );

  gsl_linalg_LU_decomp( Flu, p, &signum );

  gsl_linalg_LU_invert( Flu, p, Finv );

  gsl_matrix* Sinv = gsl_matrix_calloc( 4, 4 );

  for( int i=0; i<4; i++ ){

    gsl_matrix_set( Sinv, i, i, 1. / areas.at(i) );

  }// end for i

  gsl_matrix* Nmat = gsl_matrix_calloc( 4, 4 );

  gsl_blas_dgemm( CblasNoTrans, CblasNoTrans, - double(type), Sinv, Finv, 0., Nmat );

  for( int i=0; i<4; i++ ){

    for( int j=0; j<3; j++){

      unitnormvec[i].push_back( gsl_matrix_get( Nmat, i, j+1 ) );

    }// end j

  }// end for

  gsl_matrix_free( Flu );

  gsl_matrix_free( Finv );

  gsl_matrix_free( Sinv );

  gsl_matrix_free( Nmat );

  gsl_permutation_free( p );

}



/*
  TETRA::zerobasisgen
    generate zero-order basis vectors, fill in zerobasis
  Alert:
    zerobasis[i][i] (diagonal) is invalid
*/
void TETRA::zerobasisgen()
{

  SIMPVEC simplevector;

  POLYNOMIAL simplepoly;

  double coef [2];

  for( int i=0; i<4; i++ ){

    for( int j=0; j<4; j++ ){

      // nj subvector
      simplevector.constvec.clear();

      simplevector.polymulti.clear();

      simplevector.constvec = unitnormvec[j];

      for( int k=0; k<4; k++ ){

        if( k==i ){

          coef[0] = 0.;

          coef[1] = - tanveclen[i][j] * areas.at(j) / 6. / volume;

          // use 'i!=j' to avoid i==j POLYNOMIAL::set error
          if( i!=j )  simplepoly.set( coef, 1 );

          simplevector.polymulti.push_back( simplepoly );

        }// end if

        else{

          coef[0] = 1.;

          coef[1] = 0.;

          if( i!=j )  simplepoly.set( coef, 0 );

          simplevector.polymulti.push_back( simplepoly );

        }// end else

      }// end for k

      zerobasis[i][j].vectors.push_back( simplevector );

      // ni subvector
      simplevector.constvec.clear();

      simplevector.polymulti.clear();

      simplevector.constvec = unitnormvec[i];

      for( int k=0; k<4; k++ ){

        if( k==j ){

          coef[0] = 0.;

          coef[1] = tanveclen[i][j] * areas.at(i) / 6. / volume;

          if( i!=j )  simplepoly.set( coef, 1 );

          simplevector.polymulti.push_back( simplepoly );

        }// end if

        else{

          coef[0] = 1.;

          coef[1] = 0.;

          if( i!=j )simplepoly.set( coef, 0 );

          simplevector.polymulti.push_back( simplepoly );

        }// end else

      }// end for k

      zerobasis[i][j].vectors.push_back( simplevector );

    }// end for j

  }// end for i

}



/*
  TETRA::zerobasiscurlgen
    generate curl of zero-order basis vectors, fill in zerobasiscurl
  Alert:
    zerobasiscurl[i][i] (diagonal) is invalid
    must be called after areasgen, unitnormvecgen
*/
void TETRA::zerobasiscurlgen()
{

  SIMPVEC simplevector;

  POLYNOMIAL simplepoly;

  double coef;

  for( int i=0; i<4; i++ ){

    for( int j=0; j<4; j++ ){

      simplevector.polymulti.clear();

      simplevector.constvec.clear();

      // assign constvec
      simplevector.constvec = crossproduct( unitnormvec[i], unitnormvec[j] );

      coef = tanveclen[i][j] * areas.at(i) * areas.at(j) / ( 18. * pow(volume, 2) );

      simplepoly.set( & coef, 0 );

      // push in polymulti
      simplevector.polymulti.push_back( simplepoly );

      coef = 1.;

      simplepoly.set( & coef, 0 );

      for( int k=0; k<3; k++)  simplevector.polymulti.push_back( simplepoly );

      zerobasiscurl[i][j].vectors.push_back( simplevector );

    }// end for j

  }// end for i

}











