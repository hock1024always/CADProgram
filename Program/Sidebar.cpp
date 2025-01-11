#include "Sidebar.h"
#include "DrawingPanel.h"
#include "Shape.h"
#include <wx/filedlg.h>
#include <wx/print.h>
#include <wx/printdlg.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h> // 包含 wxStringTokenizer 头文件
#include <string>       //字符串
// using namespace std;
//  构造函数，初始化工具栏并绑定按钮事件
Sidebar::Sidebar(wxFrame *parent, DrawingPanel *drawingPanel, int width)
    : wxPanel(parent, wxID_ANY), drawingPanel(drawingPanel)
{
    SetMinSize(wxSize(width, -1)); // 设置最小宽度

    // 创建菜单栏
    wxMenuBar *menuBar = new wxMenuBar();

    // 创建文件菜单
    wxMenu *fileMenu = new wxMenu();
    fileMenu->Append(wxID_NEW, "&新建文件\tCtrl+N");
    fileMenu->Append(wxID_OPEN, "&打开文件\tCtrl+O");
    fileMenu->Append(wxID_SAVE, "&保存文件\tCtrl+S");
    fileMenu->Append(wxID_SAVEAS, "&另存为文件\tCtrl+Shift+S");
    fileMenu->Append(wxID_CLOSE, "&关闭文件\tCtrl+W");
    fileMenu->Append(wxID_PRINT, "&打印文件\tCtrl+P");

    // 将文件菜单添加到菜单栏
    menuBar->Append(fileMenu, "&文件");

    // 创建帮助菜单
    wxMenu *helpMenu = new wxMenu();
    helpMenu->Append(wxID_ABOUT, "&关于\tF1");

    // 将帮助菜单添加到菜单栏
    menuBar->Append(helpMenu, "&帮助");
    // 创建窗口菜单
    wxMenu *editMenu = new wxMenu();
    editMenu->Append(wxID_UNDO, "&回退");
    editMenu->Append(wxID_REDO, "&前进");
    menuBar->Append(editMenu, "&编辑");

    // 将菜单栏设置到父窗口
    parent->SetMenuBar(menuBar);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxButton *undoButton = new wxButton(this, wxID_UNDO, "回退");
    wxButton *redoButton = new wxButton(this, wxID_REDO, "前进");
    wxButton *rectButton = new wxButton(this, wxID_ANY, "与门");         // Rectangle
    wxButton *circleButton = new wxButton(this, wxID_ANY, "或门");       // Circle
    wxButton *triangleButton = new wxButton(this, wxID_ANY, "非门");     // Triangle
    wxButton *ellipseButton = new wxButton(this, wxID_ANY, "1信号输入"); // Ellipse
    wxButton *diamondButton = new wxButton(this, wxID_ANY, "0信号输入"); // Diamond

    // 创建静态文本，用于显示图形释放信息
    infoGrid = new wxGrid(this, wxID_ANY);
    infoGrid->CreateGrid(5, 2); // 创建5行2列的表格
    infoGrid->SetColLabelValue(0, "属性");
    infoGrid->SetColLabelValue(1, "值");
    infoGrid->SetRowLabelSize(0); // 隐藏行标签

    sizer->Add(undoButton, 0, wxALL, 5);
    sizer->Add(redoButton, 0, wxALL, 5);
    sizer->Add(rectButton, 0, wxALL, 5);
    sizer->Add(circleButton, 0, wxALL, 5);
    sizer->Add(triangleButton, 0, wxALL, 5);
    sizer->Add(ellipseButton, 0, wxALL, 5);
    sizer->Add(diamondButton, 0, wxALL, 5);
    sizer->Add(infoGrid, 1, wxALL | wxEXPAND, 5);

    SetSizer(sizer);
    undoButton->Bind(wxEVT_BUTTON, &Sidebar::OnUndo, this);
    redoButton->Bind(wxEVT_BUTTON, &Sidebar::OnRedo, this);
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
    parent->Bind(wxEVT_MENU, &Sidebar::OnUndo, this, wxID_UNDO);
    parent->Bind(wxEVT_MENU, &Sidebar::OnRedo, this, wxID_REDO);
}
void Sidebar::UpdateInfo(const wxString &info)
{
    wxStringTokenizer tokenizer(info, "\n");
    int row = 0;
    while (tokenizer.HasMoreTokens() && row < infoGrid->GetNumberRows())
    {
        wxString token = tokenizer.GetNextToken();
        wxStringTokenizer pair(token, ": ");
        if (pair.CountTokens() == 2)
        {
            infoGrid->SetCellValue(row, 0, pair.GetNextToken());
            infoGrid->SetCellValue(row, 1, pair.GetNextToken());
        }
        row++;
    }
}

