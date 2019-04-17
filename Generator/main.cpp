#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <sstream>

using namespace std;

void planeFile(float l, const string &filename) {
    ofstream myfile;
    myfile.open(filename);
    myfile << -l / 2 << " " << 0 << " " << l / 2 << "\n"; //A
    myfile << l / 2 << " " << 0 << " " << l / 2 << "\n"; //B
    myfile << l / 2 << " " << 0 << " " << -l / 2 << "\n"; //C

    myfile << l / 2 << " " << 0 << " " << -l / 2 << "\n"; //C
    myfile << -l / 2 << " " << 0 << " " << -l / 2 << "\n"; //D
    myfile << -l / 2 << " " << 0 << " " << l / 2 << "\n"; //A

    myfile.close();
    cout << "DONE" << endl;
}

void boxFile(float x, float y, float z, const string &filename) {
    ofstream myfile;
    myfile.open(filename);

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

    myfile.close();
    cout << "DONE" << endl;
}


void sphereFile(float radius, int slices, int stacks, const string &filename) {
    ofstream myfile;
    myfile.open(filename);

    float dalpha = 2 * M_PI / (slices);
    float alpha = 0;

    float ddelta = M_PI / (stacks);
    float delta = 0;

    float r = radius;

    for (alpha = 0; alpha < 2 * M_PI; alpha += dalpha) {
        for (delta = -M_PI / 2; delta <= M_PI / 2; delta += ddelta) {
            myfile << r * cos(delta) * sin(alpha) << " " << r * sin(delta) << " " << r * cos(delta) * cos(alpha)
                   << "\n";
            myfile << r * cos(delta) * sin(alpha + dalpha) << " " << r * sin(delta) << " "
                   << r * cos(delta) * cos(alpha + dalpha) << "\n";
            myfile << r * cos(delta + ddelta) * sin(alpha) << " " << r * sin(delta + ddelta) << " "
                   << r * cos(delta + ddelta) * cos(alpha) << "\n";

            myfile << r * cos(delta + ddelta) * sin(alpha + dalpha) << " " << r * sin(delta + ddelta) << " "
                   << r * cos(delta + ddelta) * cos(alpha + dalpha) << "\n";
            myfile << r * cos(delta + ddelta) * sin(alpha) << " " << r * sin(delta + ddelta) << " "
                   << r * cos(delta + ddelta) * cos(alpha) << "\n";
            myfile << r * cos(delta) * sin(alpha + dalpha) << " " << r * sin(delta) << " "
                   << r * cos(delta) * cos(alpha + dalpha) << "\n";
        }
    }

    myfile.close();
    cout << "DONE" << endl;
}

void coneFile(float radius, float height, int slices, int stacks, const string &filename) {
    ofstream myfile;
    myfile.open(filename);

    float alpha = 0;
    float dalpha = 2 * M_PI / slices;

    float h = -height / 2;
    float dh = height / stacks;

    float r = radius;
    float dr = radius / stacks;

    for (int i = 0; i < slices; i++) {
        myfile << 0 << " " << -height / 2 << " " << 0 << "\n";//O
        myfile << radius * sin(alpha + dalpha) << " " << -height / 2 << " " << radius * cos(alpha + dalpha) << "\n";//B
        myfile << radius * sin(alpha) << " " << -height / 2 << " " << radius * cos(alpha) << "\n"; //A

        alpha = alpha + dalpha;
    }

    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            myfile << r * cos(alpha) << " " << h << " " << r * sin(alpha) << '\n';
            myfile << (r - dr) * cos(alpha) << " " << h + dh << " " << (r - dr) * sin(alpha) << '\n';
            myfile << (r - dr) * cos(alpha + dalpha) << " " << h + dh << " " << (r - dr) * sin(alpha + dalpha) << '\n';

            myfile << r * cos(alpha) << " " << h << " " << r * sin(alpha) << '\n';
            myfile << (r - dr) * cos(alpha + dalpha) << " " << h + dh << " " << (r - dr) * sin(alpha + dalpha) << '\n';
            myfile << r * cos(alpha + dalpha) << " " << h << " " << r * sin(alpha + dalpha) << '\n';

            alpha += dalpha;
        }
        h += dh;
        r -= dr;
    }

    myfile.close();
    cout << "DONE" << endl;
}

