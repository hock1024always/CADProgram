#include "PointGrid.h"

// 默认构造函数
PointGrid::PointGrid() : panel(nullptr), spacing(10) {}

// 构造函数，初始化网格背景的面板和间距
PointGrid::PointGrid(wxPanel* panel, int spacing) : panel(panel), spacing(spacing) {}

// 设置面板
void PointGrid::SetPanel(wxPanel* panel) {
    this->panel = panel;
}

// 设置间距
void PointGrid::SetSpacing(int spacing) {
    this->spacing = spacing;
}

// 绘制网格背景
void PointGrid::Draw(wxBufferedPaintDC& dc) {
    if (!panel) return; // 如果面板未设置，直接返回

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