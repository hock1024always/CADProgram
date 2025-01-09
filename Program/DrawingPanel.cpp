#include "DrawingPanel.h"
#include <cmath>  // 用于计算平方根和平方
#include <algorithm> // 用于 std::min 和 std::max
#include<fstream>
#include"nlohmann/json.hpp"
#include "MainFrame.h"
using json = nlohmann::json;
// 构造函数，初始化绘图面板并创建点状图
DrawingPanel::DrawingPanel(wxFrame* parent)
    : wxPanel(parent, wxID_ANY), pointGrid(this, 10) { // 设置点的间距为10像素
    Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &DrawingPanel::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &DrawingPanel::OnLeftUp, this);
    Bind(wxEVT_MOTION, &DrawingPanel::OnMotion, this);
}

void DrawingPanel::OnPaint(wxPaintEvent& event) {
    wxBufferedPaintDC dc(this);
    dc.Clear();

    pointGrid.Draw(dc); // 绘制点状图

    for (const auto& shape : shapes) {
        for (const auto& data : shape.data) {
            const std::string& color = data["color"];
            if (color == "yellow") {
                dc.SetPen(wxPen(wxColour(255, 255, 0))); // 黄色画笔
                dc.SetBrush(wxBrush(wxColour(255, 255, 0))); // 黄色画刷
            }
            if (color == "black") {
                dc.SetPen(*wxBLACK_PEN); // 恢复黑色画笔
                dc.SetBrush(*wxBLACK_BRUSH); // 恢复黑色画刷
            }
            if (color == "red") {
                dc.SetPen(*wxRED_PEN); // 恢复红色画笔
                dc.SetBrush(*wxRED_BRUSH); // 恢复红色画刷
            }
            if (color == "blue") {
                dc.SetPen(*wxBLUE_PEN); // 恢复蓝色画笔
                dc.SetBrush(*wxBLUE_BRUSH); // 恢复蓝色画刷
            }

            const std::string& type = data["type"];
            if (type == "Rectangle") {
                dc.DrawRectangle(data["x"] + shape.x, data["y"] + shape.y, data["width"], data["height"]);//门的左侧
            }
            if (type == "Arc") {
                dc.DrawArc(data["x1"] + shape.x, data["y1"] + shape.y, data["x2"] + shape.x, data["y2"] + shape.y, data["xc"] + shape.x, data["yc"] + shape.y);//门的右侧
            }
            if (type == "Circle") {
                dc.DrawCircle(data["x"] + shape.x, data["y"] + shape.y, data["radius"]);
            }
            if (type == "Polygon") {
                wxPoint points1[3] = {
                    wxPoint(shape.x + data["x1"], shape.y + data["y1"]),
                    wxPoint(shape.x + data["x2"], shape.y + data["y2"]),
                    wxPoint(shape.x + data["x3"], shape.y + data["y3"])
                };
                dc.DrawPolygon(3, points1);
            }
        }

        // 恢复默认的画笔和刷子，如果需要的话
        dc.SetPen(*wxBLACK_PEN);
        dc.SetBrush(*wxWHITE_BRUSH);
    }

    for (const auto& line : lines) {
        dc.DrawLine(line.startX, line.startY, line.endX, line.endY);
    }
}

// 检查是否在锚点的判断域内（圆形区域）
bool DrawingPanel::IsPointOnAnchor(int x, int y) {
    for (size_t i = 0; i < shapes.size(); ++i) {
        anchorPoints = shapes[i].getanchorPoints();
        for (const auto& anchor : anchorPoints) {
            // 计算点击点与锚点的距离
            double distance = std::sqrt(std::pow(x - anchor.x, 2) + std::pow(y - anchor.y, 2));

            // 如果距离小于等于锚点的判断域半径，则认为在锚点上
            if (distance <= anchorRadius) {
                return true;
            }
        }
    }
    return false;
}

// 处理鼠标左键按下事件
void DrawingPanel::OnLeftDown(wxMouseEvent& event) {
    // 获取鼠标当前的坐标
    int mouseX = event.GetX();
    int mouseY = event.GetY();

    // 将鼠标坐标对齐到点状网格（每10个像素一个点）
    SnapToPoint(mouseX, mouseY);

    // 检查是否点击在某个锚点的判断域内
    if (IsPointOnAnchor(mouseX, mouseY)) {
        // 如果点击在锚点上，记录锚点坐标为起点
        currentLine.startX = mouseX;
        currentLine.startY = mouseY;
        return; // 退出函数
    }

    // 遍历所有图形，检查鼠标是否在某个图形内部
    for (size_t i = 0; i < shapes.size(); ++i) {
        // 检查鼠标是否在第i个图形内
        if (IsPointInShape(mouseX, mouseY, shapes[i])) {
            // 如果鼠标在图形内，开始拖动该图形
            StartDrag(i, mouseX, mouseY);
            return; // 退出函数，因为已经开始拖动
        }
    }
    currentLine.startX = 0;
    currentLine.startY = 0;
    return;//两种情况都不是 标记为0

}//分为两种情况 在锚点上和在图形上

// 处理鼠标左键释放事件
void DrawingPanel::OnLeftUp(wxMouseEvent& event) {
    // 如果当前正在拖动图形，结束拖动
    if (dragging) {
        dragging = false; // 结束拖动状态
    }
    else {
        if (currentLine.startX != 0 || currentLine.startY != 0) {//说明起始点在锚点上，处理线的绘制
            int endX = event.GetX(); // 记录线的终点
            int endY = event.GetY();

            // 将终点坐标对齐到点状网格
            SnapToPoint(endX, endY);
            //保存当前状态到回退堆栈
            undoStack.push_back({ shapes, lines });
            redoStack.clear();

            // 计算最多三条平行于网格边的线段
            std::vector<Line> segments = CalculateSegments(currentLine.startX, currentLine.startY, endX, endY);
            // 将计算出的线段添加到线段列表中
            lines.insert(lines.end(), segments.begin(), segments.end());
        }
    }
    // 刷新面板以更新显示
    Refresh();
}