void transposta(float m[4][4]) {
    int i, j;
    float t;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < i; j++) {
            t = m[j][i];
            m[j][i] = m[i][j];
            m[i][j] = t;
        }
    }
}

void multMatrixVector(float *m, float *v, float *res) {
    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }
}

float getCordPontoBelzier(float u, float v, float *p0, float *p1, float *p2, float *p3) {
    //Coeficientes de Bezier
    float m[4][4] = {{-1.0f, 3.0f,  -3.0f, 1.0f},
                     {3.0f,  -6.0f, 3.0f,  0.0f},
                     {-3.0f, 3.0f,  0.0f,  0.0f},
                     {1.0f,  0.0f,  0.0f,  0.0f}};

    //A = M * P
    float a[4][4];

    multMatrixVector((float *) m, p0, a[0]);
    multMatrixVector((float *) m, p1, a[1]);
    multMatrixVector((float *) m, p2, a[2]);
    multMatrixVector((float *) m, p3, a[3]);

    transposta(a);

    //B = A * M
    float b[4][4];

    multMatrixVector((float *) a, m[0], b[0]);
    multMatrixVector((float *) a, m[1], b[1]);
    multMatrixVector((float *) a, m[2], b[2]);
    multMatrixVector((float *) a, m[3], b[3]);

    transposta(b);

    //C = U * B
    float U[4] = {u * u * u, u * u, u, 1};
    float c[4];

    for (int i = 0; i < 4; i++) {
        c[i] = 0;
        for (int j = 0; j < 4; j++)
            c[i] += U[j] * b[j][i];
    }

    //Coordenada = C * V
    float V[4] = {v * v * v, v * v, v, 1};
    float res = 0;

    for (int i = 0; i < 4; i++) {
        res += c[i] * V[i];
    }

    return res;
}

