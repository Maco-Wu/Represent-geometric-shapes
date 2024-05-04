#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Coordinates {
    private:
    int x;
    int y;

    public:
    //Structure of the coordinates
    Coordinates(int x, int y) : x(x), y(y){}

    //By using the get() method
    int getX() const { return x; }
    int getY() const { return y; }

    //Calculate the distance between coordinates
    double distance(const Coordinates& p) const {
        int dx = p.x - x;
        int dy = p.y - y;
        return sqrt((double)(dx * dx + dy * dy));
    }

    //Translate method coordinates
    void translate(int dx, int dy) {
        x += dx;
        y += dy;
    }

    //Scale method coordinates
    void scale(int factor, bool sign) {
        if (sign) {
            x *= factor;
            y *= factor;
        } else {
            x /= factor;
            y /= factor;
        }
    }

    //Display method coordinates
    string display() const { 
        return "X = " + to_string(x) + "Y = " + to_string(y);
    }
};



//Shape methods
class Shape {
    protected:
    Coordinates position;
    int sides;

    public:
    Shape(int noOfSides, const Coordinates& coord) : sides(noOfSides), position(coord) {}

    Coordinates getCoordinates() const { return position; }

    int getSides() const { return sides; }

    void setCoordinates(const Coordinates& newCoord) { position = newCoord; }

    virtual void translate(int dx, int dy) { position.translate(dx, dy); }

    virtual void scale(int factor, bool sign) = 0;

    virtual double getArea() const = 0;

    virtual double getPerimeter() const = 0;

    virtual string display() const = 0;
};

//Rectangle class implementation
class Rectangle : public Shape {
    private:
    int length;
    int width;

    public:
    Rectangle(const Coordinates& coord, int length, int width) : Shape(4, coord), length(length), width(width) {}

    double getArea() const override { return length * width; }

    double getPerimeter() const override { return 2 * (length + width);}

    void scale(int factor, bool sign) override {
        if (sign) {
            length *= factor;
            width *= factor;
        } else {
            length /= factor;
            width /= factor;
        }
    }

    string display() const override {
        ostringstream oss;
        oss << "Position of Rectangle is " << position.display() << ", length is " << length << ", width is " << width 
            << ", Area is " << getArea() << "Finally, the perimeter is " << getPerimeter();
        return oss.str();
    }
};


//Square class implementation
class Square : public Shape {
    private:
    int side;

    public:
    Square(const Coordinates& coord, int side) : Shape(4, coord), side(side) {}

    double getArea() const override { return side * side; }

    double getPerimeter() const override { return 4 * side; }

    void scale(int factor, bool sign) override {
        if(sign) {
            side *= factor;
            } else {
                side /= factor;
            }
        }

    string display() const override {
        ostringstream oss;
        oss << "Position of Square is  " << position.display() << ", Side is " << side
            << ", Area is " << getArea() << ", Finally the perimeter is  " << getPerimeter();
        return oss.str();
    }
};


//Circle class implementation
class Circle : public Shape {
    private: 
    int radius;

    public:
    Circle(const Coordinates& coord, int radius) : Shape(0, coord), radius(radius) {}

    double getArea() const override { return M_PI * radius * radius; }

    double getPerimeter() const override { return 2 * M_PI * radius; }

    void scale(int factor, bool sign) override {
        if (sign) {
            radius *= factor;
        } else {
            radius /= factor;
        }
    }

    string display() const override {
        ostringstream oss;
        oss << "Position of Circle is " << position.display() << ", Radius is " << radius
        << ", Area is  " << getArea() << ", and finally perimeter is " << getPerimeter();
        return oss.str();
    }
};


//Triangle class implementation
class Triangle : public Shape {
    private:
    Coordinates vertex_1;
    Coordinates vertex_2;
    Coordinates vertex_3;

