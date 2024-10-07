//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
double e_LineTension_force(int i){
        
    double ddx,ddy;
    double *dxdydz = new double[2]; dxdydz[0]=0; dxdydz[1]=0;
    int v1=e[i][1], v2=e[i][2];
    torus_dx_dy_dz(dxdydz,v1,v2);
    ddx=v[v2][1]-(v[v1][1]+dxdydz[0]);
    ddy=v[v2][2]-(v[v1][2]+dxdydz[1]);
    delete []dxdydz;
    
    double eg=e_g[i];
    if(e_cell2[i]==0) eg+=g_adh;
    //else eg+=e_g[i];
    double c0 = -eg/e_length[i];
    if(e_length[i]<0.000001) c0=0;
    
    //v1
    v_F[v1][1]+=-c0*ddx;
    v_F[v1][2]+=-c0*ddy;
    
    //v2
    v_F[v2][1]+=c0*ddx;
    v_F[v2][2]+=c0*ddy;
    
    return eg*e_length[i];
}
//****************************************************************************
double e_ldotCalc(int i){
    
    double ddx,ddy;
    double *dxdydz = new double[2]; dxdydz[0]=0; dxdydz[1]=0;
    int v1=e[i][1], v2=e[i][2];
    torus_dx_dy_dz(dxdydz,v1,v2);
    ddx=v[v2][1]-(v[v1][1]+dxdydz[0]);
    ddy=v[v2][2]-(v[v1][2]+dxdydz[1]);
    delete []dxdydz;
    
    return (ddx*(v_F[v2][1]-v_F[v1][1])+ddy*(v_F[v2][2]-v_F[v1][2]))/e_length[i];
}
//****************************************************************************
double cell_perimeter(int i){
    double _bperimeter=0.;
    for(size_t j = 3; j <= 2+edges[i][2]; ++j) _bperimeter += e_length[abs(edges[i][j])];
    return _bperimeter;
}
//****************************************************************************
void f_Perimeter_force(int i, double bperimeter){

    double ddx,ddy;

    double *dxdydz = new double[2]; dxdydz[0]=0; dxdydz[1]=0;
    int v1=e[i][1], v2=e[i][2];
    torus_dx_dy_dz(dxdydz,v1,v2);
    ddx=v[v2][1]-(v[v1][1]+dxdydz[0]);
    ddy=v[v2][2]-(v[v1][2]+dxdydz[1]);
    delete []dxdydz;

    //GRADIENT
    const double c0 = -2.*(bperimeter-P0)/e_length[i];

    v_F[v1][1] += -c0*ddx;
    v_F[v1][2] += -c0*ddy;

    v_F[v2][1] += c0*ddx;
    v_F[v2][2] += c0*ddy;

}
//****************************************************************************
double c_Perimeter_force(int cell_id){
    double _perimeter=cell_perimeter(cell_id);
    for(int j=3; j <= 2+edges[cell_id][2]; j++) f_Perimeter_force(abs(edges[cell_id][j]),_perimeter);
    return pow(_perimeter-P0,2);
}
//****************************************************************************
