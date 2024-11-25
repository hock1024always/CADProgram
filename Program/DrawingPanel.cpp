#include "DrawingPanel.h"
#include <cmath>  // ���ڼ���ƽ������ƽ��
#include <algorithm> // ���� std::min �� std::max
#include<fstream>
#include"nlohmann/json.hpp"
using json = nlohmann::json;
// ���캯������ʼ����ͼ��岢������״ͼ
DrawingPanel::DrawingPanel(wxFrame* parent)
    : wxPanel(parent, wxID_ANY), pointGrid(this, 10) { // ���õ�ļ��Ϊ10����
    Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &DrawingPanel::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &DrawingPanel::OnLeftUp, this);
    Bind(wxEVT_MOTION, &DrawingPanel::OnMotion, this);
}

void DrawingPanel::OnPaint(wxPaintEvent& event) {
    wxBufferedPaintDC dc(this);
    dc.Clear();

    pointGrid.Draw(dc); // ���Ƶ�״ͼ

    for (const auto& shape : shapes) {
        
        switch (shape.type) {
        case ShapeType::AndGate: {
            dc.SetPen(wxPen(wxColour(255, 255, 0))); // ��ɫ����
            dc.SetBrush(wxBrush(wxColour(255, 255, 0))); // ��ɫ��ˢ
            dc.DrawRectangle(shape.x - 20, shape.y - 30, 20, 60);//�ŵ����
            dc.DrawArc(shape.x, shape.y + 30, shape.x, shape.y - 30, shape.x, shape.y);//�ŵ��Ҳ�
            dc.FloodFill(shape.x, shape.y, *wxYELLOW, wxFLOOD_SURFACE);//��ˮ��� 
            // ��Ӻ�ɫʵ��СԲ
            dc.SetPen(*wxBLACK_PEN); // �ָ���ɫ����
            dc.SetBrush(*wxBLACK_BRUSH); // �ָ���ɫ��ˢ
            dc.DrawCircle(shape.x - 20, shape.y + 10, 2);
            dc.DrawCircle(shape.x - 20, shape.y - 10, 2);
            dc.DrawCircle(shape.x + 30, shape.y, 2);
            dc.DrawCircle(shape.x - 20, shape.y + 20, 2);
            dc.DrawCircle(shape.x - 20, shape.y - 20, 2);
            dc.DrawCircle(shape.x - 20, shape.y, 2);
            break;
        }

        case ShapeType::OrGate: {
            // �ϲ�
            dc.SetPen(wxPen(wxColour(255, 255, 0))); // ��ɫ����
            dc.SetBrush(wxBrush(wxColour(255, 255, 0))); // ��ɫ��ˢ
            wxPoint points1[3] = {
                wxPoint(shape.x - 20, shape.y + 25),
                wxPoint(shape.x - 5, shape.y),
                wxPoint(shape.x + 30, shape.y)
            };

            dc.DrawPolygon(3, points1);
            //�²�
            wxPoint points2[3] = {
                wxPoint(shape.x - 20, shape.y - 25),
                wxPoint(shape.x - 5, shape.y),
                wxPoint(shape.x + 30, shape.y)
            };
            dc.DrawPolygon(3, points2);
            // ��Ӻ�ɫʵ��СԲ
            dc.SetPen(*wxBLACK_PEN); // �ָ���ɫ����
            dc.SetBrush(*wxBLACK_BRUSH); // �ָ���ɫ��ˢ
            dc.DrawCircle(shape.x - 10, shape.y + 20, 2);
            dc.DrawCircle(shape.x - 10, shape.y - 20, 2);
            dc.DrawCircle(shape.x - 10, shape.y + 10, 2);
            dc.DrawCircle(shape.x - 10, shape.y - 10, 2);
            dc.DrawCircle(shape.x - 10, shape.y, 2);
            dc.DrawCircle(shape.x + 30, shape.y, 2);
            break;
        }

        case ShapeType::NotGate: {
            dc.SetPen(wxPen(wxColour(255, 255, 0))); // ��ɫ����
            dc.SetBrush(wxBrush(wxColour(255, 255, 0))); // ��ɫ��ˢ
            // ����ֱ�������εĶ���Ϊ shape.x, shape.y��б����ֱ��б�߳� 40
            wxPoint points3[3] = {
                wxPoint(shape.x, shape.y),
                wxPoint(shape.x - 20, shape.y + 10),
                wxPoint(shape.x - 20, shape.y - 10)
            };
            dc.DrawPolygon(3, points3);
            dc.DrawCircle(shape.x + 5, shape.y, 5);
            // ��Ӻ�ɫʵ��СԲ
            dc.SetPen(*wxBLACK_PEN); // �ָ���ɫ����
            dc.SetBrush(*wxBLACK_BRUSH); // �ָ���ɫ��ˢ
            dc.DrawCircle(shape.x - 20, shape.y, 2);
            dc.DrawCircle(shape.x + 10, shape.y, 2);
            break;
        }

        case ShapeType::OnPin: {
            dc.SetPen(wxPen(wxColour(255, 255, 0))); // ��ɫ����
            dc.SetBrush(wxBrush(wxColour(255, 255, 0))); // ��ɫ��ˢ
            dc.SetPen(*wxBLUE_PEN); // �ָ���ɫ����
            dc.SetBrush(*wxBLUE_BRUSH); // �ָ���ɫ��ˢ
            // Բ�����ĵ�Ϊ shape.x, shape.y���뾶Ϊ 10
            dc.DrawCircle(shape.x, shape.y, 10);
            // ��Ӻ�ɫʵ��СԲ
            dc.SetPen(*wxBLACK_PEN); // �ָ���ɫ����
            dc.SetBrush(*wxBLACK_BRUSH); // �ָ���ɫ��ˢ
            dc.DrawCircle(shape.x - 10, shape.y, 2);
            break;
        }

        case ShapeType::OffPin: {
            dc.SetPen(wxPen(wxColour(255, 255, 0))); // ��ɫ����
            dc.SetBrush(wxBrush(wxColour(255, 255, 0))); // ��ɫ��ˢ
            dc.SetPen(*wxRED_PEN); // �ָ���ɫ����
            dc.SetBrush(*wxRED_BRUSH); // �ָ���ɫ��ˢ
            // �����ε����ĵ�Ϊ shape.x, shape.y���߳�Ϊ 20
            dc.DrawRectangle(shape.x - 10, shape.y - 10, 20, 20);
            // ��Ӻ�ɫʵ��СԲ
            dc.SetPen(*wxBLACK_PEN); // �ָ���ɫ����
            dc.SetBrush(*wxBLACK_BRUSH); // �ָ���ɫ��ˢ
            dc.DrawCircle(shape.x + 10, shape.y, 2);
            break;
        }
        }

        // �ָ�Ĭ�ϵĻ��ʺ�ˢ�ӣ������Ҫ�Ļ�
        dc.SetPen(*wxBLACK_PEN);
        dc.SetBrush(*wxWHITE_BRUSH);
    }

    for (const auto& line : lines) {
        dc.DrawLine(line.startX, line.startY, line.endX, line.endY);
    }
}

