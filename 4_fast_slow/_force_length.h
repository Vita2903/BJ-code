//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
double edge_length(int i){
    double ddx,ddy;
    double *dxdydz = new double[3]; dxdydz[1]=0; dxdydz[2]=0;
    int v1=e[i][1], v2=e[i][2];
    torus_dx_dy_dz(dxdydz,v1,v2);
    ddx=v[v2][1]-(v[v1][1]+dxdydz[1]);
    ddy=v[v2][2]-(v[v1][2]+dxdydz[2]);
    delete []dxdydz;
    return sqrt(ddx*ddx+ddy*ddy);
}
//****************************************************************************
double e_length_force(int i){
            
    double ddx,ddy;
    double *dxdydz = new double[3]; dxdydz[1]=0; dxdydz[2]=0;
    int v1=e[i][1], v2=e[i][2];
    torus_dx_dy_dz(dxdydz,v1,v2);
    ddx=v[v2][1]-(v[v1][1]+dxdydz[1]);
    ddy=v[v2][2]-(v[v1][2]+dxdydz[2]);
    delete []dxdydz;
    
    double eg=0;
    if(e_cells[i][0]==2) eg=e_g[i];
    else eg=eGamma+g_adh;
    double c0=-eg/e_length[i];
    
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
    double *dxdydz = new double[3]; dxdydz[1]=0; dxdydz[2]=0;
    int v1=e[i][1], v2=e[i][2];
    torus_dx_dy_dz(dxdydz,v1,v2);
    ddx=v[v2][1]-(v[v1][1]+dxdydz[1]);
    ddy=v[v2][2]-(v[v1][2]+dxdydz[2]);
    delete []dxdydz;
    
    return (ddx*(v_F[v2][1]-v_F[v1][1])+ddy*(v_F[v2][2]-v_F[v1][2]))/e_length[i];
}
//****************************************************************************
double e_pdotCalc(){
    double pdot=0;
    for(int i=1; i<=Ne; i++) if(exist[2][i]==1 && e_cells[i][0]<2) pdot+=e_ldotCalc(i);
    return pdot;
}
//****************************************************************************
double wound_perimeter(){
    double perTOT=0;
    for(int i=1; i<=Ne; i++) if(exist[2][i]==1 && e_cells[i][0]<2) perTOT+=e_length[i];
    return perTOT;
}
//****************************************************************************
double cell_perimeter(int i){
    double _cperimeter=0.;
    for(int j = 1; j <= c[i][0]; ++j) _cperimeter += e_length[abs(c[i][j])];
    return _cperimeter;
}
//****************************************************************************
void e_perimeter_force(int i, double cperimeter){

    double ddx,ddy;

    double *dxdydz = new double[3]; dxdydz[1]=0; dxdydz[2]=0;
    int v1=e[i][1], v2=e[i][2];
    torus_dx_dy_dz(dxdydz,v1,v2);
    ddx=v[v2][1]-(v[v1][1]+dxdydz[1]);
    ddy=v[v2][2]-(v[v1][2]+dxdydz[2]);
    delete []dxdydz;

    //GRADIENT
    const double c0 = -2.*(cperimeter-P0)/e_length[i];

    v_F[v1][1] += -c0*ddx;
    v_F[v1][2] += -c0*ddy;

    v_F[v2][1] += c0*ddx;
    v_F[v2][2] += c0*ddy;

}
//****************************************************************************
double c_Perimeter_force(int i){
    double _cperimeter=cell_perimeter(i);
    for(int j=1; j <= c[i][0]; j++) e_perimeter_force(abs(c[i][j]),_cperimeter);
    return pow(_cperimeter-P0,2);
}
//****************************************************************************
