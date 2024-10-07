//****************************************************************************
//****************************************************************************
//***********************EQUATION OF MOTION***********************************
//****************************************************************************
//****************************************************************************
double calc_forces(){
    
    wA=0; wP=0;
    for(int i=1; i<=Nc; i++) if(exist[3][i]==1){
        wA += c_AreaCompressibility_force_New(i);
        wP += c_Perimeter_force(i);
    }
    
    wP=0;
    for(int i=1; i<=Ne; i++) if(exist[2][i]==1){
        wP += e_length_force(i);
    }
    
    //MAX FORCE
    double Fmax=0;
    for(int i = 1; i <= Nv; i++) if(exist[1][i]==1){
        double foRce=sqrt(v_F[i][1]*v_F[i][1]+v_F[i][2]*v_F[i][2]);
        if(foRce>Fmax) Fmax=foRce;
    }
    return Fmax;
}
//****************************************************************************
double tension_rate(){
    if(tensionDynamics==1){
        if(fabs(gamma0-eGamma)>1e-14){
            double per=wound_perimeter();
            double pdot=e_pdotCalc();
            double Gt=pow(gamma0,b)*(gamma0+eGamma)/(gamma0-eGamma);
            eFg = 2*b*pow(gamma0,1+b)*pow(Gt,(-1+b)/b)*(gamma0*per-pow(Gt,1/b)*(per+(1/kM)*pdot))/((1/kM)*per*pow(pow(gamma0,b)+Gt,2));
        }
        else eFg = b*gamma0*pow(gamma0-eGamma,1./b+1.)*pow(-pow(gamma0,b)*(-2*gamma0+gamma0-eGamma),-1./b)*(1./kM);
        return fabs(eFg);
    }
    else return 0;
}
//****************************************************************************
double adapt_timeStep(double FMAX, double FgMAX){
    double hr=h0; if(FMAX>0.00000001) hr=maxDR/FMAX;
    double hg=h0; if(FgMAX>0.00000001) hg=maxDg/FgMAX;
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
void propagate_tension(){
    //PERIMETER TENSION
    if(tensionDynamics==1){
        double deGamma=h*eFg;
        if(deGamma>0) eGamma += deGamma;// + sqrt(2.*Sig*Sig*h*kM)*GaussianVariate();
        if(eGamma<0) eGamma=0;
        if(eGamma>gamma0) eGamma=gamma0;
    }
    //EDGE TENSION
    for(int i=1; i<=Ne; i++) if(exist[2][i]==1){
        e_g[i] +=  OrnsteinUhlenbeck*(-h*kM*e_g[i] + sqrt(2.*Sig*Sig*h*kM)*GaussianVariate());
        //if(e_g[i]<0) e_g[i]=0;
    }
}
//****************************************************************************
void reset_forces(){
    for(int i=1; i<=Nv; i++) if(exist[1][i]==1) for(int j=1; j<=2; j++) v_F[i][j] = 0;
    for(int i=1; i<=Ne; i++) if(exist[2][i]==1) e_Fg[i]=0;
}
//****************************************************************************
void update_lengths(){
    for(int i=1; i<=Ne; i++) if(exist[2][i]==1) {
        double elen=edge_length(i);
        e_dl[i]=(elen-e_length[i]);
        e_length[i]=elen;
    }
}
//****************************************************************************
void project_on_constraints(double r0, double Cent){
    double d0, xx, yy;
    int cnt=0;
    for(int i=1; i<=Nv; i++) if(exist[1][i]==1){
        cnt=0;
        for(int j=1; j<=v_edges[i][0]; j++) if(e_cells[v_edges[i][j]][0]<2) cnt++;
        if(cnt!=0){
            xx=v[i][1];
            yy=v[i][2];
            d0=-(pow(xx-Cent,2)+pow(yy-Cent,2)-pow(r0,2))/(2*pow(xx-Cent,2)+2*pow(yy-Cent,2));
            v[i][1]+=d0*(xx-Cent);
            v[i][2]+=d0*(yy-Cent);
        }
    }
}
//****************************************************************************
double eqOfMotion(){
    
    //EDGE LENGTHS
    for(int i=1; i<=Ne; i++) if(exist[2][i]==1) e_length[i]=edge_length(i);
    for(int i=1; i<=Nc; i++) if(exist[3][i]==1) c_area[i]=CellArea_new(i);
    
    //CALCULATE FORCES
    double FMAX=calc_forces();
    double FgMAX=tension_rate();
    
    //TIME STEP
    h=adapt_timeStep(FMAX,FgMAX);
    
    //PROPAGATE VERTICES
    for(int i=1; i<=Nv; i++) if(exist[1][i]==1){
        v[i][1] += h*v_F[i][1];
        v[i][2] += h*v_F[i][2];
        torus_vertex(i);
    }
    
    //PROJECT ON CONSTRAINT
    if(rRIM>0) project_on_constraints(rRIM,perioXYZ[1]/2.);
    
    
    //PROPAGATE TENSIONS
    propagate_tension();
    

    //RESETS FORCES
    reset_forces();
    
    
    //UPDATE EDGE LENGTHS
    update_lengths();
    
    
    //t=t+dt
    int cnt=0;
    for(int i=1; i<=Ne; i++) if(e[i][0]!=0 && e_cells[i][0]==1) cnt++;
    //printf("Time=%g\t\twA=%.16g\t\twP=%.16g\t\t | %.5g | %.5g | %d\n", Time, wA, wP, eGamma, wound_perimeter(), cnt);
    
    
    Time+=h;

    
    return wA+wP;
}
//****************************************************************************
