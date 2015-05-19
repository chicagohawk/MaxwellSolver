#include "includes.h"

/* ----------------------------------------------
   Mesh class 
     1. 3D nodes coordinates
     2. nodal indices for tetrohedrons
  ----------------------------------------------- */
class MESH{

  public:

    /* ------ data storage ------ */

    // nodal coordinates
    vector<double*> nodecords;

    // vertex index of elements
    vector<int*> elevertex;

    // node number
    size_t nodenum;

    // element number
    size_t elenum;

    /* ------ tools ------ */

    // split string
    int splitstring( string*, vector<string> * );

    // selective display nodal coordinates
    void displaynodecords();

    // selective display index of elements
 //   void displayelevertex();

};

/* 
  MESH::splitstring
    break a string line into pieces, separated by space " "
  Parameters:
    line: string to be broken
    pieces: pointer to a <string> vector containing pieces of
            sub-strings
  Return Value:
    number of sub-strings, equal to (*pieces).size()
*/
int MESH::splitstring(string* line, vector<string> * pieces)
{

  // convert string to stream
  istringstream istreamline ( *line );

  string substring;

  while( ! istreamline.eof() ){
    
    istreamline >> substring;

    (*pieces).push_back(substring);

  }
  
  return (*pieces).size();

}

/*
  MESH::displaynodecords
    display the first and last several nodal coordinates
  Parameters:
    NONE
  Return Value:
    NONE
*/
void MESH::displaynodecords()
{

  cout << "---- Display Node Cords ----\n";

  if( ( this->nodecords ).size() != 0 ){

    double* dpnt;

    dpnt = (this->nodecords).front();

    cout << "First Cord\n";

    cout << dpnt[0] << ' ' << dpnt[1] << ' '<< dpnt[2];

    cout << endl;

    dpnt = (this->nodecords).back();

    cout << "Last Cord\n";

    cout << dpnt[0] << ' ' << dpnt[1] << ' '<< dpnt[2];

    cout << endl;

  }

  else{
  
    cout << "\n displaynodecords failed !" << endl;  

  }

}


int main()
{

  // initiate mesh
  MESH mesh;

  // open mesh file
  ifstream mshfile( MSHPATH, ios::in );

  assert( mshfile.is_open() );

  // mesh file line temporary storage
  string mshline;

  // line split sub-string temporary storage
  //   syntax: mesh.splitstring( &mshline, &pieces );
  vector<string> pieces;  

  // number of split pieces
  int numpieces;

  // temporary double pointer
  double * dpnt;

  while( ! mshfile.eof() ){

    getline( mshfile, mshline );

    // readin file until $Nodes section reached
    if ( mshline.compare("$Nodes") == 0 ){
      
      // readin nodes number
      getline( mshfile, mshline );

      mesh.nodenum = (size_t) atoi( mshline.c_str() );

      // readin 1st nodal coordinates
      getline( mshfile, mshline );

      // check if $EndNodes reached
      while ( mshline.compare("$EndNodes") != 0 ){
        
        // store coordinates
        numpieces = mesh.splitstring( &mshline, &pieces );
        
        dpnt = new double [3];

        for (int i=2; i>=0; i--){

          dpnt[i] = atof( pieces.back().c_str() );

          pieces.pop_back();

        }// for i=0:2
        
        mesh.nodecords.push_back( dpnt );

        pieces.clear();

        getline( mshfile, mshline );

      }// end while $EndNodes not reached
   
    }// end if $Nodes reached

    // readin file until $Elements section reached
    if ( mshline.compare("$Elements") == 0 ){

      // readin elements number
      getline( mshfile, mshline );

      mesh.elenum = (size_t) atoi( mshline.c_str() );

      // readin 1st element index
      getline( mshfile, mshline );

      // check if $EndElements reached
      while ( mshline.compare("$EndElements") != 0 ){

        // store element index
        numpieces = mesh.splitstring( &mshline, &pieces );

        dpnt = new int [3];

        for (int i=2; i>=0; )

    }

  }// end mshfile.eof()

  mesh.displaynodecords();

  return 0; 

}
