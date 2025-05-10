#pragma once
#include <string>
#include "aimp_sdk/apiObjects.h"

class AIMPString
{
public:
    static AIMPString fromPropertyList(IAIMPPropertyList *list, int propertyId);

    AIMPString();
    AIMPString(IAIMPString *string) : m_string(string) {}
    AIMPString(const std::wstring &string);
    AIMPString(const wchar_t *string);
    ~AIMPString();

    operator IAIMPString *() { return m_string; }
    IAIMPString *operator->() { return m_string; }

private:
    IAIMPString *m_string;
};