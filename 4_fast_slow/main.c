//****************INPUT PARAMETERS************************
double gamma0=2.1;
double Sig=0.1;
double divProb=0.05;
int seed = 1;

double P0=3.72;
double kA=2.07;
double kM=.01;
double b=10;

double g_adh=0.2;

//OTHER PARAMETERS
double Time=0;          /*time*/
double tMAX=500;        /*simulation length*/
double maxDR=0.01;      /*maximal allowed change of vertex position in one time step*/
double maxDg=0.01;      /*maximal allowed change of junctional tension in one time step*/
double h0=0.001;        /*maximal allowed time step*/
double lth=0.01;        /*threshold for T1 transition*/
double h;               /*time step*/
double rRIM=0;          /*radius of the rim (constraint)*/

//TENSION DYNAMICS
int tensionDynamics=0;
int OrnsteinUhlenbeck=0;

//*******************DECLARATIONS*************************
#include "_functions.h"


double wound_area(){
    double w_area=0;
    for(int i=1; i<=Nc; i++) if(exist[3][i]==1){
        w_area+=CellArea_new(i);
    }
    return perioXYZ[1]*perioXYZ[2]-w_area;
}

//********************MAIN********************************
int main(int argc, char *argv[]){
    
    
    
    //INITIALIZE
    array_max=100000;
    if (argc != 5) { std::cerr << "Error! Wrong number of input elements!" << std::endl; return -1; }
    gamma0= std::strtod(argv[1],NULL);
    Sig= std::strtod(argv[2],NULL);
    divProb = std::strtod(argv[3],NULL);
    int seed = std::atoi(argv[4]); srand(seed);

    
    allocate();
    set_initial_fromFile();
    //*************************
    
    
    //FILE
    char filename11[200];
    snprintf(filename11, sizeof(char) * 100, "./output/rt_gt_%g_%g_%g_%d.txt", gamma0, Sig, divProb, seed);
    FILE *file11; file11 = fopen(filename11, "wt");
    fclose(file11);
    //*************************
    
    
    //DYNAMICS
    double TimeCount=0; int kount=0;
    rRIM=0;
    OrnsteinUhlenbeck=1;
    tensionDynamics=1;
    Time=0;
    while(Time<tMAX){

        //OUTPUT
        if(Time>=TimeCount){
            file11 = fopen(filename11, "at");
            fprintf(file11, "%g  %g  %g\n", Time, wound_area(), eGamma);
            fclose(file11);
            kount++; //out_tissue(kount);
            TimeCount+=1.;
        }

        //EQ OF MOTION
        eqOfMotion();

        //printf("Time=%g\t| gamma=%.5g \t | area=%.5g |\n", Time, eGamma, wound_area());

        //T1s
        T1_transitions(0.001,0.02,12);

        //CHECK IF TRIANGULAR WOUND
        int cnt=0;
        for(int i=1; i<=Ne; i++) if(e[i][0]!=0 && e_cells[i][0]==1) cnt++;
        if(cnt<=3) break;
        
        //CELL GROWTH
        for(int i=1; i<=Nc; i++) if(exist[3][i]==1){
            if(rnd()<divProb*h0/(1.*Nc)){
                c_A0[i]=2;
                printf("%g  %d\n", Time, i);
            }
        }
    }
    //*************************

    
    //DEALLOCATE
    deallocate();
    //*************************

    

    return 0;
}
//********************************************************
