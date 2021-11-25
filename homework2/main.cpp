#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

template <typename T> 
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

const double g = 9.81;



int main(int argc, char** argv)
{
    string input;
    try {


        if (argc == 2)
        {
            input = argv[1];
        }
        else {
            throw invalid_argument("wrong number of arguments");
        }
    }
    catch (invalid_argument e) {
        std::cout << e.what() << endl;
        return 0;
    }

     ifstream cin(input);

    double h0;
    cin >> h0;
    double vx0, vy0;
    cin >> vx0 >> vy0;
    double xi, hi;
    vector<double> xis;
    vector<double> his;

    double y = h0, t = 0, x = 0.0, vx = vx0, vy = vy0;
    int ans = 0;


    while (cin >> xi >> hi) {
        xis.push_back(xi);
        his.push_back(hi);       
    }

    while (x > xis[ans]) {
        ans++;
    }

    
    while (true) {
      
        int dir = sgn(vx);
   
        int next = (dir > 0) ? ans : ans - 1;
        
   

        if (next < 0 || next >= xis.size()) {
            cout << ans;
            return 0;
        }


        
        double dt = (xis[next] - x) / vx;
       
        y = y + vy * dt - g * dt * dt / 2;

       
        if (y <= 0.0) {
            std::cout << ans;
            return 0;
        } 
        else if (y >= his[next]) {
           
            
            
            x = xis[next];            
            
            
            ans += dir;
        }
        else if (y < his[next]) {
           
            vx = -vx;  
          
            x = xis[next];
            
        }
     
        vy = vy - g * dt;
        t += dt;

    }    
    return 0;
}



