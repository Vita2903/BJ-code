//****************************************************************************
//****************************************************************************
//******************************ALLOCATE**************************************
//****************************************************************************
//****************************************************************************
void reset_arrays(){
    
    for(int i = 1; i<=array_max; i++){
        
        //***********************
        //GEOMETRIC ELEMENTS*****
        //***********************
        for(int j = 0; j < 3; j++){
            v[i][j]=0;
            v_pass[i][j]=0;
        }
        for(int j = 0; j < 3; j++) e[i][j]=0;
        edges[i][1]=0; edges[i][2]=0;
        vertices[i][1]=0; vertices[i][2]=0;
        //***********************
        
        
        //***********************
        //ATTRIBUTES*************
        //***********************
        //vertices
        for(int j = 1; j < 3; j++) v_F[i][j]=0;
        v_cells[i][1]=0; v_cells[i][2]=0;
        v_edges[i][1]=0; v_edges[i][2]=0;
        v_T1dir[i]=0;
        v_edgeT1[i]=0;
        v_clock[i]=0;
        //***********************
        
        //passive vertices
        v_pass_cell[i]=0;
        //***********************
        
        //edges
        e_cell1[i]=0;
        e_cell2[i]=0;
        e_length[i]=0;
        e_dldt[i]=0;
        e_g[i]=0;
        e_Fg[i]=0;
        //***********************
        
        //cells
        c_cent[i]=0;
        c_area[i]=0;
        c_coordSphere[i]=0;
        //***********************
    }
    
}
//****************************************************************************
void allocate(){
    
    int arrayMax=array_max+1;
    
    
    Nv      = 0;
    Nv_pass = 0;
    Ne      = 0; 
    Nc      = 0;
    
    //GEOMETRIC ELEMENTS
    v        = new double*[arrayMax];
    v_pass   = new double*[arrayMax];
    e = new int*[arrayMax];
    for(int i=0; i < arrayMax; i++){
        v[i]        = new double[3];
        v_pass[i]   = new double[3];
        e[i]   = new int[3];
    }
    edges    = new int*[arrayMax];
    vertices = new int*[arrayMax];
    for(int i=0; i < arrayMax; i++){
        edges[i]    = new int[25];
        vertices[i] = new int[25];
    }
    
    //ATTRIBUTES
    //vertices
    v_F      = new double*[arrayMax];
    for(int i=0; i < arrayMax; i++) v_F[i] = new double[3];
    v_cells   = new int*[arrayMax];
    v_edges   = new int*[arrayMax];
    for(int i=0; i < arrayMax; i++){
        v_cells[i]   = new int[25];
        v_edges[i]   = new int[25];
    }
    v_T1dir    = new int[arrayMax];
    v_edgeT1   = new int[arrayMax];
    v_clock   = new double[arrayMax];
    
    //passive vertices
    v_pass_cell = new int[arrayMax];

    //edges
    e_cell1    = new int[arrayMax];
    e_cell2    = new int[arrayMax];
    e_length = new double[arrayMax];
    e_dldt = new double[arrayMax];
    e_g = new double[arrayMax];
    e_Fg = new double[arrayMax];

    //cells
    c_cent = new int[arrayMax];
    c_area = new double[arrayMax];
    c_coordSphere = new int[arrayMax];

    
    //MISC
    perioXYZ = new double[2];
    h              = 0;
    Time           = 0;
    wA             = 0;
    wP             = 0;
    wL             = 0;
    
    //RESET ARRAYS
    reset_arrays();

    return ;
}
//****************************************************************************
void deallocate(){
    
    int arrayMax=array_max+1;

    //GEOMETRIC ELEMENTS
    for(int i=0; i < arrayMax; i++){
        delete [] v[i]      ;
        delete [] v_pass[i];
        delete [] e[i];
    }
    delete [] v;
    delete [] v_pass;
    delete [] e;
    for(int i=0; i < arrayMax; i++){
        delete [] edges[i]   ;
        delete [] vertices[i];
    }
    delete [] edges   ;
    delete [] vertices;

    //vertices
    for(int i=0; i < arrayMax; i++) delete [] v_F[i];
    delete [] v_F;
    for(int i=0; i < arrayMax; i++){
        delete [] v_cells[i]  ;
        delete [] v_edges[i]  ;
    }
    delete [] v_cells  ;
    delete [] v_edges  ;
    delete [] v_T1dir   ;
    delete [] v_edgeT1  ;
    delete [] v_clock  ;

    //passive vertices
    delete [] v_pass_cell;
    
    //edges
    delete [] e_cell1   ;
    delete [] e_cell2   ;
    delete [] e_length;
    delete [] e_dldt;
    delete [] e_g;
    delete [] e_Fg;
    
    //cells
    delete [] c_cent;
    delete [] c_area;
    delete [] c_coordSphere;
    
    //MISC
    delete [] perioXYZ;

    return ;
}
//****************************************************************************
