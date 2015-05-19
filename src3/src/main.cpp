#include "includes.h"
#include "buildmesh.h"
#include "polyclass.h"
#include "polylib.h"
#include "preprocess.h"
#include "polyvector.h"
#include "tetraclass.h"

int main()
{

  // mesh
  PREPROCESS mesh;

  mesh.extractmshfile<double>();

  mesh.extractmshfile<int>();

  mesh.extractlinsur();

  mesh.displaynodecords();

  mesh.displayelevertex();

  mesh.displaylinsurlabels();

  // polynomial

  POLYPNT polylib;

  buildpolylib( & polylib );

  // sort elevertex
  mesh.sortelevertex();

  // split code generation
  vector< vector<int> > splitcode;

  splitcode = mesh.splitcodegen(4,4);

  // order of accuracy
  int p = 2;

  // edge basis registry
  mesh.edgebasreggen( p );

  // face basis registry
  mesh.facebasreggen( p );

  // interior basis registry
  mesh.intbasreggen( p );

  // tetra class
  TETRA tet;

  tet.definematrix(& mesh.nodecords, mesh.elevertex.at(1));

  tet.tanvecgen( & mesh.nodecords, mesh.elevertex.at(1) );

  tet.areasgen();

  tet.unitnormvecgen();

  tet.zerobasisgen();

  tet.zerobasiscurlgen();

  // test innerproduct
  COMPPOLY inprod;

  inprod = tet.zerobasis[1][2].innerproduct( tet.zerobasis[1][2] );

  return 0;

}








