#pragma once

#include <stdexcept>
#include <string>
#include "aimp_sdk/apiCore.h"
#include "helpers/AIMPString.h"

class Config
{
public:
    Config(IAIMPCore *core);
    ~Config();

    std::wstring get(const wchar_t *keyName);
    std::wstring get(const std::wstring &keyName);

    void set(const wchar_t *keyName, const wchar_t *valueStr);
    void set(const std::wstring &keyName, const std::wstring &valueStr);


private:
    IAIMPConfig *m_config;

    static constexpr const wchar_t *SectionName = L"YandexMusic";

    IAIMPString *createKeyPath(const std::wstring &keyName);
};
