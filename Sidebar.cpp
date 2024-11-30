#include "Sidebar.h"
#include "DrawingPanel.h"
#include <wx/filedlg.h>
#include <wx/print.h>
#include <wx/printdlg.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h> // ���� wxStringTokenizer ͷ�ļ�
#include <wx/log.h>



//// ���캯������ʼ�����������󶨰�ť�¼�
//Sidebar::Sidebar(wxFrame* parent, DrawingPanel* drawingPanel, int width)
//    : wxPanel(parent, wxID_ANY), drawingPanel(drawingPanel) {
//    SetMinSize(wxSize(width, -1)); // ������С���
//
//    // �����˵���
//    wxMenuBar* menuBar = new wxMenuBar();
//
//    // ���� wxGrid �ؼ�
//    grid = new wxGrid(this, wxID_ANY);
//    grid->CreateGrid(3, 1); // ����һ�� 3 �� 1 �еı��
//    grid->SetColLabelValue(0, "����");
//    grid->SetRowLabelValue(0, "����");
//    grid->SetRowLabelValue(1, "�������");
//    grid->SetRowLabelValue(2, "�������");
//    grid->SetRowLabelValue(3, "����");
//
//    // ���ò���
//    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
//    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);
//    SetSizer(sizer);
//
//    // �����ļ��˵�
//    wxMenu* fileMenu = new wxMenu();
//    fileMenu->Append(wxID_NEW, "&�½��ļ�\tCtrl+N");
//    fileMenu->Append(wxID_OPEN, "&���ļ�\tCtrl+O");
//    fileMenu->Append(wxID_SAVE, "&�����ļ�\tCtrl+S");
//    fileMenu->Append(wxID_SAVEAS, "&���Ϊ�ļ�\tCtrl+Shift+S");
//    fileMenu->Append(wxID_CLOSE, "&�ر��ļ�\tCtrl+W");
//    fileMenu->Append(wxID_PRINT, "&��ӡ�ļ�\tCtrl+P");
//    fileMenu->AppendSeparator();
//    fileMenu->Append(wxID_EXIT, "&�˳�����\tCtrl+Q");
//
//    // ���ļ��˵���ӵ��˵���
//    menuBar->Append(fileMenu, "&�ļ�");
//
//    // ���������˵�
//    wxMenu* helpMenu = new wxMenu();
//    helpMenu->Append(wxID_ABOUT, "&����\tF1");
//
//    // �������˵���ӵ��˵���
//    menuBar->Append(helpMenu, "&����");
//
//    // ���˵������õ�������
//    parent->SetMenuBar(menuBar);
//
//    //wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
//
//    wxButton* rectButton = new wxButton(this, wxID_ANY, "����"); // Rectangle
//    wxButton* circleButton = new wxButton(this, wxID_ANY, "����"); // Circle
//    wxButton* triangleButton = new wxButton(this, wxID_ANY, "����"); // Triangle
//    wxButton* ellipseButton = new wxButton(this, wxID_ANY, "1�ź�����"); // Ellipse
//    wxButton* diamondButton = new wxButton(this, wxID_ANY, "0�ź�����"); // Diamond
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
//    // �󶨲˵����¼�
//    parent->Bind(wxEVT_MENU, &Sidebar::OnNewFile, this, wxID_NEW);
//    parent->Bind(wxEVT_MENU, &Sidebar::OnOpenFile, this, wxID_OPEN);
//    parent->Bind(wxEVT_MENU, &Sidebar::OnSaveFile, this, wxID_SAVE);
//    parent->Bind(wxEVT_MENU, &Sidebar::OnSaveAsFile, this, wxID_SAVEAS);
//    parent->Bind(wxEVT_MENU, &Sidebar::OnCloseFile, this, wxID_CLOSE);
//    parent->Bind(wxEVT_MENU, &Sidebar::OnPrintFile, this, wxID_PRINT);
//    parent->Bind(wxEVT_MENU, &Sidebar::OnExit, this, wxID_EXIT);
//}

