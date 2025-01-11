#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include"nlohmann/json.hpp"
using json = nlohmann::json;
// ����ê��ṹ
struct AnchorPoint {
    int x;
    int y;

    AnchorPoint(int x, int y) : x(x), y(y) {}
};


// ���� ShapeType ö�����ͣ���ʾͼ������
enum class ShapeType {
    AndGate,
    OrGate,
    NotGate,
    OnPin,
    OffPin,
    Unknown // ��� Unknown ��Ա
};

// ���� Shape �ṹ�壬��ʾͼ�ε�λ�ú�����
struct Shape {
    json data;
    ShapeType type; // ͼ�ε�����
    int x, y;       // ͼ�ε�λ������
    std::vector<AnchorPoint> getanchorPoints() {
        std::vector<AnchorPoint>AnchorPoint;
        switch (type) {
        case ShapeType::AndGate:
            AnchorPoint.emplace_back(x - 30, y + 30);
            AnchorPoint.emplace_back(x - 30, y - 15);
            AnchorPoint.emplace_back(x + 45, y);
            AnchorPoint.emplace_back(x - 30, y + 15);
            AnchorPoint.emplace_back(x - 30, y - 30);
            AnchorPoint.emplace_back(x - 30, y);
            break;
        
        case ShapeType::OrGate:
            AnchorPoint.emplace_back(x - 15, y + 30);
            AnchorPoint.emplace_back(x - 15, y - 30);
            AnchorPoint.emplace_back(x - 15, y + 15);
            AnchorPoint.emplace_back(x - 15, y - 15);
            AnchorPoint.emplace_back(x - 15, y);
            AnchorPoint.emplace_back(x + 45, y);
            break;
        
        case ShapeType::NotGate:
            AnchorPoint.emplace_back(x - 30, y);
            AnchorPoint.emplace_back(x + 15, y);
            break;
        
        case ShapeType::OnPin:
            AnchorPoint.emplace_back(x - 15, y);
            break;
        
        case ShapeType::OffPin:
            AnchorPoint.emplace_back(x + 15, y);
            break;

        }
        return AnchorPoint;
    }
};

// ���� Line �ṹ�壬��ʾ�����������յ�
struct Line {
    int startX, startY, endX, endY; // �����������յ�����
};

#endif // SHAPE_H