#include "Sidebar.h"
#include "DrawingPanel.h"
#include <wx/filedlg.h>
#include <wx/print.h>
#include <wx/printdlg.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h> // 包含 wxStringTokenizer 头文件
#include <wx/log.h>



//// 构造函数，初始化工具栏并绑定按钮事件
//Sidebar::Sidebar(wxFrame* parent, DrawingPanel* drawingPanel, int width)
//    : wxPanel(parent, wxID_ANY), drawingPanel(drawingPanel) {
//    SetMinSize(wxSize(width, -1)); // 设置最小宽度
//
//    // 创建菜单栏
//    wxMenuBar* menuBar = new wxMenuBar();
//
//    // 创建 wxGrid 控件
//    grid = new wxGrid(this, wxID_ANY);
//    grid->CreateGrid(3, 1); // 创建一个 3 行 1 列的表格
//    grid->SetColLabelValue(0, "属性");
//    grid->SetRowLabelValue(0, "名称");
//    grid->SetRowLabelValue(1, "接入口数");
//    grid->SetRowLabelValue(2, "输出口数");
//    grid->SetRowLabelValue(3, "功能");
//
//    // 设置布局
//    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
//    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);
//    SetSizer(sizer);
//
//    // 创建文件菜单
//    wxMenu* fileMenu = new wxMenu();
//    fileMenu->Append(wxID_NEW, "&新建文件\tCtrl+N");
//    fileMenu->Append(wxID_OPEN, "&打开文件\tCtrl+O");
//    fileMenu->Append(wxID_SAVE, "&保存文件\tCtrl+S");
//    fileMenu->Append(wxID_SAVEAS, "&另存为文件\tCtrl+Shift+S");
//    fileMenu->Append(wxID_CLOSE, "&关闭文件\tCtrl+W");
//    fileMenu->Append(wxID_PRINT, "&打印文件\tCtrl+P");
//    fileMenu->AppendSeparator();
//    fileMenu->Append(wxID_EXIT, "&退出程序\tCtrl+Q");
//
//    // 将文件菜单添加到菜单栏
//    menuBar->Append(fileMenu, "&文件");
//
//    // 创建帮助菜单
//    wxMenu* helpMenu = new wxMenu();
//    helpMenu->Append(wxID_ABOUT, "&关于\tF1");
//
//    // 将帮助菜单添加到菜单栏
//    menuBar->Append(helpMenu, "&帮助");
//
//    // 将菜单栏设置到父窗口
//    parent->SetMenuBar(menuBar);
//
//    //wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
//
//    wxButton* rectButton = new wxButton(this, wxID_ANY, "与门"); // Rectangle
//    wxButton* circleButton = new wxButton(this, wxID_ANY, "或门"); // Circle
//    wxButton* triangleButton = new wxButton(this, wxID_ANY, "非门"); // Triangle
//    wxButton* ellipseButton = new wxButton(this, wxID_ANY, "1信号输入"); // Ellipse
//    wxButton* diamondButton = new wxButton(this, wxID_ANY, "0信号输入"); // Diamond
//
//
//    sizer->Add(rectButton, 0, wxALL, 5);
//    sizer->Add(circleButton, 0, wxALL, 5);
//    sizer->Add(triangleButton, 0, wxALL, 5);
//    sizer->Add(ellipseButton, 0, wxALL, 5);
//    sizer->Add(diamondButton, 0, wxALL, 5);
//    
//
//    rectButton->Bind(wxEVT_BUTTON, &Sidebar::OnRectButton, this);
//    circleButton->Bind(wxEVT_BUTTON, &Sidebar::OnCircleButton, this);
//    triangleButton->Bind(wxEVT_BUTTON, &Sidebar::OnTriangleButton, this);
//    ellipseButton->Bind(wxEVT_BUTTON, &Sidebar::OnEllipseButton, this);
//    diamondButton->Bind(wxEVT_BUTTON, &Sidebar::OnDiamondButton, this);
//
//    // 绑定菜单项事件
//    parent->Bind(wxEVT_MENU, &Sidebar::OnNewFile, this, wxID_NEW);
//    parent->Bind(wxEVT_MENU, &Sidebar::OnOpenFile, this, wxID_OPEN);
//    parent->Bind(wxEVT_MENU, &Sidebar::OnSaveFile, this, wxID_SAVE);
//    parent->Bind(wxEVT_MENU, &Sidebar::OnSaveAsFile, this, wxID_SAVEAS);
//    parent->Bind(wxEVT_MENU, &Sidebar::OnCloseFile, this, wxID_CLOSE);
//    parent->Bind(wxEVT_MENU, &Sidebar::OnPrintFile, this, wxID_PRINT);
//    parent->Bind(wxEVT_MENU, &Sidebar::OnExit, this, wxID_EXIT);
//}