// ����Ƿ���ê����ж����ڣ�Բ������
bool DrawingPanel::IsPointOnAnchor(int x, int y) {
    for (size_t i = 0; i < shapes.size(); ++i) {
        anchorPoints = shapes[i].getanchorPoints();
        for (const auto& anchor : anchorPoints) {
            // ����������ê��ľ���
            double distance = std::sqrt(std::pow(x - anchor.x, 2) + std::pow(y - anchor.y, 2));

            // �������С�ڵ���ê����ж���뾶������Ϊ��ê����
            if (distance <= anchorRadius) {
                return true;
            }
        }
    }
    return false;
}

// ���������������¼�
void DrawingPanel::OnLeftDown(wxMouseEvent& event) {
    // ��ȡ��굱ǰ������
    int mouseX = event.GetX();
    int mouseY = event.GetY();

    // �����������뵽��״����ÿ10������һ���㣩
    SnapToPoint(mouseX, mouseY);

    // ����Ƿ�����ĳ��ê����ж�����
    if (IsPointOnAnchor(mouseX, mouseY)) {
        // ��������ê���ϣ���¼ê������Ϊ���
        currentLine.startX = mouseX;
        currentLine.startY = mouseY;
        return; // �˳�����
    }

    // ��������ͼ�Σ��������Ƿ���ĳ��ͼ���ڲ�
    for (size_t i = 0; i < shapes.size(); ++i) {
        // �������Ƿ��ڵ�i��ͼ����
        if (IsPointInShape(mouseX, mouseY, shapes[i])) {
            // ��������ͼ���ڣ���ʼ�϶���ͼ��
            StartDrag(i, mouseX, mouseY);
            return; // �˳���������Ϊ�Ѿ���ʼ�϶�
        }
    }
    currentLine.startX = 0;
    currentLine.startY = 0;
    return;//������������� ���Ϊ0

}//��Ϊ������� ��ê���Ϻ���ͼ����

