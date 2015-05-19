/* signature */
#ifndef SIG_INCLUDES

  #include "includes.h"

#endif

#define SIG_POLYCLASS "polyclass.h"

/* ----------------------------------------------------------------------
   POLYNOMIAL class

     Syntax:

       POLYNOMIAL a, b, c, d;

       double p1[] = {1, 0, 1};    // 1 + x^2

       int deg1 = 2;               // polynomial degree

       double p2[] = {4, 3};       // 4 + 3x

       int deg2 = 1;               // polynomial degree

       a.set(p1, deg1);            // set coefficients

       b.set(p2, deg2);

       a.print() << endl;          // print polynomial

       c = a.plus( b );            // a + b

       c = a.minus ( b );          // a - b
 
       c = a.multiply ( b );       // a * b

       d = c.differentiate();      // differentiate
 
       c.evaluate ( 2. );          // evaluate

       a.chvar( b );               // change of variable

       a.scale( 3.7 );             // scale polynomial

     Notice:

       Polynomial degree cannot exceed 49, i.e. x^n with max(n) = 49
   ---------------------------------------------------------------------- */


class POLYNOMIAL
{
  private:

    // coef[0] coefficient of x^0
    // coef[1] coefficient of x^1
    // coef[n] coefficient of x^n
    double coef[50];

    // degree of polynomial (0 for the zero polynomial)
    int deg;

  public:

    POLYNOMIAL()
    {
      for ( int i = 0; i < 50; i++ )
      {
        coef[i] = 0;
      }
    }
    
    // polycoef <= [coef_x0, coef_x1, ... , coef_xdeg]
    //   e.g. x^2+3, 
    //     polycoef = [3, 0, 1]
    //     deg = 2
    void set ( double* polycoef, int polydeg)
    {
      for(int i=0; i<50; i++){
        coef[i] = 0;
      }
      for(int i=0; i<=polydeg; i++)
        coef[i] = polycoef[i];
      deg = degree();
      assert(deg == polydeg);
    }
    
    int degree()
    {
      int d = 0;
      for ( int i = 49; i >=0; i-- ){
        if ( coef[i] != 0 ){ d = i;  break; }
      }
      return d;
    }
    
    void print()
    {
      bool is0 = true;
      for ( int i = 49; i >= 0; i-- ) {
        if ( coef[i] != 0 ) {
          cout << coef[i] << " * x" << i << "  ";
          is0 = false;
        }
      }
      if ( is0 )  cout << "0 * x0 ";
      cout << endl;
    }

    void scale( double scaler )
    {
      for(int i=0; i<=deg; i++)
        coef[i] = coef[i] * scaler;
      deg = degree();
    }

    double evaluate ( double x )
    {
      double p = 0;
      for ( int i = deg; i >= 0; i-- )
        p = coef[i] + ( x * p );
      return p;
    }
    
    POLYNOMIAL differentiate()
    {
      if ( deg == 0 ) {
        POLYNOMIAL t;
        double nullcoef = 0;
        t.set ( &nullcoef, 0 );
        return t;
      }
      POLYNOMIAL deriv;
      deriv.deg = deg - 1;
      for ( int i = 0; i < deg; i++ )
        deriv.coef[i] = ( i + 1 ) * coef[i + 1];
      return deriv;
    }

    POLYNOMIAL plus ( POLYNOMIAL b )
    {
      POLYNOMIAL c;
      for ( int i = 0; i <= deg; i++ )   c.coef[i] += coef[i];
      for ( int i = 0; i <= b.deg; i++ ) c.coef[i] += b.coef[i];
      c.deg = c.degree();
      return c;
    }

    POLYNOMIAL minus ( POLYNOMIAL b )
    {
      POLYNOMIAL c;
      for ( int i = 0; i <= deg; i++ )   c.coef[i] += coef[i];
      for ( int i = 0; i <= b.deg; i++ ) c.coef[i] -= b.coef[i];
      c.deg = c.degree();
      return c;
    }

    POLYNOMIAL multiply ( POLYNOMIAL b )
    {
      POLYNOMIAL c;
      for ( int i = 0; i <= deg; i++ )
        for ( int j = 0; j <= b.deg; j++ )
          c.coef[i+j] += ( coef[i] * b.coef[j] );
      c.deg = c.degree();
      return c;
    }
    
    POLYNOMIAL chvar ( POLYNOMIAL );
};

// change of variables, specifically change x to b(x), where b is a polynomial
// for example, this -> 4x, b -> 2x-0.5, result -> 8x-2
POLYNOMIAL POLYNOMIAL::chvar( POLYNOMIAL b )
{
    POLYNOMIAL newpoly;
    newpoly.coef[0] = this->coef[0];
    POLYNOMIAL temp_poly;

    for (int i=1; i<=this->deg; i++){
        temp_poly.set(b.coef, b.deg);
        for (int j=1; j<i; j++){
            temp_poly = temp_poly.multiply(b);
        }
        for (int k=0; k<=temp_poly.deg; k++){
            temp_poly.coef[k] *= this->coef[i];
        }
        newpoly = newpoly.plus(temp_poly);
    }
    return newpoly;
}








