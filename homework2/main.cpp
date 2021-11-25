#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// функция определения знака числа
template <typename T> 
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

// ускорение свободного падения
const double g = 9.81;



int main(int argc, char** argv)
{
    // входной файл
    string input;
    try {


        if (argc == 2)
        {
            // если есть аргументы на входе
            input = argv[1];
        }
        else {
            // выкидываем исключение
            throw invalid_argument("wrong number of arguments");
            //input = "input.txt";
        }
    }
    catch (invalid_argument e) {
        // нет входного файла
        std::cout << e.what() << endl;
        return 0;
    }

    // входной поток из файла
     ifstream cin(input);

     // начальная высота
    double h0;
    cin >> h0;
    // начальные скорости
    double vx0, vy0;
    cin >> vx0 >> vy0;
    // вектор препятсвий
    double xi, hi;
    vector<double> xis;
    vector<double> his;

    // текущая высота, время, дистанция и скорости
    double y = h0, t = 0, x = 0.0, vx = vx0, vy = vy0;
    // текущий участок
    int ans = 0;

    // попробуем добавить в начало и конец препятсвия отрицательной высоты
    // для удобства
    //xis.push_back(0.0);
    //his.push_back(-1.);

    // ввод препятсвий из файла
    while (cin >> xi >> hi) {
        xis.push_back(xi);
        his.push_back(hi);       
    }

    // в конце препятсвие отрицательной высоты
    //xis.push_back(xis.back()*2+10.0);
   // his.push_back(-1.);

    // найдем начальную секцию
    while (x > xis[ans]) {
        ans++;
    }

    
    while (true) {
        // определяем направление движения, как знак скорости по иксу
        int dir = sgn(vx);
        // определям следующее препятсвие.
        // ans+1 если движемся вперед
        // ans если движемся обратно
        //int next = (dir > 0) ? ans + dir : ans;
        int next = (dir > 0) ? ans : ans - 1;
        
        // если высота следующего препятсвия отрицательная 
        // это либо первое, либо последнее - заканчиваем на текущем участке
        //if (his[next] < 0 ) {
        //    std::cout << ans;
        //    return 0;
        //}

        if (next < 0 || next >= xis.size()) {
            cout << ans;
            return 0;
        }


        // если мы в первой секции и движемся в обратную сторону от броска
        // то заканчиваем на 0 участке
        //if (ans == 0 && dir < 0) {
        //    std::cout << 0;
        //    return 0;
        //}
        
        // рассчитаем время полета в текущем участке
        double dt = (xis[next] - x) / vx;
        // рассчитаем высоту на момент столкновения
        y = y + vy * dt - g * dt * dt / 2;

        // если высота меньше 0, то мы уже на земле
        if (y <= 0.0) {
            std::cout << ans;
            return 0;
        } // иначе если высота выше следующего препятсвия, то мы перелетели его
        else if (y >= his[next]) {
            // перелетели 
            // проверяем следующее препятствие
            
            // изменяем координату х
            x = xis[next];            
            
            // изменяем текущий участок в сторону направления движения
            ans += dir;
        } // если не перелетели
        else if (y < his[next]) {
            // не перелетели
            // отталкиеваемся в обратную сторону
            // скорость по х - меняет знак
            vx = -vx;  
            // текущая кордината х
            x = xis[next];
            
        }
        // обновляем скорости и время
        vy = vy - g * dt;
        t += dt;

    }    
    return 0;
}