    double calculateSemiPerimeter() const {
        double a = vertex_1.distance(vertex_2);
        double b = vertex_2.distance(vertex_3);
        double c = vertex_3.distance(vertex_1);
        return (a + b + c) / 2;
    }

    double calculateArea() const {
        double a = vertex_1.distance(vertex_2);
        double b = vertex_2.distance(vertex_3);
        double c = vertex_3.distance(vertex_1);
        double s = calculateSemiPerimeter();
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    public:
    Triangle(const Coordinates& vertex_1, const Coordinates& vertex_2, const Coordinates& vertex_3) : Shape(3, vertex_1), vertex_1(vertex_1), vertex_2(vertex_2), vertex_3(vertex_3) {}

    double getArea() const override { return calculateArea(); }

    double getPerimeter() const override {
        double a = vertex_1.distance(vertex_2);
        double b = vertex_2.distance(vertex_3);
        double c = vertex_3.distance(vertex_1);
        return a + b + c;
    }

    void translate(int dx, int dy) override {
        vertex_1.translate(dx,dy);
        vertex_2.translate(dx,dy);
        vertex_3.translate(dx,dy);
    }

    void scale(int factor, bool sign) override {
        if (sign) {
            vertex_1.scale(factor, true);
            vertex_2.scale(factor, true);
            vertex_3.scale(factor, true);
        } else {
            vertex_1.scale(factor, false);
            vertex_2.scale(factor, false);
            vertex_3.scale(factor, false);
        }
    }

    string display() const override {
        ostringstream oss;
        oss << "The vertex 1 of triangle is " << vertex_1.display() << ", the vertex 2 of triangle is " << vertex_2.display() << ", the vertex 3 of triangle is " << vertex_3.display()
            << ", the area of the triangle is " << getArea() << ", finally the perimeter of triangle is " << getPerimeter();
        return oss.str();
    }


};


class ShapeList {
    private:
    vector <Shape*> listOfShapes;

    public:
    ShapeList() {
        for (Shape* shape : listOfShapes) {
            delete shape;
        }
        listOfShapes.clear();
    }

    void addShape(Shape* shape) { listOfShapes.push_back(shape); }

    void translateShapes(int dx, int dy) {
        for (Shape* shape : listOfShapes) {
            shape->translate(dx, dy);
        }
    }

    Shape* getShape(int position) {
        if (position >=0 && position < listOfShapes.size()) {
            return listOfShapes[position];
        } 
        return nullptr;
    }

    bool removeShape(int position) {
        if (position >=0 && position < listOfShapes.size()) {
            delete listOfShapes[position];
            listOfShapes.erase(listOfShapes.begin() + position);
            return true;
        }
        return false;
    }

    double area(int position) {
        Shape* shape = getShape(position);
        if (shape) {
            return shape->getArea();
        }
        return 0.0;
    }

    void scale(int factor, bool sign) {
        for (Shape* shape : listOfShapes) {
            shape->scale(factor, sign);
        }
    }

    double perimeter(int position) {
        Shape* shape = getShape(position);
        if (shape) {
            return shape->getPerimeter();
        }
        return 0.0;
    }

    string display() const {
        ostringstream oss;
        oss << "ShapeList: " << listOfShapes.size() << " shapes: " << endl;
        for (int i = 0; i < listOfShapes.size(); i++) {
            oss << "i" << ": " << listOfShapes[i]->display() << endl;
        }
        return oss.str();
    }
};


class ShapeManagement {
    private:
    ShapeList shapeList;

    public:
    void run() {
        int choice;
        do {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;
            handleChoice(choice);
        } while (choice != 0);
    }

    private:
    void displayMenu() {
        cout << "\nManagement Menu:\n";
        cout << "1. Add shape\n";
        cout << "2. Remove a shape by position\n";
        cout << "3. Get info about a shape by position\n";
        cout << "4. Area and perimeter of the shape by position\n";
        cout << "5. Display info for all the shapes\n";
        cout << "6. Translate all the shapes\n";
        cout << "7. Scale all the shapes\n";
        cout << "8. Quit\n";
    }

