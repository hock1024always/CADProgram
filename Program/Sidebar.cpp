#include "Sidebar.h"
#include "DrawingPanel.h"
#include "Shape.h"
#include <wx/filedlg.h>
#include <wx/print.h>
#include <wx/printdlg.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h> // 包含 wxStringTokenizer 头文件
#include <string> //字符串
//using namespace std;
// 构造函数，初始化工具栏并绑定按钮事件
Sidebar::Sidebar(wxFrame* parent, DrawingPanel* drawingPanel, int width)
    : wxPanel(parent, wxID_ANY), drawingPanel(drawingPanel) {
    SetMinSize(wxSize(width, -1)); // 设置最小宽度

    // 创建菜单栏
    wxMenuBar* menuBar = new wxMenuBar();

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
ShapeType ShapeTypeFromString(const wxString& str) {
    if (str == "AndGate") return ShapeType::AndGate;
    if (str == "OrGate") return ShapeType::OrGate;
    if (str == "NotGate") return ShapeType::NotGate;
    if (str == "OnPin") return ShapeType::OnPin;
    if (str == "OffPin") return ShapeType::OffPin;
    // 添加其他类型
    return ShapeType::Unknown;
}

// 辅助函数：从 ShapeType 转换为字符串
wxString ShapeTypeToString(ShapeType type) {
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

// 添加新的图形
void DrawingPanel::AddShape(ShapeType type, int x, int y) {
    // 将新图形添加到图形列表中
    shapes.push_back({ type, x, y });
    wxString file = ShapeTypeToString(type);
    std::string filename = std::string(file.mb_str()) + ".json";
        //LoadFromJSON(filename);
        // 刷新面板以更新显示
        Refresh();
}