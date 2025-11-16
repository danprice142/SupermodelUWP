#include "FilePicker.h"

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Devices::Input;
using namespace Windows::Graphics::Display;
using namespace Windows::Foundation;
using namespace Windows::System;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;

template <typename T>
void WaitForAsync(IAsyncOperation<T>^ A)
{
    while (A->Status == Windows::Foundation::AsyncStatus::Started) {
        CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
    }

    Windows::Foundation::AsyncStatus S = A->Status;
}

std::string UWP::pick_a_file()
{
    std::string out = "";
    auto folderPicker = ref new Windows::Storage::Pickers::FileOpenPicker();
    folderPicker->SuggestedStartLocation = Windows::Storage::Pickers::PickerLocationId::Desktop;
    folderPicker->FileTypeFilter->Append("*");

    auto folder_operation = folderPicker->PickSingleFileAsync();
    WaitForAsync(folder_operation);
    auto folder = folder_operation->GetResults();
    if (folder != nullptr) {
        // Application now has read/write access to all contents in the picked file
        Windows::Storage::AccessCache::StorageApplicationPermissions::FutureAccessList->AddOrReplace("PickedFileToken", folder);
        auto selected = folder->Path;
        out = std::string(selected->Begin(), selected->End());
    }
    return out;
}
