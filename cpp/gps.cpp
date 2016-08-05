#include <iostream>
#include <cmath>

using namespace std;

namespace constants
{
    const double pi(3.14159);
    const double km(6371);
}

class Coordinate
{
    private:
        double x, y;

    public:
        Coordinate(double lx=0.0, double ly=0.0) : x(lx), y(ly) { }
        Coordinate(const Coordinate &c) {
            x = c.latitude();
            y = c.longitude();
        }

        double latitude(void)  const    { return x;  }
        double longitude(void) const    { return y; }
        double lat(void) const { return x; }
        double log(void) const { return y; }
        void  latitude(double v)       { x = v;  }
        void  longitude(double v)      { y = v; }

        friend std::ostream& operator<< (std::ostream &out, const Coordinate &c)
        {
            out<< "(" << c.latitude() << ", " << c.longitude() << ")";;
             return out;
        }
};


double toRadian(double v)
{
    return (v * constants::pi) / 180;
}


/* double distance(Coordinate c1, Coordinate c2)
{
    double dLat = toRadian(c2.latitude() - c1.latitude());
    double dLon = toRadian(c2.longitude() - c1.longitude());
    double lat1 = toRadian(c1.latitude());
    double lat2 = toRadian(c2.latitude());

    double a = sin(dLat/2) * sin(dLat/2) +
                sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return constants::km * c;
} */

double distance(Coordinate c1, Coordinate c2)
{
    double d = sqrt( pow((c2.lat()-c1.lat()), 2) +
                     pow((c2.log()-c1.log()), 2) );
    return d;
}


double distance(Coordinate (&ep)[2])
{
    return distance(ep[0], ep[1]);
}


class Circle
{
    private:
        Coordinate cp;
        double rd;

    public:
        Circle(Coordinate c, int r) : cp(c), rd(r) {}
    
        Coordinate center_point(void) const {
            return cp;
        }
};

class Line
{
    private:
        double d;

    public:
        Coordinate ep[2];
        Line(Coordinate ps[2]) {
            std::copy(ep, ep+2, ps);
            d = ::distance(ep);
        }

        Line(Coordinate p1=0.0, Coordinate p2=0.0) : ep({p1,p2}) {
            d = ::distance(ep);
        }

        double distance(void) {
            return d;
        }
};


/* Calculate if the line intersects the circle */

double checkIntersection(Line l, Circle c)
{
    double d = l.distance();
    double dx = (l.ep[1].lat() - l.ep[0].lat()) / d;
    double dy = (l.ep[1].log() - l.ep[0].log()) / d;

    double t = dx * (c.center_point().lat() - l.ep[0].lat()) + 
               dy * (c.center_point().log() - l.ep[0].log());

    double ex = t * dx + l.ep[0].lat();
    double ey = t * dy + l.ep[0].log();

    cout << "(" << ex << ", " << ey << ")" << endl;

    return 0.0;
}

int main(void)
{
    Coordinate p1(52.216691, 0.105535);
    Coordinate p2(52.216288, 0.106272);
    Coordinate cp(52.216410, 0.106017);

    Circle c = Circle(cp, 2);
    Line l(p1, p2);
    
    cout << p1.latitude() << endl;
    cout <<  l.distance() << endl;
    checkIntersection(l, c);

    //cout << toRadians(c1.get_latitude()) << endl;
    
    return 0;
}
