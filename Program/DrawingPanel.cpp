#include "DrawingPanel.h"
#include <cmath>  // ���ڼ���ƽ������ƽ��
#include <algorithm> // ���� std::min �� std::max
#include<fstream>
#include"nlohmann/json.hpp"
#include "MainFrame.h"
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
        for (const auto& data : shape.data) {
            const std::string& color = data["color"];
            if (color == "yellow") {
                dc.SetPen(wxPen(wxColour(255, 255, 0))); // ��ɫ����
                dc.SetBrush(wxBrush(wxColour(255, 255, 0))); // ��ɫ��ˢ
            }
            if (color == "black") {
                dc.SetPen(*wxBLACK_PEN); // �ָ���ɫ����
                dc.SetBrush(*wxBLACK_BRUSH); // �ָ���ɫ��ˢ
            }
            if (color == "red") {
                dc.SetPen(*wxRED_PEN); // �ָ���ɫ����
                dc.SetBrush(*wxRED_BRUSH); // �ָ���ɫ��ˢ
            }
            if (color == "blue") {
                dc.SetPen(*wxBLUE_PEN); // �ָ���ɫ����
                dc.SetBrush(*wxBLUE_BRUSH); // �ָ���ɫ��ˢ
            }

            const std::string& type = data["type"];
            if (type == "Rectangle") {
                dc.DrawRectangle(data["x"] + shape.x, data["y"] + shape.y, data["width"], data["height"]);//�ŵ����
            }
            if (type == "Arc") {
                dc.DrawArc(data["x1"] + shape.x, data["y1"] + shape.y, data["x2"] + shape.x, data["y2"] + shape.y, data["xc"] + shape.x, data["yc"] + shape.y);//�ŵ��Ҳ�
            }
            if (type == "Circle") {
                dc.DrawCircle(data["x"] + shape.x, data["y"] + shape.y, data["radius"]);
            }
            if (type == "Polygon") {
                wxPoint points1[3] = {
                    wxPoint(shape.x + data["x1"], shape.y + data["y1"]),
                    wxPoint(shape.x + data["x2"], shape.y + data["y2"]),
                    wxPoint(shape.x + data["x3"], shape.y + data["y3"])
                };
                dc.DrawPolygon(3, points1);
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
            //���浱ǰ״̬�����˶�ջ
            undoStack.push_back({ shapes, lines });
            redoStack.clear();

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
    x = (x / 15) * 15;
    y = (y / 15) * 15;
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
        return x >= shape.x - 22 && x <= shape.x + 30 && y >= shape.y - 45 && y <= shape.y + 45;
    }

    case ShapeType::OrGate: {
        // Բ������Ϊ (shape.x , shape.y )���뾶Ϊ 20
        return x >= shape.x - 7 && x <= shape.x + 38 && y >= shape.y - 30 && y <= shape.y + 30;
    }

    case ShapeType::NotGate: {
        return x >= shape.x - 22 && x <= shape.x + 8 && y >= shape.y - 15 && y <= shape.y + 15;
    }

    case ShapeType::OnPin: {
        return x >= shape.x - 8 && x <= shape.x + 15 && y >= shape.y - 15 && y <= shape.y + 15;
    }

    case ShapeType::OffPin: {
        return x >= shape.x - 15 && x <= shape.x + 8 && y >= shape.y - 15 && y <= shape.y + 15;
    }

    default:
        return false;
    }
}

// �������ͼ��
void DrawingPanel::Clear() {
    undoStack.push_back({ shapes, lines });
    redoStack.clear();
    shapes.clear();
    lines.clear();
    Refresh();
}
//���˲���
void DrawingPanel::Undo() {
    if (!undoStack.empty()) {
        redoStack.push_back({ shapes, lines });
        auto state = undoStack.back();
        shapes = state.first;
        lines = state.second;
        undoStack.pop_back();
        Refresh();
    }
}

// ǰ������
void DrawingPanel::Redo() {
    if (!redoStack.empty()) {
        undoStack.push_back({ shapes, lines });
        auto state = redoStack.back();
        shapes = state.first;
        lines = state.second;
        redoStack.pop_back();
        Refresh();
    }
}

// ��ȡ����ͼ��
const std::vector<Shape>& DrawingPanel::GetShapes() const {
    return shapes;
}

json LoadFromJSON(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        json data;
        file >> data;
        file.close();
        return data;
    } else {
        wxMessageBox("Failed to open file", "Error", wxICON_ERROR);
    }
}

// ����µ�ͼ��
void DrawingPanel::AddShape(ShapeType type, int x, int y) {
    // ���浱ǰ״̬��������ջ
    undoStack.push_back({ shapes, lines });
    redoStack.clear();
    // ����ͼ����ӵ�ͼ���б���
    wxString file = ShapeTypeToString(type);
    std::string filename = "json/" + std::string(file.mb_str()) + ".json";
    json data = LoadFromJSON(filename);
    shapes.push_back({ data,type, x, y });
    // ˢ������Ը�����ʾ
    Refresh();
}

// �������������ַ���ת��Ϊ ShapeType
ShapeType ShapeTypeFromString(const wxString& str) {
    if (str == "AndGate") return ShapeType::AndGate;
    if (str == "OrGate") return ShapeType::OrGate;
    if (str == "NotGate") return ShapeType::NotGate;
    if (str == "OnPin") return ShapeType::OnPin;
    if (str == "OffPin") return ShapeType::OffPin;
    // �����������
    return ShapeType::Unknown;
}

// ������������ ShapeType ת��Ϊ�ַ���
wxString ShapeTypeToString(ShapeType type) {
    switch (type) {
    case ShapeType::AndGate: return "AndGate";
    case ShapeType::OrGate: return "OrGate";
    case ShapeType::NotGate: return "NotGate";
    case ShapeType::OnPin: return "OnPin";
    case ShapeType::OffPin: return "OffPin";
        // �����������
    default: return "Unknown";
    }
}
