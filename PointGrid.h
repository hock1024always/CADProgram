#ifndef POINTGRID_H
#define POINTGRID_H

#include <wx/wx.h>
#include <wx/dcbuffer.h> // 添加这个头文件以使用 wxBufferedPaintDC

// 定义 PointGrid 类，用于绘制网格背景
class PointGrid {
public:
    PointGrid(wxPanel* panel, int spacing);
    void Draw(wxBufferedPaintDC& dc);

private:
    wxPanel* panel; // 指向绘图面板的指针
    int spacing;    // 网格的间距
};

#endif // POINTGRID_H
