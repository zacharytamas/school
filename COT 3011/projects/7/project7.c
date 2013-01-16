/*
 *  COT 3011, University of West Florida
 *  Project 7
 *
 *  @author Zachary Jones <zacharytamas@gmail.com>
 *  @version 1.0
 *  @releasedate April 15, 2011
 */

#include <stdio.h>

#define SIZE        5
#define FIELD_SIZE  20

/*
    1 Ð Add a Vehicle to the list
    2 Ð Remove a Vehicle from the list
    3 Ð Display one Vehicle
    4 Ð Display all Vehicles
    5 Ð Display all Vehicles in a specific price range
    6 Ð Display all Vehicles of a specific style
    7 Ð Terminate the program
*/

enum Style {
    TWO_DOOR,
    FOUR_DOOR,
    CONVERTIBLE,
    SUV,
    TRUCK
};

enum Color {
    RED,
    BLUE,
    YELLOW,
    WHITE,
    SILVER,
    BLACK
};

typedef struct Vehicle {
    int vin;
    int year;
    char make[FIELD_SIZE];
    double price;
    enum Style style;
    char color[FIELD_SIZE];
} Vehicle;


int main(void)
{
    
    return 1;
}

