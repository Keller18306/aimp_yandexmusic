#include "AIMPString.h"
#include "../Plugin.h"

AIMPString::AIMPString()
{
    if (SUCCEEDED(Plugin::getAIMPCore()->CreateObject(IID_IAIMPString, reinterpret_cast<void **>(&m_string))))
    {
        m_string->AddRef();
    }
}

AIMPString::AIMPString(const std::wstring &string)
{
    if (SUCCEEDED(Plugin::getAIMPCore()->CreateObject(IID_IAIMPString, reinterpret_cast<void **>(&m_string))))
    {
        m_string->AddRef();
        m_string->SetData(const_cast<wchar_t *>(string.data()), string.size());
    }
}

AIMPString::AIMPString(const wchar_t *string)
{
    if (SUCCEEDED(Plugin::getAIMPCore()->CreateObject(IID_IAIMPString, reinterpret_cast<void **>(&m_string))))
    {
        m_string->AddRef();
        m_string->SetData(const_cast<wchar_t *>(string), wcslen(string));
    }
}

AIMPString::~AIMPString()
{
    if (m_string)
        m_string->Release();
}