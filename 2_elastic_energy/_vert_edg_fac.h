//****************************************************************************
//****************************************************************************
//***********************VERT, EDG********************************************
//****************************************************************************
//****************************************************************************
int make_vertex(double x, double y){
    
    int v_id=v_freeId.get(Nv+1);
    v[v_id][0]=v_id;
    v[v_id][1]=x;
    v[v_id][2]=y;
    torus_vertex(v_id);
    
    v_cells[v_id][1]=v_id;
    v_edges[v_id][1]=v_id;
    
    if(v_id>Nv) Nv++;
    return v_id;
}
//****************************************************************************
int make_vertex_pass(double x, double y){
    
    int v_id=v_pass_freeId.get(Nv_pass+1);
    v_pass[v_id][0]=v_id;
    v_pass[v_id][1]=x;
    v_pass[v_id][2]=y;
    
    if(v_id>Nv_pass) Nv_pass++;
    return v_id;
}
//****************************************************************************
int make_edge(int v1, int v2, int e_id){
    
    e[e_id][0]=e_id;
    e[e_id][1]=v1;
    e[e_id][2]=v2;
    
    //v_edges
    //v1
    v_edges[v1][2]++;
    v_edges[v1][2+v_edges[v1][2]]=e_id;
    //v2
    v_edges[v2][2]++;
    v_edges[v2][2+v_edges[v2][2]]=e_id;
    
    //attributes
    e_length[e_id]=0;
    e_dldt[e_id]=0;
    e_g[e_id]=0;
    e_Fg[e_id]=0;
    
    if(e_id>Ne) Ne++;
    return e_id;
}
//****************************************************************************
