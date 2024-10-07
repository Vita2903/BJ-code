//****************************************************************************
//****************************************************************************
//***********************T1***************************************************
//****************************************************************************
//****************************************************************************
int nr_of_triangles(int eID){
    int nrTRI=0;
    for(int i=1; i<=e_cells[eID][0]; i++){
        int cID=e_cells[eID][i];
        if( c[cID][0]==3 ) nrTRI++;
    }
    return nrTRI;
}
//****************************************************************************
int appropriate_for_T1(int i){
    if( nr_of_triangles(i)!=0 ) return 0;
    if( v_edges[e[i][1]][0]>3 || v_edges[e[i][2]][0]>3 ) return 0;
    return 1;
}
//****************************************************************************
void T1_transitions(double fin_len, double clck, int flag){
    
    if(flag==1 || flag==12){
        //EDGE-TO-VERTEX
        for(int i=1; i<=Ne; i++) if(exist[2][i]==1){
            if(appropriate_for_T1(i) && e_length[i]<lth && e_dl[i]<0 ){
                printf("EV transition\n");
                printf("%d\n", e_cells[i][0]);
                printf("%d\n", e_Vcells[i][0]);
                int vID=T1_EDGE_TO_VERTEX(i);
                v_clock[vID]=0;
            }
        }
    }
    
    if(flag==2 || flag==12){
        //VERTEX-TO-EDGE
        for(int i=1; i<=Nv; i++) if(exist[1][i]==1 && v_edges[i][0]==4){
            if( v_clock[i]>=clck) {
                printf("VE transition\n");
                int newe=T1_VERTEX_TO_EDGE(i,fin_len);
                v_clock[i]=0;
                e_g[newe]=Sig*GaussianVariate();
            }
            else v_clock[i]+=h;
        }
    }
        
}
//****************************************************************************
