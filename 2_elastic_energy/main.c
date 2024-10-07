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
double h0=0.001;        /*maximal allowed time step*/
double lth=0.01;        /*threshold for T1 transition*/
double maxDR=0.01;      /*maximal allowed change of vertex position in one time step*/
double maxDg=0.01;      /*maximal allowed change of junctional tension in one time step*/
int deletedCells=0;     /*number of cells that get deleted*/
double rRIM=0;          /*radius of the rim (constraint)*/
double rRIM_init=0;     /*initial radius of the rim (constraint) before expansion*/
double rRIM_MAX=0;      /*max radius of the rim (constraint) before contraction*/
double CentX, CentY;




//*******************DECLARATIONS*************************
#include "_functions.h"

//********************MAIN********************************
int main(int argc, char *argv[]){
    
    
    //INPUT PARAMETERS
    array_max=600000;
    if(argc != 3) {std::cerr << "Error! Wrong number of input elements!" << std::endl; return -1; }
    P0 = std::strtod(argv[1],NULL);
    kA = std::strtod(argv[2],NULL);
    srand(2);
    //*************************
    
    
    //INITIALIZE
    allocate(); 
    set_initial_fromFile2D();   
    //out_tissue(1); 
    //*************************

    //SIMULATION

    //STEP 1 expansion
    Time=0; h=h0; rRIM_init=calc_rRIM(); Sig=0;
    double values[] = {
        2.0 * rRIM_init,
        std::abs(CentX - perioXYZ[1]),
        std::abs(CentX - perioXYZ[2]),
        std::abs(CentY - perioXYZ[1]),
        std::abs(CentY - perioXYZ[2])
    };
    double* minElement = std::min_element(values, values + 5);
    rRIM_MAX = *minElement;

    while(Time <= 0.1*TimeMAX){ 

        // RIM EXPANSION
        expansion(); 
        
        //FORCES AND EQUATION OF MOTION
        eqOfMotion(); 
        
    }

    //STEP 2
    Time=0; h=h0; rRIM = rRIM_MAX;
    while(Time<=0.4*TimeMAX){ 

        //FORCES AND EQUATION OF MOTION
        eqOfMotion(); 
    }
    out_tissue(1);
    
    
    //STEP 3 contraction
    Time=0; h=h0;
    int i=0;
    while(Time<=0.5*TimeMAX){ 
        
        // RIM CONTRACTION
        contraction(); 
        
        //FORCES AND EQUATION OF MOTION
        eqOfMotion();
        
        //OUTPUT  
        if(i%100 == 0){
            out_energy(i);}
        i += 1;
    }
    out_tissue(2); 
    //*************************

    
    //DEALLOCATE
    deallocate();
    //*************************
    
    
    return 0;
}
//********************************************************
