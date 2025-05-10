#include "Config.h"

Config::Config(IAIMPCore *core)
{
    if (FAILED(core->QueryInterface(IID_IAIMPConfig, reinterpret_cast<void **>(&m_config))))
    {
        throw std::runtime_error("Cannot get IAIMPConfig");
    }
}

std::wstring Config::get(const wchar_t *keyName)
{
    return get(std::wstring(keyName));
}

std::wstring Config::get(const std::wstring &keyName)
{
    IAIMPString *value = nullptr;

    if (FAILED(m_config->GetValueAsString(createKeyPath(keyName), &value)))
    {
        throw std::runtime_error("Failed to read string value from config");
    }

    std::wstring result(value->GetData());

    return result;
}

void Config::set(const wchar_t *keyName, const wchar_t *valueStr)
{
    return set(std::wstring(keyName), std::wstring(valueStr));
}

void Config::set(const std::wstring &keyName, const std::wstring &valueStr)
{
    if (FAILED(m_config->SetValueAsString(createKeyPath(keyName), AIMPString(valueStr))))
    {
        throw std::runtime_error("Failed to write string value to config");
    }
}

Config::~Config()
{
    if (m_config)
        m_config->Release();
}

IAIMPString *Config::createKeyPath(const std::wstring &keyName)
{
    return AIMPString(std::wstring(SectionName) + L"\\" + keyName);
}