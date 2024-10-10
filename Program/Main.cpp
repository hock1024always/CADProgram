#include <wx/wx.h>       // ���� wxWidgets ���ͷ�ļ�
#include <wx/sizer.h>    // ���� wxSizer ���ͷ�ļ�
#include <wx/dcbuffer.h> // ���� wxBufferedPaintDC ���ͷ�ļ�
#include <vector>        // ������׼��� vector ����

// ���� ShapeType ö�����ͣ���ʾͼ������
enum class ShapeType { Rectangle, Circle };

// ���� Shape �ṹ�壬��ʾͼ�ε�λ�ú�����
struct Shape {
    ShapeType type; // ͼ�ε����ͣ����λ�Բ�Σ�
    int x, y;       // ͼ�ε�λ������
};

// ���� Line �ṹ�壬��ʾ�����������յ�
struct Line {
    int startX, startY, endX, endY; // �����������յ�����
};

// ���� DrawingPanel �࣬�̳��� wxPanel�����ڴ����ͼ�¼�
class DrawingPanel : public wxPanel {
public:
    // ���캯������ʼ����岢���¼�������
    DrawingPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY) {
        Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);         // �󶨻�ͼ�¼�
        Bind(wxEVT_LEFT_DOWN, &DrawingPanel::OnLeftDown, this);  // �������������¼�
        Bind(wxEVT_LEFT_UP, &DrawingPanel::OnLeftUp, this);      // ���������ͷ��¼�
        Bind(wxEVT_MOTION, &DrawingPanel::OnMotion, this);       // ������ƶ��¼�
    }

    // �����ͼ�¼�������ͼ�κ�����
    void OnPaint(wxPaintEvent& event) {
        wxBufferedPaintDC dc(this); // ʹ��˫�����ͼ�Ա�����˸
        dc.Clear();                 // ��ջ�ͼ����

        // ��������ͼ��
        for (const auto& shape : shapes) {
            if (shape.type == ShapeType::Rectangle) {
                dc.DrawRectangle(shape.x, shape.y, 50, 50); // ���ƾ���
            }
            else if (shape.type == ShapeType::Circle) {
                dc.DrawCircle(shape.x, shape.y, 25);        // ����Բ��
            }
        }

        // ������������
        for (const auto& line : lines) {
            dc.DrawLine(line.startX, line.startY, line.endX, line.endY); // ��������
        }
    }

    // ���������������¼�
    void OnLeftDown(wxMouseEvent& event) {
        int mouseX = event.GetX(); // ��ȡ������� X ����
        int mouseY = event.GetY(); // ��ȡ������� Y ����

        // ����Ƿ�����ĳ��ͼ��
        for (size_t i = 0; i < shapes.size(); ++i) {
            if (IsPointInShape(mouseX, mouseY, shapes[i])) {
                StartDrag(i, mouseX, mouseY); // ��ʼ�϶�ͼ��
                return;
            }
        }

        // ���û�е��ͼ�Σ���ʼ��������
        currentLine.startX = mouseX; // �������������Ϊ�����λ��
        currentLine.startY = mouseY;
    }

    // �����������ͷ��¼�
    void OnLeftUp(wxMouseEvent& event) {
        if (dragging) {
            dragging = false; // ����ͼ���϶�
        }
        else {
            // ������������
            currentLine.endX = event.GetX(); // �����������յ�Ϊ����ͷ�λ��
            currentLine.endY = event.GetY();
            lines.push_back(currentLine);    // ��������ӵ������б���
        }
        Refresh(); // ˢ����������»���
    }

    // ��������ƶ��¼�
    void OnMotion(wxMouseEvent& event) {
        if (dragging) {
            // �϶�ͼ��
            shapes[dragIndex].x = event.GetX() - dragOffsetX; // ����ͼ��λ��
            shapes[dragIndex].y = event.GetY() - dragOffsetY;
            Refresh(); // ˢ����������»���
        }
        else if (event.Dragging()) {
            // ��������
            currentLine.endX = event.GetX(); // �����������յ�
            currentLine.endY = event.GetY();
            Refresh(); // ˢ����������»���
        }
    }

    // ���ͼ�ε�����
    void AddShape(ShapeType type, int x, int y) {
        shapes.push_back({ type, x, y }); // ��ͼ����ӵ�ͼ���б���
        Refresh(); // ˢ����������»���
    }

    // ��ʼ�϶�ͼ��
    void StartDrag(int index, int x, int y) {
        dragIndex = index;                      // ���õ�ǰ�϶���ͼ������
        dragOffsetX = x - shapes[index].x;      // �����϶�ƫ����
        dragOffsetY = y - shapes[index].y;
        dragging = true;                        // ����Ϊ�����϶�״̬
    }

