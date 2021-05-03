#include <iostream>
#include "p1.cpp"
#include "p2.cpp"
#include "p3.cpp"

int main() {
    printf( "******************** BASE DE DATOS 2 - LAB 1 ***************************\n");
    P1_FixedRecord::test("../datos1");
    P2_FixedRecord::test("../datos2");
    return 0;
}
