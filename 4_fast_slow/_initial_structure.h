//****************************************************************************
//****************************************************************************
//***********************INITIAL STRUCTURE************************************
//****************************************************************************
//****************************************************************************
int central_vertex(){
    double Cent=perioXYZ[1]/2.;
    int iMIN;
    double minDist=1000;
    for(int i=1; i<=Nv; i++) if(exist[1][i]==1){
        double xx=v[i][1];
        double yy=v[i][2];
        double d0=sqrt(pow(xx-Cent,2)+pow(yy-Cent,2));
        if(d0<minDist){
            minDist=d0;
            iMIN=i;
        }
    }
    return iMIN;
}
//****************************************************************************
//int central_edge(){
//    int jMIN;
//    double minDistE=1000;
//    for(int j=1; j<=Ne; j++){
//        int vID=e[j][1];
//        double xcoor=v[vID][1];
//        double ycoor=v[vID][2];
//
//        double rDIST=sqrt(pow(xcoor-perioXYZ[0]/2.,2)+pow(ycoor-perioXYZ[1]/2.,2));
//        if(rDIST<minDistE){
//            minDistE=rDIST;
//            jMIN=j;
//        }
//    }
//    return jMIN;
//}
//****************************************************************************
void make_a_hole(){
    
    int cVertex=central_vertex(); printf("%d\n", cVertex);
    for(int i=1; i<=v_cells[cVertex][0]; i++) printf("%d  ", v_cells[cVertex][i]);
    printf("\n");
    
//    int THEcell=central_cell(); c_coordSphere[THEcell]=1;
//    for(int j=3; j<=2+edges[THEcell][2]; j++){
//        int edID=abs(edges[THEcell][j]);
//        int c1=e_cell1[edID]; if(c_coordSphere[c1]==0) c_coordSphere[c1]=2;
//        int c2=e_cell2[edID]; if(c_coordSphere[c2]==0) c_coordSphere[c2]=2;
//    }
//    for(int k=2; k<=2; k++){
//        for(int i=1; i<=Nc; i++) if(c_coordSphere[i]==k){
//            for(int j=3; j<=2+edges[i][2]; j++){
//                int edID=abs(edges[i][j]);
//                int c1=e_cell1[edID]; if(c_coordSphere[c1]==0) c_coordSphere[c1]=k+1;
//                int c2=e_cell2[edID]; if(c_coordSphere[c2]==0) c_coordSphere[c2]=k+1;
//            }
//        }
//    }
    
    //DISSOLVE CELL
    dissolve_cell(16); delete_cell(16);
    dissolve_cell(125); delete_cell(125);
    dissolve_cell(199); delete_cell(199);
    
    //DISSOLVE EDGES
    for(int i=1; i<=Ne; i++) if(exist[2][i]==1){
        if(e_cells[i][0]==0) dissolve_edge(i,0);
    }
    
    //DISSOLVE VERTICES
    for(int i=1; i<=Nv; i++) if(exist[1][i]==1){
        if(v_edges[i][0]==0) dissolve_vertex(i);
    }
}
//****************************************************************************
void set_initial_fromFile(){
    
    int *sides; sides = new int[13];
    int nrSides, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15;
    
    //FILE
    char filename2[100];
    snprintf(filename2, sizeof(char) * 100, "./initial/final_324_%g_%g.vt2d", kA, P0);
    FILE *file1; file1 = fopen(filename2, "rt");
    
    
    //V,E,P,C
    int nrV=0, nrE=0, nrC=0;
    fscanf(file1, "%d  %d  %d\n", &nrV, &nrE, &nrC);
    
    //perioXYZ
    fscanf(file1, "%lf  %lf\n", &perioXYZ[1], &perioXYZ[2]);
    
    //VERTICES
    double xx, yy, blank1, blank2;
    for(int i=1; i<=nrV; i++){
        fscanf(file1, "%lf  %lf  %lf  %lf\n", &xx, &yy, &blank1, &blank2);
        make_vertex(xx,yy);
//        printf("%g  %g\n", xx, yy);
    }

    //EDGES
    int v1, v2;
    double blank3;
    for(int i=1; i<=nrE; i++){
        fscanf(file1, "%d  %d  %lf\n", &v1, &v2, &blank3);
//        printf("%d  %d\n", v1, v2);
        make_edge(v1,v2,0);
    }

    //POLYGONS
    for(int i=0; i<=12; i++) sides[i]=0;
    for(int i=1; i<=nrC; i++){
        fscanf(file1, "%d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d\n", &nrSides, &b1, &b2, &b3, &b4, &b5, &b6, &b7, &b8, &b9, &b10, &b11, &b12);
        if(b1!=0) sides[1]=b1;
        if(b2!=0) sides[2]=b2;
        if(b3!=0) sides[3]=b3;
        if(b4!=0) sides[4]=b4;
        if(b5!=0) sides[5]=b5;
        if(b6!=0) sides[6]=b6;
        if(b7!=0) sides[7]=b7;
        if(b8!=0) sides[8]=b8;
        if(b9!=0) sides[9]=b9;
        if(b10!=0) sides[10]=b10;
        if(b11!=0) sides[11]=b11;
        if(b12!=0) sides[12]=b12;
        cell_sides(nrSides,sides,0);
    }
    delete [] sides;
    
    //MAKE CELLS
    for(int i=1; i<=Nc; i++) if(c[i][0]!=0) make_cell(i);
    
//    make_a_hole();
    
    fclose(file1);
}
//****************************************************************************
void set_initial_fromFile_old(){
    
    int *sides; sides = new int[13];
    int nrSides, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15;
    
    //FILE
    char filename2[100];
    snprintf(filename2, sizeof(char) * 100, "./initial/old/final_%g.vt2d", P0);
    FILE *file1; file1 = fopen(filename2, "rt");
    
    
    //V,E,P,C
    int nrV=0, nrE=0, nrC=0;
    fscanf(file1, "%d  %d  %d\n", &nrV, &nrE, &nrC);
    
    //perioXYZ
    fscanf(file1, "%lf  %lf\n", &perioXYZ[1], &perioXYZ[2]);
    
    //VERTICES
    double xx, yy, blank1, blank2;
    for(int i=1; i<=nrV; i++){
        fscanf(file1, "%lf  %lf\n", &xx, &yy);
        make_vertex(xx,yy);
    }

    //EDGES
    int v1, v2;
    double blank3;
    for(int i=1; i<=nrE; i++){
        fscanf(file1, "%d  %d\n", &v1, &v2);
        make_edge(v1,v2,0);
    }

    //POLYGONS
    for(int i=0; i<=12; i++) sides[i]=0;
    for(int i=1; i<=nrC; i++){
        fscanf(file1, "%d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d\n", &nrSides, &b1, &b2, &b3, &b4, &b5, &b6, &b7, &b8, &b9, &b10, &b11, &b12, &b13, &b14, &b15);
        if(b1!=0) sides[1]=b1;
        if(b2!=0) sides[2]=b2;
        if(b3!=0) sides[3]=b3;
        if(b4!=0) sides[4]=b4;
        if(b5!=0) sides[5]=b5;
        if(b6!=0) sides[6]=b6;
        if(b7!=0) sides[7]=b7;
        if(b8!=0) sides[8]=b8;
        if(b9!=0) sides[9]=b9;
        if(b10!=0) sides[10]=b10;
        if(b11!=0) sides[11]=b11;
        if(b12!=0) sides[12]=b12;
        cell_sides(nrSides,sides,0);
    }
    delete [] sides;
    
    //MAKE CELLS
    for(int i=1; i<=Nc; i++) if(c[i][0]!=0) make_cell(i);
    
    //printf("%g  %g\n", perioXYZ[1], perioXYZ[2]);
    
    fclose(file1);
}
//****************************************************************************