private:
    std::vector<Shape> shapes; // �洢����ͼ�ε��б�
    std::vector<Line> lines;   // �洢�����������б�
    Line currentLine;          // ��ǰ���ڻ��Ƶ�����
    bool dragging = false;     // �Ƿ������϶�ͼ�εı�־
    int dragIndex = -1;        // ��ǰ�϶���ͼ������
    int dragOffsetX = 0, dragOffsetY = 0; // �϶�ͼ�ε�ƫ����

    // ��������λ���Ƿ���ͼ����
    bool IsPointInShape(int x, int y, const Shape& shape) {
        if (shape.type == ShapeType::Rectangle) {
            // �����Ƿ��ھ�����
            return x >= shape.x && x <= shape.x + 50 && y >= shape.y && y <= shape.y + 50;
        }
        else if (shape.type == ShapeType::Circle) {
            // �����Ƿ���Բ����
            return (x - (shape.x + 25)) * (x - (shape.x + 25)) + (y - (shape.y + 25)) * (y - (shape.y + 25)) <= 25 * 25;
        }
        return false;
    }
};

// ���� Sidebar �࣬�̳��� wxPanel��������ʾ������
class Sidebar : public wxPanel {
public:
    // ���캯������ʼ�����������󶨰�ť�¼�
    Sidebar(wxFrame* parent, DrawingPanel* drawingPanel) : wxPanel(parent, wxID_ANY), drawingPanel(drawingPanel) {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL); // ������ֱ���ֵ� sizer

        wxButton* rectButton = new wxButton(this, wxID_ANY, "Rectangle"); // �������ΰ�ť
        wxButton* circleButton = new wxButton(this, wxID_ANY, "Circle");   // ����Բ�ΰ�ť

        sizer->Add(rectButton, 0, wxALL, 5);  // �����ΰ�ť��ӵ� sizer
        sizer->Add(circleButton, 0, wxALL, 5); // ��Բ�ΰ�ť��ӵ� sizer

        SetSizer(sizer); // �������� sizer

        rectButton->Bind(wxEVT_BUTTON, &Sidebar::OnRectButton, this);  // �󶨾��ΰ�ť�¼�
        circleButton->Bind(wxEVT_BUTTON, &Sidebar::OnCircleButton, this); // ��Բ�ΰ�ť�¼�
    }

    // ������ΰ�ť����¼�
    void OnRectButton(wxCommandEvent& event) {
        drawingPanel->AddShape(ShapeType::Rectangle, 50, 50); // ��Ӿ���
    }

    // ����Բ�ΰ�ť����¼�
    void OnCircleButton(wxCommandEvent& event) {
        drawingPanel->AddShape(ShapeType::Circle, 50, 50); // ���Բ��
    }

private:
    DrawingPanel* drawingPanel; // ָ���ͼ����ָ��
};

// ���� MainFrame �࣬�̳��� wxFrame�����ڴ���������
class MainFrame : public wxFrame {
public:
    // ���캯������ʼ�������ڲ����ò���
    MainFrame() : wxFrame(nullptr, wxID_ANY, "wxWidgets Drawing App") {
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL); // ����ˮƽ���ֵ� sizer

        drawingPanel = new DrawingPanel(this); // ������ͼ���
        sidebar = new Sidebar(this, drawingPanel); // ����������

        sizer->Add(sidebar, 0, wxEXPAND | wxALL, 5);  // ����������ӵ� sizer
        sizer->Add(drawingPanel, 1, wxEXPAND | wxALL, 5); // ����ͼ�����ӵ� sizer

        SetSizerAndFit(sizer); // ���� sizer ���������ڴ�С
        SetSize(800, 600);     // ���ô��ڴ�С
    }

private:
    DrawingPanel* drawingPanel; // ָ���ͼ����ָ��
    Sidebar* sidebar;           // ָ�򹤾�����ָ��
};

// ���� MyApp �࣬�̳��� wxApp������Ӧ�ó�������
class MyApp : public wxApp {
public:
    // Ӧ�ó����ʼ������
    virtual bool OnInit() {
        MainFrame* frame = new MainFrame(); // ����������
        frame->Show(true);                  // ��ʾ������
        return true;                        // ���� true ��ʾ��ʼ���ɹ�
    }
};

// ʵ��Ӧ�ó������
wxIMPLEMENT_APP(MyApp);