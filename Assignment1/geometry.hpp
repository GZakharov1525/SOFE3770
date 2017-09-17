#ifndef GEOMETRY_HPP  // These are file guards
#define GEOMETRY_HPP

#include <iostream>
#include <vector>

class Point
{
<<<<<<< HEAD
public:
	int x;
	int y;
	friend std::ostream& operator<<(std::ostream& os, const Point& point);  // Define os << operator for Point
	Point()
	{
		/**
		 * This is the default constructor
		 */
		this->x = 0;
		this->y = 0;
	}
	Point(int x_cord, int y_cord)
	{
		/**
		 * This constructor creates objects with the values passed in
		 */
		this->x = x_cord;
		this->y = y_cord;
	}
=======
   public:
    int x;
    int y;
    friend std::ostream& operator<<(std::ostream& os,
                                    const Point& point);  // Define os << operator fo Point
    Point()
    {
        /**
         * This is the default constructor
         */
        this->x = 0;
        this->y = 0;
    }
    Point(int x_cord, int y_cord)
    {
        /**
         * This constructor creates objects with the values passed on
         */
        this->x = x_cord;
        this->y = y_cord;
    }
>>>>>>> 415bb857038d5367f1faa18daea3d0cbeb54cf9f
};

// Make Line class here.
class Segment
{
<<<<<<< HEAD
public:
	Point start;
	Point end;

	// put prototype functions here
	double compareSegments(Segment a, Segment b); 

	// Constructors are defined in headers
	Segment()
	{
		Point default_set = { 0, 0 };
		this->start = default_set;
		this->end = default_set;
	}

	Segment(Point a, Point b)
	{
		this->start = a;
		this->end = b;
	}
=======
   public:
    Point start;
    Point end;
    double getLength(); // Returns the length of the line
    Segment()
    {
        Point default_set = {0, 0};
        this->start       = default_set;
        this->end         = default_set;
    }
>>>>>>> 415bb857038d5367f1faa18daea3d0cbeb54cf9f

    Segment(Point a, Point b)
    {
        this->start = a;
        this->end   = b;
    }
};

// Add method declarations(prototypes) here. For example
double getEuclideanDistance(Point, Point);

// George! you need to implement this, BEFORE MONDAY!!
Segment findBiggestEdge(std::vector<Segment>);

// I will implement these
std::vector<Segment> generateDiagonals(std::vector<Segment>);
Segment findBiggestSegment(std::vector<Segment>);
bool doIntersect(Segment,Segment);
bool doIntersect(Segment,std::vector<Segment>);

#endif /* GEOMETRY_HPP */
