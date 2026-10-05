#include <gui/i18n.h>
#include <unordered_map>

namespace gui::i18n {
    static std::string currentLanguage = "zh-CN";

    static const std::unordered_map<std::string, std::string> zh = {
        {"Source", "信号源"},
        {"Sinks", "输出"},
        {"Band Plan", "频段计划"},
        {"Display", "显示"},
        {"Theme", "主题"},
        {"VFO Color", "VFO颜色"},
        {"Module Manager", "模块管理"},
        {"Language", "语言"},
        {"Chinese", "中文"},
        {"English", "English"},
        {"Main", "主界面"},
        {"Debug", "调试"},
        {"Frame time: %.3f ms/frame", "帧时间：%.3f 毫秒/帧"},
        {"Framerate: %.1f FPS", "帧率：%.1f FPS"},
        {"Center Frequency: %.0f Hz", "中心频率：%.0f Hz"},
        {"Source name: %s", "信号源名称：%s"},
        {"Show demo window", "显示 ImGui 演示窗口"},
        {"ImGui version: %s", "ImGui 版本：%s"},
        {"Test Bug", "测试错误"},
        {"Testing something", "测试功能"},
        {"WF Single Click", "瀑布图单击调谐"},
        {"Lock Menu Order", "锁定菜单顺序"},
        {"Zoom", "缩放"},
        {"Max", "最大值"},
        {"Min", "最小值"},
        {"Initializing UI", "正在初始化界面"},
        {"Loading modules", "正在加载模块"},
        {"Loading color maps", "正在加载颜色映射"},
        {"Loading configuration", "正在加载配置"},
        {"Direct Sampling", "直接采样"},
        {"PPM Correction", "PPM 频率校正"},
        {"Gain", "增益"},
        {"Theme", "主题"},
        {"Source", "信号源"},
        {"Sinks", "输出"},
        {"Band Plan", "频段计划"},
        {"Display", "显示"}
    };

    void setLanguage(const std::string& language) {
        currentLanguage = (language == "zh-CN" || language == "zh") ? "zh-CN" : "en";
    }

    const std::string& getLanguage() {
        return currentLanguage;
    }

    bool isChinese() {
        return currentLanguage == "zh-CN";
    }

    const char* tr(const char* text) {
        if (!isChinese()) {
            return text;
        }
        auto it = zh.find(text);
        return it == zh.end() ? text : it->second.c_str();
    }

    std::string tr(const std::string& text) {
        return std::string(tr(text.c_str()));
    }
}
