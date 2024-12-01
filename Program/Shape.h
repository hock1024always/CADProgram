#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include"nlohmann/json.hpp"
using json = nlohmann::json;
// 定义锚点结构
struct AnchorPoint {
    int x;
    int y;

    AnchorPoint(int x, int y) : x(x), y(y) {}
};


// 定义 ShapeType 枚举类型，表示图形类型
enum class ShapeType {
    AndGate,
    OrGate,
    NotGate,
    OnPin,
    OffPin,
    Unknown // 添加 Unknown 成员
};

// 定义 Shape 结构体，表示图形的位置和类型
struct Shape {
    json data;
    ShapeType type; // 图形的类型
    int x, y;       // 图形的位置坐标
    std::vector<AnchorPoint> getanchorPoints() {
        std::vector<AnchorPoint>AnchorPoint;
        switch (type) {
        case ShapeType::AndGate:
            AnchorPoint.emplace_back(x - 20, y + 10);
            AnchorPoint.emplace_back(x - 20, y - 10);
            AnchorPoint.emplace_back(x + 30, y);
            AnchorPoint.emplace_back(x - 20, y + 20);
            AnchorPoint.emplace_back(x - 20, y - 20);
            AnchorPoint.emplace_back(x - 20, y);
            break;
        
        case ShapeType::OrGate:
            AnchorPoint.emplace_back(x - 10, y + 20);
            AnchorPoint.emplace_back(x - 10, y - 20);
            AnchorPoint.emplace_back(x - 10, y + 10);
            AnchorPoint.emplace_back(x - 10, y - 10);
            AnchorPoint.emplace_back(x - 10, y);
            AnchorPoint.emplace_back(x + 30, y);
            break;
        
        case ShapeType::NotGate:
            AnchorPoint.emplace_back(x - 20, y);
            AnchorPoint.emplace_back(x + 10, y);
            break;
        
        case ShapeType::OnPin:
            AnchorPoint.emplace_back(x - 10, y);
            break;
        
        case ShapeType::OffPin:
            AnchorPoint.emplace_back(x + 10, y);
            break;

        }
        return AnchorPoint;
    }
};

// 定义 Line 结构体，表示线条的起点和终点
struct Line {
    int startX, startY, endX, endY; // 线条的起点和终点坐标
};

#endif // SHAPE_H