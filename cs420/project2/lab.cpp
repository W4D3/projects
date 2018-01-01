#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

float distance(int i1,int i2,int j1,int j2){
    float rij, absx, absy;
    absx = abs(i1-j1);
    absy = abs(i2-j2);

    if(absx > 15)
        absx = 30 - absx;
    if(absy > 15)
        absy = 30 - absy;

    rij = absx+absy;

    return rij;
}

void calcCorrelation(int ca[][30],vector<float> &corrs){
    int i1,i2,j1,j2,l;
    int sumij, sumi, N;
    float dist, coeff1, coeff2, Cl,pl;

    sumij = sumi = 0;

    for(l=0;l<15;l++){
        
        sumij = sumi = 0;

        for(i1=0;i1<30;i1++){
            for(i2=0;i2<30;i2++){

                for(j1=0;j1<i1;j1++){
                    for(j2=0;j2<i2;j2++){

                        dist = distance(i1,i2,j1,j2);
                        if(dist == l){
                            sumij += ca[i1][i2] * ca[j1][j2];
                        }
                    }
                }
                sumi += ca[i1][i2];
            }
        }

        //correlation formula
        N = 30;
        if(l==0){
            pl = 1-pow(((1/(N*N))*sumi),2);
        }else{
            Cl = 4*l;
            coeff1 = 2/(N*N*Cl);
            coeff2 = 1/(N*N);
            pl = (coeff1*sumij) - pow(coeff2*sumi,2);
        }

        pl = abs(pl);
        //printf("%f\n",pl);

        corrs.push_back(pl);
    }

}

void calcMutualInfo(int ca[][30],float H,vector<float> Hl,vector<float> &vec){
    int l;
    float Il;

    for(l=0;l<15;l++){
        Il = 2*H-Hl[l];
        vec.push_back(Il);
    }
}

void calcJointEntropy(int ca[][30],vector<float> &vec){
   int i,j,l;
   float convert_sumi,convert_sum_negi,convert_sumj,convert_sum_negj;
   float H, sumij,sumijNeg,pl1,pl2,pl3,N,Cl,dist;
   float term1,term2,term3;
   int i1,i2,j1,j2;

    //sum of converted cells
    for(l=0;l<15;l++){
    
    sumij = sumijNeg = 0;

        for(i1=0;i1<30;i1++){
            for(i2=0;i2<30;i2++){

                for(j1=0;j1<i1;j1++){
                    for(j2=0;j2<i2;j2++){
                        
                        convert_sumi = (ca[i1][i2]+1)/2;
                        convert_sum_negi = (-ca[i1][i2]+1)/2;
                        
                        convert_sumj = (ca[j1][j2]+1)/2;
                        convert_sum_negj = (-ca[j1][j2]+1)/2;

                        dist = distance(i1,i2,j1,j2);
                        if(dist == l){
                            sumij += convert_sumi * convert_sumj;
                            sumijNeg += convert_sum_negi * convert_sum_negj;
                        }

                    }
                }
            }
        }

        N = 30.0;
        Cl = 4*l;

        if(l==0){
            pl1 = 0;
            pl2 = 0;
        }else{
            //Pl{+1,+1}
            pl1 = (2/((N*N)*Cl))*sumij;
            //Pl{-1,-1}
            pl2 = (2/((N*N)*Cl))*sumijNeg;
        }
        //Pl{+1,-1}
        pl3 = 1-pl1-pl2;

        term1 = 0.0;
        term2 = 0.0;
        term3 = 0.0;

        if(pl1 > 0)
            term1 = pl1*log(pl1);
        if(pl2 > 0)
            term2 = pl2*log(pl2);
        if(pl3 > 0)
            term3 = pl3*log(pl3);

        H = -(term1+term2+term3);

        vec.push_back(H);

    }
}

float calcEntropy(int ca[][30]){
    int i,j;
    float H,probPos,probNeg,term1,term2,convert_sum,N;

    convert_sum = 0;
    N=30.0;

    //sum of converted cells
    for(i=0;i<30;i++){
        for(j=0;j<30;j++){
            convert_sum += (ca[i][j]+1)/2;
        }
    }

    //probability of state value 1
    probPos = (1/(N*N))*convert_sum;

    //probability of state value -1
    probNeg = 1 - probPos;

    //compute overall entropy
    if(probPos == 0)
        term1 = 0;
    else
        term1 = probPos * log(probPos);
    if(probNeg == 0)
        term2 = 0;
    else
        term2 = probNeg * log(probNeg);

    H = -1*(term1 + term2);

    //printf("%f\n",H);
    return(H);
}

void createPGM(int ca[][30],string str){
    FILE *pgm;
    int i,j;

    pgm = fopen(str.c_str(),"w+");
    if(pgm == NULL){ printf("could not open file\n"); exit(1); }

    fprintf(pgm,"P2\n30 30\n255\n");

    for(i=0; i<30; i++){
        for(j=0;j<30;j++){
            if(ca[i][j] == 1){
                fprintf(pgm,"0 ");
            }else{
                fprintf(pgm,"255 ");
            }
        }
        fprintf(pgm,"\n");
    }

    fclose(pgm);
}

