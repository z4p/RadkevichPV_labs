#include <string>
#include <iostream>

using namespace std;

class Transport
{
public:
    Transport() {};
    Transport(string name)
    {
        this->name = name;
    }
    Transport(const Transport &t) = delete;
    Transport& operator=(const Transport &t) = delete;
    Transport(Transport &&t) = delete;
    Transport& operator=(const Transport &&t) = delete;
    virtual ~Transport() {};

    string getName()
    {
        return name;
    }
    virtual int getTime(int distance) const = 0;
    virtual int getPrice(int distance) const = 0;
private:
    string name;
};

class Train : public Transport
{
public:
    Train() {};
    Train(int speed, int tariff, string name) : Transport(name)
    {
        this->speed = speed;
        this->tariff = tariff;
    }

    virtual int getTime(int distance) const override
    {
        return distance / speed + 1;
    }

    virtual int getPrice(int distance) const override
    {
        return distance * tariff;
    }

protected:
    int speed;
    int tariff;
};

class Plane : public Transport
{
public:
    Plane() {};
    Plane(int speed, int tariff, string name) : Transport(name)
    {
        this->speed = speed;
        this->tariff = tariff;
    }

    virtual int getTime(int distance) const override
    {
        return distance / speed + 1;
    }

    virtual int getPrice(int distance) const override
    {
        int x = 1;
        if (distance < 500)
        {
            x = 2;
        }
        return distance*tariff * x;
    }

protected:
    int speed;
    int tariff;
};

class Bus : public Transport
{
public:
    Bus() {};
    Bus(int speed, int tariff, int tariff_hotel, string name) : Transport(name)
    {
        this->speed = speed;
        this->tariff = tariff;
        this->tariff_hotel = tariff_hotel;
    }

    virtual int getTime(int distance) const override
    {
        int waytm = distance / speed;
        int hotel_time = 0;
        if (waytm > 16)
        {
            hotel_time = (waytm / 16) * 8;
            if (waytm % 16 == 0)
            {
                hotel_time -= 8;
            }
        }

        return waytm + hotel_time;
    }

    virtual int getPrice(int distance) const override
    {
        int hotel_price = 0;
        int waytm = distance / speed;
        if (waytm > 16)
        {
            hotel_price = tariff_hotel * (waytm / 16);
        }
        return distance*tariff + hotel_price;
    }

protected:
    int speed;
    int tariff;
    int tariff_hotel;
};

int main()
{
    Train t1(110, 5, "Elektron"), t2(650, 10, "Tokio-Kioto-style train");
    Bus b1(90, 7, 50, "Auto Polska"), b2(40, 1, 10, "Zaporozec");
    Plane p1(600, 10, "Boing 747"), p2(120, 8, "Estonia Airlines");
    
    cout << t1.getName() << " | " << t1.getPrice(500) << " | " << t1.getTime(500) << endl;
    cout << t2.getName() << " | " << t2.getPrice(800) << " | " << t2.getTime(800) << endl;
    
    cout << b1.getName() << " | " << b1.getPrice(1000) << " | " << b1.getTime(1000) << endl;
    cout << b2.getName() << " | " << b2.getPrice(1000) << " | " << b2.getTime(1000) << endl;
    
    cout << p1.getName() << " | " << p1.getPrice(400) << " | " << p1.getTime(400) << endl;
    cout << p2.getName() << " | " << p2.getPrice(800) << " | " << p2.getTime(800) << endl;
    
    return 0;
}
