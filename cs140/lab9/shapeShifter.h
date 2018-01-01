#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

typedef vector <string> svec;

class Shape_Shifter {
	public:
		Shape_Shifter(svec board);
		bool Shape_Shifter_Enum(int shape);
		void Apply_Shape(int row, int col, int shape);
		bool isCorrect();
	protected:
		svec grid;
		vector <svec> shapes;
}
