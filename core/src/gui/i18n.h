#pragma once
#include <string>

namespace gui::i18n {
    void setLanguage(const std::string& language);
    const std::string& getLanguage();
    bool isChinese();
    const char* tr(const char* text);
    std::string tr(const std::string& text);
}
