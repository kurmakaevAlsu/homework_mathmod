#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

double get_t(double x_0, double x, double vx,int d)
{
    return (x - x_0)/(d*vx);
}

double get_vy(double vy_0, double t)
{
    return vy_0 - 9.81*t;
}

double get_height(double h_0, double vy, double t)
{
    return h_0 + vy*t - 9.81/2 * pow(t, 2);
}

void get_h0(ifstream &input_file, double &h)
{
    string temp;
    input_file >> temp;
    h = stod(temp);
}

void get_v0(ifstream &input_file, double &vx,double &vy) // Функция получения начальной скорости
{
    string v1;
    string v2;
    input_file >> v1 >> ws >> v2;
    vx = stod(v1);
    vy = stod(v2);
}

void get_bar(ifstream &input_file,vector<double> &X, vector<double> &H) // функция считывания параметров столбов
{
    string x;
    string h;
    input_file >> x >> ws >> h;
    X.push_back(stod(x));
    H.push_back(stod(h));
}
void calculate_2(double x0,double h0, double vx, double vy, vector<double> &X, vector<double> &H, int &result,
                 int dir)
{
    double y;
    double t;
    for (int i = result; (i > -1 && i < X.size()); i = i + dir)
    {
        t = get_t(x0, X[i+dir], vx, dir);
        y = get_height(h0, vy, t);
        if (H[i + dir] < y)
        {
            result += dir;
        } else if((y < 0) || (result == 0))
        {
            return;
        }
        else
        {
            double vyt = get_vy(vy, t);
            dir = dir * -1;
            calculate_2(X[i], y, vx, vyt, X, H, result, dir);
            return;
        }
    }
}


void calculate_1(ifstream &input_file, double &h0, double &vx, double &vy, vector<double> &X, vector<double> &H,
                 int &result)
{
    string line;
    double t;
    double y;
    while (getline(input_file,line))
    {
        get_bar(input_file, X, H);
        t = get_t(0, X.back(), vx, 1);
        y = get_height(h0, vy, t);
        if(H.back() < y)
        {
            result++;
        }
        else if((y < 0) || (result == 0))
        {
            return;
        }
        else
        {
            double vyt = get_vy(vy, t);
            calculate_2(X.back(), y, vx, vyt, X, H, result, -1);
            return;
        }
    }
}



int main(int argc, char** argv)
{
    string input_filename;

    if (argc == 2)
    {
        input_filename = argv[1];
    } else {
        input_filename = "input.txt";
    }
    ifstream input_file(input_filename);

    double h0;
    double vx;
    double vy;

    int result = 0;

    vector<double> X;
    vector<double> H;

    get_h0(input_file, h0);
    get_v0(input_file, vx, vy);

    calculate_1(input_file, h0, vx, vy, X, H, result);

    cout << result << endl;
    return 0;
}
