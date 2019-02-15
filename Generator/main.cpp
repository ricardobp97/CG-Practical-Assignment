#include <string>
#include <iostream>
#include <fstream>

void planeFile(float l, const std::string &filename) {
    std::ofstream myFile;
    myFile.open(filename);



    myFile.close();
    std::cout << "DONE" << std::endl;
}

void boxFile(float x, float y, float z, const std::string &filename) {
    std::ofstream myFile;
    myFile.open(filename);



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