void bezier(const string &input_file, float tl, const string &output_file) {
    ifstream inFile(input_file);
    ofstream outFile;

    outFile.open(output_file, ofstream::out);

    if (inFile.is_open()) {
        string data;

        getline(inFile, data);
        int np = stoi(data);

        map<int, int *> indp = map<int, int *>();

        for (int i = 0; i < np; i++) {
            int *ind = new int[16];
            getline(inFile, data);
            istringstream ss(data);

            int j = 0;
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                ind[j] = stoi(substr);
                j++;
            }

            indp.insert(make_pair(i, ind));
        }

        getline(inFile, data);
        int ncp = stoi(data);

        map<int, float *> cp = map<int, float *>();

        for (int i = 0; i < ncp; i++) {
            auto *cpoint = new float[3];

            getline(inFile, data);
            stringstream ss(data);

            int j = 0;
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                cpoint[j] = stof(substr);
                j++;
            }

            cp.insert(make_pair(i, cpoint));
        }

        float ustep = 1 / tl;
        float vstep = 1 / tl;

        for (int p = 0; p < np; p++) {
            int *indices = indp.at(p);

            float *p00 = cp.at(indices[0]);
            float *p01 = cp.at(indices[1]);
            float *p02 = cp.at(indices[2]);
            float *p03 = cp.at(indices[3]);
            float *p10 = cp.at(indices[4]);
            float *p11 = cp.at(indices[5]);
            float *p12 = cp.at(indices[6]);
            float *p13 = cp.at(indices[7]);
            float *p20 = cp.at(indices[8]);
            float *p21 = cp.at(indices[9]);
            float *p22 = cp.at(indices[10]);
            float *p23 = cp.at(indices[11]);
            float *p30 = cp.at(indices[12]);
            float *p31 = cp.at(indices[13]);
            float *p32 = cp.at(indices[14]);
            float *p33 = cp.at(indices[15]);

            float p0x[4] = {p00[0], p01[0], p02[0], p03[0]};
            float p1x[4] = {p10[0], p11[0], p12[0], p13[0]};
            float p2x[4] = {p20[0], p21[0], p22[0], p23[0]};
            float p3x[4] = {p30[0], p31[0], p32[0], p33[0]};

            float p0y[4] = {p00[1], p01[1], p02[1], p03[1]};
            float p1y[4] = {p10[1], p11[1], p12[1], p13[1]};
            float p2y[4] = {p20[1], p21[1], p22[1], p23[1]};
            float p3y[4] = {p30[1], p31[1], p32[1], p33[1]};

            float p0z[4] = {p00[2], p01[2], p02[2], p03[2]};
            float p1z[4] = {p10[2], p11[2], p12[2], p13[2]};
            float p2z[4] = {p20[2], p21[2], p22[2], p23[2]};
            float p3z[4] = {p30[2], p31[2], p32[2], p33[2]};

            for (float u = 0; u + ustep <= 1; u += ustep) {
                for (float v = 0; v + vstep <= 1; v += vstep) {
                    float p1[3];
                    p1[0] = getCordPontoBelzier(u, v, p0x, p1x, p2x, p3x);
                    p1[1] = getCordPontoBelzier(u, v, p0y, p1y, p2y, p3y);
                    p1[2] = getCordPontoBelzier(u, v, p0z, p1z, p2z, p3z);

                    float p2[3];
                    p2[0] = getCordPontoBelzier(u, v + vstep, p0x, p1x, p2x, p3x);
                    p2[1] = getCordPontoBelzier(u, v + vstep, p0y, p1y, p2y, p3y);
                    p2[2] = getCordPontoBelzier(u, v + vstep, p0z, p1z, p2z, p3z);

                    float p3[3];
                    p3[0] = getCordPontoBelzier(u + ustep, v, p0x, p1x, p2x, p3x);
                    p3[1] = getCordPontoBelzier(u + ustep, v, p0y, p1y, p2y, p3y);
                    p3[2] = getCordPontoBelzier(u + ustep, v, p0z, p1z, p2z, p3z);

                    float p4[3];
                    p4[0] = getCordPontoBelzier(u + ustep, v + vstep, p0x, p1x, p2x, p3x);
                    p4[1] = getCordPontoBelzier(u + ustep, v + vstep, p0y, p1y, p2y, p3y);
                    p4[2] = getCordPontoBelzier(u + ustep, v + vstep, p0z, p1z, p2z, p3z);

                    outFile << p1[0] << " " << p1[1] << " " << p1[2] << "\n";
                    outFile << p3[0] << " " << p3[1] << " " << p3[2] << "\n";
                    outFile << p2[0] << " " << p2[1] << " " << p2[2] << "\n";

                    outFile << p3[0] << " " << p3[1] << " " << p3[2] << "\n";
                    outFile << p4[0] << " " << p4[1] << " " << p4[2] << "\n";
                    outFile << p2[0] << " " << p2[1] << " " << p2[2] << "\n";

                }
            }
        }
    } else {
        cerr << "Não foi possível abrir " << input_file << endl;
    }
}

int main(int argc, char **argv) {
    if (argc == 4 && argv[1] == string("plane")) {
        planeFile(stof(argv[2]), argv[3]);
    }

    else if (argc == 4 && argv[1] == string("plane")) {
        planeFile((stof(argv[2])), argv[3]);
    }

    else if (argc == 6 && argv[1] == string("box")) {
        boxFile(stof(argv[2]), stof(argv[3]), stof(argv[4]), argv[5]);
    }

    else if (argc == 6 && argv[1] == string("sphere")) {
        sphereFile(stof(argv[2]), stoi(argv[3]), stoi(argv[4]), argv[5]);
    }

    else if (argc == 7 && argv[1] == string("cone")) {
        coneFile(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]), argv[6]);
    }

    else if (argc == 5 && argv[1] == string("bezier")) {
        bezier(argv[2], stof(argv[3]), argv[4]);
    }

    else {
        cout << "Input Inválido" << endl;
    }

    return 0;
}
