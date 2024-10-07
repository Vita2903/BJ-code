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
#include <algorithm>


//GEOMETRIC ELEMENTS
size_t Nv, Nv_pass, Ne, Nc;
double **v; //v[vert_id][i]; i=1 - x, i=2 - y (vertex xy coordinates)
double **v_pass; //location of cell center or average vertex position (xy coordinates)
int **e; //e[edge_id][i]; i=1 - v_id 1 , i=2 - v_id 2 (vertices on this edge)
int **edges; //edges[cell_id][i]; i=2 - # of cell edges, i>2 - edge_id
int **vertices; //veritices[cell_id][3] - vert_ref_id, 

//ATTRIBUTES (atribute[*_id])
//vertices
double **v_F    ; // v_F[vert_id][1] and v_F[vert_id][2] -  x and y forces on this vertex
int **v_cells   ; //cells with this vertex
int **v_edges   ; //edges from this vertex
int *v_T1dir    ;
int *v_edgeT1   ;
double *v_clock ;

//passive vertices 
int *v_pass_cell; //cell center

//edges
int *e_cell1    ; //if 1 cell has this edge
int *e_cell2    ; //if 2 cells have this edge
double *e_length; //edge length
double *e_dldt  ; //edge length rate of change
double *e_g     ; //edge tension
double *e_Fg    ; //edge tension rate of change
    
//cells
int *c_cent     ; //location of cell center
double *c_area  ; //cell area
int *c_coordSphere; //circular layers

//MISC
double *perioXYZ;
double h, Time; //time step, total time
double wA, wP, wL; //energies: (A-1)^2, (P-P0), ()
double F_r;
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
#include "_rim_contraction.h"
//****************************************************************************
//****************************************************************************
