#include <math.h>
#include <stdio.h>

#define M_PI 3.14159265358979323846

typedef struct {
    int x, y;
} Point;

double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

Point calculate_endpoint(Point start, double angle, double length) {
    Point end;
    end.x = start.x + (int)(length * cos(angle));
    end.y = start.y + (int)(length * sin(angle));
    return end;
}

void put_pixel(int x, int y) {
    // Placeholder function for putting a pixel on the screen.
    // You need to implement this based on your graphical library.
    printf("Putting pixel at (%d, %d)\n", x, y);
}

void draw_line(Point start, Point end) {
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);
    int sx = start.x < end.x ? 1 : -1;
    int sy = start.y < end.y ? 1 : -1;
    int err = dx - dy;

    while (1) {
        put_pixel(start.x, start.y);

        if (start.x == end.x && start.y == end.y) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            start.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            start.y += sy;
        }
    }
}

int main() {
    Point center = {100, 100}; // Center point
    double length = 50;        // Length of each line
    int num_lines = 12;        // Number of lines to draw
    double angle_increment = 360.0 / num_lines;

    for (int i = 0; i < num_lines; ++i) {
        double angle_deg = i * angle_increment;
        double angle_rad = degrees_to_radians(angle_deg);
        Point end = calculate_endpoint(center, angle_rad, length);
        draw_line(center, end);
    }

    return 0;
}

