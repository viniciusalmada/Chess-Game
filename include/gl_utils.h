//#pragma once
//#include <array>
//#include <string>
//#include <vector>
//#include <map>
//#include <filesystem>
//#include <coordinate.h>
//#include <iostream>
//
//class [[deprecated]] GlUtils
//{
//public:
//
//  struct Color
//  {
//    unsigned int hexColor = 0x0;
//    int alpha = 0xFF;
//
//    std::array<float, 4> getColorsF();
//  };
//
//  struct SquareBufferData
//  {
//    Coordinate topLeft;
//    Coordinate topRight;
//    Coordinate botRight;
//    Coordinate botLeft;
//    Color color;
//  };
//
//  struct VertexAttributes
//  {
//    float x;
//    float y;
//    float red;
//    float green;
//    float blue;
//
//    void loadFromSquare(SquareBufferData& data, int index, int sideSize);
//  };
//
//  static Color RED;
//  static Color WHITE;
//
//  static void uglClearColor(Color color);
//
//  static void uglColor3f(Color color);
//
//  static void uglColor4f(Color color);
//
//  static void uglViewportAndOrtho(int size);
//
//  static void drawSquare(int x, int y, int squareSize);
//
//  static void draw2DTexture(int texId, int x, int y, int sq, Color color = 
//    WHITE);
//
//  static void drawElements(int totalIndices);
//};