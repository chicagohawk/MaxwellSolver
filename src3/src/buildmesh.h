/* signature */
#ifndef SIG_INCLUDES

  #include "includes.h"

#endif

#define SIG_BUILDMESH "buildmesh.h"

/* ----------------------------------------------
   Mesh class

   Functional:

     1. 3D nodes coordinates
     2. nodal indices for tetrohedrons
     3. geometry line & surface elements
     4. data display
  
   Syntax:
   
     // initiate instance
     MESH mesh;

     // extract nodal coordinates
     mesh.extractmshfile<double>();

     // extract element vertex
     mesh.extractmshfile<int>();

     // extract geometry line & surface elements
     mesh.extractlinsur();

     // display nodal coordinates
     mesh.displaynodecords();

     // display element vertex
     mesh.displayelevertex();

     // display line & surface labels
     mesh.displaylinsurlabels();

  ----------------------------------------------- */
class MESH{

  public:

    // extract .msh file for nodal coordinates and element vertex
    template <class DATATYPE>  void extractmshfile();

    // extract .msh file for line and surface elements
    void extractlinsur();

    /* ------ data storage ------ */

    // nodal coordinates
    vector<double*> nodecords;

    // vertex index of elements
    vector<int*> elevertex;

    // node number
    size_t nodenum;

    // element number
    size_t elenum;

    // line elements (geometry edges)
    vector<LIN_ELE> lineelements;

    // surface elements (geometry surfaces)
    vector<SUR_ELE> surfaceelements;  

    /* ------ tools ------ */

    // split string
    int splitstring( string*, vector<string> * );

    // selective display nodal coordinates
    void displaynodecords();

    // selective display index of elements
    void displayelevertex();

    // display line and surface labels
    void displaylinsurlabels();

  private:

    // accessory function for extractmshfile()
    void pushbackdata( double* );

    void pushbackdata( int* );

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

}// MESH::splitstring



/*
  MESH::displaynodecords
    display the first and last coordinates
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

    cout << "First Cords\n";

    cout << dpnt[0] << ' ' << dpnt[1] << ' ' << dpnt[2];

    cout << endl;

    dpnt = (this->nodecords).at(1);

    cout << dpnt[0] << ' ' << dpnt[1] << ' ' << dpnt[2];

    cout << endl;

    dpnt = (this->nodecords).back();

    cout << "Last Cord\n";

    cout << dpnt[0] << ' ' << dpnt[1] << ' ' << dpnt[2];

    cout << endl;

  }

  else{
  
    cout << "\n displaynodecords failed !" << endl;  

  }

}// MESH::displaynodecords



/*
  MESH::displayelevertex
    display the first and last several tetrohedron vertex
  Parameters:
    NONE
  Return Value:
    NONE
*/
void MESH::displayelevertex()
{

  cout << "---- Display Element Vertex ----\n";

  if( ( this->elevertex ).size() != 0 ){

    int* dpnt;

    dpnt = (this->elevertex).front();

    cout << "First Vertices\n";

    cout << dpnt[0] << ' ' << dpnt[1] << ' ' << dpnt[2] << ' ' << dpnt[3];

    cout << endl;

    dpnt = (this->elevertex).at(1);

    cout << dpnt[0] << ' ' << dpnt[1] << ' ' << dpnt[2] << ' ' << dpnt[3];

    cout << endl;

    dpnt = (this->elevertex).back();

    cout << "Last Vertex\n";

    cout << dpnt[0] << ' ' << dpnt[1] << ' ' << dpnt[2] << ' ' << dpnt[3];

    cout << endl;

  }

  else{
  
    cout << "\n displayelevertex failed !" << endl;  

  }

}// MESH::displayelevertex



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

      num = 3;  flag = 0;

      start_str.assign("$Nodes");

      end_str.assign("$EndNodes");

  }
  else if ( typeid(DATATYPE) == typeid(int) ){
    
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
      
      // readin number line
      getline( mshfile, mshline );

      // if $Nodes, store nodenum
      if ( flag==0 ){  this->nodenum = (size_t) atoi( mshline.c_str() );  }

      // readin 1st line data
      getline( mshfile, mshline );

      // check if end string reached
      while ( mshline.compare(end_str) != 0 ){
        
        // break and store data line
        numpieces = this->splitstring( &mshline, &pieces );
        
        dpnt = new DATATYPE [num];

        for (int i=num-1; i>=0; i--){

          // if $Nodes
          if ( flag==0 ){  dpnt[i] = atof( pieces.back().c_str() );  }

          // if $Elements and tetrahedron
          else if( atoi( pieces.at(1).c_str() ) == 4 ){
  
              dpnt[i] = atoi( pieces.back().c_str() ) - 1;

          }// end else if

          else{

            free( dpnt );

            dpnt = NULL;

          }

          pieces.pop_back();

        }// end for i

        // check if non-tetra elements
        if ( flag == 1 && atoi( pieces.at(1).c_str() ) != 4){
        
          pieces.clear();

          getline( mshfile, mshline );

          continue;

        }// end if

        // push in data
        this->pushbackdata( dpnt );

        pieces.clear();

        getline( mshfile, mshline );

      }// end while $EndNodes not reached
   
    }// end if $Nodes reached

  }// end mshfile.eof()

  // if $Elements, store elenum
  if( flag==1 ){  this->elenum = (size_t) elevertex.size();  }

  mshfile.close();

}// MESH::extractmshfile



