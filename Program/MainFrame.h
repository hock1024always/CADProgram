#pragma once
#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include "DrawingPanel.h"
#include "Sidebar.h"

// 定义 MainFrame 类，继承自 wxFrame，用于创建主窗口
class MainFrame : public wxFrame {
public:
    MainFrame(); // 构造函数

private:
    DrawingPanel* drawingPanel; // 指向绘图面板的指针
    Sidebar* sidebar;           // 指向工具栏的指针
};

#endif // MAINFRAME_H
