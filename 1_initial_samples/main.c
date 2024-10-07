//****************INPUT PARAMETERS************************
//MODEL PARAMETERS TO VARY
double kA;              /*bulk modulus of the cells*/
double P0;              /*preferred cell perimeter*/
double kM=1;            /*myosin turnover rate*/
double Sig;             /*noise on tension*/
double Sig0=0.4;        /*noise on tension*/
double g_adh=0;         /*tension at ambient concentration*/

//OTHER PARAMETERS
double TimeMAX=10000;    /*simulation length*/
double TimeThermalizing=1000; 
double h0=0.001;        /*maximal allowed time step*/
double lth=0.01;        /*threshold for T1 transition*/
double maxDR=0.01;      /*maximal allowed change of vertex position in one time step*/
double maxDg=0.01;      /*maximal allowed change of junctional tension in one time step*/
int deletedCells=0;     /*number of cells that get deleted*/
double rRIM=0;          /*radius of the rim (constraint)*/
double CentX, CentY;

//*******************DECLARATIONS*************************
#include "_functions.h"

//********************MAIN********************************
int main(int argc, char *argv[]){
    
    
    //INPUT PARAMETERS
    array_max=600000;
    if(argc != 3) { std::cerr << "Error! Wrong number of input elements!" << std::endl; return -1; }
    P0 = std::strtod(argv[1],NULL);
    kA = std::strtod(argv[2],NULL);
    srand(3);
    //*************************
    
    
    //INITIALIZE
    allocate();
    set_initial_fromFile2D();
    //out_tissue(1);
    //*************************
    
    
    //SIMULATION
    //STEP 1
    Time=0; h=h0; Sig=Sig0; rRIM=-1;
    while(Time<=TimeThermalizing){
        //SET NOISE VALUE
        Sig=0.4-Time*Sig0/TimeThermalizing;
        if(Sig<0) Sig=0;
        //FORCES AND EQUATION OF MOTION
        eqOfMotion();
        //TOPOLOGICAL CHANGES
        T1_transitions();
    }
    //out_tissue(2);
    for(int i=1; i<=100; i++) rosetteResolution(0.001,0.02);
    make_a_hole();
    //out_tissue(3);
    
    
    //STEP 2
    Time=0; h=h0; Sig=0; rRIM=-1;
    while(Time<=0.1*TimeMAX){
        //FORCES AND EQUATION OF MOTION
        eqOfMotion();
        //TOPOLOGICAL CHANGES
        T1_transitions();
        if(seal_the_hole()==0) return 0;

    }
    out_tissue(4);


    //STEP 3
    h=h0; Sig=Sig0; rRIM=calc_rRIM();
    while(Time<=TimeMAX){
        //SET NOISE VALUE
        if(Time>=0.95*TimeMAX) Sig=0;
        else if(Time>0.1*TimeMAX){
            Sig=-1.17647*Sig0/TimeMAX*Time+1.11765*Sig0;
            if(Sig<0) Sig=0;
        }
        //FORCES AND EQUATION OF MOTION
        eqOfMotion();
        //TOPOLOGICAL CHANGES
        T1_transitions();
    }


    //OUTPUT .vt2d
    for(int i=1; i<=100; i++) rosetteResolution(0.001,0.02);
    out_tissue(5);
    out_Vertissue2D();
    //printf("rRIM=%g\n", rRIM);
    //*************************

    
    //DEALLOCATE
    deallocate();
    //*************************
    
    
    return 0;
}
//********************************************************
