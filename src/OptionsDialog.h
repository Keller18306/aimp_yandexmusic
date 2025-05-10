#include "helpers/IUnknownBridge.h"
#include "aimp_sdk/apiOptions.h"
#include "aimp_sdk/apiGUI.h"
#include <stdexcept>

class OptionsDialog : public IUnknownBridge<IAIMPOptionsDialogFrame, &IID_IAIMPOptionsDialogFrame>
{
public:
    static HRESULT RegisterExtension(IAIMPCore *core);
    OptionsDialog(IAIMPServiceOptionsDialog *service) : m_service(service) {}
    ~OptionsDialog();

    HRESULT WINAPI GetName(IAIMPString **S);
    HWND WINAPI CreateFrame(HWND ParentWnd);
    void WINAPI DestroyFrame();
    void WINAPI Notification(int ID);

private:
    IAIMPServiceOptionsDialog *m_service = nullptr;
    IAIMPServiceUI *ui = nullptr;
    IAIMPUIForm *form = nullptr;
    IAIMPUIEdit *tokenEdit = nullptr;

    template <typename TControl, typename TEventHandler = IUnknown>
    TControl *_createControl(IAIMPUIWinControl *parent, const IID &iid, IAIMPString *name, TEventHandler *eventsHandler = nullptr)
    {
        TControl *control = nullptr;

        if (ui && parent)
        {
            if (SUCCEEDED(ui->CreateControl(form, parent, name, reinterpret_cast<IUnknown *>(eventsHandler), iid, reinterpret_cast<void **>(&control))))
            {
                return control;
            }
        }

        throw std::runtime_error("Cannot create from control");
    }
};