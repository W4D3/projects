#include "Mafia.cpp"

int main(int argc, char **argv)
{
    int i;
    class Mafia TheClass;
    int retval;
    vector &lt;int&gt; guilt;
    vector &lt;string&gt; responses;
    int playerIndex;

    if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); exit(1); }

    /*
       guilt = ;
       responses = ;
       playerIndex = ;
     */


    if (atoi(argv[1]) == 0) {
        guilt.push_back(500);
        guilt.push_back(500);
        guilt.push_back(500);
        guilt.push_back(500);
        responses.push_back("ADCb");
        responses.push_back( "bADC");
        responses.push_back( "CbAD");
        responses.push_back( "DCbA");
        playerIndex = 1;
    }

    if (atoi(argv[1]) == 1) {
        guilt.push_back(500);
        guilt.push_back(500);
        guilt.push_back(500);
        guilt.push_back(500);
        guilt.push_back(501);
        responses.push_back("ADCbE");
        responses.push_back( "bADCE");
        responses.push_back( "CbADE");
        responses.push_back( "DCbAE");
        responses.push_back( "EDCbA");
        playerIndex = 1;
    }

    if (atoi(argv[1]) == 2) {
        guilt.push_back(500);
        guilt.push_back(500);
        guilt.push_back(500);
        guilt.push_back(500);
        guilt.push_back(500);
        guilt.push_back(500);
        responses.push_back("cccccc");
        responses.push_back( "BBBBBB");
        responses.push_back( "dddddd");
        responses.push_back( "FFFFFF");
        responses.push_back( "GGGGGG");
        responses.push_back( "hhhhhh");
        playerIndex = 0;
    }

    if (atoi(argv[1]) == 3) {
        guilt.push_back(501);
        guilt.push_back( 499);
        guilt.push_back( 499);
        guilt.push_back( 499);
        responses.push_back("ABCD");
        responses.push_back( "zfAg");
        responses.push_back( "ESAS");
        responses.push_back( "atsm");
        playerIndex = 0;
    }

    if (atoi(argv[1]) == 4) {
        guilt.push_back(800);
        responses.push_back("E");
        playerIndex = 0;
    }

    if (atoi(argv[1]) == 5) {
        guilt.push_back(643);
        guilt.push_back(457);
        guilt.push_back(642);
        guilt.push_back(710);
        guilt.push_back(595);
        guilt.push_back(631);
        guilt.push_back(566);
        guilt.push_back(634);
        responses.push_back("APOSIfjf");
        responses.push_back( "ewFOJWeJ");
        responses.push_back( "jElLLoSS");
        responses.push_back( "GeOSSmff");
        responses.push_back( "zWSTsOuu");
        responses.push_back( "fmfOPPsa");
        responses.push_back( "MSoPPWXn");
        responses.push_back( "FeojwFAM");
        playerIndex = 5;
    }

    retval = TheClass.play(guilt, responses, playerIndex);
    cout << retval << endl;

    exit(0);
}

