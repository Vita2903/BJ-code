//****************************************************************************
//****************************************************************************
//***************************LIST MANIPULATION********************************
//****************************************************************************
//****************************************************************************
void remove_edge_from_edges(int edg_id, int cell_id){
    
    for(int i=3; i<=2+edges[cell_id][2]; i++){
        if(abs(edges[cell_id][i])==edg_id){
            for(int j=i; j<2+edges[cell_id][2]; j++){
                edges[cell_id][j]=edges[cell_id][j+1];
            }
        }
    }
    edges[cell_id][2]-=1;
}
//****************************************************************************
int insert_edge_to_edges(int edg_id, int cell_id, int edg_prev, int edg_next){
    
    int vstart;
    
    for(size_t i=3; i<2+edges[cell_id][2]; i++){
        if(abs(edges[cell_id][i])==edg_prev && abs(edges[cell_id][i+1])==edg_next){
            for(size_t j=2+edges[cell_id][2]+1; j>i+2; j--){
                edges[cell_id][j]=edges[cell_id][j-1];
            }
            if(edges[cell_id][i]>0) vstart=e[abs(edges[cell_id][i])][2];
            else if(edges[cell_id][i]<0) vstart=e[abs(edges[cell_id][i])][1];
            if(vstart==e[edg_id][1]){
                edges[cell_id][i+2]=edges[cell_id][i+1];
                edges[cell_id][i+1]=edg_id;
            }
            else if (vstart==e[edg_id][2]){
                edges[cell_id][i+2]=edges[cell_id][i+1];
                edges[cell_id][i+1]=-edg_id;
            }
            edges[cell_id][2]+=1;
            return 0;
        }
        else if(abs(edges[cell_id][i])==edg_next && abs(edges[cell_id][i+1])==edg_prev){
            for(size_t j=2+edges[cell_id][2]+1; j>i+2; j--){
                edges[cell_id][j]=edges[cell_id][j-1];
            }
            if(edges[cell_id][i]>0) vstart=e[abs(edges[cell_id][i])][2];
            else if(edges[cell_id][i]<0) vstart=e[abs(edges[cell_id][i])][1];
            if(vstart==e[edg_id][1]){
                edges[cell_id][i+2]=edges[cell_id][i+1];
                edges[cell_id][i+1]=edg_id;
            }
            else if (vstart==e[edg_id][2]){
                edges[cell_id][i+2]=edges[cell_id][i+1];
                edges[cell_id][i+1]=-edg_id;
            }
            edges[cell_id][2]+=1;
            return 0;
        }
        
    }
    size_t i=2+edges[cell_id][2];
    if(abs(edges[cell_id][i])==edg_prev && abs(edges[cell_id][3])==edg_next){
        if(edges[cell_id][i]>0) vstart=e[abs(edges[cell_id][i])][2];
        else if(edges[cell_id][i]<0) vstart=e[abs(edges[cell_id][i])][1];
        if(vstart==e[edg_id][1]) edges[cell_id][i+1]=edg_id;
        else if (vstart==e[edg_id][2]) edges[cell_id][i+1]=-edg_id;
    }
    else if(abs(edges[cell_id][i])==edg_next && abs(edges[cell_id][3])==edg_prev){
        if(edges[cell_id][i]>0) vstart=e[abs(edges[cell_id][i])][2];
        else if(edges[cell_id][i]<0) vstart=e[abs(edges[cell_id][i])][1];
        if(vstart==e[edg_id][1]) edges[cell_id][i+1]=edg_id;
        else if (vstart==e[edg_id][2]) edges[cell_id][i+1]=-edg_id;
    }
    edges[cell_id][2]+=1;
    return 0;
}
//****************************************************************************
int divide_cell_in_edge_network(int i, int e1, int e2, int ee1, int ee2, int newe){
    
    int edges_copy[15];
    int edges_newc[15];
    
    //MAKES COPY OF CELL i
    int j,k;
    for(j=1; j<=2+edges[i][2]; j++){
        edges_copy[j]=edges[i][j];
    }
    
    //MAKES NEW CELL i
    edges[i][1]=i;
    edges[i][2]=0;
    j=3;
    while(abs(edges_copy[j])!=e1){
        edges[i][j]=edges_copy[j];
        j++;
    }
    //
    k=3;
    if(edges_copy[j]>0){
        edges[i][j]=e1;
        edges_newc[k]=ee1;
    }
    else{
        edges[i][j]=-ee1;
        edges_newc[k]=-e1;
    }
    k++;
    j++;
    //
    edges[i][j]=newe;
    j++;
    //
    int jj=j-1;
    while(abs(edges_copy[jj])!=e2){
        edges_newc[k]=edges_copy[jj];
        k++;
        jj++;
    }
    if(edges_copy[jj]>0){
        edges[i][j]=ee2;
        edges_newc[k]=e2;
    }
    else{
        edges[i][j]=-e2;
        edges_newc[k]=-ee2;
    }
    k++;
    jj++;
    j++;
    //
    while(jj<=2+edges_copy[2]){
        edges[i][j]=edges_copy[jj];
        jj++;
        j++;
    }
    edges[i][2]=j-3;
    //
    edges_newc[k]=-newe;
    k++;
    edges_newc[2]=k-3;
    for(j=k; j<=14; j++){
        edges_newc[j]=0;
    }
    
    //MAKE NEW CELL
    int newc=make_cell(edges_newc[2],edges_newc[3],edges_newc[4],edges_newc[5],edges_newc[6],edges_newc[7],edges_newc[8],edges_newc[9],edges_newc[10],edges_newc[11],edges_newc[12],edges_newc[13],edges_newc[14]);
    
    return newc;
}
//****************************************************************************
void replace_one_edge_with_two_edges(int i, int e1, int ee1){
    
    int j;
    for(j=2+edges[i][2]+1;j>=4;j--){
        if(abs(edges[i][j-1])==e1){
            if(edges[i][j-1]>0) {
                edges[i][j]=ee1;
                edges[i][j-1]=e1;
            }
            else {
                edges[i][j]=-e1;
                edges[i][j-1]=-ee1;
            }
            break;
        }
        else edges[i][j]=edges[i][j-1];
    }
    edges[i][2]+=1;
    
}
//****************************************************************************
