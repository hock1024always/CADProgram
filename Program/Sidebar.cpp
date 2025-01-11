#include "Sidebar.h"
#include "DrawingPanel.h"
#include "Shape.h"
#include <wx/filedlg.h>
#include <wx/print.h>
#include <wx/printdlg.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h> // ���� wxStringTokenizer ͷ�ļ�
#include <string>       //�ַ���
// using namespace std;
//  ���캯������ʼ�����������󶨰�ť�¼�
Sidebar::Sidebar(wxFrame *parent, DrawingPanel *drawingPanel, int width)
    : wxPanel(parent, wxID_ANY), drawingPanel(drawingPanel)
{
    SetMinSize(wxSize(width, -1)); // ������С���

    // �����˵���
    wxMenuBar *menuBar = new wxMenuBar();

    // �����ļ��˵�
    wxMenu *fileMenu = new wxMenu();
    fileMenu->Append(wxID_NEW, "&�½��ļ�\tCtrl+N");
    fileMenu->Append(wxID_OPEN, "&���ļ�\tCtrl+O");
    fileMenu->Append(wxID_SAVE, "&�����ļ�\tCtrl+S");
    fileMenu->Append(wxID_SAVEAS, "&���Ϊ�ļ�\tCtrl+Shift+S");
    fileMenu->Append(wxID_CLOSE, "&�ر��ļ�\tCtrl+W");
    fileMenu->Append(wxID_PRINT, "&��ӡ�ļ�\tCtrl+P");

    // ���ļ��˵���ӵ��˵���
    menuBar->Append(fileMenu, "&�ļ�");

    // ���������˵�
    wxMenu *helpMenu = new wxMenu();
    helpMenu->Append(wxID_ABOUT, "&����\tF1");

    // �������˵���ӵ��˵���
    menuBar->Append(helpMenu, "&����");
    // �������ڲ˵�
    wxMenu *editMenu = new wxMenu();
    editMenu->Append(wxID_UNDO, "&����");
    editMenu->Append(wxID_REDO, "&ǰ��");
    menuBar->Append(editMenu, "&�༭");

    // ���˵������õ�������
    parent->SetMenuBar(menuBar);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxButton *undoButton = new wxButton(this, wxID_UNDO, "����");
    wxButton *redoButton = new wxButton(this, wxID_REDO, "ǰ��");
    wxButton *rectButton = new wxButton(this, wxID_ANY, "����");         // Rectangle
    wxButton *circleButton = new wxButton(this, wxID_ANY, "����");       // Circle
    wxButton *triangleButton = new wxButton(this, wxID_ANY, "����");     // Triangle
    wxButton *ellipseButton = new wxButton(this, wxID_ANY, "1�ź�����"); // Ellipse
    wxButton *diamondButton = new wxButton(this, wxID_ANY, "0�ź�����"); // Diamond

    // ������̬�ı���������ʾͼ���ͷ���Ϣ
    infoGrid = new wxGrid(this, wxID_ANY);
    infoGrid->CreateGrid(5, 2); // ����5��2�еı��
    infoGrid->SetColLabelValue(0, "����");
    infoGrid->SetColLabelValue(1, "ֵ");
    infoGrid->SetRowLabelSize(0); // �����б�ǩ

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

    // �󶨲˵����¼�
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
    // ���پɵı��
    if (infoGrid)
    {
        infoGrid->Destroy();
    }
    // �����µı��
    infoGrid = new wxGrid(this, wxID_ANY);
    infoGrid->CreateGrid(4, 2); // ����4��2�еı��
    infoGrid->SetColLabelValue(0, "����");
    infoGrid->SetColLabelValue(1, "ֵ");
    infoGrid->SetRowLabelSize(0); // �����б�ǩ
    infoGrid->SetCellValue(0, 0, "����");
    infoGrid->SetCellValue(0, 1, "����");
    infoGrid->SetCellValue(1, 0, "�������");
    infoGrid->SetCellValue(1, 1, "2");
    infoGrid->SetCellValue(2, 0, "�������");
    infoGrid->SetCellValue(2, 1, "1");
    infoGrid->SetCellValue(3, 0, "����");
    infoGrid->SetCellValue(3, 1, "˫�����");
    // ���µı����ӵ�������
    GetSizer()->Add(infoGrid, 1, wxALL | wxEXPAND, 5);
    GetSizer()->Layout();
}

void Sidebar::OnCircleButton(wxCommandEvent &event)
{
    drawingPanel->AddShape(ShapeType::OrGate, 150, 100);
    // ���پɵı��
    if (infoGrid)
    {
        infoGrid->Destroy();
    }
    // �����µı��
    infoGrid = new wxGrid(this, wxID_ANY);
    infoGrid->CreateGrid(4, 2); // ����4��2�еı��
    infoGrid->SetColLabelValue(0, "����");
    infoGrid->SetColLabelValue(1, "ֵ");
    infoGrid->SetRowLabelSize(0); // �����б�ǩ
    infoGrid->SetCellValue(0, 0, "����");
    infoGrid->SetCellValue(0, 1, "����");
    infoGrid->SetCellValue(1, 0, "�������");
    infoGrid->SetCellValue(1, 1, "2");
    infoGrid->SetCellValue(2, 0, "�������");
    infoGrid->SetCellValue(2, 1, "1");
    infoGrid->SetCellValue(3, 0, "����");
    infoGrid->SetCellValue(3, 1, "�������");
    // ���µı����ӵ�������
    GetSizer()->Add(infoGrid, 1, wxALL | wxEXPAND, 5);
    GetSizer()->Layout();
}