void MESH::pushbackdata( double * dpnt )
{

  ( this->nodecords ).push_back( dpnt );

}

void MESH::pushbackdata( int * dpnt)
{

  ( this->elevertex ).push_back( dpnt );

}



/* 
  MESH::extractlinsur
    extract .msh file for line and surface elements
  Parameters:
    None
  Return Value:
    None
*/
void MESH::extractlinsur()
{
  
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

  // temporary LIN_ELE storage
  LIN_ELE lin;

  // temporary SUR_ELE storage
  SUR_ELE sur;

  while( ! mshfile.eof() ){

    getline( mshfile, mshline );

    // read in file until $Elements reached
    if ( mshline.compare("$Elements") == 0 ){

      while( mshline.compare("$EndElements") != 0 ){

        getline( mshfile, mshline );
        
        pieces.clear();

        numpieces = this->splitstring( &mshline, &pieces);

        try{
          
          // if line elements
          if( atoi( pieces.at(1).c_str() ) == 1 ){

            // extract vertex
            lin.vertex[1] = atoi( pieces.back().c_str() );

            pieces.pop_back();

            lin.vertex[0] = atoi( pieces.back().c_str() );

            // extract label
            lin.label = atoi( pieces.at(4).c_str() );

            lineelements.push_back( lin );

          }// end if line elements

          // if surface elements
          else if( atoi( pieces.at(1).c_str() ) == 2 ){

            // extract vertex
            for(int i=2; i>=0; i--){

              sur.vertex[i] = atoi( pieces.back().c_str() );

              pieces.pop_back();

            }// end extract vertex

            // extract label
            sur.label = atoi( pieces.at(4).c_str() );
            
            surfaceelements.push_back( sur );

          }// end if surface elements

        }// end try

        // catch out_of_range error (vector)
        //   investigate err message by errinfo.what()
        catch( out_of_range& errinfo ){

          continue;

        }// end catch

      }// end while $EndElements not reached

    }// end if $Elements reached

  }// end while ! mshfile.eof()

  mshfile.close();

}// MESH::extractlinsur



/*
  MESH::displaylinsurlabels
    display all line and surface labels
  Parameters:
    None
  Return Value:
    None
*/
void MESH::displaylinsurlabels()
{

  if ( lineelements.size()==0 || surfaceelements.size()==0 ){
  
    cout << "Display lin sur labels failed !" << endl;

    return;
  
  }// end if display failed

  vector<int> linlabels, surlabels;

  vector<int>::iterator it_int;

  vector<LIN_ELE>::iterator it_lin;

  vector<SUR_ELE>::iterator it_sur;

  // extract line labels
  for ( it_lin=lineelements.begin(); it_lin<lineelements.end(); it_lin++ ){

    // if label not in linlabels
    if ( find( linlabels.begin(), linlabels.end(), it_lin->label )
        == linlabels.end() ){

      linlabels.push_back( it_lin->label );

    }// end if label not in linlabel

  }// end for lineelements iterator

  // extract surface labels
  for ( it_sur=surfaceelements.begin(); it_sur<surfaceelements.end(); it_sur++ ){

    // if label not in surlabels
    if ( find( surlabels.begin(), surlabels.end(), it_sur->label )
         == surlabels.end() ){

      surlabels.push_back( it_sur->label );

    }// end if label not in surlabels

  }// end for surfaceelements iterator

  // display labels
  cout << "---- Line Elements ----\n";

  for ( it_int=linlabels.begin(); it_int<linlabels.end(); it_int++ ){

    cout << *it_int << endl;

  }// end for display line elements

  cout << "---- Surface Elements ----\n";

  for ( it_int=surlabels.begin(); it_int<surlabels.end(); it_int++ ){

    cout << *it_int << endl;

  }// end for display surface elements

}// MESH::displaylinsurlabels