int main(int argc, char *argv[]){

    //variables
    int CA[30][30], updates[30][30];
    int i,j,x,y,num;
    float dist,nearSum,farSum;
    float j1,j2,h,r1,r2;
    float j1sum,j2sum,s;
    bool needsUpdating, isUpdated;
    int count,count2;

    needsUpdating = true;
    isUpdated = false;

    nearSum = farSum = count = count2 = dist = 0;

    count2 = 900;

    if(argc < 6){ printf("usage: lab [j1] [j2] [h] [r1] [r2]\n"); exit(1); };

    j1 = atof(argv[1]);
    j2 = atof(argv[2]);
    h = atof(argv[3]);
    r1 = atof(argv[4]);
    r2 = atof(argv[5]);

    printf("j1:%f j2:%f h:%f r1:%f r2:%f\n",j1,j2,h,r1,r2);

    //initialize
    srand(time(NULL));
    for(i=0;i<30;i++){
        for(j=0;j<30;j++){
            num = rand()%2;
            if(num == 0){
                CA[i][j] = -1;
            }else{
                CA[i][j] = 1;
            }
        }
    }

    string str1 = "initial";
    char hBuff[10];
    sprintf(hBuff, "%d", h);
    str1 += hBuff;
    char r1Buff[10];
    sprintf(r1Buff, "%d", r1);
    str1 += r1Buff;
    str1 += "-";
    char r2Buff[10];
    sprintf(r2Buff, "%d", r2);
    str1 += r2Buff;
    str1 += ".pgm";

    //to_string((int)h) + "-" + to_string((int)r1) + "-" + to_string((int)r2) + ".pgm";

    createPGM(CA,str1.c_str());
    
   //outer loop
   while(!isUpdated){

       isUpdated = true;
       needsUpdating = true;
       count2 = 900;

       for(i=0;i<30;i++){
           for(j=0;j<30;j++){
               updates[i][j] = 0;
           }
       }

        //inner loop
       while(needsUpdating){

           if(count2 == 0){
               needsUpdating = false;
               continue;
           }

           //get random
           do{
               x = rand() % 30;
               y = rand() % 30;
           }while(updates[x][y] == 1);

           //set updated
           updates[x][y] = 1;
           count2--;

            nearSum = 0;
            farSum = 0;

           for(i=0;i<30;i++){
               for(j=0;j<30;j++){
                   dist = distance(x,y,i,j);
                   //if < r1 add to near
                   if(dist < r1){
                       nearSum += CA[i][j];
                   }else if(dist >= r1 && dist < r2){
                       farSum += CA[i][j];
                   }
               }
           }

           //calculate update
           j1sum = nearSum*j1;
           j2sum = farSum*j2;
           s = h+j1sum+j2sum;

           if(s>=0){
               if(CA[x][y] != 1){
                   CA[x][y] = 1;
                   isUpdated = false;
               }
           }else{
               if(CA[x][y] != -1){
                   CA[x][y] = -1;
                   isUpdated = false;
               }
           }

       }
       count++;
   }

    vector<float> corr,mut;
    vector<float> h2;
    float h1;
   calcCorrelation(CA,corr);
   h1 = calcEntropy(CA);
   calcJointEntropy(CA,h2);
   calcMutualInfo(CA,h1,h2,mut);

    string str2 = "final";
    char hBuff2[10];
    sprintf(hBuff2, "%d", h);
    str2 += hBuff2;
    str2 += "-";
    char r1Buff2[10];
    sprintf(r1Buff2, "%d", r1);
    str2 += r1Buff2;
    str2 += "-";
    char r2Buff2[10];
    sprintf(r2Buff2, "%d", r2);
    str2 += r2Buff2;
    str2 += ".pgm";

    //string str2 = "final" + to_string((int)h) + "-" + to_string((int)r1) + "-" + to_string((int)r2) + ".pgm";
    createPGM(CA,str2.c_str());

//    string str3 = "open -a ToyViewer " + str1;
//    system(str3.c_str());
 //   str3 = "open -a ToyViewer " + str2;
 //   system(str3.c_str());

    FILE *csv;

    csv = fopen("experiments.csv","a+");
    if(csv == NULL){ printf("could not open csv\n"); exit(1); }

    fprintf(csv,"J1, J2, h, R1, R2\n");
    fprintf(csv,"%f, %f, %f, %f, %f\n\n",j1,j2,h,r1,r2);
    fprintf(csv,"L,Correlation,Joint Entropy,Mutual Information\n");
    for(i=0;i<15;i++)
        fprintf(csv,"%d, %f, %f, %f\n",i,corr[i],h2[i],mut[i]);
     fprintf(csv,"\n\n\n");

    fclose(csv);
}
