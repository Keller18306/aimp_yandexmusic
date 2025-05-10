#include "AIMPString.h"
#include "../Plugin.h"
#include <stdexcept>

AIMPString AIMPString::fromPropertyList(IAIMPPropertyList *list, int propertyId)
{
    IAIMPString *str = nullptr;

    if (FAILED(list->GetValueAsObject(propertyId, IID_IAIMPString, reinterpret_cast<void **>(&str))))
    {
        throw std::runtime_error("Cannot get AIMPString from propterty list");
    }

    return AIMPString(str);
}

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