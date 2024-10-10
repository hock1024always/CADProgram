#include "PointGrid.h"

// ���캯������ʼ����״ͼ�����ͼ��
PointGrid::PointGrid(wxPanel* panel, int spacing) : panel(panel), spacing(spacing) {}

// ���Ƶ�״ͼ
void PointGrid::Draw(wxBufferedPaintDC& dc) {
    wxBrush brush(wxColour(200, 200, 200)); // �����ɫ
    dc.SetBrush(brush);

    // ���Ƶ�״����
    for (int x = 0; x < panel->GetSize().GetWidth(); x += spacing) {
        for (int y = 0; y < panel->GetSize().GetHeight(); y += spacing) {
            dc.DrawCircle(x, y, 2); // ����СԲ��
        }
    }
}