void Sidebar::OnRectButton(wxCommandEvent &event)
{
    drawingPanel->AddShape(ShapeType::AndGate, 50, 50);
    // 销毁旧的表格
    if (infoGrid)
    {
        infoGrid->Destroy();
    }
    // 创建新的表格
    infoGrid = new wxGrid(this, wxID_ANY);
    infoGrid->CreateGrid(4, 2); // 创建4行2列的表格
    infoGrid->SetColLabelValue(0, "属性");
    infoGrid->SetColLabelValue(1, "值");
    infoGrid->SetRowLabelSize(0); // 隐藏行标签
    infoGrid->SetCellValue(0, 0, "名称");
    infoGrid->SetCellValue(0, 1, "与门");
    infoGrid->SetCellValue(1, 0, "接入口数");
    infoGrid->SetCellValue(1, 1, "2");
    infoGrid->SetCellValue(2, 0, "输出口数");
    infoGrid->SetCellValue(2, 1, "1");
    infoGrid->SetCellValue(3, 0, "功能");
    infoGrid->SetCellValue(3, 1, "双真出真");
    // 将新的表格添加到布局中
    GetSizer()->Add(infoGrid, 1, wxALL | wxEXPAND, 5);
    GetSizer()->Layout();
}

void Sidebar::OnCircleButton(wxCommandEvent &event)
{
    drawingPanel->AddShape(ShapeType::OrGate, 150, 100);
    // 销毁旧的表格
    if (infoGrid)
    {
        infoGrid->Destroy();
    }
    // 创建新的表格
    infoGrid = new wxGrid(this, wxID_ANY);
    infoGrid->CreateGrid(4, 2); // 创建4行2列的表格
    infoGrid->SetColLabelValue(0, "属性");
    infoGrid->SetColLabelValue(1, "值");
    infoGrid->SetRowLabelSize(0); // 隐藏行标签
    infoGrid->SetCellValue(0, 0, "名称");
    infoGrid->SetCellValue(0, 1, "或门");
    infoGrid->SetCellValue(1, 0, "接入口数");
    infoGrid->SetCellValue(1, 1, "2");
    infoGrid->SetCellValue(2, 0, "输出口数");
    infoGrid->SetCellValue(2, 1, "1");
    infoGrid->SetCellValue(3, 0, "功能");
    infoGrid->SetCellValue(3, 1, "有真出真");
    // 将新的表格添加到布局中
    GetSizer()->Add(infoGrid, 1, wxALL | wxEXPAND, 5);
    GetSizer()->Layout();
}

void Sidebar::OnTriangleButton(wxCommandEvent &event)
{
    drawingPanel->AddShape(ShapeType::NotGate, 50, 100);
    // 销毁旧的表格
    if (infoGrid) {
        infoGrid->Destroy();
    }
    // 创建新的表格
    infoGrid = new wxGrid(this, wxID_ANY);
    infoGrid->CreateGrid(4, 2); // 创建4行2列的表格
    infoGrid->SetColLabelValue(0, "属性");
    infoGrid->SetColLabelValue(1, "值");
    infoGrid->SetRowLabelSize(0); // 隐藏行标签
    infoGrid->SetCellValue(0, 0, "名称");
    infoGrid->SetCellValue(0, 1, "非门");
    infoGrid->SetCellValue(1, 0, "接入口数");
    infoGrid->SetCellValue(1, 1, "2");
    infoGrid->SetCellValue(2, 0, "输出口数");
    infoGrid->SetCellValue(2, 1, "1");
    infoGrid->SetCellValue(3, 0, "功能");
    infoGrid->SetCellValue(3, 1, "双假出真");
    // 将新的表格添加到布局中
    GetSizer()->Add(infoGrid, 1, wxALL | wxEXPAND, 5);
    GetSizer()->Layout();
}

void Sidebar::OnEllipseButton(wxCommandEvent &event)
{
    drawingPanel->AddShape(ShapeType::OnPin, 150, 150);
    // 销毁旧的表格
    if (infoGrid) {
        infoGrid->Destroy();
    }
    // 创建新的表格
    infoGrid = new wxGrid(this, wxID_ANY);
    infoGrid->CreateGrid(4, 2); // 创建4行2列的表格
    infoGrid->SetColLabelValue(0, "属性");
    infoGrid->SetColLabelValue(1, "值");
    infoGrid->SetRowLabelSize(0); // 隐藏行标签
    infoGrid->SetCellValue(0, 0, "名称");
    infoGrid->SetCellValue(0, 1, "1输入设备");
    infoGrid->SetCellValue(1, 0, "接入口数");
    infoGrid->SetCellValue(1, 1, "0");
    infoGrid->SetCellValue(2, 0, "输出口数");
    infoGrid->SetCellValue(2, 1, "1");
    infoGrid->SetCellValue(3, 0, "功能");
    infoGrid->SetCellValue(3, 1, "输出1");
    // 将新的表格添加到布局中
    GetSizer()->Add(infoGrid, 1, wxALL | wxEXPAND, 5);
    GetSizer()->Layout();
}

