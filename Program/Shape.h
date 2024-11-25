#pragma once
#ifndef SHAPE_H
#define SHAPE_H

// ����ê��ṹ
struct AnchorPoint {
    int x;
    int y;

    AnchorPoint(int x, int y) : x(x), y(y) {}
};

/*
struct rectangle {
    int x;
    int y;
    int width;
    int height;
};

struct arc {
    int x1;
    int y1;
    int x2;
    int y2;
    int xc;
    int yc;
};

struct circle{
    int x;
    int y;
    int radius;
};

struct polygon {
    int x1;
    int y1;
    int x2;
    int y2;
    int x3;
    int y3;
};
*/


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
    ShapeType type; // ͼ�ε�����
    int x, y;       // ͼ�ε�λ������
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

// ���� Line �ṹ�壬��ʾ�����������յ�
struct Line {
    int startX, startY, endX, endY; // �����������յ�����
};

#endif // SHAPE_H