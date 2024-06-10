#pragma once

// Random number
void genRandSeed(); // Setup seed for randomize
int getRandNum(int, int); // Random a number in a range
int getRandNumbWithProb(int, int, int); // Random a number base on prob

// Time
char* getCurrTime();
void printCurrTime();

//------------------Point3D--------------------------------------
struct Point3D
{
private:
    int x, y, z;

public:
    Point3D();
    Point3D(int a, int b, int c) :x(a), y(b), z(c) {};
    ~Point3D();

    int getX() const{ return x; };
    int getY() const{ return y; };
    int getZ() const{ return z; };

    friend std::ostream& operator<< (std::ostream& out, Point3D& p);
    friend std::istream& operator>> (std::istream& in, Point3D& p);

    bool operator== (Point3D& other);
};

//------------------Point2D------------------------------------
struct Point2D
{
private:
    int x, y;

public:
    Point2D();
    Point2D(int a, int b) :x(a), y(b) {};
    ~Point2D();

    int getX() const{ return x; };
    int getY() const{ return y; };

    friend std::ostream& operator<< (std::ostream& out, Point2D& p);
    friend std::istream& operator>> (std::istream& in, Point2D& p);

    bool operator== (Point2D& other);
    bool operator< (Point2D& other);
    bool operator> (Point2D& other);
};

// --------------Player Infomation ---------------------
struct Infomation
{
private:
    std::string player_name;
    std::string date;
    int age;
    long long highscore;
};

//--------------Colorful text---------------------------
struct ColorfulCell // Color every cell
{
private:
    int value = 0;
    int color;
    std::string colorText();
};