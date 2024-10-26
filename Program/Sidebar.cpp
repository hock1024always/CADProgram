#include "Sidebar.h"

// 构造函数，初始化工具栏并绑定按钮事件
Sidebar::Sidebar(wxFrame* parent, DrawingPanel* drawingPanel, int width)
    : wxPanel(parent, wxID_ANY), drawingPanel(drawingPanel) {
    SetMinSize(wxSize(width, -1)); // 设置最小宽度

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxButton* rectButton = new wxButton(this, wxID_ANY, "与门"); // Rectangle
    wxButton* circleButton = new wxButton(this, wxID_ANY, "或门"); // Circle
    wxButton* triangleButton = new wxButton(this, wxID_ANY, "非门"); // Triangle
    wxButton* ellipseButton = new wxButton(this, wxID_ANY, "1信号输入"); // Ellipse
    wxButton* diamondButton = new wxButton(this, wxID_ANY, "0信号输入"); // Diamond

    // 创建静态文本，用于显示图形释放信息
    infoText = new wxStaticText(this, wxID_ANY, "元件属性表");
    infoText->SetMinSize(wxSize(-1, 50)); // 设置文本区域的最小高度

    sizer->Add(rectButton, 0, wxALL, 5);
    sizer->Add(circleButton, 0, wxALL, 5);
    sizer->Add(triangleButton, 0, wxALL, 5);
    sizer->Add(ellipseButton, 0, wxALL, 5);
    sizer->Add(diamondButton, 0, wxALL, 5);
    sizer->Add(infoText, 0, wxALL | wxEXPAND, 5); // 添加信息显示区域

    SetSizer(sizer);

    rectButton->Bind(wxEVT_BUTTON, &Sidebar::OnRectButton, this);
    circleButton->Bind(wxEVT_BUTTON, &Sidebar::OnCircleButton, this);
    triangleButton->Bind(wxEVT_BUTTON, &Sidebar::OnTriangleButton, this);
    ellipseButton->Bind(wxEVT_BUTTON, &Sidebar::OnEllipseButton, this);
    diamondButton->Bind(wxEVT_BUTTON, &Sidebar::OnDiamondButton, this);
}

void Sidebar::OnRectButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::AndGate, 50, 50);
    wxString info = "名称: 与门\n接入口数: 2\n输出口数: 1\n功能: 双真出真";
    infoText->SetLabel(info);
}

void Sidebar::OnCircleButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::OrGate, 150, 100);
    infoText->SetLabel("名称: 或门\n接入口数: 2\n输出口数: 1\n功能: 有真出真");
}

void Sidebar::OnTriangleButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::NotGate, 50, 100);
    infoText->SetLabel("名称: 非门\n接入口数: 2\n输出口数: 1\n功能: 双假出真");
}

void Sidebar::OnEllipseButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::OnPin, 150, 150);
    infoText->SetLabel("名称: 1输入设备\n接入口数: 0\n输出口数: 1\n功能: 输出1");
}

void Sidebar::OnDiamondButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::OffPin, 100, 150);
    infoText->SetLabel("名称: 0输入设备\n接入口数: 0\n输出口数: 1\n功能: 输出0");
}