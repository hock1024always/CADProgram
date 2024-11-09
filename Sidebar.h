#pragma once
#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <wx/wx.h>
#include "DrawingPanel.h"
#include <wx/grid.h>//��߿��ʾ������Ҫ

// ���� Sidebar �࣬�̳��� wxPanel��������ʾ������
class Sidebar : public wxPanel {
public:
    Sidebar(wxFrame* parent, DrawingPanel* drawingPanel, int width); // ���캯��

private:
    void OnRectButton(wxCommandEvent& event);      // �������ΰ�ť����¼�
    void OnCircleButton(wxCommandEvent& event);    // ����Բ�ΰ�ť����¼�
    void OnTriangleButton(wxCommandEvent& event);  // ���������ΰ�ť����¼�
    void OnEllipseButton(wxCommandEvent& event);    // ������Բ��ť����¼�
    void OnDiamondButton(wxCommandEvent& event);    // �������ΰ�ť����¼�

    void OnNewFile(wxCommandEvent& event);         // �����½��ļ��¼�
    void OnOpenFile(wxCommandEvent& event);        // �������ļ��¼�
    void OnSaveFile(wxCommandEvent& event);        // ���������ļ��¼�
    void OnSaveAsFile(wxCommandEvent& event);      // ��������Ϊ�ļ��¼�
    void OnCloseFile(wxCommandEvent& event);       // �����ر��ļ��¼�
    void OnPrintFile(wxCommandEvent& event);       // ������ӡ�ļ��¼�
    void OnExit(wxCommandEvent& event);            // �����˳������¼�

    static ShapeType ShapeTypeFromString(const wxString& str); // �������������ַ���ת��Ϊ ShapeType
    static wxString ShapeTypeToString(ShapeType type);         // ������������ ShapeType ת��Ϊ�ַ���

    //wxStaticText* infoText; // ������ʾ�ͷŵ�ͼ����Ϣ
    DrawingPanel* drawingPanel; // ָ���ͼ����ָ��
    wxGrid* grid; // ���� wxGrid ��Ա����
};

#endif // SIDEBAR_H