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

    void OnNewFile(wxCommandEvent& event);         // 处理新建文件事件
    void OnOpenFile(wxCommandEvent& event);        // 处理打开文件事件
    void OnSaveFile(wxCommandEvent& event);        // 处理保存文件事件
    void OnSaveAsFile(wxCommandEvent& event);      // 处理另存为文件事件
    void OnCloseFile(wxCommandEvent& event);       // 处理关闭文件事件
    void OnPrintFile(wxCommandEvent& event);       // 处理打印文件事件
    void OnExit(wxCommandEvent& event);            // 处理退出程序事件

    wxStaticText* infoText; // 用于显示释放的图形信息
    DrawingPanel* drawingPanel; // 指向绘图面板的指针
};

#endif // SIDEBAR_H·