// 处理鼠标移动事件
void DrawingPanel::OnMotion(wxMouseEvent& event) {
    // 如果当前处于拖动状态
    if (dragging) {
        // 更新被拖动图形的坐标
        shapes[dragIndex].x = event.GetX() - dragOffsetX;
        shapes[dragIndex].y = event.GetY() - dragOffsetY;
        // 将图形坐标对齐到点状网格
        SnapToPoint(shapes[dragIndex].x, shapes[dragIndex].y);
        // 刷新面板以更新显示
        Refresh();
    }
    else if (event.Dragging()) { // 如果没有拖动图形，但鼠标在拖动中（绘制线过程）
        // 更新当前正在绘制的线的终点坐标
        currentLine.endX = event.GetX();
        currentLine.endY = event.GetY();
        // 将终点坐标对齐到点状网格
        SnapToPoint(currentLine.endX, currentLine.endY);
        // 刷新面板以更新显示
        Refresh();
    }
}

// 将坐标对齐到点状网格
void DrawingPanel::SnapToPoint(int& x, int& y) {
    // 将 x 和 y 坐标对齐到最近的网格点（每10个像素一个点）
    x = (x / 15) * 15;
    y = (y / 15) * 15;
}

// 计算最多三条平行于网格边的线段
std::vector<Line> DrawingPanel::CalculateSegments(int startX, int startY, int endX, int endY) {
    std::vector<Line> segments;

    // 计算水平和垂直距离
    int dx = endX - startX;
    int dy = endY - startY;

    // 如果已经是一条水平或垂直线，直接返回
    if (dx == 0 || dy == 0) {
        segments.push_back({ startX, startY, endX, endY });
        return segments;
    }

    // 计算中点
    int midX = startX + dx / 2;

    // 对齐到网格
    SnapToPoint(midX, startY);
    SnapToPoint(midX, endY);

    // 添加三条线段
    segments.push_back({ startX, startY, midX, startY }); // 线段1：(a, b) -> (midx, b)
    segments.push_back({ midX, startY, midX, endY });   // 线段2：(midx, b) -> (midx, d)
    segments.push_back({ midX, endY, endX, endY });     // 线段3：(midx, d) -> (c, d)

    return segments;
}

// 开始拖动某个图形
void DrawingPanel::StartDrag(int index, int x, int y) {
    // 记录当前拖动的图形索引
    dragIndex = index;
    // 计算鼠标相对于图形左上角的偏移量
    dragOffsetX = x - shapes[index].x;
    dragOffsetY = y - shapes[index].y;
    // 设置拖动状态
    dragging = true;
}

// 检查点是否在图形内
bool DrawingPanel::IsPointInShape(int x, int y, const Shape& shape) {
    switch (shape.type) {
    case ShapeType::AndGate: {
        // 正方形的左上角为 (shape.x, shape.y)，宽高为 40
        return x >= shape.x - 22 && x <= shape.x + 30 && y >= shape.y - 45 && y <= shape.y + 45;
    }

    case ShapeType::OrGate: {
        // 圆的中心为 (shape.x , shape.y )，半径为 20
        return x >= shape.x - 7 && x <= shape.x + 38 && y >= shape.y - 30 && y <= shape.y + 30;
    }

    case ShapeType::NotGate: {
        return x >= shape.x - 22 && x <= shape.x + 8 && y >= shape.y - 15 && y <= shape.y + 15;
    }

    case ShapeType::OnPin: {
        return x >= shape.x - 8 && x <= shape.x + 15 && y >= shape.y - 15 && y <= shape.y + 15;
    }

    case ShapeType::OffPin: {
        return x >= shape.x - 15 && x <= shape.x + 8 && y >= shape.y - 15 && y <= shape.y + 15;
    }

    default:
        return false;
    }
}

// 清除所有图形
void DrawingPanel::Clear() {
    undoStack.push_back({ shapes, lines });
    redoStack.clear();
    shapes.clear();
    lines.clear();
    Refresh();
}
//回退操作
void DrawingPanel::Undo() {
    if (!undoStack.empty()) {
        redoStack.push_back({ shapes, lines });
        auto state = undoStack.back();
        shapes = state.first;
        lines = state.second;
        undoStack.pop_back();
        Refresh();
    }
}

// 前进操作
void DrawingPanel::Redo() {
    if (!redoStack.empty()) {
        undoStack.push_back({ shapes, lines });
        auto state = redoStack.back();
        shapes = state.first;
        lines = state.second;
        redoStack.pop_back();
        Refresh();
    }
}

// 获取所有图形
const std::vector<Shape>& DrawingPanel::GetShapes() const {
    return shapes;
}

json LoadFromJSON(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        json data;
        file >> data;
        file.close();
        return data;
    } else {
        wxMessageBox("Failed to open file", "Error", wxICON_ERROR);
    }
}

// 添加新的图形
void DrawingPanel::AddShape(ShapeType type, int x, int y) {
    // 保存当前状态到撤销堆栈
    undoStack.push_back({ shapes, lines });
    redoStack.clear();
    // 将新图形添加到图形列表中
    wxString file = ShapeTypeToString(type);
    std::string filename = "json/" + std::string(file.mb_str()) + ".json";
    json data = LoadFromJSON(filename);
    shapes.push_back({ data,type, x, y });
    // 刷新面板以更新显示
    Refresh();
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
