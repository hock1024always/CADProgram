#ifndef POINTGRID_H
#define POINTGRID_H

#include <wx/wx.h>
#include <wx/dcbuffer.h> // ������ͷ�ļ���ʹ�� wxBufferedPaintDC

// ���� PointGrid �࣬���ڻ������񱳾�
class PointGrid {
public:
    PointGrid(); // Ĭ�Ϲ��캯��
    PointGrid(wxPanel* panel, int spacing);
    void Draw(wxBufferedPaintDC& dc);

    void SetPanel(wxPanel* panel); // �������
    void SetSpacing(int spacing);  // ���ü��

private:
    wxPanel* panel; // ָ���ͼ����ָ��
    int spacing;    // ����ļ��
};

#endif // POINTGRID_H