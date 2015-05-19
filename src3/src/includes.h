/* include libraries */
#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>
#include <stdlib.h>
#include <sstream>
#include <typeinfo>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <stdio.h>
#include <cmath>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>

/* signature */
#define SIG_INCLUDES "includes.h"

/* macros */
#define MSHPATH "/home/voila/Documents/Prototypes/EM/src3/mesh/square/square.msh"


/* namespaces */
using namespace std;



/* structures */

// line element
struct LIN_ELE{

  // nodal vertex
  int vertex [2];

  // group label
  int label;

};

// surface element
struct SUR_ELE{

  // nodal vertex
  int vertex [3];

  // group label
  int label;

};
