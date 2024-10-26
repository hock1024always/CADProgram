#pragma once
#ifndef SHAPE_H
#define SHAPE_H

// 定义 ShapeType 枚举类型，表示图形类型
enum class ShapeType {
    AndGate, 
    OrGate, 
    NotGate, 
    OnPin, 
    OffPin 
};

// 定义 Shape 结构体，表示图形的位置和类型
struct Shape {
    ShapeType type; // 图形的类型
    int x, y;       // 图形的位置坐标
};

// 定义 Line 结构体，表示线条的起点和终点
struct Line {
    int startX, startY, endX, endY; // 线条的起点和终点坐标
};

#endif // SHAPE_H