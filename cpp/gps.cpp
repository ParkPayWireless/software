#include <iostream>
#include <cmath>

using namespace std;

namespace constants
{
    const double pi(3.14159);   
}


class Point
{
    private:
        double value;

    public:
        Point(double v=0.0) : value(v) { }

        float get(void) const { return value; }
        void  set(double v) { value = v; };
};

class Coordinate
{
    private:
        Point latitude;
        Point longitude;

    public:
        Coordinate(double lat=0.0, double log=0.0) : latitude(lat), longitude(log) { }

        float get_latitude(void)  const    { return latitude.get();  }
        float get_longitude(void) const    { return longitude.get(); }
        void  set_latitude(double v)             { latitude.set(v);  }
        void  set_longitude(double v)            { longitude.set(v); }
        
        friend std::ostream& operator<< (std::ostream &out, const Coordinate &c)
        {
            out<< "(" << c.get_latitude() << ", " << c.get_longitude() << ")";;
            return out;
        }
};

double toRadian(double v) 
{
    return (v * constants::pi) / 180;
}

double distance(Coordinate c1, Coordinate c2) 
{
    double dLat = toRadian(c2.get_latitude() - c1.get_latitude());
    double dLon = toRadian(c2.get_longitude() - c1.get_longitude());
    double lat1 = toRadian(c1.get_latitude());
    double lat2 = toRadian(c2.get_latitude());

    double a = sin(dLat/2) * sin(dLat/2) +
                sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return 6371 * c;
}


int main(void)
{
    Coordinate c1(52.225606, 0.087515);
    Coordinate c2(52.214042, 0.110569);
    cout << c1 << endl;
    cout << c2 << endl;

    cout << distance(c1,c2) << endl;


    //cout << toRadians(c1.get_latitude()) << endl;
    
    return 0;
}
