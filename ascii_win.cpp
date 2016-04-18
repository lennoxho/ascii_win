// ascii_win.cpp
// Written by      "Lennox" Shou Hao Ho     
// https://ca.linkedin.com/in/lennoxho
// February 2016

#include "ascii_win.h"
#include "processing.h"

using namespace std;
using namespace Gdiplus;

int main(int argc, char **argv){

	if (argc != 2){
		cerr << "Invalid number of arguments!" << endl;
		return E_BAD_ARGS;
	}

	string filename{ argv[1] };
	wstring wfilename{ filename.begin(), filename.end() };

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	process(wfilename);

	GdiplusShutdown(gdiplusToken);

	return 0;
}