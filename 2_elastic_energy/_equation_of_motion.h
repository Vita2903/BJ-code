//****************************************************************************
//****************************************************************************
//***********************EQUATION OF MOTION***********************************
//****************************************************************************
//****************************************************************************
double calc_forces(){
    
    //AREA AND PERIMETER TERM
    wA=0; wP=0;
    for(int i = 1; i <= Nc; i++) if(edges[i][1]!=0){
        wA += c_AreaCompressibility_force_New(i); 
        wP += c_Perimeter_force(i); 
    }
    
    //LENGTH TERM
    wL=0;
    for(int i=1; i<=Ne; i++) if(e[i][0]!=0) wL+=e_LineTension_force(i);
    
    //MAX FORCE
    double Fmax=0;
    for(int i = 1; i <= Nv; i++) if(v[i][0]>0.5){
        double foRce=sqrt(v_F[i][1]*v_F[i][1]+v_F[i][2]*v_F[i][2]);
        if(foRce>Fmax) Fmax=foRce;
    }
    return Fmax;
    
}
//****************************************************************************
double tension_rate(){
    double FgMAX=0;
    for(int i=1; i<=Ne; i++) if(e[i][0]!=0){
        e_Fg[i] = -kM*e_g[i];
        double efgabs=fabs(e_Fg[i]);
        if(efgabs>FgMAX) FgMAX=efgabs;
    }
    return FgMAX;
}
//****************************************************************************
double adapt_timeStep(double FMAX, double FgMAX){
    double hr=2*h0; if(FMAX>0.00000001) hr=maxDR/FMAX;
    double hg=2*h0; if(FgMAX>0.00000001) hg=maxDg/FgMAX;
    if( hg<=hr ) {
        if(hg<h0) return hg;
        else return h0;
    }
    else{
        if(hr<h0) return hr;
        else return h0;
    }
}
//****************************************************************************
double propagate_tension(){
    double gMAX=0;
    for(int i=1; i<=Ne; i++) if(e[i][0]!=0){
        e_g[i] += h*e_Fg[i] + sqrt(2.*Sig*Sig*h*kM)*GaussianVariate();
        double gg=fabs(e_g[i]); if(gg>gMAX) gMAX=gg;
    }
    return gMAX;
}
//****************************************************************************
void reset_forces(){
    for(int i = 1; i <= Nv; i++) if(v[i][0]>0.5) for(int j = 1; j<=2; j++) v_F[i][j] = 0;
    for(int i = 1; i <= Ne; i++) if(e[i][0]!=0) e_Fg[i]=0;
}
//****************************************************************************
void update_lengths(){
    for(int i=1; i<=Ne; i++) if(e[i][0]!=0) {
        double elen=edge_length(i);
        e_dldt[i]=(elen-e_length[i])/h;
        e_length[i]=elen;
    }
}
//****************************************************************************
void project_on_constraints(double r0, double Cent){
    
    double d0, xx, yy;
    int cnt=0;
    for(int i=1; i<=Nv; i++) if(v[i][0]>0.5){
        
        cnt=0;
        for(int j=1; j<=v_edges[i][2]; j++) if(e_cell1[v_edges[i][2+j]]==0 || e_cell2[v_edges[i][2+j]]==0) cnt++;

        if(cnt!=0){
            xx=v[i][1];
            yy=v[i][2];
            d0=-(pow(xx-CentX,2)+pow(yy-CentY,2)-pow(r0,2))/(2*pow(xx-CentX,2)+2*pow(yy-CentY,2));
            v[i][1]+=d0*(xx-CentX);
            v[i][2]+=d0*(yy-CentY);
        }
    }
    
}
//****************************************************************************
double eqOfMotion(){
    
    
    //SET e_length[] AND c_area[]
    for(int i=1; i<=Ne; i++) if(e[i][0]!=0) e_length[i]=edge_length(i);
    for(int i=1; i<=Nc; i++) if(edges[i][1]!=0) c_area[i]=CellArea_new(i);
    
    
    //CALCULATES FORCES AND CHANGES OF TENSIONS
    double FMAX=calc_forces();
    double FgMAX=tension_rate();


    //ADAPT TIME STEP
    h=adapt_timeStep(FMAX,FgMAX);
    
    
    //PROPAGATE VERTICES
    for(int i = 1; i <= Nv; i++) if(v[i][0]>0.5){
        
        //MOVES VERTICES
        v[i][1] += h*v_F[i][1];
        v[i][2] += h*v_F[i][2];
        
        //PERIODIC BOUNDARY CONDITIONS
        torus_vertex(i);
    }
    
    
    //PROJECT ON CONSTRAINT
    if(rRIM>0) project_on_constraints(rRIM,perioXYZ[0]/2.);
    
    //PROPAGATE TENSIONS
    double gMAX=propagate_tension();
    
    
    //RESETS FORCES
    reset_forces();
    
    
    //UPDATE EDGE LENGTHS
    update_lengths();
    
    
    //t=t+dt
    printf("Time=%g\tw=%.6g\tr=%.6g\trmax=%.6g||\th=%g\tfluct=%g\n", Time, wA+wP, rRIM, rRIM_MAX, h, Sig);
    Time+=h;
    
    
    return 0;
}
//****************************************************************************
