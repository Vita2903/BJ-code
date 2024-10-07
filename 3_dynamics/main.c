//****************INPUT PARAMETERS************************
double P0;          /*preferred cell perimeter*/
double kA;          /*bulk modulus of the cells*/
double kM;          /*myosin turnover rate*/
double gamma0;      /*maximal active tension*/
double b;           /*Hill coefficient*/


double Sig=0;       /*noise on tension*/
double g_adh=0;     /*tension at ambient concentration*/

//OTHER PARAMETERS
double Time=0;          /*time*/
double tMAX=30;         /*simulation length*/
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

//********************MAIN********************************
int main(int argc, char *argv[]){
    
    
    //INITIALIZE
    array_max=100000;

    if(argc != 6) { std::cerr << "Error! Wrong number of input elements!" << std::endl; return -1; }
    P0 = std::strtod(argv[1],NULL);
    kA = std::strtod(argv[2],NULL);
    kM = std::strtod(argv[3],NULL);
    gamma0 = std::strtod(argv[4],NULL);
    b = std::strtod(argv[5],NULL);


    allocate();
    set_initial_fromFile();
    for(int i=1; i<=Nv; i++) if(exist[1][i]==1){
        v[i][1] += 0.1*(-1+2*rnd());
        v[i][2] += 0.1*(-1+2*rnd());
        torus_vertex(i);
    }

    //FILE r(t) and gamma(t)
    //char filename11[200];
    //snprintf(filename11, sizeof(char) * 100, "./output/rt_gt_%g_%g.txt", P0, kA);
    //FILE *file11; file11 = fopen(filename11, "wt");
    //fclose(file11);
    //*************************
    
    
    //DYNAMICS
    double TimeCount=0; int kount=0;
    rRIM=0;
    OrnsteinUhlenbeck=1;
    tensionDynamics=1;
    Time=0;
    bool closed = false;

    eqOfMotion();
    double r0 = wound_perimeter();

    while(Time<tMAX){
        
        //OUTPUT r(t) and gamma(t)

        //if(Time>=TimeCount){
        //    file11 = fopen(filename11, "at");
        //    fprintf(file11, "%g  %g  %g\n", Time, wound_perimeter(), eGamma);
        //    fclose(file11);
        //    kount++; //out_tissue(kount);
        //    TimeCount+=0.5;
        //}
        
        //EQ OF MOTION
        eqOfMotion();
        
        //T1s
        //T1_transitions(0.001,0.02,12);

        //CHECK IF UNSTABLE
        if (((wound_perimeter() - r0) * (wound_perimeter() - r0)) / (r0 * r0) >= 0.04) {
            closed = true;
            break;
        }
        
        //CHECK IF TRIANGULAR WOUND
        int cnt=0;
        for(int i=1; i<=Ne; i++) if(e[i][0]!=0 && e_cells[i][0]==1) cnt++;
        if(cnt<=3) {
            closed = true; 
            break;
        }
    }
    //*************************

    // Simulation data
    char filename10[200]; 
    
    snprintf(filename10, sizeof(char) * 100, "./output/_sd.txt");

    FILE *file2; file2 = fopen(filename10, "a");

    
    if (closed) {
                    fprintf(file2, "%g %g %g %g %g %g %d \n", P0, kA, kM, gamma0, b, Time, 1);

    } 
    else {
                    fprintf(file2, "%g %g %g %g %g %g %d \n", P0, kA, kM, gamma0, b, Time, -1);

    }

    //*************************

    //DEALLOCATE
    deallocate();
    //*************************


    return 0;
}
//********************************************************
