/*
 Кентавром считается тот, чьё имя содержит чётное 
 количество гласных. Как известно, длина имени кентавра 
 соответствует социальному положению в обществе: чем длиннее 
 его имя, тем более высокое положение он может занимать.
 Для таких рангов как жрец, требуется имя не короче 8 букв.
 
 Время для выборов кентавра-жреца на ближайшие 5 лет, требуется
 вывести список возможных претендентов.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

class isNotKentavr {
private:
public:
    isNotKentavr() = default;
    isNotKentavr(isNotKentavr& obj) = default;
    isNotKentavr(isNotKentavr&& obj) = default;
    isNotKentavr& operator=(isNotKentavr& rv) = default;
    isNotKentavr& operator=(isNotKentavr&& rv) = default;
    ~isNotKentavr() = default;
    
    bool operator()(string s) {
        string g("aeiouy");
        int c = count_if(s.begin(), s.end(), [g](char ch){ return g.find(ch) != 
string::npos; });
        return c % 2;//толькі у вас атрымалася наадварот нецотная колькасць, а 
//так файна з гумарам 
        // не, четная, просто предикат писался для отсеивания некентавров. 
// Посему неграмотным было его название. Пофикшено
    }
};

int main() {
    vector<string> v;
    fstream f("names.txt", ios::in);
    while(!f.eof()) {
        string name;
        f >> name;
        v.push_back(name);
    }
    f.close();
    
    vector<string>::iterator end;
    end = remove_if(v.begin(), v.end(), isNotKentavr()); // отсеяли некентавров
    end = remove_if(v.begin(), end, [](string s){ return s.length() < 8; } ); // отсеяли кентавров-плебеев
    
    cout << "Подходящие кентавры: " << endl;
    for(auto i = v.begin(); i != end; ++i)
        cout << *i << endl;
    
    return 0;
}
