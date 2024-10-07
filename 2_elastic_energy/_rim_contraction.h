//****************************************************************************
//****************************************************************************
//***********************CONTRACTION******************************************
//****************************************************************************
//****************************************************************************
double out_energy(int i){
    
    char filename[100];
    snprintf(filename, sizeof(char) * 100, "./output/energy_%g_%g.txt", kA, P0);

    FILE *file; file = fopen(filename, "a");
    if (i == 0){
        fprintf(file, "%g %g 0 0 \n", rRIM_init, rRIM_MAX);}
    fprintf(file, "%g %g %g %g %g\n", wA, wP, wA+wP, rRIM, F_r); 
    fclose(file);
    
    return 0;
}

//in time 0.1*TimeMAX: rRIM_init --> rRIM_MAX
double expansion(){
    rRIM = rRIM_MAX - ((0.1*TimeMAX - Time)/ (0.1*TimeMAX)) * (rRIM_MAX - rRIM_init);
    return 0;
}

//in time 0.5*TimeMAX: rRIM_MAX --> 0
double contraction(){
    rRIM = ((0.5*TimeMAX - Time)/ (0.5*TimeMAX))* rRIM_MAX;
    return 0;
}




