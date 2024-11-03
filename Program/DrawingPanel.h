#pragma once
#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include <wx/wx.h>
#include <vector>
#include "Shape.h"
#include "PointGrid.h"
#include <cmath>  // ���ڼ���ƽ������ƽ��



// ���� DrawingPanel �࣬�̳��� wxPanel�����ڴ����ͼ�¼�
class DrawingPanel : public wxPanel {
public:
    DrawingPanel(wxFrame* parent); // ���캯��

    void OnPaint(wxPaintEvent& event); // �����ͼ�¼�
    void OnLeftDown(wxMouseEvent& event); // ���������������¼�
    void OnLeftUp(wxMouseEvent& event); // �����������ͷ��¼�
    void OnMotion(wxMouseEvent& event); // ��������ƶ��¼�
    void AddShape(ShapeType type, int x, int y); // ���ͼ�ε�����
    void Clear(); // �������ͼ��
    const std::vector<Shape>& GetShapes() const; // ��ȡ����ͼ��

private:
    PointGrid pointGrid; // ��״ͼ�Ķ���
    std::vector<Shape> shapes; // �洢����ͼ�ε��б�
    std::vector<Line> lines; // �洢�����������б�
    std::vector<AnchorPoint> anchorPoints; // �洢ê����б�
    Line currentLine; // ��ǰ���ڻ��Ƶ�����
    bool dragging = false; // �Ƿ������϶�ͼ�εı�־
    int dragIndex = -1; // ��ǰ�϶���ͼ������
    int dragOffsetX = 0, dragOffsetY = 0; // �϶�ͼ�ε�ƫ����

    // ����������ê����ж���뾶
    const int anchorRadius = 4;

    void StartDrag(int index, int x, int y); // ��ʼ�϶�ͼ��
    bool IsPointInShape(int x, int y, const Shape& shape); // ��������λ���Ƿ���ͼ����
    bool IsPointOnAnchor(int x, int y); // �����Ƿ���ê����

    void SnapToPoint(int& x, int& y); // ��������뵽����ĵ�״ͼ��
    std::vector<Line> CalculateSegments(int startX, int startY, int endX, int endY); // �����������ƽ��������ߵ��߶�

};

#endif // DRAWINGPANEL_H