#include "Sidebar.h"
#include "DrawingPanel.h"
#include "Shape.h"
#include <wx/filedlg.h>
#include <wx/print.h>
#include <wx/printdlg.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h> // ���� wxStringTokenizer ͷ�ļ�
#include <string> //�ַ���
//using namespace std;
// ���캯������ʼ�����������󶨰�ť�¼�
Sidebar::Sidebar(wxFrame* parent, DrawingPanel* drawingPanel, int width)
    : wxPanel(parent, wxID_ANY), drawingPanel(drawingPanel) {
    SetMinSize(wxSize(width, -1)); // ������С���

    // �����˵���
    wxMenuBar* menuBar = new wxMenuBar();

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

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxButton* rectButton = new wxButton(this, wxID_ANY, "����"); // Rectangle
    wxButton* circleButton = new wxButton(this, wxID_ANY, "����"); // Circle
    wxButton* triangleButton = new wxButton(this, wxID_ANY, "����"); // Triangle
    wxButton* ellipseButton = new wxButton(this, wxID_ANY, "1�ź�����"); // Ellipse
    wxButton* diamondButton = new wxButton(this, wxID_ANY, "0�ź�����"); // Diamond

    // ������̬�ı���������ʾͼ���ͷ���Ϣ
    infoText = new wxStaticText(this, wxID_ANY, "Ԫ�����Ա�");
    infoText->SetMinSize(wxSize(-1, 50)); // �����ı��������С�߶�

    sizer->Add(rectButton, 0, wxALL, 5);
    sizer->Add(circleButton, 0, wxALL, 5);
    sizer->Add(triangleButton, 0, wxALL, 5);
    sizer->Add(ellipseButton, 0, wxALL, 5);
    sizer->Add(diamondButton, 0, wxALL, 5);
    sizer->Add(infoText, 0, wxALL | wxEXPAND, 5); // �����Ϣ��ʾ����

    SetSizer(sizer);

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
    wxString info = "����: ����\n�������: 2\n�������: 1\n����: ˫�����";
    infoText->SetLabel(info);
}

void Sidebar::OnCircleButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::OrGate, 150, 100);
    infoText->SetLabel("����: ����\n�������: 2\n�������: 1\n����: �������");
}

void Sidebar::OnTriangleButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::NotGate, 50, 100);
    infoText->SetLabel("����: ����\n�������: 2\n�������: 1\n����: ˫�ٳ���");
}

void Sidebar::OnEllipseButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::OnPin, 150, 150);
    infoText->SetLabel("����: 1�����豸\n�������: 0\n�������: 1\n����: ���1");
}

void Sidebar::OnDiamondButton(wxCommandEvent& event) {
    drawingPanel->AddShape(ShapeType::OffPin, 100, 150);
    infoText->SetLabel("����: 0�����豸\n�������: 0\n�������: 1\n����: ���0");
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
ShapeType ShapeTypeFromString(const wxString& str) {
    if (str == "AndGate") return ShapeType::AndGate;
    if (str == "OrGate") return ShapeType::OrGate;
    if (str == "NotGate") return ShapeType::NotGate;
    if (str == "OnPin") return ShapeType::OnPin;
    if (str == "OffPin") return ShapeType::OffPin;
    // �����������
    return ShapeType::Unknown;
}

// ������������ ShapeType ת��Ϊ�ַ���
wxString ShapeTypeToString(ShapeType type) {
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

// ����µ�ͼ��
void DrawingPanel::AddShape(ShapeType type, int x, int y) {
    // ����ͼ����ӵ�ͼ���б���
    shapes.push_back({ type, x, y });
    wxString file = ShapeTypeToString(type);
    std::string filename = std::string(file.mb_str()) + ".json";
        //LoadFromJSON(filename);
        // ˢ������Ը�����ʾ
        Refresh();
}