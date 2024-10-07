//****************************************************************************
//****************************************************************************
//******************************OUTPUT****************************************
//****************************************************************************
//****************************************************************************
double out_polygons(int fcount){
    
    
    char filename2[100]; char filename3[100];
    
    if(fabs(P0-3.7224194364083982)<0.001) snprintf(filename2, sizeof(char) * 100, "./output/X_3.7224_%g_%d.txt", kA, fcount);
    else snprintf(filename2, sizeof(char) * 100, "./output/X_%g_%g_%d.txt", P0, kA, fcount);

    if(fabs(P0-3.7224194364083982)<0.001) snprintf(filename3, sizeof(char) * 100, "./output/Y_3.7224_%g_%d.txt", kA, fcount);
    else snprintf(filename3, sizeof(char) * 100, "./output/Y_%g_%g_%d.txt", P0, kA, fcount);
    
    double *dxdydz = new double[2];
    dxdydz[0]=0; dxdydz[1]=0;
    int vert_ref_id, vert_id;
    FILE *file2; file2 = fopen(filename2, "wt");
    FILE *file3; file3 = fopen(filename3, "wt");
    
    for(int i=1; i<=Nc; i++){
        if(edges[i][1]!=0){
            
            fprintf(file2, "%d ", vertices[i][2]);
            fprintf(file3, "%d ", vertices[i][2]);
            
            vert_ref_id=vertices[i][3];
            fprintf(file2, "%g ", v[vert_ref_id][1]);
            fprintf(file3, "%g ", v[vert_ref_id][2]);
            
            for(int j = 4; j <= 2+edges[i][2]; j++){
                vert_id=vertices[i][j];
                torus_dx_dy_dz(dxdydz,vert_id,vert_ref_id);
                fprintf(file2, "%g ", v[vert_id][1] + dxdydz[0]);
                fprintf(file3, "%g ", v[vert_id][2] + dxdydz[1]);
            }
            
            for(int j = edges[i][2]; j <= 15; j++){
                fprintf(file2, "0 ");
                fprintf(file3, "0 ");
            }
            
            fprintf(file2, "\n");
            fprintf(file3, "\n");
        }
    }
    fclose(file2);
    fclose(file3);
    
    delete []dxdydz;
    
    return 0;
}
//****************************************************************************
double out_edges(int fcount){
    
    char filename2[100];
    if(fabs(P0-3.7224194364083982)<0.001) snprintf(filename2, sizeof(char) * 100, "./output/edges_3.7224_%d.txt", fcount);
    else snprintf(filename2, sizeof(char) * 100, "./output/edges_%g_%d.txt", P0, fcount);

    double *dxdydz = new double[2]; dxdydz[0]=0; dxdydz[1]=0;
    FILE *file2; file2 = fopen(filename2, "wt");
    
    for(int i=1; i<=Ne; i++) if(e[i][0]!=0){
        int vert_ref_id=e[i][1];
        int vert_id=e[i][2];
        torus_dx_dy_dz(dxdydz,vert_id,vert_ref_id);
        fprintf(file2, "%g  %g  %g  %g\n", v[vert_ref_id][1], v[vert_ref_id][2], v[vert_id][1] + dxdydz[0], v[vert_id][2] + dxdydz[1]);
    }
    fclose(file2);
    
    delete []dxdydz;
    
    return 0;
}
//****************************************************************************
double out_coordSpheres(int fcount){
    
    char filename2[100];
    if(fabs(P0-3.7224194364083982)<0.001) snprintf(filename2, sizeof(char) * 100, "./output/coordSpheres_3.7224_%d.txt", fcount);
    else snprintf(filename2, sizeof(char) * 100, "./output/coordSpheres_%g_%d.txt", P0, fcount);

    FILE *file2; file2 = fopen(filename2, "wt");
    for(int i=1; i<=Nc; i++) if(edges[i][1]!=0) fprintf(file2, "%d\n", c_coordSphere[i]);
    fclose(file2);
        
    return 0;
}
//****************************************************************************
double out_vertices(int fcount){
    
    char filename2[100];
    if(fabs(P0-3.7224194364083982)<0.001) snprintf(filename2, sizeof(char) * 100, "./output/vert_3.7224_%d.txt", fcount);
    else snprintf(filename2, sizeof(char) * 100, "./output/vert_%g_%d.txt", P0, fcount);

    FILE *file2; file2 = fopen(filename2, "wt");
    for(int i=1; i<=Nv; i++) if(v[i][0]>0.5) fprintf(file2, "%g  %g\n", v[i][1], v[i][2]);
    fclose(file2);
        
    return 0;
}
//****************************************************************************
void out_tissue(int fcount){
    out_polygons(fcount);
}
//****************************************************************************
