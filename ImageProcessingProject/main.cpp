#include "Pixel.h"
#include "Image.h"
#include "Blend.h"
#include <iostream>
using namespace std;

int main() {
    //Open Files:
    Image layer1("./input/layer1.tga");
    Image pattern1("./input/pattern1.tga");
    Image layer2("./input/layer2.tga");
    Image pattern2("./input/pattern2.tga");
    Image car("./input/car.tga");
    Image circles("./input/circles.tga");
    Image layer_red("./input/layer_red.tga");
    Image layer_green("./input/layer_green.tga");
    Image layer_blue("./input/layer_blue.tga");
    Image text("./input/text.tga");
    Image text2("./input/text2.tga");

    //Extra Credit:
    Blend::ExtraCredit(text, pattern1, car, circles).writeImage("./output/extracredit.tga");

    //Task 1:
    Blend::Multiply(layer1, pattern1).writeImage("./output/part1.tga");

    //Task 2:
    Blend::Subtract(layer2, car).writeImage("./output/part2.tga");

    //Task 3:
    Blend::Screen(text, Blend::Multiply(layer1, pattern2)).writeImage("./output/part3.tga");

    //Task 4:
    Blend::Subtract(pattern2, Blend::Multiply(layer2, circles)).writeImage("./output/part4.tga");

    //Task 5:
    Blend::Overlay(layer1, pattern1).writeImage("./output/part5.tga");

    //Task 6:
    Image task6(car);
    for (unsigned int i = 0; i < task6.getSize(); i++) {
        Blend::AdjustGreen(task6, 200, i, true);
    }
    task6.writeImage("./output/part6.tga");

    //Task 7:
    Image task7(car);
    Blend::ScaleRed(task7, 4);
    Blend::ScaleBlue(task7, 0);
    task7.writeImage("./output/part7.tga");

    //Task 8:
    Image task8_r(car);
    Image task8_g(car);
    Image task8_b(car);
    for (unsigned int i = 0; i < task8_r.getSize(); i++) {
        task8_r.getPixels()[i].setGreen(car.getPixels()[i].getRed());
        task8_r.getPixels()[i].setBlue(car.getPixels()[i].getRed());
        task8_g.getPixels()[i].setRed(car.getPixels()[i].getGreen());
        task8_g.getPixels()[i].setBlue(car.getPixels()[i].getGreen());
        task8_b.getPixels()[i].setRed(car.getPixels()[i].getBlue());
        task8_b.getPixels()[i].setGreen(car.getPixels()[i].getBlue());
    }
    task8_r.writeImage("./output/part8_r.tga");
    task8_g.writeImage("./output/part8_g.tga");
    task8_b.writeImage("./output/part8_b.tga");

    //Task 9:
    Image task9(layer_red);
    for (unsigned int i = 0; i < task9.getSize(); i++) {
        task9.getPixels()[i].setGreen(layer_green.getPixels()[i].getGreen());
        task9.getPixels()[i].setBlue(layer_blue.getPixels()[i].getBlue());
    }
    task9.writeImage("./output/part9.tga");

    //Task 10:
    Blend::Rotate(text2).writeImage("./output/part10.tga");

    //Load Examples:
    Image EXAMPLE_extracredit("./examples/EXAMPLE_extracredit.tga");
    Image EXAMPLE_part1("./examples/EXAMPLE_part1.tga");
    Image EXAMPLE_part2("./examples/EXAMPLE_part2.tga");
    Image EXAMPLE_part3("./examples/EXAMPLE_part3.tga");
    Image EXAMPLE_part4("./examples/EXAMPLE_part4.tga");
    Image EXAMPLE_part5("./examples/EXAMPLE_part5.tga");
    Image EXAMPLE_part6("./examples/EXAMPLE_part6.tga");
    Image EXAMPLE_part7("./examples/EXAMPLE_part7.tga");
    Image EXAMPLE_part8_r("./examples/EXAMPLE_part8_r.tga");
    Image EXAMPLE_part8_g("./examples/EXAMPLE_part8_g.tga");
    Image EXAMPLE_part8_b("./examples/EXAMPLE_part8_b.tga");
    Image EXAMPLE_part9("./examples/EXAMPLE_part9.tga");
    Image EXAMPLE_part10("./examples/EXAMPLE_part10.tga");

    //Load Output:
    Image OUTPUT_extracredit("./output/extracredit.tga");
    Image OUTPUT_part1("./output/part1.tga");
    Image OUTPUT_part2("./output/part2.tga");
    Image OUTPUT_part3("./output/part3.tga");
    Image OUTPUT_part4("./output/part4.tga");
    Image OUTPUT_part5("./output/part5.tga");
    Image OUTPUT_part6("./output/part6.tga");
    Image OUTPUT_part7("./output/part7.tga");
    Image OUTPUT_part8_r("./output/part8_r.tga");
    Image OUTPUT_part8_g("./output/part8_g.tga");
    Image OUTPUT_part8_b("./output/part8_b.tga");
    Image OUTPUT_part9("./output/part9.tga");
    Image OUTPUT_part10("./output/part10.tga");

    unsigned int score = 0;

    //Evaluate Test 1:
    if (Blend::Evaluate(EXAMPLE_extracredit, OUTPUT_extracredit, 1)) {
        score++;
    }

    //Evaluate Test 2:
    if (Blend::Evaluate(EXAMPLE_part1, OUTPUT_part1, 2)) {
        score++;
    }

    //Evaluate Test 3:
    if (Blend::Evaluate(EXAMPLE_part2, OUTPUT_part2, 3)) {
        score++;
    }

    //Evaluate Test 4:
    if (Blend::Evaluate(EXAMPLE_part3, OUTPUT_part3, 4)) {
        score++;
    }

    //Evaluate Test 5:
    if (Blend::Evaluate(EXAMPLE_part4, OUTPUT_part4, 5)) {
        score++;
    }

    //Evaluate Test 6:
    if (Blend::Evaluate(EXAMPLE_part5, OUTPUT_part5, 6)) {
        score++;
    }
    //Evaluate Test 7:
    if (Blend::Evaluate(EXAMPLE_part6, OUTPUT_part6, 7)) {
        score++;
    }

    //Evaluate Test 8:
    if (Blend::Evaluate(EXAMPLE_part7, OUTPUT_part7, 8)) {
        score++;
    }

    //Evaluate Test 9:
    if (Blend::Evaluate(EXAMPLE_part8_r, OUTPUT_part8_r, 9)) {
        score++;
    }

    //Evaluate Test 10:
    if (Blend::Evaluate(EXAMPLE_part8_g, OUTPUT_part8_g, 10)) {
        score++;
    }

    //Evaluate Test 11:
    if (Blend::Evaluate(EXAMPLE_part8_b, OUTPUT_part8_b, 11)) {
        score++;
    }

    //Evaluate Test 12:
    if (Blend::Evaluate(EXAMPLE_part9, OUTPUT_part9, 12)) {
        score++;
    }

    //Evaluate Test 13:
    if (Blend::Evaluate(EXAMPLE_part10, OUTPUT_part10, 13)) {
        score++;
    }

    cout << "Total Score: " << score << " / 13!" << endl;

    return 0;
}