// 构造函数，初始化工具栏并绑定按钮事件
Sidebar::Sidebar(wxFrame* parent, DrawingPanel* drawingPanel, int width)
    : wxPanel(parent, wxID_ANY), drawingPanel(drawingPanel) {
    SetMinSize(wxSize(width, -1)); // 设置最小宽度

    // 创建菜单栏
    wxMenuBar* menuBar = new wxMenuBar();

    // 创建 wxGrid 控件
    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(3, 1); // 创建一个 3 行 1 列的表格
    grid->SetColLabelValue(0, "属性");
    grid->SetRowLabelValue(0, "名称");
    grid->SetRowLabelValue(1, "接入口数");
    grid->SetRowLabelValue(2, "输出口数");
    grid->SetRowLabelValue(3, "功能");

    // 创建按钮
    wxButton* rectButton = new wxButton(this, wxID_ANY, "与门"); // Rectangle
    wxButton* circleButton = new wxButton(this, wxID_ANY, "或门"); // Circle
    wxButton* triangleButton = new wxButton(this, wxID_ANY, "非门"); // Triangle
    wxButton* ellipseButton = new wxButton(this, wxID_ANY, "1信号输入"); // Ellipse
    wxButton* diamondButton = new wxButton(this, wxID_ANY, "0信号输入"); // Diamond

    // 创建按钮竖直布局
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);//设置按钮是竖直的
    buttonSizer->Add(rectButton, 0, wxALL, 5);
    buttonSizer->Add(circleButton, 0, wxALL, 5);
    buttonSizer->Add(triangleButton, 0, wxALL, 5);
    buttonSizer->Add(ellipseButton, 0, wxALL, 5);
    buttonSizer->Add(diamondButton, 0, wxALL, 5);

    // 设置布局
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 5); // 按钮放在上面
    sizer->Add(grid, 1, wxEXPAND | wxALL, 5); // 属性表放在下面
    SetSizer(sizer);

    // 创建文件菜单
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(wxID_NEW, "&新建文件\tCtrl+N");
    fileMenu->Append(wxID_OPEN, "&打开文件\tCtrl+O");
    fileMenu->Append(wxID_SAVE, "&保存文件\tCtrl+S");
    fileMenu->Append(wxID_SAVEAS, "&另存为文件\tCtrl+Shift+S");
    fileMenu->Append(wxID_CLOSE, "&关闭文件\tCtrl+W");
    fileMenu->Append(wxID_PRINT, "&打印文件\tCtrl+P");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "&退出程序\tCtrl+Q");

    // 将文件菜单添加到菜单栏
    menuBar->Append(fileMenu, "&文件");

    // 创建帮助菜单
    wxMenu* helpMenu = new wxMenu();
    helpMenu->Append(wxID_ABOUT, "&关于\tF1");

    // 将帮助菜单添加到菜单栏
    menuBar->Append(helpMenu, "&帮助");

    // 将菜单栏设置到父窗口
    parent->SetMenuBar(menuBar);

    // 绑定按钮事件
    rectButton->Bind(wxEVT_BUTTON, &Sidebar::OnRectButton, this);
    circleButton->Bind(wxEVT_BUTTON, &Sidebar::OnCircleButton, this);
    triangleButton->Bind(wxEVT_BUTTON, &Sidebar::OnTriangleButton, this);
    ellipseButton->Bind(wxEVT_BUTTON, &Sidebar::OnEllipseButton, this);
    diamondButton->Bind(wxEVT_BUTTON, &Sidebar::OnDiamondButton, this);

    // 绑定菜单项事件
    parent->Bind(wxEVT_MENU, &Sidebar::OnNewFile, this, wxID_NEW);
    parent->Bind(wxEVT_MENU, &Sidebar::OnOpenFile, this, wxID_OPEN);
    parent->Bind(wxEVT_MENU, &Sidebar::OnSaveFile, this, wxID_SAVE);
    parent->Bind(wxEVT_MENU, &Sidebar::OnSaveAsFile, this, wxID_SAVEAS);
    parent->Bind(wxEVT_MENU, &Sidebar::OnCloseFile, this, wxID_CLOSE);
    parent->Bind(wxEVT_MENU, &Sidebar::OnPrintFile, this, wxID_PRINT);
    parent->Bind(wxEVT_MENU, &Sidebar::OnExit, this, wxID_EXIT);
}


void Sidebar::OnRectButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::AndGate, 50, 50);

    // 更新 grid 中的单元格数据
    grid->SetCellValue(0, 0, "与门");
    grid->SetCellValue(1, 0, "5");
    grid->SetCellValue(2, 0, "1");
    grid->SetCellValue(3, 0, "均为真时输出为真");
}

void Sidebar::OnCircleButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::OrGate, 150, 100);

    // 更新 grid 中的单元格数据
    grid->SetCellValue(0, 0, "或门");
    grid->SetCellValue(1, 0, "5");
    grid->SetCellValue(2, 0, "1");
    grid->SetCellValue(3, 0, "存在真值输入输出真");
}



