#include "OptionsDialog.h"
#include "helpers/AIMPString.h"
#include "helpers/CallbackChangeHandler.h"
#include "Plugin.h"

HRESULT OptionsDialog::RegisterExtension(IAIMPCore *core)
{
    IAIMPServiceOptionsDialog *dialogService = nullptr;

    if (FAILED(core->QueryInterface(IID_IAIMPServiceOptionsDialog, reinterpret_cast<void **>(&dialogService))))
    {
        throw std::runtime_error("Cannot get dialog service");
    }

    return core->RegisterExtension(IID_IAIMPServiceOptionsDialog, static_cast<IAIMPOptionsDialogFrame *>(new OptionsDialog(dialogService)));
}

HRESULT WINAPI OptionsDialog::GetName(IAIMPString **S)
{
    AIMPString str(L"TestSettings");

    str->AddRef();
    *S = str;

    return S_OK;
}

HWND WINAPI OptionsDialog::CreateFrame(HWND ParentWnd)
{
    Plugin::getAIMPCore()->QueryInterface(IID_IAIMPServiceUI, reinterpret_cast<void **>(&ui));
    ui->CreateForm(ParentWnd, AIMPUI_SERVICE_CREATEFORM_FLAGS_CHILD, nullptr, nullptr, &form);

    IAIMPUIGroupBox *groupBox = _createControl<IAIMPUIGroupBox>(form, IID_IAIMPUIGroupBox, AIMPString(L"Group"));

    auto handler = new CallbackChangeHandler([&]()
                                             { m_service->FrameModified(this); });

    tokenEdit = _createControl<IAIMPUIEdit>(groupBox, IID_IAIMPUIEdit, AIMPString(L"TokenEdit"), handler);

    return form->GetHandle();
}

void WINAPI OptionsDialog::DestroyFrame()
{
}

void WINAPI OptionsDialog::Notification(int ID)
{
    switch (ID)
    {
    case AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_RESET:
        break;

    case AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_LOAD:
    {
        std::wstring token = Plugin::config->get(L"token");
        tokenEdit->SetValueAsObject(AIMPUI_BASEEDIT_PROPID_TEXT, AIMPString(token));

        break;
    }

    case AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_SAVE:
    {
        wchar_t *data = AIMPString::fromPropertyList(tokenEdit, AIMPUI_BASEEDIT_PROPID_TEXT)->GetData();
        Plugin::config->set(L"token", data);

        break;
    }
    }
}

OptionsDialog::~OptionsDialog()
{
    if (m_service)
        m_service->Release();

    if (ui)
        ui->Release();
}