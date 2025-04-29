#pragma once

#include <string>

#include "apiObjects.h"

class AIMPString
{
public:
    AIMPString();
    AIMPString(const std::wstring &string);
    AIMPString(const wchar_t *string);
    ~AIMPString();

    operator IAIMPString *() { return m_string; }
    IAIMPString *operator->() { return m_string; }

private:
    IAIMPString *m_string;
};