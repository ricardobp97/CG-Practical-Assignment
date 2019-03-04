#include <string>
#include <iostream>
#include <fstream>

void planeFile(float l, const std::string &filename) {
    std::ofstream myFile;
    myFile.open(filename);
	myfile << -l / 2 << " " << 0 << " " << l / 2 << "\n"; //A
	myfile << l / 2 << " " << 0 << " " << l / 2 << "\n"; //B
	myfile << l / 2 << " " << 0 << " " << -l / 2 << "\n"; //C
	
	myfile << l / 2 << " " << 0 << " " << -l / 2 << "\n"; //C
	myfile << -l / 2 << " " << 0 << " " << -l / 2 << "\n"; //D
	myfile << -l / 2 << " " << 0 << " " << l / 2 << "\n"; //A

    myFile.close();
    std::cout << "DONE" << std::endl;
}

void boxFile(float x, float y, float z, const std::string &filename) {
    std::ofstream myFile;
    myFile.open(filename);
	
	//Base Inferior
	myfile << x / 2 << " " << 0 << " " << z / 2 << "\n"; //A
	myfile << -x / 2 << " " << 0 << " " << z / 2 << "\n"; //D
	myfile << -x / 2 << " " << 0 << " " << -z / 2 << "\n"; //C

	myfile << x / 2 << " " << 0 << " " << z / 2 << "\n"; //A
	myfile << -x / 2 << " " << 0 << " " << -z / 2 << "\n"; //C
	myfile << x / 2 << " " << 0 << " " << -z / 2 << "\n"; //B
	
	//Base Superior
	myfile << x / 2 << " " << y << " " << z / 2 << "\n"; //F
	myfile << x / 2 << " " << y << " " << -z / 2 << "\n"; //G
	myfile << -x / 2 << " " << y << " " << -z / 2 << "\n"; //H
	
	myfile << x / 2 << " " << y << " " << z / 2 << "\n"; //F
	myfile << -x / 2 << " " << y << " " << -z / 2 << "\n"; //H
	myfile << -x / 2 << " " << y << " " << z / 2 << "\n"; //E

	//Lateral Frente
	myfile << x / 2 << " " << 0 << " " << z / 2 << "\n"; //A
	myfile << x / 2 << " " << y << " " << z / 2 << "\n"; //F
	myfile << -x / 2 << " " << y << " " << z / 2 << "\n"; //E
	
	myfile << x / 2 << " " << 0 << " " << z / 2 << "\n"; //A
	myfile << -x / 2 << " " << y << " " << z / 2 << "\n"; //E
	myfile << -x / 2 << " " << 0 << " " << z / 2 << "\n"; //D

	//Lateral Trás
	myfile << x / 2 << " " << 0 << " " << -z / 2 << "\n"; //B
	myfile << -x / 2 << " " << 0 << " " << -z / 2 << "\n"; //C
	myfile << -x / 2 << " " << y << " " << -z / 2 << "\n"; //H

	myfile << x / 2 << " " << 0 << " " << -z / 2 << "\n"; //B
	myfile << -x / 2 << " " << y << " " << -z / 2 << "\n"; //H
	myfile << x / 2 << " " << y << " " << -z / 2 << "\n"; //G
	
	//Lateral Direita
	myfile << x / 2 << " " << 0 << " " << z / 2 << "\n"; //A
	myfile << x / 2 << " " << 0 << " " << -z / 2 << "\n"; //B
	myfile << x / 2 << " " << y << " " << -z / 2 << "\n"; //G

	myfile << x / 2 << " " << 0 << " " << z / 2 << "\n"; //A
	myfile << x / 2 << " " << y << " " << -z / 2 << "\n"; //G
	myfile << x / 2 << " " << y << " " << z / 2 << "\n"; //F
	
	//Lateral Esquerda
	myfile << -x / 2 << " " << 0 << " " << z / 2 << "\n"; //D
	myfile << -x / 2 << " " << y << " " << z / 2 << "\n"; //E
	myfile << -x / 2 << " " << 0 << " " << -z / 2 << "\n"; //C

	myfile << -x / 2 << " " << y << " " << z / 2 << "\n"; //E
	myfile << -x / 2 << " " << y << " " << -z / 2 << "\n"; //H
	myfile << -x / 2 << " " << 0 << " " << -z / 2 << "\n"; //C

    myFile.close();
    std::cout << "DONE" << std::endl;
}


void sphereFile(float radius, int slices, int stacks, const std::string &filename) {
    std::ofstream myFile;
    myFile.open(filename);



    myFile.close();
    std::cout << "DONE" << std::endl;
}

void coneFile(float radius, float height, int slices, int stacks, const std::string &filename) {
    std::ofstream myFile;
    myFile.open(filename);
	float alpha = 0;
	float dalpha = 2 * M_PI / slices;

	for (int i = 0; i < slices; i++) {
		
		//Base
		myfile << 0 << " " << -height / 2 << " " << 0 << "\n";//O
		myfile << radius * sin(alpha + dalpha) << " " << -height / 2 << " " << radius * cos(alpha + dalpha) << "\n";//B
		myfile << radius*sin(alpha) << " " << -height / 2 << " " << radius*cos(alpha) << "\n"; //A

		//Lateral
		myfile << radius*sin(alpha) << " " << -height / 2 << " " << radius*cos(alpha) << "\n";//A
		myfile << radius * sin(alpha + dalpha) << " " << -height / 2 << " " << radius * cos(alpha + dalpha) << "\n";//B
		myfile << 0.0 << " " << height / 2 << " " << 0.0 << "\n"; //V	

		alpha = alpha + dalpha;

	}


    myFile.close();
    std::cout << "DONE" << std::endl;
}


int main(int argc, char **argv) {
    float plane_l, box_x, box_y, box_z, sphere_radius, cone_radius, cone_height;
    int sphere_slices, sphere_stacks, cone_slices, cone_stacks;
    std::string filename;
    int draw = -1;

    if(argc == 4) {
        if (argv[1] == std::string("plane")) {
            plane_l = std::stof(argv[2]);
            filename = argv[3];
            draw = 0;
        }
    }

    else if (argc == 6) {
        if (argv[1] == std::string("box")) {
            box_x = std::stof(argv[2]);
            box_y = std::stof(argv[3]);
            box_z = std::stof(argv[4]);
            filename = argv[5];
            draw = 1;
        }

        else if (argv[1] == std::string("sphere")) {
            sphere_radius = std::stof(argv[2]);
            sphere_slices = std::stoi(argv[3]);
            sphere_stacks = std::stoi(argv[4]);
            filename = argv[5];
            draw = 2;
        }
    }

    else if (argc == 7) {
        if (argv[1] == std::string("cone")) {
            cone_radius = std::stof(argv[2]);
            cone_height = std::stof(argv[3]);
            cone_slices = std::stoi(argv[4]);
            cone_stacks = std::stoi(argv[5]);
            filename = argv[6];
            draw = 3;
        }
    }

    switch(draw) {
        case 0 :
            planeFile(plane_l, filename);
            break;
        case 1 : boxFile(box_x, box_y, box_z, filename);
            break;
        case 2 :
            sphereFile(sphere_radius, sphere_slices, sphere_stacks, filename);
            break;
        case 3 :
            coneFile(cone_radius, cone_height, cone_slices, cone_stacks, filename);
            break;
        default : std::cout << "ERROR" << std::endl; break;
    }

    return 0;
}
