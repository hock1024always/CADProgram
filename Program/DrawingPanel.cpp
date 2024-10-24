#include "DrawingPanel.h"
#include <cmath>  // ���ڼ���ƽ������ƽ��
#include <algorithm> // ���� std::min �� std::max

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
    // ���û�ɫ�Ļ��ʺͻ�ˢ
    dc.SetPen(wxPen(wxColour(255, 255, 0))); // ��ɫ����
    dc.SetBrush(wxBrush(wxColour(255, 255, 0))); // ��ɫ��ˢ

    switch (shape.type) {
    case ShapeType::AndGate:
        // �����ε����ĵ�Ϊ shape.x, shape.y���߳�Ϊ 40
        dc.DrawRectangle(shape.x - 20, shape.y - 20, 40, 40);
        // ��Ӻ�ɫʵ��СԲ
        dc.SetPen(*wxBLACK_PEN); // �ָ���ɫ����
        dc.SetBrush(*wxBLACK_BRUSH); // �ָ���ɫ��ˢ
        dc.DrawCircle(shape.x - 20, shape.y + 10, 3);
        dc.DrawCircle(shape.x - 20, shape.y - 10, 3);
        dc.DrawCircle(shape.x + 20, shape.y, 3);
        break;
    case ShapeType::OrGate:
        // Բ�����ĵ�Ϊ shape.x, shape.y���뾶Ϊ 20
        dc.DrawCircle(shape.x, shape.y, 20);
        // ��Ӻ�ɫʵ��СԲ
        dc.SetPen(*wxBLACK_PEN); // �ָ���ɫ����
        dc.SetBrush(*wxBLACK_BRUSH); // �ָ���ɫ��ˢ
        dc.DrawCircle(shape.x - 20, shape.y + 10, 3);
        dc.DrawCircle(shape.x - 20, shape.y - 10, 3);
        dc.DrawCircle(shape.x + 20, shape.y, 3);
        break;
    case ShapeType::NotGate: {
        // ����ֱ�������εĶ���Ϊ shape.x, shape.y��б����ֱ��б�߳� 40
        wxPoint points[3] = {
            wxPoint(shape.x, shape.y),
            wxPoint(shape.x - 20, shape.y + 20),
            wxPoint(shape.x - 20, shape.y - 20)
        };
        dc.DrawPolygon(3, points);
        // ��Ӻ�ɫʵ��СԲ
        dc.SetPen(*wxBLACK_PEN); // �ָ���ɫ����
        dc.SetBrush(*wxBLACK_BRUSH); // �ָ���ɫ��ˢ
        dc.DrawCircle(shape.x - 20, shape.y + 10, 3);
        dc.DrawCircle(shape.x - 20, shape.y - 10, 3);
        dc.DrawCircle(shape.x, shape.y, 3);
        break;
    }
    case ShapeType::OnPin:
        // Բ�����ĵ�Ϊ shape.x, shape.y���뾶Ϊ 10
        dc.DrawCircle(shape.x, shape.y, 10);
        // ��Ӻ�ɫʵ��СԲ
        dc.SetPen(*wxBLACK_PEN); // �ָ���ɫ����
        dc.SetBrush(*wxBLACK_BRUSH); // �ָ���ɫ��ˢ
        dc.DrawCircle(shape.x + 10, shape.y, 3);
        break;
    case ShapeType::OffPin: {
        // �����ε����ĵ�Ϊ shape.x, shape.y���߳�Ϊ 20
        dc.DrawRectangle(shape.x - 10, shape.y - 10, 20, 20);
        // ��Ӻ�ɫʵ��СԲ
        dc.SetPen(*wxBLACK_PEN); // �ָ���ɫ����
        dc.SetBrush(*wxBLACK_BRUSH); // �ָ���ɫ��ˢ
        dc.DrawCircle(shape.x + 10, shape.y, 3);
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
    for (const auto& anchor : anchorPoints) {
        // ����������ê��ľ���
        double distance = std::sqrt(std::pow(x - anchor.x, 2) + std::pow(y - anchor.y, 2));

        // �������С�ڵ���ê����ж���뾶������Ϊ��ê����
        if (distance <= anchorRadius) {
            return true;
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
        return; // �˳���������Ϊ�Ѿ���ʼ������
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

    // ���û�е�����κ�ͼ�λ�ê�㣬��ʼ�����µ���
    currentLine.startX = mouseX; // ��¼�ߵ����
    currentLine.startY = mouseY;
}


// �����������ͷ��¼�
void DrawingPanel::OnLeftUp(wxMouseEvent& event) {
    // �����ǰ�����϶�ͼ�Σ������϶�
    if (dragging) {
        dragging = false; // �����϶�״̬
    }
    else {
        // ���û���϶�ͼ�Σ������ߵĻ���
        int endX = event.GetX(); // ��¼�ߵ��յ�
        int endY = event.GetY();

        // ���յ�������뵽��״����
        SnapToPoint(endX, endY);

        // ����Ƿ��ͷ�λ����ĳ��ê����
        if (IsPointOnAnchor(endX, endY)) {
            // ����ͷ�λ����ê���ϣ����յ�����Ϊ���ê�������
            endX = currentLine.startX;
            endY = currentLine.startY;
        }

        // �����������ƽ��������ߵ��߶�
        std::vector<Line> segments = CalculateSegments(currentLine.startX, currentLine.startY, endX, endY);
        // ����������߶���ӵ��߶��б���
        lines.insert(lines.end(), segments.begin(), segments.end());
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

// ����µ�ͼ��
void DrawingPanel::AddShape(ShapeType type, int x, int y) {
    // ����ͼ�ε�������뵽��״����
    SnapToPoint(x, y);
    // ����ͼ����ӵ�ͼ���б���
    shapes.push_back({ type, x, y });
    // ˢ������Ը�����ʾ
    Refresh();
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


bool DrawingPanel::IsPointInShape(int x, int y, const Shape& shape) {
    switch (shape.type) {
    case ShapeType::AndGate:
        // �����ε����Ͻ�Ϊ (shape.x, shape.y)�����Ϊ 40
        return x >= shape.x - 20 && x <= shape.x + 20 && y >= shape.y -20 && y <= shape.y + 20;
    case ShapeType::OrGate:
        // Բ������Ϊ (shape.x , shape.y )���뾶Ϊ 20
        return (x - shape.x ) * (x - shape.x ) + (y - shape.y ) * (y - shape.y) <= 20 * 20;
    case ShapeType::NotGate: {
        // �����ε���������
        wxPoint p(x, y);
        wxPoint a(shape.x, shape.y - 20); // �϶���
        wxPoint b(shape.x - 20, shape.y + 20); // ���¶���
        wxPoint c(shape.x + 20, shape.y + 20); // ���¶���

        // �жϵ��Ƿ�����������
        bool inside = false;
        int A = (b.y - a.y) * (c.x - b.x) + (b.x - a.x) * (c.y - b.y);
        int B1 = (b.y - p.y) * (c.x - b.x) + (b.x - p.x) * (c.y - b.y);
        int B2 = (c.y - b.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y);
        int C1 = (p.y - a.y) * (b.x - a.x) + (a.x - p.x) * (b.y - a.y);
        int C2 = (c.y - a.y) * (p.x - c.x) + (a.x - c.x) * (p.y - c.y);

        if (A >= 0) {
            if (B1 >= 0 && B2 >= 0 && C1 >= 0 && C2 >= 0) inside = true;
        }
        else {
            if (B1 <= 0 && B2 <= 0 && C1 <= 0 && C2 <= 0) inside = true;
        }
        return inside;
    }
    case ShapeType::OnPin:
        // ��Բ���볤��Ϊ 5�������Ϊ 3.5
        return (x - shape.x) * (x - shape.x) + (y - shape.y) * (y - shape.y) <= 10 * 10;
    case ShapeType::OffPin: {
        return x >= shape.x - 10 && x <= shape.x + 10 && y >= shape.y - 10 && y <= shape.y + 10;
    }
    default:
        return false;
    }
}

