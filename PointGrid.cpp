#include "PointGrid.h"

// 构造函数，初始化网格背景的面板和间距
PointGrid::PointGrid(wxPanel* panel, int spacing) : panel(panel), spacing(spacing) {}

// 绘制网格背景
void PointGrid::Draw(wxBufferedPaintDC& dc) {
    // 设置网格的背景颜色
    wxBrush brush(wxColour(220, 226, 241)); // 背景颜色
    dc.SetBrush(brush);
    dc.DrawRectangle(0, 0, panel->GetSize().GetWidth(), panel->GetSize().GetHeight()); // 绘制背景

    // 设置线条颜色和宽度
    wxPen pen(wxColour(255, 242, 226), 1); // 线条颜色和宽度
    dc.SetPen(pen);

    // 绘制网格线
    for (int x = 0; x < panel->GetSize().GetWidth(); x += spacing) {
        dc.DrawLine(x, 0, x, panel->GetSize().GetHeight()); // 垂直线
    }
    for (int y = 0; y < panel->GetSize().GetHeight(); y += spacing) {
        dc.DrawLine(0, y, panel->GetSize().GetWidth(), y); // 水平线
    }
}