void Sidebar::OnTriangleButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::NotGate, 50, 100);

    // 更新 grid 中的单元格数据
    grid->SetCellValue(0, 0, "非门");
    grid->SetCellValue(1, 0, "2");
    grid->SetCellValue(2, 0, "1");
    grid->SetCellValue(3, 0, "双假出真");
}



void Sidebar::OnEllipseButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::OnPin, 150, 150);

    // 更新 grid 中的单元格数据
    grid->SetCellValue(0, 0, "输出1");
    grid->SetCellValue(1, 0, "0");
    grid->SetCellValue(2, 0, "1");
    grid->SetCellValue(3, 0, "双假出真");
}


void Sidebar::OnDiamondButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::OffPin, 100, 150);
    //wxColor sidebarBackgroundColor = wxColour(192, 192, 192); // 示例颜色为灰色

    //// 设置网格默认单元格的背景颜色
    //grid->SetDefaultCellBackgroundColour(sidebarBackgroundColor);

    // 更新 grid 中的单元格数据
    grid->SetCellValue(0, 0, "输出0");
    grid->SetCellValue(1, 0, "0");
    grid->SetCellValue(2, 0, "1");
    grid->SetCellValue(3, 0, "双假出真");
}



// 菜单项事件处理函数
void Sidebar::OnNewFile(wxCommandEvent& event) {
    // 新建文件的逻辑
    drawingPanel->Clear(); // 假设 DrawingPanel 类有一个 Clear 方法
    wxMessageBox("新建文件已创建", "提示", wxOK | wxICON_INFORMATION);
}

void Sidebar::OnOpenFile(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, _("打开文件"), "", "",
        "All files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // 用户取消

    // 打开文件的逻辑
    wxTextFile file;
    if (file.Open(openFileDialog.GetPath())) {
        drawingPanel->Clear();
        for (wxString str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine()) {
            // 假设每行包含形状类型和位置
            // 例如：AndGate 50 50
            wxStringTokenizer tokenizer(str, " ");
            wxString shapeType = tokenizer.GetNextToken();
            long x, y;
            tokenizer.GetNextToken().ToLong(&x);
            tokenizer.GetNextToken().ToLong(&y);
            drawingPanel->AddShape(ShapeTypeFromString(shapeType), x, y);
        }
    }
}

void Sidebar::OnSaveFile(wxCommandEvent& event) {
    // 保存文件的逻辑
    wxFileDialog saveFileDialog(this, _("保存文件"), "", "",
        "All files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // 用户取消

    wxTextFile file;
    if (file.Create(saveFileDialog.GetPath())) {
        const auto& shapes = drawingPanel->GetShapes();
        for (const auto& shape : shapes) {
            file.AddLine(wxString::Format("%s %d %d", ShapeTypeToString(shape.type), shape.x, shape.y));
        }
        file.Write();
        file.Close();
    }
}

void Sidebar::OnSaveAsFile(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, _("另存为文件"), "", "",
        "All files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // 用户取消

    wxTextFile file;
    if (file.Create(saveFileDialog.GetPath())) {
        const auto& shapes = drawingPanel->GetShapes();
        for (const auto& shape : shapes) {
            file.AddLine(wxString::Format("%s %d %d", ShapeTypeToString(shape.type), shape.x, shape.y));
        }
        file.Write();
        file.Close();
    }
}

void Sidebar::OnCloseFile(wxCommandEvent& event) {
    // 关闭文件的逻辑
    drawingPanel->Clear();
    wxMessageBox("文件已关闭", "提示", wxOK | wxICON_INFORMATION);
}

void Sidebar::OnPrintFile(wxCommandEvent& event) {
    wxPrinter printer;
    wxPrintDialogData printDialogData(printer.GetPrintDialogData());
    wxPrintDialog printDialog(this, &printDialogData);

    if (printDialog.ShowModal() == wxID_OK) {
        // 打印文件的逻辑
        wxMessageBox("打印文件功能尚未实现", "提示", wxOK | wxICON_INFORMATION);
    }
}

void Sidebar::OnExit(wxCommandEvent& event) {
    Close(true); // 退出程序
}

// 辅助函数：从字符串转换为 ShapeType
ShapeType Sidebar::ShapeTypeFromString(const wxString& str) {
    if (str == "AndGate") return ShapeType::AndGate;
    if (str == "OrGate") return ShapeType::OrGate;
    if (str == "NotGate") return ShapeType::NotGate;
    if (str == "OnPin") return ShapeType::OnPin;
    if (str == "OffPin") return ShapeType::OffPin;
    // 添加其他类型
    return ShapeType::Unknown;
}

// 辅助函数：从 ShapeType 转换为字符串
wxString Sidebar::ShapeTypeToString(ShapeType type) {
    switch (type) {
    case ShapeType::AndGate: return "AndGate";
    case ShapeType::OrGate: return "OrGate";
    case ShapeType::NotGate: return "NotGate";
    case ShapeType::OnPin: return "OnPin";
    case ShapeType::OffPin: return "OffPin";
        // 添加其他类型
    default: return "Unknown";
    }
}