// ���캯������ʼ�����������󶨰�ť�¼�
Sidebar::Sidebar(wxFrame* parent, DrawingPanel* drawingPanel, int width)
    : wxPanel(parent, wxID_ANY), drawingPanel(drawingPanel) {
    SetMinSize(wxSize(width, -1)); // ������С���

    // �����˵���
    wxMenuBar* menuBar = new wxMenuBar();

    // ���� wxGrid �ؼ�
    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(3, 1); // ����һ�� 3 �� 1 �еı��
    grid->SetColLabelValue(0, "����");
    grid->SetRowLabelValue(0, "����");
    grid->SetRowLabelValue(1, "�������");
    grid->SetRowLabelValue(2, "�������");
    grid->SetRowLabelValue(3, "����");

    // ������ť
    wxButton* rectButton = new wxButton(this, wxID_ANY, "����"); // Rectangle
    wxButton* circleButton = new wxButton(this, wxID_ANY, "����"); // Circle
    wxButton* triangleButton = new wxButton(this, wxID_ANY, "����"); // Triangle
    wxButton* ellipseButton = new wxButton(this, wxID_ANY, "1�ź�����"); // Ellipse
    wxButton* diamondButton = new wxButton(this, wxID_ANY, "0�ź�����"); // Diamond

    // ������ť��ֱ����
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);//���ð�ť����ֱ��
    buttonSizer->Add(rectButton, 0, wxALL, 5);
    buttonSizer->Add(circleButton, 0, wxALL, 5);
    buttonSizer->Add(triangleButton, 0, wxALL, 5);
    buttonSizer->Add(ellipseButton, 0, wxALL, 5);
    buttonSizer->Add(diamondButton, 0, wxALL, 5);

    // ���ò���
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 5); // ��ť��������
    sizer->Add(grid, 1, wxEXPAND | wxALL, 5); // ���Ա��������
    SetSizer(sizer);

    // �����ļ��˵�
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(wxID_NEW, "&�½��ļ�\tCtrl+N");
    fileMenu->Append(wxID_OPEN, "&���ļ�\tCtrl+O");
    fileMenu->Append(wxID_SAVE, "&�����ļ�\tCtrl+S");
    fileMenu->Append(wxID_SAVEAS, "&���Ϊ�ļ�\tCtrl+Shift+S");
    fileMenu->Append(wxID_CLOSE, "&�ر��ļ�\tCtrl+W");
    fileMenu->Append(wxID_PRINT, "&��ӡ�ļ�\tCtrl+P");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "&�˳�����\tCtrl+Q");

    // ���ļ��˵���ӵ��˵���
    menuBar->Append(fileMenu, "&�ļ�");

    // ���������˵�
    wxMenu* helpMenu = new wxMenu();
    helpMenu->Append(wxID_ABOUT, "&����\tF1");

    // �������˵���ӵ��˵���
    menuBar->Append(helpMenu, "&����");

    // ���˵������õ�������
    parent->SetMenuBar(menuBar);

    // �󶨰�ť�¼�
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
    parent->Bind(wxEVT_MENU, &Sidebar::OnExit, this, wxID_EXIT);
}


void Sidebar::OnRectButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::AndGate, 50, 50);

    // ���� grid �еĵ�Ԫ������
    grid->SetCellValue(0, 0, "����");
    grid->SetCellValue(1, 0, "5");
    grid->SetCellValue(2, 0, "1");
    grid->SetCellValue(3, 0, "��Ϊ��ʱ���Ϊ��");
}

void Sidebar::OnCircleButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::OrGate, 150, 100);

    // ���� grid �еĵ�Ԫ������
    grid->SetCellValue(0, 0, "����");
    grid->SetCellValue(1, 0, "5");
    grid->SetCellValue(2, 0, "1");
    grid->SetCellValue(3, 0, "������ֵ���������");
}



