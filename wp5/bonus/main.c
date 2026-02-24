#include <stdint.h>
#include <stdio.h>

// Bitfield with Least Significant Bit (LSB) up top
// and Most Significant Bit (MSP) at the bottom
typedef struct {
    uint8_t brake2   : 1; // Bit 0 (LSB)
    uint8_t brake1   : 1; // Bit 1
    uint8_t door_pos : 2; // Bits 2-3
    uint8_t floor_pos: 3; // Bits 4-6
    uint8_t engine_on: 1; // Bit 7 (MSB)
} Bitfield;

// Bit union map
typedef union {
    uint8_t value; // used to derive the hex value from the bitfield
    Bitfield bf;
} Map;

// Function definitions
uint8_t validateArgs(char *argv[]);

// main function
int main(int argc, char *argv[]) {
    // argc should be 6 (Program name + 5 args)
    // If argc is not exacly 6, print "invalid" and exit program
    if (argc != 6 || !validateArgs(argv)) {
        puts("invalid");
        return 0;
    }

    // declare and init a new bit union map
    Map map = {0};

    // assign the integer value of the bits
    map.bf.engine_on = argv[1][0] - '0'; // subtract '0' to get the integer value
    map.bf.floor_pos = argv[2][0] - '0';
    map.bf.door_pos  = argv[3][0] - '0';
    map.bf.brake1    = argv[4][0] - '0';
    map.bf.brake2    = argv[5][0] - '0';

    // print the hex value of the bitfield to console
    printf("0x%02X\n", map.value);

    return 0;
}

// function to validate args are of correct width
uint8_t validateArgs(char *argv[]) {
    // check if the args are of correct width and size by bitshifting
    // and checking if any non-zero bits exist beyond the expected width
    if ((argv[1][0] - '0') >> 1) return 0; // return false
    if ((argv[2][0] - '0') >> 3) return 0;
    if ((argv[3][0] - '0') >> 2) return 0;
    if ((argv[4][0] - '0') >> 1) return 0;
    if ((argv[5][0] - '0') >> 1) return 0;

    return 1;
}
