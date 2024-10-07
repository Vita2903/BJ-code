//****************************************************************************
//****************************************************************************
//***************************DISSOLVE*****************************************
//****************************************************************************
//****************************************************************************
void dissolve_vertex(int i){
        
    //VERTEX
    v[i][0]=0;
    v[i][1]=0;
    v[i][2]=0;
    
    //ATTRIBUTES
    v_F[i][1]=0; v_F[i][2]=0;
    v_cells[i][1]=0; v_cells[i][2]=0;
    v_edges[i][1]=0; v_edges[i][2]=0;
    v_T1dir[i]=0;
    v_edgeT1[i]=0;
    
    v_freeId.add(i);
}
//****************************************************************************
void dissolve_vertex_pass(int i){
        
    //PASSIVE VERTEX
    v_pass[i][0]=0;
    v_pass[i][1]=0;
    v_pass[i][2]=0;
    
    //ATTRIBUTES OF OTHER ELEMENTS
    if(v_pass_cell[i]!=0) c_cent[v_pass_cell[i]]=0;
    
    //ATTRIBUTES
    v_pass_cell[i]=0;
    
    v_pass_freeId.add(i);
}
//****************************************************************************
void dissolve_edge(int i){
        
    //ATTRIBUTES OF OTHER ELEMENTS
    for(int j=1; j<=2; j++){
        int vert_id=e[i][j];
        for(int k=3; k<=2+v_edges[vert_id][2]; k++){
            if(v_edges[vert_id][k]==i){
                v_edges[vert_id][k]=v_edges[vert_id][2+v_edges[vert_id][2]];
                v_edges[vert_id][2]--;
            }
        }
    }
    
    //EDGE
    e[i][0]=0;
    e[i][1]=0;
    e[i][2]=0;
    
    //ATTRIBUTES
    e_cell1[i]=0;
    e_cell2[i]=0;
    e_length[i]=0;
    e_dldt[i]=0;
    e_g[i]=0;
    
    //e_freeId.add(i);
}
//****************************************************************************
void dissolve_cell(int i){
    
    int pass_vert=v_pass_cell[i];
    
    //PASSIVE VERTICES
    dissolve_vertex_pass(pass_vert);
    
    int vert_id, edge_id;
    
    //DELETES LIST vertices ( is recreated by make_cell_side() )
    for(size_t j=3; j<=2+edges[i][2]; j++){
        
        //v_cell
        vert_id=vertices[i][j];
        for(int k=3; k<=2+v_cells[vert_id][2]; k++){
            if(v_cells[vert_id][k]==i){
                v_cells[vert_id][k]=v_cells[vert_id][2+v_cells[vert_id][2]];
                v_cells[vert_id][2]--;
            }
        }
        
        //vertices
        vertices[i][j]=0;
        
        //e_cell
        edge_id=abs(edges[i][j]);
        if(e_cell1[edge_id]==i) e_cell1[edge_id]=0;
        if(e_cell2[edge_id]==i) e_cell2[edge_id]=0;
    }
    vertices[i][1]=0;
    vertices[i][2]=0;
    
    //ATTRIBUTES
    c_cent[i]=0;
}
//****************************************************************************
void delete_cell_from_list(int i){
        
    for(size_t j=0; j<=14; j++) edges[i][j]=0;
    
    //ATTRIBUTES
    c_area[i]=0;
    c_coordSphere[i]=0;
    
    c_freeId.add(i);
}
//****************************************************************************
