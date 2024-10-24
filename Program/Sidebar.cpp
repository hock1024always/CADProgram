#include "Sidebar.h"

// ���캯������ʼ�����������󶨰�ť�¼�
Sidebar::Sidebar(wxFrame* parent, DrawingPanel* drawingPanel, int width)
    : wxPanel(parent, wxID_ANY), drawingPanel(drawingPanel) {
    SetMinSize(wxSize(width, -1)); // ������С���

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