// �����������ͷ��¼�
void DrawingPanel::OnLeftUp(wxMouseEvent& event) {
    // �����ǰ�����϶�ͼ�Σ������϶�
    if (dragging) {
        dragging = false; // �����϶�״̬
    }
    else {
        if (currentLine.startX != 0 || currentLine.startY != 0) {//˵����ʼ����ê���ϣ������ߵĻ���
            int endX = event.GetX(); // ��¼�ߵ��յ�
            int endY = event.GetY();

            // ���յ�������뵽��״����
            SnapToPoint(endX, endY);


            // �����������ƽ��������ߵ��߶�
            std::vector<Line> segments = CalculateSegments(currentLine.startX, currentLine.startY, endX, endY);
            // ����������߶���ӵ��߶��б���
            lines.insert(lines.end(), segments.begin(), segments.end());
        }
    }
    // ˢ������Ը�����ʾ
    Refresh();
}

// ��������ƶ��¼�
void DrawingPanel::OnMotion(wxMouseEvent& event) {
    // �����ǰ�����϶�״̬
    if (dragging) {
        // ���±��϶�ͼ�ε�����
        shapes[dragIndex].x = event.GetX() - dragOffsetX;
        shapes[dragIndex].y = event.GetY() - dragOffsetY;
        // ��ͼ��������뵽��״����
        SnapToPoint(shapes[dragIndex].x, shapes[dragIndex].y);
        // ˢ������Ը�����ʾ
        Refresh();
    }
    else if (event.Dragging()) { // ���û���϶�ͼ�Σ���������϶��У������߹��̣�
        // ���µ�ǰ���ڻ��Ƶ��ߵ��յ�����
        currentLine.endX = event.GetX();
        currentLine.endY = event.GetY();
        // ���յ�������뵽��״����
        SnapToPoint(currentLine.endX, currentLine.endY);
        // ˢ������Ը�����ʾ
        Refresh();
    }
}

// ��������뵽��״����
void DrawingPanel::SnapToPoint(int& x, int& y) {
    // �� x �� y ������뵽���������㣨ÿ10������һ���㣩
    x = (x / 10) * 10;
    y = (y / 10) * 10;
}

