/* signature */
#ifndef SIG_BUILDMESH

  #include "buildmesh.h"

#endif

#define SIG_PREPROCESS "preprocess.h"

class PREPROCESS : public MESH{

  public:

    /* ------ data storage ------ */

    // edge associated basis registry table
    vector<int*> edgebasreg;

    // face associated basis registry table
    vector<int*> facebasreg;

    // interior associated basis registry table
    vector<int*> intbasreg;

    /* ------ tools ------ */
    
    // sort element vertices
    int sortelevertex();

    // split code generation
    vector< vector<int> > splitcodegen(int, int);

    // generate edge basis registry table
    void edgebasreggen(int);

    // generate face basis registry table
    void facebasreggen(int);

    // generate interior associated basis registry table
    void intbasreggen(int);

  private:

    // interior split code generation
    vector< vector<int> > interiorcodegen(int);

    // comparator for sortelevertex
    static int comparator(const void *, const void *);

};


/*
  PREPROCESS::sortelevertex
    sort the integer vertices of elements in ascending order
  Parameters:
    NONE
  Return Value:
    if PREPROCESS.elevertex.size() == 0, return error 1
    else return 0
*/
int PREPROCESS::sortelevertex()
{
  
  // null elevertex check
  if ( elevertex.size()==0 )  return 1;

  for (int i=0; i<elevertex.size(); i++){
  
    qsort(elevertex.at(i), 4, sizeof(int), comparator);
  
  }// for i in elevertex

}


/*
  PREPROCESS::comparator
    comparison operator used in qsort
  Parameters:
    void pointers, whose pointing values are to be compared
  Return Value:
    comparison result indicator
*/ 
int PREPROCESS::comparator(const void *a, const void * b)
{

  return ( * (int*) a > * (int*) b );

}


/*
  PREPROCESS::splitcodegen
    recursive generation of split code, obtain all combinations that put
    n numbers into m bits.
  Parameters:
    n : n = p + 2, where p is order of accuracy,
    m : m = 4 for 3D (tetrahedron), m = 3 for 2D (triangle)
  Return Values:
    splitcode : splitcode.at(i).at(j) is the j'th bit in the i'th entry, 
                with 0 < i < #entries, 0 < j < m
*/
vector< vector<int> > PREPROCESS::splitcodegen(int n, int m)
{

  vector< vector<int>  > splitcode;

  vector<int> onecode;

  if ( n==0 ){

    onecode.assign( m, 0 );

    splitcode.push_back( onecode );

    return splitcode;

  }// end if n==0

  if ( m==1 ){

    onecode.assign( 1, n );

    splitcode.push_back( onecode );

    return splitcode;

  }// end if m==1

  vector< vector<int> > subcode;

  // for i = number to be put in last bit
  for (int i=0; i<=n; i++){

    subcode = splitcodegen( n-i, m-1 );

    for (int j=0; j<subcode.size(); j++){

      subcode.at(j).push_back( i );

      splitcode.push_back( subcode.at(j) );

    }// end for j

  }// end for i

  return splitcode;

}

/*
  PREPROCESS::edgebasreggen
    generate edge associated basis registry table
  Parameters:
    p : order of accuracy
  Return Value:
    NONE
  Comment:
    registry table is ordered by
    start_vertex  end_vertex  #i=0...p  basis_global_index
  Alert:
    must call sortelevertex() before calling this function
*/
void PREPROCESS::edgebasreggen( int p )
{

  edgebasreg.clear();

  int VERTEX[6][2] = { {0, 1}, {0, 2}, {0, 3},
                       {1, 2}, {1, 3}, {2, 3} };

  int startver, endver, global_index=0, flag=0;

  int* entry;

  vector<int*>::iterator it_ele, it_reg;

  for( it_ele=elevertex.begin(); it_ele<elevertex.end(); it_ele++ ){
    
    for( int i=0; i<6; i++ ){

      flag = 0;

      startver = (*it_ele)[ VERTEX[i][0] ];

      endver   = (*it_ele)[ VERTEX[i][1] ];

      // check if edge already registered
      for( it_reg=edgebasreg.begin(); it_reg<edgebasreg.end(); it_reg++ ){

        if( (*it_reg)[0]==startver && (*it_reg)[1]==endver ){

          flag = 1;  break;

        }// end if

      }// end for it_reg

      // register in new entry
      if ( flag == 0 ){

        for ( int j=0; j<=p; j++ ){

          entry = new int [4];

          entry[0] = startver;

          entry[1] = endver;

          entry[2] = j;

          entry[3] = global_index;

          global_index++;

          edgebasreg.push_back( entry );

        }// end for j

      }// end if flag==0
    
    }// end for i

  }// end for elevertex

}


