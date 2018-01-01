#include "ActivateGame.cpp"

int main(int argc, char **argv)
{
    int i;
    class ActivateGame TheClass;
    int retval;
    vector <string> grid;

    if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); exit(1); }

    /*
       grid = ;
     */


    if (atoi(argv[1]) == 0) {
        grid.push_back("05");
        grid.push_back( "aB");
    }

    if (atoi(argv[1]) == 1) {
        grid.push_back("03");
        grid.push_back( "21");
    }

    if (atoi(argv[1]) == 2) {
        grid.push_back("John");
        grid.push_back( "Brus");
        grid.push_back( "Gogo");
    }

    if (atoi(argv[1]) == 3) {
        grid.push_back("AAA");
        grid.push_back( "AAA");
        grid.push_back( "AAA");
    }

    retval = TheClass.findMaxScore(grid);
    cout << retval << endl;

    exit(0);
}

