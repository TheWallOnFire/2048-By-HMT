#include "pch.h"
#include "Types.h"

using namespace std;

// ------------------------RandomNumber---------------------------
// Generate a random seed based on the current system time
void genRandSeed() {
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);
    std::cout << "Random seed generated: " << seed << "\n";
}

// Generate a random number between 'minValue' and 'maxValue'
int getRandNum(int min, int max) {
    return min + (rand() % (max - min + 1));
}

// Generate a random number based on a given percentage
int getRandNumbWithProb(int min, int max, int prob = 50) {
    int rand = getRandNum(0, 100);
    if (rand < prob) {
        return min;
    }
    else {
        return max;
    }
}

char* getCurrTime()
{
    //time_t rawtime;
    //time(&rawtime);
    //return ctime(&rawtime);
    return nullptr;
}
void printCurrTime()
{
    printf("The current local time is: %s", getCurrTime());
}



// ----------------------------Point 3D-------------------------------
Point3D::Point3D()
{
    x = 0; y = 0; z = 0;
}
Point3D::~Point3D()
{
}

std::ostream& operator<<(std::ostream& out, Point3D& p)
{
    out << "(" << p.x << "," << p.y << "," << p.z << ")";
    return out;
}
std::istream& operator>>(std::istream& in, Point3D& p)
{
    in >> p.x >> p.y >> p.z;
    return in;
}
bool Point3D::operator== (Point3D& other)
{
    return (x == other.getX()) && (y == other.getY())
        && (z == other.getY());
}

// ----------------------------Point 2D-------------------------------
Point2D::Point2D()
{
    x = 0; y = 0;
}
Point2D::~Point2D()
{
}

std::ostream& operator<<(std::ostream& out, Point2D& p)
{
    out << "(" << p.x << "," << p.y << ")";
    return out;
}
std::istream& operator>>(std::istream& in, Point2D& p)
{
    in >> p.x >> p.y;
    return in;
}

bool Point2D::operator==(Point2D& other)
{
    return (x == other.getX()) && (y == other.getY());
}
bool Point2D::operator<(Point2D& other)
{
    return (x * y * (x + y)) < (other.getX() * other.getY() * (other.getX() + other.getY()));
}
bool Point2D::operator>(Point2D& other)
{
    return (x * y * (x + y)) > (other.getX() * other.getY() * (other.getX() + other.getY()));
}