/*
  PREPROCESS::facebasreggen
    generate face associated basis registry table
  Parameters:
    p : order of accuracy
  Return Value:
    NONE
  Comment:
    registry table is ordered by
    vertex0  vertex1  vertex2  global_split_code_drop_0 
    edge_vertices_associated  basis_global_index
  Alert:
    must call sortelevertex() before calling this function
    must call edgebasreggen() before calling this function
*/
void PREPROCESS::facebasreggen( int p )
{

  facebasreg.clear();

  // check edgebasreggen() already called
  assert( edgebasreg.size() > 0 );

  vector< vector<int> > facecode = splitcodegen(p-1, 3);

  vector< vector<int> >::iterator it_code;

  int VERTEX[4][3] = { {0, 1, 2}, {0, 1, 3}, {0, 2, 3}, {1, 2, 3} };

  int* entry;

  int flag, v0, v1, v2, global_index = edgebasreg.size();

  vector<int*>::iterator it_ele, it_reg;

  for( it_ele=elevertex.begin(); it_ele<elevertex.end(); it_ele++ ){

    for ( int i=0; i<4; i++ ){

      flag = 0;

      v0 = (*it_ele)[ VERTEX[i][0] ];

      v1 = (*it_ele)[ VERTEX[i][1] ];

      v2 = (*it_ele)[ VERTEX[i][2] ];

      // check if face already registered
      for( it_reg=facebasreg.begin(); it_reg<facebasreg.end(); it_reg++ ){

        if( (*it_reg)[0]==v0 && (*it_reg)[1]==v1 && (*it_reg)[2]==v2 ){

          flag = 1;  break;

        }// end if

      }// end for it_reg

      // register in new entry
      if ( flag==0 ){

        for( it_code=facecode.begin(); it_code<facecode.end(); it_code++ ){

          // associate with edge v0-v1
          entry = new int [9];

          entry[0] = v0;
 
          entry[1] = v1;

          entry[2] = v2;

          entry[3] = (*it_code).at(0) + 1;

          entry[4] = (*it_code).at(1) + 1;

          entry[5] = (*it_code).at(2) + 1;

          entry[6] = v0;

          entry[7] = v1;

          entry[8] = global_index;

          global_index++;

          facebasreg.push_back( entry );

          // associate with edge v1-v2
          entry = new int [9];

          entry[0] = v0;
 
          entry[1] = v1;

          entry[2] = v2;

          entry[3] = (*it_code).at(0) + 1;

          entry[4] = (*it_code).at(1) + 1;

          entry[5] = (*it_code).at(2) + 1;

          entry[6] = v1;

          entry[7] = v2;

          entry[8] = global_index;

          global_index++;

          facebasreg.push_back( entry );

        }// end for it_code

      }// end if flag

    }// end for i=0

  }// end for it_ele

}


/*
  PREPROCESS::interiorcodegen
    interior split code generation, similar to splitcodegen,
    but erases edge & surface associated elements
  Parameters:
    p : order of accuracy
  Return Value:
    interior split code
  Notice:
    if p<2, NULL vector is returned
*/
vector< vector<int> > PREPROCESS::interiorcodegen( int p )
{

  vector< vector<int> > interiorcode;

  if( p < 2 ){

    interiorcode.clear();

    return interiorcode;

  }// end if p<2

  interiorcode = splitcodegen( p+2, 4 );

  vector< vector<int> >::iterator it = interiorcode.begin();

  do{

    for( int i=0; i<(*it).size(); i++){
 
      if( (*it).at(i) == 0 ){

        interiorcode.erase(it);

        it--;

        break;

      }// end if ==0

    }// end for

    it++;

  }while( it < interiorcode.end() ); // end do while

  return interiorcode;

}


/*
  PREPROCESS::intbasreggen
    generate interior associated basis registry table
  Parameters:
    p : order of accuracy
  Return Value:
    NONE
  Comment:
    registry table is ordered by
    #tetrahedron  global_interior_split_code  start_vertex
    end_vertex  basis_global_index
  Alert:
    must call sortelevertex() before calling this function
    must call edgebasreggen() before calling this function
    must call facebasreggen() before calling this function
*/
void PREPROCESS::intbasreggen( int p )
{

  intbasreg.clear();

  assert( edgebasreg.size() > 0 && facebasreg.size() > 0 );

  if( p<2 )  return;

  vector< vector<int> > interiorcode = interiorcodegen( p );

  int VERTEX[3][2] = { {0, 1}, {1, 2}, {2, 3} };

  int* entry;

  int global_index = edgebasreg.size() + facebasreg.size(); 

  for( int i=0; i<elenum; i++ ){

    for( int j=0; j<interiorcode.size(); j++ ){

      for( int k=0; k<3; k++){

        entry = new int [8];

        entry[0] = i;

        for( int l=0; l<4; l++){

          entry[1+l] = interiorcode.at(j).at(l);

        }// end for l

        entry[5] = elevertex.at(i)[ VERTEX[k][0] ];

        entry[6] = elevertex.at(i)[ VERTEX[k][1] ];

        entry[7] = global_index;

        global_index++;

        intbasreg.push_back( entry );

      }// end for k

    }// end for j

  }// end for i

}









