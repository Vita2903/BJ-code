//DECLARATIONS
#include <stdio.h>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include "_freeid.h"
#include <time.h>

//GEOMETRIC ELEMENTS
size_t Nv, Nv_pass, Ne, Nc;
double **v;
double **v_pass;
int **e;
int **edges;
int **vertices;

//ATTRIBUTES
//vertices
double **v_F    ;
int **v_cells   ;
int **v_edges   ;
int *v_T1dir    ;
int *v_edgeT1   ;
double *v_clock ;

//passive vertices
int *v_pass_cell;

//edges
int *e_cell1    ;
int *e_cell2    ;
double *e_length;
double *e_dldt  ;
double *e_g     ;
double *e_Fg    ;
    
//cells
int *c_cent     ;
double *c_area  ;
int *c_coordSphere;

//MISC
double *perioXYZ;
double h, Time;
double wA, wP, wL;
FreeId v_freeId, v_pass_freeId, e_freeId, c_freeId;
size_t array_max, seed;
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
#include "_allocate.h"
#include "_rndom.h"
#include "_torus.h"
#include "_distances.h"
#include "_vert_edg_fac.h"
#include "_cell_network.h"
#include "_cell_side.h"
#include "_force_area.h"
#include "_force_length.h"
#include "_output.h"
#include "_equation_of_motion.h"
#include "_dissolve.h"
#include "_list_manipulation.h"
#include "_T1_transformation.h"
#include "_cell_extrusion.h"
#include "_contraction_resolution.h"
#include "_initial_structure.h"
//****************************************************************************
//****************************************************************************
