#include <iostream>
using namespace std;

struct Point {
    double x, y;
};

struct Segment {
    Point start, end;
};

float getSlope(Segment& seg) {
    float m = (seg.end.y - seg.start.y) / (seg.end.x - seg.start.x);
    //cout << "Slope = " << m << endl;
    return m;
}

float getIntercept(Segment& seg) {
    float b = seg.end.y - getSlope(seg) * seg.end.x;
    return b;
}

float getX(float m1, float m2, float b1, float b2) {
    float x = (b2 - b1) / (m1 - m2);
    return x;
}

float getY(float x, float m1, float b1) {
    float y = m1 * x + b1;
    return y;
}

bool isInBounds(Segment& seg1, Segment& seg2, float x, float y) {
    bool x_valid = (x > seg1.start.x && x > seg2.start.x) && (x < seg1.end.x && x < seg2.end.x);
    bool y_valid_1; bool y_valid_2;
    bool isValid;

    if (getSlope(seg1) > 0) {
        y_valid_1 = (y > seg1.start.y && y < seg1.end.y);
    } else {
        y_valid_1 = (y < seg1.start.y && y > seg1.end.y);
    }
    
    if (getSlope(seg2) > 0) {
        y_valid_2 = (y > seg2.start.y && y < seg2.end.y);
        cout << "THIS ONE";
    } else {
        y_valid_2 = (y < seg2.start.y && y > seg2.end.y);
        cout << "No this!";
    }
    
    bool y_valid = y_valid_1 && y_valid_2;
    isValid = x_valid && y_valid;


    cout << "Seg1 X bounds: (" << seg1.start.x << " -> " << seg1.end.x << ")\n";
    cout << "Seg1 Y bounds: (" << seg1.start.y << " -> " << seg1.end.y << ")\n";
    cout << "Seg2 X bounds: (" << seg2.start.x << " -> " << seg2.end.x << ")\n";
    cout << "Seg2 Y bounds: (" << seg2.start.y << " -> " << seg2.end.y << ")\n";
    cout << "intersection: (" << x << ", " << y << ")\n";
    cout << "Logic: " << x_valid << " " << y_valid << endl;

    return x_valid && y_valid;
}

// Return true if seg1 and seg2 intersect
bool doSegmentsIntersect(Segment& seg1, Segment& seg2) {
    float m1 = getSlope(seg1); 
    float m2 = getSlope(seg2);
    float b1 = getIntercept(seg1);
    float b2 = getIntercept(seg2);
    
    // Intercept point
    float x = getX(m1, m2, b1, b2);
    float y = getY(x, m1 , b1);

    // Check if intercept is in bounds

    return isInBounds(seg1, seg2, x, y);
}


int main() {
    
    // Define points
    Point seg1_start;
    Point seg1_end;
    Point seg2_start;
    Point seg2_end;

    seg1_start.x = 0; seg1_start.y = 0;
    seg1_end.x = 2; seg1_end.y = 2;
    seg2_start.x = 0; seg2_start.y = 1;
    seg2_end.x = 1; seg2_end.y = 0;

    // Define segments
    Segment seg1;
    Segment seg2;
    seg1.start = seg1_start; seg1.end = seg1_end;
    seg2.start = seg2_start; seg2.end = seg2_end;
    
    bool doIntersect = doSegmentsIntersect(seg1, seg2);
    cout << "Result: " << doIntersect;

    
    return 0;
}