//****************************************************************************
//****************************************************************************
//***********************INITIAL STRUCTURE************************************
//****************************************************************************
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
    }

    //EDGES
    int v1, v2;
    int blank3;
    for(int i=1; i<=nrE; i++){
        fscanf(file1, "%d  %d  %d\n", &v1, &v2, &blank3);
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
    
    //printf("%g  %g\n", perioXYZ[1], perioXYZ[2]);
    
    fclose(file1);
}

