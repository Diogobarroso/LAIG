/* 
 * G0_Base: projeto inicial de CGra
 * 
 */

#include <iostream>
#include <exception>

#include "CGFapplication.h"
#include "DemoScene.h"

#include "ANFScene.h"
#include "ANFInterface.h"

using std::cout;
using std::exception;


int main(int argc, char* argv[]) {

	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		/* Parser here */
		//XMLScene scene = XMLScene (argv[1]);
		//ANFScene scene2 = ANFScene (argv[1]);

		ANFScene * scene = new ANFScene(argv[1]);

		ANFInterface * inter = new ANFInterface();

		app.setScene(scene);
		inter->setScene(scene);
		/*
		app.setScene(new DemoScene());
		*/
		app.setInterface(inter);
		
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Error: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Unexpected error: " << ex.what();
		return -1;
	}

	system("pause");

	return 0;
}