//****************************************************************************
//****************************************************************************
//***********************INITIAL STRUCTURE************************************
//****************************************************************************
//****************************************************************************
void set_initial_regHex(int _Nx){
    
    //INTERNAL VARIABLES
    double *v_stitching_edge; //only useful for building regular hexagonal network
    v_stitching_edge = new double[array_max];
    int Ny=_Nx/2;
    double dd=1.2408064788027995;
    double ddx=0.08;
    
    int e_id=0;
    
    //GLOBAL VARIABLES
    perioXYZ[0] = _Nx*sqrt(3)*dd/2.; 
    perioXYZ[1] = Ny*(dd+dd/2); 
    
    for(int i=1; i<=Ny; i++){
        for (int j =1; j<=_Nx; j++){
            double x0=(j-1)*sqrt(3)*dd/2+ddx;
            double y0=(3*dd/2)*(i-1)+ddx;
            make_vertex(
                        x0,
                        y0-dd/2+dd/2
                        );
            make_vertex(
                        x0+sqrt(3)*dd/4,
                        y0-dd/4+dd/2
                        );
            make_vertex(
                        x0+sqrt(3)*dd/4,
                        y0+dd/4+dd/2
                        );
            make_vertex(
                        x0,
                        y0+dd/2+dd/2
                        );
        }
        
        e_id++; make_edge(i*_Nx*4-2, (i-1)*_Nx*4+1, e_id);
        e_id++; make_edge((i-1)*_Nx*4+1, (i-1)*_Nx*4+2, e_id);
        e_id++; make_edge((i-1)*_Nx*4+2, (i-1)*_Nx*4+3, e_id);
        e_id++; make_edge((i-1)*_Nx*4+3, (i-1)*_Nx*4+4, e_id);
        e_id++; make_edge((i-1)*_Nx*4+4, i*_Nx*4-1, e_id);
        
        for (int j =2; j<=_Nx; j++){
            e_id++; make_edge((i-1)*_Nx*4+(j-2)*4+2, (i-1)*_Nx*4+(j-2)*4+5, e_id);
            e_id++; make_edge((i-1)*_Nx*4+(j-2)*4+5, (i-1)*_Nx*4+(j-2)*4+6, e_id);
            e_id++; make_edge((i-1)*_Nx*4+(j-2)*4+6, (i-1)*_Nx*4+(j-2)*4+7, e_id);
            e_id++; make_edge((i-1)*_Nx*4+(j-2)*4+7, (i-1)*_Nx*4+(j-2)*4+8, e_id);
            e_id++; make_edge((i-1)*_Nx*4+(j-2)*4+8, (i-1)*_Nx*4+(j-2)*4+3, e_id);
        }
    }
    
    for (int i =1; i<=Ny-1; i++){
        for (int j =1; j<=_Nx; j++){
            e_id++; int edgid=make_edge(_Nx*4*(i-1)+4+(j-1)*4, _Nx*4*i+1+(j-1)*4, e_id);
            v_stitching_edge[_Nx*4*(i-1)+4+(j-1)*4]=edgid;
        }
    }
    
    int i = Ny;
    for (int j=1; j<=_Nx; j++){
        e_id++; int edgid=make_edge(_Nx*4*(i-1)+4+(j-1)*4, 1+(j-1)*4, e_id);
        v_stitching_edge[_Nx*4*(i-1)+4+(j-1)*4]=edgid;
    }
    
    
    
    //*************************************
    //*************************************
    //*************************************
    //EDGES
    //*************************************x
    //LIHE VRSTICE
    for (int i=1; i<=Ny; i++){
        
        make_cell(
                  6,
                  (i-1)*_Nx*5+1,
                  (i-1)*_Nx*5+2,
                  (i-1)*_Nx*5+3,
                  (i-1)*_Nx*5+4,
                  (i-1)*_Nx*5+5,
                  -((i-1)*_Nx*5+(_Nx*5-2)),
                  0,0,0,0,0,0
                  );
        
        for (int j=6; j<=_Nx*5-4; j+=5){
            make_cell(
                      6,
                      (i-1)*_Nx*5+j,
                      (i-1)*_Nx*5+j+1,
                      (i-1)*_Nx*5+j+2,
                      (i-1)*_Nx*5+j+3,
                      (i-1)*_Nx*5+j+4,
                      -((i-1)*_Nx*5+j-3),
                      0,0,0,0,0,0
                      );
        }
    }
    
    //SODE VRSTICE
    for (int i=1; i<=Ny-1; i++){
        
        for (int j=1; j<=_Nx-1; j++){
            make_cell(
                      6,
                      -(4+(j-1)*5+(i-1)*_Nx*5),
                      -(10+(j-1)*5+(i-1)*_Nx*5),
                      v_stitching_edge[e[(10+(j-1)*5)+(i-1)*_Nx*5][1]],
                      -(5*_Nx+6+(j-1)*5+(i-1)*_Nx*5),
                      -(5*_Nx+6+(j-1)*5-4+(i-1)*_Nx*5),
                      -(v_stitching_edge[e[(10+(j-1)*5)+(i-1)*_Nx*5][1]]-1),
                      0,0,0,0,0,0
                      );
        }
        
        make_cell(
                  6,
                  -(4+(_Nx-1)*5+(i-1)*_Nx*5),
                  -(5+(i-1)*_Nx*5),
                  v_stitching_edge[e[10+(i-1)*_Nx*5][1]]-1,
                  -(5*_Nx+6-4-1+(i-1)*_Nx*5),
                  -(5*_Nx+6+(_Nx-1)*5-4+(i-1)*_Nx*5),
                  -(v_stitching_edge[e[(10+(_Nx-1-1)*5+(i-1)*_Nx*5)][1]]),
                  0,0,0,0,0,0
                  );
    }
    
    //ZADNJA VRSTICA
    for (int j=1; j<=_Nx-1; j++){
        
        make_cell(
                  6,
                  -(4+(j-1)*5+(Ny-1)*_Nx*5),
                  -(10+(j-1)*5+(Ny-1)*_Nx*5),
                  v_stitching_edge[e[(10+(j-1)*5)+(Ny-1)*_Nx*5][1]],
                  -(6+(j-1)*5),
                  -(2+(j-1)*5),
                  -(v_stitching_edge[e[(10+(j-1)*5)+(Ny-1)*_Nx*5][1]]-1),
                  0,0,0,0,0,0
                  );
    }
    
    make_cell(
              6,
              -(4+(_Nx-1)*5+(Ny-1)*_Nx*5),
              -(5+(Ny-1)*_Nx*5),
              v_stitching_edge[e[10+(Ny-1)*_Nx*5][1]]-1,
              -1,
              -(_Nx*5-3),
              -(v_stitching_edge[e[(10+(_Nx-1-1)*5+(Ny-1)*_Nx*5)][1]]),
              0,0,0,0,0,0
              );
    
    
    delete [] v_stitching_edge;
    
    //CREATE 3D TISSUE
    make_cell_side_ALL();
    
    Time=0;
    
    //INITIAL EDGE LENGTHS
    for(int i=1; i<=Ne; i++) if(e[i][0]!=0) e_length[i]=edge_length(i);
    //INITIAL CELL AREAS
    for(int i = 1; i <= Nc; i++) if(edges[i][1]!=0) c_area[i]=CellArea_new(i);
    
    //printf("Lx=%g  Ly=%g\n", perioXYZ[0], perioXYZ[1]);
    
}