    void handleChoice(int choice) {
        switch (choice) {
            case 1: addShape(); break;
            case 2: removeShape(); break;
            case 3: getShapeInfo(); break;
            case 4: getShapeAreaPerimeter(); break;
            case 5: displayAllShapes(); break;
            case 6: translateShapes(); break;
            case 7: scaleShapes(); break;
            case 8: cout << "Exiting\n"; break;
            default: cout << "Number is not valid, enter again.\n";
        }
    }

    void addShape() {
        int choice;
        cout << "Select what shape you want to add.\n";
        cout << "1. Rectangle\n";
        cout << "2. Square\n";
        cout << "3. Circle\n";
        cout << "4. Triangle\n";
        cout << "Choice: ";
        cin >> choice;

        int x, y;
        cout << "Enter the x and y coordinates of the shape: ";
        cin >> x >> y;
        Coordinates coord(x, y);

        Shape* newShape = nullptr;
        switch (choice) {
            case 1: {
                int length, width;
                cout << "Enter the length and width of the shape of rectangle: ";
                cin >> length >> width;
                newShape = new Rectangle(coord, length, width);
                break;
            }
            case 2: {
                int side;
                cout << "Enter the side length of the shape of square: ";
                cin >> side;
                newShape = new Square(coord, side);
                break;
            }
            case 3: {
                int radius;
                cout << "Enter the radius of the shape of circle: ";
                cin >> radius;
                newShape = new Circle(coord, radius);
                break;
            }
            case 4: {
                int x_1, y_1, x_2, y_2, x_3, y_3;
                cout << "Enter the x and y coordinates of the triangle(x_1 y_1 x_2 y_2 x_3 y_3): ";
                cin >> x_1 >> y_1 >> x_2 >> y_2 >> x_3 >> y_3;
                Coordinates v_1(x_1, y_1), v_2(x_2, y_2), v_3(x_3, y_3);
                newShape = new Triangle(v_1, v_2, v_3);
                break;
            }
            default:
            cout << "Invalid choice\n";
            return;
        }

        if (newShape) {
            shapeList.addShape(newShape);
            cout << "Shape created successfully.\n";
        } else {
            cout << "Failed to create shape.\n";
        }
    }

    void removeShape() {
        int position;
        cout << "Enter the position of the shape to remove: ";
        cin >> position;
        if (shapeList.removeShape(position)) {
            cout << "Shape removed successfully.\n";
        } else {
            cout << "Position out of range or no such shape exists.\n";
        }
    }

    void getShapeInfo() {
        int position;
        cout << "Enter the position of the shape to display information for: ";
        cin >> position;
        Shape* shape = shapeList.getShape(position);
        if (shape) {
            cout << shape->display() << "\n";
        } else {
            cout << "No shape at that position or invalid position.\n";
        }
    }

    void getShapeAreaPerimeter() {
        int position;
        cout << "Enter the position of the shape: ";
        cin >> position;
        cout << "Area: " << shapeList.area(position) << "\n";
        cout << "Perimeter: " << shapeList.perimeter(position) << "\n";
    }

    void displayAllShapes() {
        cout << shapeList.display();
    }

    void translateShapes() {
        int dx, dy;
        cout << "Enter the x distance to translate: ";
        cin >> dx;
        cout << "Enter the y distance to translate: ";
        cin >> dy;
        shapeList.translateShapes(dx, dy);
        cout << "All done\n";
    }

    void scaleShapes() {
        int factor;
        bool sign;
        cout << "Enter the scaling factor: ";
        cin >> factor;
        cout << "Enter 1 for multiplication or 0 for division: ";
        cin >> sign;
        shapeList.scale(factor, sign);
        cout << "All done\n";
    }


};



//Main Function
int main() {
    ShapeManagement shapeManagement;
    shapeManagement.run();
    return 0;
};