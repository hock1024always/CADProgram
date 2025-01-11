#include "MainFrame.h"

// 构造函数，初始化主窗口并设置布局
MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "wxWidgets Drawing App") {
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL); // 创建水平布局的 sizer

    drawingPanel = new DrawingPanel(this); // 创建绘图面板
    sidebar = new Sidebar(this, drawingPanel, 200); // 假设原来的宽度是 100，现在设置为 200

    sizer->Add(sidebar, 0, wxEXPAND | wxALL, 5);  // 将工具栏添加到 sizer
    sizer->Add(drawingPanel, 1, wxEXPAND | wxALL, 5); // 将绘图面板添加到 sizer

    SetSizerAndFit(sizer); // 设置 sizer 并调整窗口大小
    SetSize(800, 600);     // 设置窗口大小
}