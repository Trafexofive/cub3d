
#include <math.h>
#include <stdio.h>
#include "../inc/macros.h"

#define PI 3.14159265358979323846

double radians_to_degrees(double radians) {
    return radians * (180.0 / PI);
}

double degrees_to_radians(double degrees) {
    return degrees * (PI / 180.0);
}

int main() {
    double angle_rad = PI / 4; // 45 degrees in radians
    double angle_deg = 45.0;     // 45 degrees

    printf("45 degrees in radians: %f\n", degrees_to_radians(angle_deg));
    printf("PI/4 radians in degrees: %f\n", radians_to_degrees(angle_rad));

    return 0;
}

