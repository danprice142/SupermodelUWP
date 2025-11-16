#include "pch.h"

#include <windows.h>
#include <windows.applicationmodel.core.h>
#include <wrl.h>

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Microsoft::WRL;
using namespace Platform;

// SDL main entry
extern "C" int SDL_main(int argc, char* argv[]);

ref class UWPApp sealed : public IFrameworkView
{
public:
    UWPApp() {}

    // IFrameworkView Methods
    virtual void Initialize(CoreApplicationView^ applicationView)
    {
        applicationView->Activated += ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &UWPApp::OnActivated);
    }

    virtual void SetWindow(CoreWindow^ window)
    {
        window->VisibilityChanged += ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &UWPApp::OnVisibilityChanged);
        window->Closed += ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &UWPApp::OnClosed);
    }

    virtual void Load(String^ entryPoint) {}

    virtual void Run()
    {
        // Call SDL main
        char* argv[] = { "Supermodel" };
        SDL_main(1, argv);
    }

    virtual void Uninitialize() {}

protected:
    void OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
    {
        CoreWindow::GetForCurrentThread()->Activate();
    }

    void OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args) {}

    void OnClosed(CoreWindow^ sender, CoreWindowEventArgs^ args) {}
};

ref class UWPAppSource sealed : IFrameworkViewSource
{
public:
    virtual IFrameworkView^ CreateView()
    {
        return ref new UWPApp();
    }
};

[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^ args)
{
    auto appSource = ref new UWPAppSource();
    CoreApplication::Run(appSource);
    return 0;
}