// �����������ƽ��������ߵ��߶�
std::vector<Line> DrawingPanel::CalculateSegments(int startX, int startY, int endX, int endY) {
    std::vector<Line> segments;

    // ����ˮƽ�ʹ�ֱ����
    int dx = endX - startX;
    int dy = endY - startY;

    // ����Ѿ���һ��ˮƽ��ֱ�ߣ�ֱ�ӷ���
    if (dx == 0 || dy == 0) {
        segments.push_back({ startX, startY, endX, endY });
        return segments;
    }

    // �����е�
    int midX = startX + dx / 2;

    // ���뵽����
    SnapToPoint(midX, startY);
    SnapToPoint(midX, endY);

    // ��������߶�
    segments.push_back({ startX, startY, midX, startY }); // �߶�1��(a, b) -> (midx, b)
    segments.push_back({ midX, startY, midX, endY });   // �߶�2��(midx, b) -> (midx, d)
    segments.push_back({ midX, endY, endX, endY });     // �߶�3��(midx, d) -> (c, d)

    return segments;
}

// ��ʼ�϶�ĳ��ͼ��
void DrawingPanel::StartDrag(int index, int x, int y) {
    // ��¼��ǰ�϶���ͼ������
    dragIndex = index;
    // ������������ͼ�����Ͻǵ�ƫ����
    dragOffsetX = x - shapes[index].x;
    dragOffsetY = y - shapes[index].y;
    // �����϶�״̬
    dragging = true;
}

// �����Ƿ���ͼ����
bool DrawingPanel::IsPointInShape(int x, int y, const Shape& shape) {
    switch (shape.type) {
    case ShapeType::AndGate: {
        // �����ε����Ͻ�Ϊ (shape.x, shape.y)�����Ϊ 40
        return x >= shape.x - 14 && x <= shape.x + 20 && y >= shape.y - 30 && y <= shape.y + 30;
    }

    case ShapeType::OrGate: {
        // Բ������Ϊ (shape.x , shape.y )���뾶Ϊ 20
        return x >= shape.x - 5 && x <= shape.x + 25 && y >= shape.y - 20 && y <= shape.y + 20;
    }

    case ShapeType::NotGate: {
        return x >= shape.x - 15 && x <= shape.x + 5 && y >= shape.y - 10 && y <= shape.y + 10;
    }

    case ShapeType::OnPin: {
        return x >= shape.x - 5 && x <= shape.x + 10 && y >= shape.y - 10 && y <= shape.y + 10;
    }

    case ShapeType::OffPin: {
        return x >= shape.x - 10 && x <= shape.x + 5 && y >= shape.y - 10 && y <= shape.y + 10;
    }

    default:
        return false;
    }
}

// �������ͼ��
void DrawingPanel::Clear() {
    shapes.clear();
    lines.clear();
    Refresh();
}

// ��ȡ����ͼ��
const std::vector<Shape>& DrawingPanel::GetShapes() const {
    return shapes;
}

/*
void DrawingPanel::LoadFromJSON(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
            json data;
            file >> data;
            file.close();
            for (const auto& shape : data) {
                const std::string& type = shape["type"];
                if (type == "Rectangle") {
                    //dc.SetPen(wxPen(wxColour(255, 255, 0))); // ��ɫ����
                    //dc.SetBrush(wxBrush(wxColour(255, 255, 0))); // ��ɫ��ˢ
                    //dc.DrawRectangle(shape["x"], shape["y"],shape["width"],shape["height"]);//�ŵ����
                }
                if (type == "Arc") {
                    //dc.SetPen(wxPen(wxColour(255, 255, 0))); // ��ɫ����
                    //dc.SetBrush(wxBrush(wxColour(255, 255, 0))); // ��ɫ��ˢ
                    //dc.DrawArc(shape["x1"], shape["y1"],shape["x2"],shape["y2"],shape["xc"], shape["yc"]);//�ŵ��Ҳ�
                }
                if (type == "Circle"){
                    //dc.SetPen(*wxBLACK_PEN); // �ָ���ɫ����
                    //dc.SetBrush(*wxBLACK_BRUSH); // �ָ���ɫ��ˢ
                    // ��Ӻ�ɫʵ��СԲ
                    //dc.DrawCircle(shape["x"], shape["y"], shape["radius"]);
                }
            }
        }else {
            wxMessageBox("Failed to open file", "Error", wxICON_ERROR);
        }
    }
*/