//****************************************************************************
void set_initial_fromFile2D(){
    
    char filename2[100];

    //initial structure with circular gap
    snprintf(filename2, sizeof(char) * 100, "./initial/final_324_%g_%g.vt2d", kA, P0); 
    FILE *file1; file1 = fopen(filename2, "rt");
    
    //V,E,C
    int nrV=0, nrE=0, nrC=0;
    fscanf(file1, "%d  %d  %d\n", &nrV, &nrE, &nrC);
    
    //perioXYZ
    fscanf(file1, "%lf  %lf\n", &perioXYZ[0], &perioXYZ[1]);
    
    //VERTICES
    double xx, yy, vclock, t1vdir;
    int vID;
    for(int i=1; i<=nrV; i++){
        fscanf(file1, "%lf  %lf  %lf  %lf\n", &xx, &yy, &vclock, &t1vdir);
        vID=make_vertex(xx,yy);
        v_clock[vID]=0;
        v_T1dir[vID]=0;
    }
    
    //EDGES
    int v1, v2; double eG1, eG2; int e_id=0;
    for(int i=1; i<=nrE; i++){
        fscanf(file1, "%d  %d  %lf\n", &v1, &v2, &eG1);
        e_id++; int EIDd=make_edge(v1,v2,e_id);
        e_g[EIDd]=0;
    }
    
    //CELLS
    int b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13;
    for(int i=1; i<=nrC; i++){
        fscanf(file1, "%d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d\n", &b1, &b2, &b3, &b4, &b5, &b6, &b7, &b8, &b9, &b10, &b11, &b12, &b13);
        make_cell(b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13);
    }
    fclose(file1);
    
    //CREATE 3D TISSUE
    make_cell_side_ALL();
    
    Time=0;
    
    //INITIAL EDGE LENGTHS
    for(int i=1; i<=Ne; i++) if(e[i][0]!=0) e_length[i]=edge_length(i);
    
    //INITIAL CELL AREAS
    for(int i = 1; i <= Nc; i++) if(edges[i][1]!=0) c_area[i]=CellArea_new(i);
    
    //printf("Lx=%g  Ly=%g\n", perioXYZ[0], perioXYZ[1]);
}
//****************************************************************************
void rescale_box(double desiredL){
    
    for(int i=1; i<=Nv; i++){
        v[i][1]*=desiredL/perioXYZ[0];
        v[i][2]*=desiredL/perioXYZ[1];
    }
    
    perioXYZ[0] = desiredL;
    perioXYZ[1] = desiredL;
    
    for(int i=1; i<=Nv; i++) torus_vertex(i);
    
    for(int i = 1; i<=Nc; i++) if(edges[i][1]!=0) cell_center(i,0);
}
//****************************************************************************
int central_cell(){
    int iMIN;
    double minDist=1000;
    for(int i=1; i<=Nc; i++){
        int passID=c_cent[i];
        double xcoor=v_pass[passID][1];
        double ycoor=v_pass[passID][2];
        double rDIST=sqrt(pow(xcoor-perioXYZ[0]/2.,2)+pow(ycoor-perioXYZ[1]/2.,2));
        if(rDIST<minDist){
            minDist=rDIST;
            iMIN=i;
        }
    }
    return iMIN;
}
//****************************************************************************
int central_edge(){
    int jMIN;
    double minDistE=1000;
    for(int j=1; j<=Ne; j++){
        int vID=e[j][1];
        double xcoor=v[vID][1];
        double ycoor=v[vID][2];
        
        double rDIST=sqrt(pow(xcoor-perioXYZ[0]/2.,2)+pow(ycoor-perioXYZ[1]/2.,2));
        if(rDIST<minDistE){
            minDistE=rDIST;
            jMIN=j;
        }
    }
    return jMIN;
}
//****************************************************************************
void make_a_hole(){
    
    int THEcell=central_cell(); c_coordSphere[THEcell]=1;
    for(int j=3; j<=2+edges[THEcell][2]; j++){
        int edID=abs(edges[THEcell][j]);
        int c1=e_cell1[edID]; if(c_coordSphere[c1]==0) c_coordSphere[c1]=2;
        int c2=e_cell2[edID]; if(c_coordSphere[c2]==0) c_coordSphere[c2]=2;
    }
    for(int k=2; k<=2; k++){
        for(int i=1; i<=Nc; i++) if(c_coordSphere[i]==k){
            for(int j=3; j<=2+edges[i][2]; j++){
                int edID=abs(edges[i][j]);
                int c1=e_cell1[edID]; if(c_coordSphere[c1]==0) c_coordSphere[c1]=k+1;
                int c2=e_cell2[edID]; if(c_coordSphere[c2]==0) c_coordSphere[c2]=k+1;
            }
        }
    }
    
    //DISSOLVE CELL
    for(int i=1; i<=Nc; i++) if(c_coordSphere[i]!=0) dissolve_cell(i);
    for(int i=1; i<=Nc; i++) if(c_coordSphere[i]!=0) {delete_cell_from_list(i); deletedCells++;}
    
    //DISSOLVE EDGES
    for(int i=1; i<=Ne; i++) if(e[i][0]!=0 && e_cell1[i]==0 && e_cell2[i]==0) dissolve_edge(i);
    
    //DISSOLVE VERTICES
    for(int i=1; i<=Nv; i++) if(v[i][0]>0.5 && v_cells[i][2]==0) dissolve_vertex(i);
    
    //GET RID OF EXTRA VERTICES
    for(int i=1; i<=Nv; i++) if(v[i][0]!=0 && v_edges[i][2]==2) merge_vertices(v_edges[i][3]);
}
//****************************************************************************
void out_Vertissue2D(int n){
    
    char filename2[50]; snprintf(filename2, sizeof(char) * 50, "./output/final_%d_%f_%f_%d.vt2d", (int)Nc, P0, kA, n);
    FILE *file1; file1 = fopen(filename2, "wt");
    int nrV=0, nrE=0, nrC=0;
    
    //ALLOCATE INTERNAL VARIABLES
    int **v_natural_id;
    int **e_natural_id;
    int **c_natural_id;
    v_natural_id  = new int*[Nv+1];
    e_natural_id  = new int*[Ne+1];
    c_natural_id  = new int*[Nc+1];
    for(int i=0; i < Nv+1; i++){
        v_natural_id[i]  = new int[3];
    }
    for(int i=0; i < Ne+1; i++){
        e_natural_id[i]  = new int[3];
    }
    for(int i=0; i < Nc+1; i++){
        c_natural_id[i]  = new int[3];
    }
    
    //RESET NATURAL IDS
    for(int i=1; i<=Nv; i++){
        v_natural_id[i][1]=0;
        v_natural_id[i][2]=0;
    }
    for(int i=1; i<=Ne; i++){
        e_natural_id[i][1]=0;
        e_natural_id[i][2]=0;
    }
    for(int i=1; i<=Nc; i++){
        c_natural_id[i][1]=0;
        c_natural_id[i][2]=0;
    }
    
    //VERTICES
    int cnt=0;
    for(int i=1; i<=Nv; i++){
        if(v[i][0]!=0){
            cnt++;
            v_natural_id[i][1]=cnt;
            v_natural_id[cnt][2]=i;
        }
    }
    nrV=cnt;
    
    //EDGES
    cnt=0;
    for(int i=1; i<=Ne; i++){
        if(e[i][0]!=0){
            cnt++;
            e_natural_id[i][1]=cnt;
            e_natural_id[cnt][2]=i;
        }
    }
    nrE=cnt;
    
    //CELLS
    cnt=0;
    for(int i=1; i<=Nc; i++){
        if(edges[i][1]!=0){
            cnt++;
            c_natural_id[i][1]=cnt;
            c_natural_id[cnt][2]=i;
        }
    }
    nrC=cnt;
    fprintf(file1, "%d  %d  %d\n\n", nrV, nrE, nrC);
    fprintf(file1, "%g  %g\n\n", perioXYZ[0], perioXYZ[1]);
    
    
    //VERTICES
    for(int i=1; i<=Nv; i++) if(v[i][0]!=0){
        if(v_edges[i][2]>3) fprintf(file1, "%f  %f  %f  %d\n", v[i][1], v[i][2], v_clock[i], v_T1dir[i]);
        else fprintf(file1, "%f  %f  0  0\n", v[i][1], v[i][2]);
    }
    fprintf(file1, "\n");
    
    //EDGES
    for(int i=1; i<=Ne; i++)if(e[i][0]!=0) fprintf(file1, "%d  %d  0\n", v_natural_id[e[i][1]][1], v_natural_id[e[i][2]][1]);
    fprintf(file1, "\n");
    
    //CELLS
    for(int i=1; i<=Nc; i++){
        if(edges[i][1]!=0){
            fprintf(file1, "%d  ", edges[i][2]);
            for(int j=3; j<=2+edges[i][2]; j++){
                if(edges[i][j]<0) fprintf(file1, "%d  ", -e_natural_id[abs(edges[i][j])][1]);
                else fprintf(file1, "%d  ", e_natural_id[abs(edges[i][j])][1]);
            }
            for(int j=12; j>edges[i][2]; j--){
                fprintf(file1, "0  ");
            }
            fprintf(file1, "\n");
        }
    }
    
    //DEALLOCATE INTERNAL VARIABLES
    for(int i=0; i < Nv+1; ++i){
        delete [] v_natural_id[i] ;
    }
    for(int i=0; i < Ne+1; ++i){
        delete [] e_natural_id[i] ;
    }
    for(int i=0; i < Nc+1; ++i){
        delete [] c_natural_id[i] ;
    }
    delete [] v_natural_id;
    delete [] e_natural_id;
    delete [] c_natural_id;
    
    fclose(file1);
}
//****************************************************************************
double calc_rRIM(){
    CentX=0;
    CentY=0;
    int nrVr=0;
    for(int i = 1; i <= Nv; i++) if(v[i][0]>0.5 && v_cells[i][2]<3){
        CentX+=v[i][1];
        CentY+=v[i][2];
        nrVr++;
    }
    CentX/=nrVr;
    CentY/=nrVr;
    
    double rAVG=0;
    for(int i = 1; i <= Nv; i++) if(v[i][0]>0.5 && v_cells[i][2]<3){
        double rr=sqrt(pow(v[i][1]-CentX,2)+pow(v[i][2]-CentY,2));
        rAVG+=rr/nrVr;
    }
    return rAVG;
}
//****************************************************************************
