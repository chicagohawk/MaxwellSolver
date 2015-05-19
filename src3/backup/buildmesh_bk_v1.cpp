#include "includes.h"

/* ----------------------------------------------
   Mesh class 
     1. 3D nodes coordinates
     2. nodal indices for tetrohedrons
  ----------------------------------------------- */
class MESH{

  public:

    // extract .msh file data
    template <class DATATYPE>  void extractmshfile();

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


/*
  MESH::extractmshfile
    extract nodal coordinates and element index from .msh file
    extractmshfile<int>() extracts nodal coordinates
    extractmshfile<double>() extracts element index
  Parameters:
    None
  Return Value:
    None
*/
template <class DATATYPE>  void MESH::extractmshfile()
{

  // determine number of array from DATATYPE
  //   double : 3 (nodecords);  flag = 0;
  //   int    : 4 (elevertex);  flag = 1;
  int num, flag;

  string start_str, end_str;

  if ( typeid(DATATYPE) == typeid(double) ){

      cout << "double";

      num = 3;  flag = 0;

      start_str.assign("$Nodes");

      end_str.assign("$EndNodes");

  }
  else if ( typeid(DATATYPE) == typeid(int) ){
    
      cout << "int";

      num = 4;  flag = 1;

      start_str.assign("$Elements");

      end_str.assign("$EndElements");

  }
  else{

      cout << "Invalid datatype !" << endl;

      assert( 0 );
      
  }

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

  // temporary double/int pointer
  DATATYPE * dpnt;

  while( ! mshfile.eof() ){

    getline( mshfile, mshline );

    // readin file until start string reached
    if ( mshline.compare( start_str ) == 0 ){
      
      // readin nodes number
      getline( mshfile, mshline );

      // if $Nodes
      if ( flag==0 ){  this->nodenum = (size_t) atoi( mshline.c_str() );  }

      // if $Elements
      else{  this->elenum = (size_t) atoi( mshline.c_str() );  }

      // readin 1st line data
      getline( mshfile, mshline );

      // check if $EndNodes reached
      while ( mshline.compare(end_str) != 0 ){
        
        // break and store data line
        numpieces = this->splitstring( &mshline, &pieces );
        
        dpnt = new DATATYPE [num];

        for (int i=num-1; i>=0; i--){

          // if $Nodes
          if ( flag==0 ){  dpnt[i] = atof( pieces.back().c_str() );  }

          // if $Elements
          else{  dpnt[i] = atoi( pieces.back().c_str() );  }

          pieces.pop_back();

        }// for i=0:2
 
        if ( flag==0 ){  ( this->nodecords ).push_back( dpnt );  }

        else{  ( this->elevertex ).push_back( dpnt );  }

        pieces.clear();

        getline( mshfile, mshline );

      }// end while $EndNodes not reached
   
    }// end if $Nodes reached

  }// end mshfile.eof()

  mshfile.close();

}



int main()
{

  // initiate mesh
  MESH mesh;

  mesh.extractmshfile<int>();

  mesh.displaynodecords();

  return 0; 

}
