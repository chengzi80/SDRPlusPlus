#include <gui/style.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <config.h>
#include <utils/flog.h>
#include <filesystem>

namespace style {
    ImFont* baseFont;
    ImFont* bigFont;
    ImFont* hugeFont;
    ImVector<ImWchar> baseRanges;
    ImVector<ImWchar> bigRanges;
    ImVector<ImWchar> hugeRanges;

#ifndef __ANDROID__
    float uiScale = 1.0f;
#else
    float uiScale = 3.0f;
#endif

    bool loadFonts(std::string resDir) {
        ImFontAtlas* fonts = ImGui::GetIO().Fonts;
        if (!std::filesystem::is_directory(resDir)) {
            flog::error("Invalid resource directory: {0}", resDir);
            return false;
        }

        // Include Latin, Cyrillic and common Simplified Chinese glyphs.
        ImFontGlyphRangesBuilder baseBuilder;
        baseBuilder.AddRanges(fonts->GetGlyphRangesDefault());
        baseBuilder.AddRanges(fonts->GetGlyphRangesCyrillic());
        baseBuilder.AddRanges(fonts->GetGlyphRangesChineseSimplifiedCommon());
        baseBuilder.BuildRanges(&baseRanges);

        ImFontGlyphRangesBuilder bigBuilder;
        const ImWchar bigRange[] = { '.', '9', 0 };
        bigBuilder.AddRanges(bigRange);
        bigBuilder.BuildRanges(&bigRanges);

        ImFontGlyphRangesBuilder hugeBuilder;
        const ImWchar hugeRange[] = { 'S', 'S', 'D', 'D', 'R', 'R', '+', '+', ' ', ' ', 0 };
        hugeBuilder.AddRanges(hugeRange);
        hugeBuilder.BuildRanges(&hugeRanges);

        std::string regularFont = resDir + "/fonts/Roboto-Medium.ttf";
        std::string cjkFont;
#ifdef _WIN32
        const char* cjkCandidates[] = {
            "C:/Windows/Fonts/msyh.ttc",
            "C:/Windows/Fonts/msyhbd.ttc"
        };
#elif defined(__ANDROID__)
        const char* cjkCandidates[] = {
            "/system/fonts/NotoSansCJK-Regular.ttc",
            "/system/fonts/NotoSansCJK-VF.ttc"
        };
#else
        const char* cjkCandidates[] = {
            "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",
            "/usr/share/fonts/noto-cjk/NotoSansCJK-Regular.ttc",
            "/usr/share/fonts/truetype/noto/NotoSansCJK-Regular.ttc"
        };
#endif
        for (const char* candidate : cjkCandidates) {
            if (std::filesystem::exists(candidate)) {
                cjkFont = candidate;
                break;
            }
        }

        if (!cjkFont.empty()) {
            ImFontConfig cjkConfig;
            cjkConfig.FontNo = 0;
            baseFont = fonts->AddFontFromFileTTF(cjkFont.c_str(), 16.0f * uiScale, &cjkConfig, baseRanges.Data);
            bigFont = fonts->AddFontFromFileTTF(cjkFont.c_str(), 45.0f * uiScale, &cjkConfig, bigRanges.Data);
            hugeFont = fonts->AddFontFromFileTTF(cjkFont.c_str(), 128.0f * uiScale, &cjkConfig, hugeRanges.Data);
            flog::info("Loaded CJK font: {0}", cjkFont);
        }
        else {
            baseFont = fonts->AddFontFromFileTTF(regularFont.c_str(), 16.0f * uiScale, NULL, baseRanges.Data);
            bigFont = fonts->AddFontFromFileTTF(regularFont.c_str(), 45.0f * uiScale, NULL, bigRanges.Data);
            hugeFont = fonts->AddFontFromFileTTF(regularFont.c_str(), 128.0f * uiScale, NULL, hugeRanges.Data);
            flog::warn("CJK font not found, Chinese text may not render correctly");
        }

        return baseFont != NULL && bigFont != NULL && hugeFont != NULL;
    }

    void beginDisabled() {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        auto& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;
        ImVec4 btnCol = colors[ImGuiCol_Button];
        ImVec4 frameCol = colors[ImGuiCol_FrameBg];
        ImVec4 textCol = colors[ImGuiCol_Text];
        btnCol.w = 0.15f;
        frameCol.w = 0.30f;
        textCol.w = 0.65f;
        ImGui::PushStyleColor(ImGuiCol_Button, btnCol);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, frameCol);
        ImGui::PushStyleColor(ImGuiCol_Text, textCol);
    }

    void endDisabled() {
        ImGui::PopItemFlag();
        ImGui::PopStyleColor(3);
    }
}

namespace ImGui {
    void LeftLabel(const char* text) {
        float vpos = ImGui::GetCursorPosY();
        ImGui::SetCursorPosY(vpos + GImGui->Style.FramePadding.y);
        ImGui::TextUnformatted(text);
        ImGui::SameLine();
        ImGui::SetCursorPosY(vpos);
    }

    void FillWidth() {
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    }
}
