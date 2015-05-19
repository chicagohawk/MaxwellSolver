/* signature */
#ifndef SIG_POLYCLASS

  #include "polyclass.h"

#endif

#define SIG_POLYVECTOR "polyvector.h"

/*
  simple vector
    4 polynomials times a constant vector
    SIMPVEC.polymulti.at(i) is the polynomial associated
    with zeta_i
  Alert:
    in the assignment, make sure polymulti.size()==4
    and constvec.size()==3
*/
struct SIMPVEC
{

  // polynomial multiplier
  vector<POLYNOMIAL> polymulti;

  // constant vector
  vector<double> constvec;

};

/*
  additive size 4 polynomials
    stores the inner product of two COMPVEC, e.g.
      P0*P1*P2*P3 + Q0*Q1*Q2*Q3
    + R0*R1*R2*R3 + S0*S1*S2*S3
  Notice:
    COMPPOLY.at(i).size()==4
*/
typedef vector< vector<POLYNOMIAL> >  COMPPOLY;


/*
  complex vector
    additive simple vectors
*/
class COMPVEC
{

  public:

    // vectors storage
    vector<SIMPVEC> vectors;

    COMPPOLY innerproduct( COMPVEC );

};


/*
  COMPVEC::innerproduct
    inner product of two COMPVEC
    COMPPOLY result = COMPVEC * vec_2_multi
  Syntax:
    COMPPOLY inprod;
    inprod = tet.zerobasis[1][2].innerproduct( tet.zerobasis[1][2] );
    inprod = tet.zerobasiscurl[2][1].innerproduct( tet.zerobasiscurl[1][3] );
*/
COMPPOLY COMPVEC::innerproduct( COMPVEC vec_2_multi )
{

  COMPPOLY result;

  vector<POLYNOMIAL> result_entry;

  double scaler;

  for( int i=0; i<vectors.size(); i++ ){

    for( int j=0; j<vec_2_multi.vectors.size(); j++ ){

      for( int k=0; k<4; k++ ){

        result_entry.push_back( 
        
          vectors.at(i).polymulti.at(k).multiply (
          
          vec_2_multi.vectors.at(j).polymulti.at(k)
          
          )// multiply

        );// push_back

      }// end for k

      // scale polynomial by constvec1 * constvec2
      scaler = 0.;

      for( int l=0; l<3; l++ ){

        scaler += vectors.at(i).constvec.at(l)

                * vec_2_multi.vectors.at(j).constvec.at(l);

      }// end for l

      result_entry.at(0).scale( scaler );

      result.push_back( result_entry );

      result_entry.clear();

    }// end for j

  }// end for i

  return result;

}