void Sidebar::OnTriangleButton(wxCommandEvent &event)
{
    drawingPanel->AddShape(ShapeType::NotGate, 50, 100);
    // ���پɵı��
    if (infoGrid) {
        infoGrid->Destroy();
    }
    // �����µı��
    infoGrid = new wxGrid(this, wxID_ANY);
    infoGrid->CreateGrid(4, 2); // ����4��2�еı��
    infoGrid->SetColLabelValue(0, "����");
    infoGrid->SetColLabelValue(1, "ֵ");
    infoGrid->SetRowLabelSize(0); // �����б�ǩ
    infoGrid->SetCellValue(0, 0, "����");
    infoGrid->SetCellValue(0, 1, "����");
    infoGrid->SetCellValue(1, 0, "�������");
    infoGrid->SetCellValue(1, 1, "2");
    infoGrid->SetCellValue(2, 0, "�������");
    infoGrid->SetCellValue(2, 1, "1");
    infoGrid->SetCellValue(3, 0, "����");
    infoGrid->SetCellValue(3, 1, "˫�ٳ���");
    // ���µı����ӵ�������
    GetSizer()->Add(infoGrid, 1, wxALL | wxEXPAND, 5);
    GetSizer()->Layout();
}

void Sidebar::OnEllipseButton(wxCommandEvent &event)
{
    drawingPanel->AddShape(ShapeType::OnPin, 150, 150);
    // ���پɵı��
    if (infoGrid) {
        infoGrid->Destroy();
    }
    // �����µı��
    infoGrid = new wxGrid(this, wxID_ANY);
    infoGrid->CreateGrid(4, 2); // ����4��2�еı��
    infoGrid->SetColLabelValue(0, "����");
    infoGrid->SetColLabelValue(1, "ֵ");
    infoGrid->SetRowLabelSize(0); // �����б�ǩ
    infoGrid->SetCellValue(0, 0, "����");
    infoGrid->SetCellValue(0, 1, "1�����豸");
    infoGrid->SetCellValue(1, 0, "�������");
    infoGrid->SetCellValue(1, 1, "0");
    infoGrid->SetCellValue(2, 0, "�������");
    infoGrid->SetCellValue(2, 1, "1");
    infoGrid->SetCellValue(3, 0, "����");
    infoGrid->SetCellValue(3, 1, "���1");
    // ���µı����ӵ�������
    GetSizer()->Add(infoGrid, 1, wxALL | wxEXPAND, 5);
    GetSizer()->Layout();
}

void Sidebar::OnDiamondButton(wxCommandEvent &event)
{
    drawingPanel->AddShape(ShapeType::OffPin, 100, 150);
    // ���پɵı��
    if (infoGrid) {
        infoGrid->Destroy();
    }
    // �����µı��
    infoGrid = new wxGrid(this, wxID_ANY);
    infoGrid->CreateGrid(4, 2); // ����4��2�еı��
    infoGrid->SetColLabelValue(0, "����");
    infoGrid->SetColLabelValue(1, "ֵ");
    infoGrid->SetRowLabelSize(0); // �����б�ǩ
    infoGrid->SetCellValue(0, 0, "����");
    infoGrid->SetCellValue(0, 1, "0�����豸");
    infoGrid->SetCellValue(1, 0, "�������");
    infoGrid->SetCellValue(1, 1, "0");
    infoGrid->SetCellValue(2, 0, "�������");
    infoGrid->SetCellValue(2, 1, "1");
    infoGrid->SetCellValue(3, 0, "����");
    infoGrid->SetCellValue(3, 1, "���0");
    // ���µı����ӵ�������
    GetSizer()->Add(infoGrid, 1, wxALL | wxEXPAND, 5);
    GetSizer()->Layout();
}

// �˵����¼�������
void Sidebar::OnNewFile(wxCommandEvent &event)
{
    // �½��ļ����߼�
    drawingPanel->Clear(); // ���� DrawingPanel ����һ�� Clear ����
    wxMessageBox("�½��ļ��Ѵ���", "��ʾ", wxOK | wxICON_INFORMATION);
}

void Sidebar::OnOpenFile(wxCommandEvent &event)
{
    wxFileDialog openFileDialog(this, _("���ļ�"), "", "",
                                "All files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // �û�ȡ��

    // ���ļ����߼�
    wxTextFile file;
    if (file.Open(openFileDialog.GetPath()))
    {
        drawingPanel->Clear();
        for (wxString str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine())
        {
            // ����ÿ�а�����״���ͺ�λ��
            // ���磺AndGate 50 50
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
    // �����ļ����߼�
    wxFileDialog saveFileDialog(this, _("�����ļ�"), "", "",
                                "All files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // �û�ȡ��

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
    wxFileDialog saveFileDialog(this, _("���Ϊ�ļ�"), "", "",
                                "All files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // �û�ȡ��

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
    // �ر��ļ����߼�
    drawingPanel->Clear();
    wxMessageBox("�ļ��ѹر�", "��ʾ", wxOK | wxICON_INFORMATION);
}

void Sidebar::OnPrintFile(wxCommandEvent &event)
{
    wxPrinter printer;
    wxPrintDialogData printDialogData(printer.GetPrintDialogData());
    wxPrintDialog printDialog(this, &printDialogData);

    if (printDialog.ShowModal() == wxID_OK)
    {
        // ��ӡ�ļ����߼�
        wxMessageBox("��ӡ�ļ�������δʵ��", "��ʾ", wxOK | wxICON_INFORMATION);
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