void Sidebar::OnTriangleButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::NotGate, 50, 100);

    // ���� grid �еĵ�Ԫ������
    grid->SetCellValue(0, 0, "����");
    grid->SetCellValue(1, 0, "2");
    grid->SetCellValue(2, 0, "1");
    grid->SetCellValue(3, 0, "˫�ٳ���");
}



void Sidebar::OnEllipseButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::OnPin, 150, 150);

    // ���� grid �еĵ�Ԫ������
    grid->SetCellValue(0, 0, "���1");
    grid->SetCellValue(1, 0, "0");
    grid->SetCellValue(2, 0, "1");
    grid->SetCellValue(3, 0, "˫�ٳ���");
}


void Sidebar::OnDiamondButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::OffPin, 100, 150);
    //wxColor sidebarBackgroundColor = wxColour(192, 192, 192); // ʾ����ɫΪ��ɫ

    //// ��������Ĭ�ϵ�Ԫ��ı�����ɫ
    //grid->SetDefaultCellBackgroundColour(sidebarBackgroundColor);

    // ���� grid �еĵ�Ԫ������
    grid->SetCellValue(0, 0, "���0");
    grid->SetCellValue(1, 0, "0");
    grid->SetCellValue(2, 0, "1");
    grid->SetCellValue(3, 0, "˫�ٳ���");
}



// �˵����¼�������
void Sidebar::OnNewFile(wxCommandEvent& event) {
    // �½��ļ����߼�
    drawingPanel->Clear(); // ���� DrawingPanel ����һ�� Clear ����
    wxMessageBox("�½��ļ��Ѵ���", "��ʾ", wxOK | wxICON_INFORMATION);
}

void Sidebar::OnOpenFile(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, _("���ļ�"), "", "",
        "All files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // �û�ȡ��

    // ���ļ����߼�
    wxTextFile file;
    if (file.Open(openFileDialog.GetPath())) {
        drawingPanel->Clear();
        for (wxString str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine()) {
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

void Sidebar::OnSaveFile(wxCommandEvent& event) {
    // �����ļ����߼�
    wxFileDialog saveFileDialog(this, _("�����ļ�"), "", "",
        "All files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // �û�ȡ��

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
    wxFileDialog saveFileDialog(this, _("���Ϊ�ļ�"), "", "",
        "All files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // �û�ȡ��

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
    // �ر��ļ����߼�
    drawingPanel->Clear();
    wxMessageBox("�ļ��ѹر�", "��ʾ", wxOK | wxICON_INFORMATION);
}

void Sidebar::OnPrintFile(wxCommandEvent& event) {
    wxPrinter printer;
    wxPrintDialogData printDialogData(printer.GetPrintDialogData());
    wxPrintDialog printDialog(this, &printDialogData);

    if (printDialog.ShowModal() == wxID_OK) {
        // ��ӡ�ļ����߼�
        wxMessageBox("��ӡ�ļ�������δʵ��", "��ʾ", wxOK | wxICON_INFORMATION);
    }
}

void Sidebar::OnExit(wxCommandEvent& event) {
    Close(true); // �˳�����
}

// �������������ַ���ת��Ϊ ShapeType
ShapeType Sidebar::ShapeTypeFromString(const wxString& str) {
    if (str == "AndGate") return ShapeType::AndGate;
    if (str == "OrGate") return ShapeType::OrGate;
    if (str == "NotGate") return ShapeType::NotGate;
    if (str == "OnPin") return ShapeType::OnPin;
    if (str == "OffPin") return ShapeType::OffPin;
    // �����������
    return ShapeType::Unknown;
}

// ������������ ShapeType ת��Ϊ�ַ���
wxString Sidebar::ShapeTypeToString(ShapeType type) {
    switch (type) {
    case ShapeType::AndGate: return "AndGate";
    case ShapeType::OrGate: return "OrGate";
    case ShapeType::NotGate: return "NotGate";
    case ShapeType::OnPin: return "OnPin";
    case ShapeType::OffPin: return "OffPin";
        // �����������
    default: return "Unknown";
    }
}