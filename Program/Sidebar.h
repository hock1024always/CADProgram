#pragma once
#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <wx/wx.h>
#include "DrawingPanel.h"

// 定义 Sidebar 类，继承自 wxPanel，用于显示工具栏
class Sidebar : public wxPanel {
public:
    Sidebar(wxFrame* parent, DrawingPanel* drawingPanel, int width); // 构造函数

private:
    void OnRectButton(wxCommandEvent& event);      // 处理矩形按钮点击事件
    void OnCircleButton(wxCommandEvent& event);    // 处理圆形按钮点击事件
    void OnTriangleButton(wxCommandEvent& event);  // 处理三角形按钮点击事件
    void OnEllipseButton(wxCommandEvent& event);    // 处理椭圆按钮点击事件
    void OnDiamondButton(wxCommandEvent& event);    // 处理菱形按钮点击事件

    wxStaticText* infoText; // 用于显示释放的图形信息
    DrawingPanel* drawingPanel; // 指向绘图面板的指针
};

#endif // SIDEBAR_H
