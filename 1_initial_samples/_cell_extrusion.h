//****************************************************************************
//****************************************************************************
//******************************CELL EXTRUSION********************************
//****************************************************************************
//****************************************************************************
void ReadFromLists_T2(int *edgesE, int *cellsC, int *edgesEE, int *verticesV){

    //IDENTIFIES EDGES e
    edgesE[1]=0; edgesE[2]=0; edgesE[3]=0;
    for(int j=1; j<=Ne; j++) if(e[j][0]!=0 && e_cell2[j]==0){
        if(edgesE[1]==0) edgesE[1]=j;
        else if(edgesE[2]==0) edgesE[2]=j;
        else edgesE[3]=j;
    }
    //printf("%d  %d  %d\n", edgesE[1], edgesE[2], edgesE[3]);
    
    //IDENTIFIES VERTICES v
    verticesV[1]=0; verticesV[2]=0; verticesV[3]=0;
    int EID=edgesE[1];
    verticesV[1]=e[EID][1];
    verticesV[2]=e[EID][2];
    for(int j=2; j<=3; j++){
        int EID=edgesE[j];
        int v1=e[EID][1]; int v2=e[EID][2];
        if(v1!=verticesV[1] && v1!=verticesV[2]) {verticesV[3]=v1; break;}
        if(v2!=verticesV[1] && v2!=verticesV[2]) {verticesV[3]=v2; break;}
    }
    //printf("%d  %d  %d\n", verticesV[1], verticesV[2], verticesV[3]);
    
    //IDENTIFIES CELLS c
    for(int j=1; j<=3; j++) cellsC[j]=e_cell1[edgesE[j]];
    //printf("%d  %d  %d\n", cellsC[1], cellsC[2], cellsC[3]);
    
    //IDENTIFIES EDGES ee
    edgesEE[1]=0; edgesEE[2]=0; edgesEE[3]=0;
    for(int j=1; j<=3; j++) {
        int vert_id=verticesV[j];
        for(int k=3; k<=5; k++) if( v_edges[vert_id][k]!=edgesE[1] && v_edges[vert_id][k]!=edgesE[2] && v_edges[vert_id][k]!=edgesE[3] ) edgesEE[j]=v_edges[vert_id][k];
    }
    //printf("%d  %d  %d\n", edgesEE[1], edgesEE[2], edgesEE[3]);
    
}
//****************************************************************************
int close_up_the_hole(){
    
    //FINDS ELEMENTS ASSOCIATED WITH TRANSFORMATION
    int *edgesE; edgesE = new int[4];
    int *cellsC; cellsC = new int[4];
    int *edgesEE; edgesEE = new int[4];
    int *verticesV; verticesV = new int[4];
    ReadFromLists_T2(edgesE,cellsC,edgesEE,verticesV);
    
    //READS CENTER OF EXTRUDING CELL
    int v1=verticesV[1], v2=verticesV[2], v3=verticesV[3]; //printf("%d  %d  %d\n", v_edges[v1][2], v_edges[v2][2], v_edges[v3][2]);
    if( v_edges[v1][2]>3 || v_edges[v2][2]>3 || v_edges[v3][2]>3 ) return 0;
    double x_cent=(v[v1][1]+v[v2][1]+v[v3][1])/3.;
    double y_cent=(v[v1][2]+v[v2][2]+v[v3][2])/3.;
    //printf("(%g,%g)\n", x_cent, y_cent);

    //DISSOLVES CELLS c1, c2 & c3
    for(int j=1; j<=3; j++) dissolve_cell(cellsC[j]);

    //DISSOLVES EDGES e1,e2 & e3
    for(int j=1; j<=3; j++) dissolve_edge(edgesE[j]);

    //DISSOLVES VERTICES v2 & v3
    for(int j=2; j<=3; j++) dissolve_vertex(verticesV[j]);

    //MOVES VERTEX v1 TO THE CENTER
    v[verticesV[1]][1]=x_cent; v[verticesV[1]][2]=y_cent;

    //RESTITCHES EDGES ee
    for(int j=1; j<=3; j++) {
        if(e[edgesEE[j]][1]==verticesV[j]){
            v1=verticesV[1];
            v2=e[edgesEE[j]][2];
        }
        else{
            v1=e[edgesEE[j]][1];
            v2=verticesV[1];
        }
        dissolve_edge(edgesEE[j]);
        make_edge(v1,v2,edgesEE[j]);
    }

    //REMOVES EDGES e1, e2 & e3 FROM edges
    for(int j=1; j<=3; j++) remove_edge_from_edges(edgesE[j],cellsC[j]);

    //REMAKES CELLS
    for(size_t j=1; j<=3; j++) make_cell_side(cellsC[j]);

    //DELETE ELEMENTS
    int remVert=verticesV[1];
    delete [] edgesE; delete [] cellsC; delete [] edgesEE; delete [] verticesV;

    printf("time: %g  %d\n", Time, remVert);
    return remVert;
}
//****************************************************************************
int seal_the_hole(){
    int ste=0; for(int i=1; i<=Ne; i++) if(e[i][0]!=0 && e_cell2[i]==0) ste++;
    if(ste==3) {
        close_up_the_hole();
        return 0;
    }
    return 1;
}
//****************************************************************************