void Sidebar::OnDiamondButton(wxCommandEvent &event)
{
    drawingPanel->AddShape(ShapeType::OffPin, 100, 150);
    // 销毁旧的表格
    if (infoGrid) {
        infoGrid->Destroy();
    }
    // 创建新的表格
    infoGrid = new wxGrid(this, wxID_ANY);
    infoGrid->CreateGrid(4, 2); // 创建4行2列的表格
    infoGrid->SetColLabelValue(0, "属性");
    infoGrid->SetColLabelValue(1, "值");
    infoGrid->SetRowLabelSize(0); // 隐藏行标签
    infoGrid->SetCellValue(0, 0, "名称");
    infoGrid->SetCellValue(0, 1, "0输入设备");
    infoGrid->SetCellValue(1, 0, "接入口数");
    infoGrid->SetCellValue(1, 1, "0");
    infoGrid->SetCellValue(2, 0, "输出口数");
    infoGrid->SetCellValue(2, 1, "1");
    infoGrid->SetCellValue(3, 0, "功能");
    infoGrid->SetCellValue(3, 1, "输出0");
    // 将新的表格添加到布局中
    GetSizer()->Add(infoGrid, 1, wxALL | wxEXPAND, 5);
    GetSizer()->Layout();
}

// 菜单项事件处理函数
void Sidebar::OnNewFile(wxCommandEvent &event)
{
    // 新建文件的逻辑
    drawingPanel->Clear(); // 假设 DrawingPanel 类有一个 Clear 方法
    wxMessageBox("新建文件已创建", "提示", wxOK | wxICON_INFORMATION);
}

void Sidebar::OnOpenFile(wxCommandEvent &event)
{
    wxFileDialog openFileDialog(this, _("打开文件"), "", "",
                                "All files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // 用户取消

    // 打开文件的逻辑
    wxTextFile file;
    if (file.Open(openFileDialog.GetPath()))
    {
        drawingPanel->Clear();
        for (wxString str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine())
        {
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

void Sidebar::OnSaveFile(wxCommandEvent &event)
{
    // 保存文件的逻辑
    wxFileDialog saveFileDialog(this, _("保存文件"), "", "",
                                "All files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // 用户取消

    wxTextFile file;
    if (file.Create(saveFileDialog.GetPath()))
    {
        const auto &shapes = drawingPanel->GetShapes();
        for (const auto &shape : shapes)
        {
            file.AddLine(wxString::Format("%s %d %d", ShapeTypeToString(shape.type), shape.x, shape.y));
        }
        file.Write();
        file.Close();
    }
}

void Sidebar::OnSaveAsFile(wxCommandEvent &event)
{
    wxFileDialog saveFileDialog(this, _("另存为文件"), "", "",
                                "All files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // 用户取消

    wxTextFile file;
    if (file.Create(saveFileDialog.GetPath()))
    {
        const auto &shapes = drawingPanel->GetShapes();
        for (const auto &shape : shapes)
        {
            file.AddLine(wxString::Format("%s %d %d", ShapeTypeToString(shape.type), shape.x, shape.y));
        }
        file.Write();
        file.Close();
    }
}

void Sidebar::OnCloseFile(wxCommandEvent &event)
{
    // 关闭文件的逻辑
    drawingPanel->Clear();
    wxMessageBox("文件已关闭", "提示", wxOK | wxICON_INFORMATION);
}

void Sidebar::OnPrintFile(wxCommandEvent &event)
{
    wxPrinter printer;
    wxPrintDialogData printDialogData(printer.GetPrintDialogData());
    wxPrintDialog printDialog(this, &printDialogData);

    if (printDialog.ShowModal() == wxID_OK)
    {
        // 打印文件的逻辑
        wxMessageBox("打印文件功能尚未实现", "提示", wxOK | wxICON_INFORMATION);
    }
}

void Sidebar::OnUndo(wxCommandEvent &event)
{
    drawingPanel->Undo();
}

void Sidebar::OnRedo(wxCommandEvent &event)
{
    drawingPanel->Redo();
}
