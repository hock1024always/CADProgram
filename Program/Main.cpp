#include <wx/wx.h>
#include "MainFrame.h"

// 定义 MyApp 类，继承自 wxApp，用于应用程序的入口
class MyApp : public wxApp {
public:
    // 应用程序初始化函数
    virtual bool OnInit() {
        MainFrame* frame = new MainFrame(); // 创建主窗口
        frame->Show(true);                  // 显示主窗口
        return true;                        // 返回 true 表示初始化成功
    }
};

// 实现应用程序入口
wxIMPLEMENT_APP(MyApp);