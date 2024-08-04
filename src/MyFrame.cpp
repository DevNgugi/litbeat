#include "MyFrame.h"
#include "HTTPClient.h"

using namespace std;

MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
    wxPanel *panel = new wxPanel(this);
    

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxStaticText *nameLabel = new wxStaticText(panel, wxID_ANY, "Url:");
    textCtrl = new wxTextCtrl(panel, wxID_ANY);

    checkBox = new wxCheckBox(panel, wxID_ANY, "Subscribe to newsletter");

    wxButton *submitButton = new wxButton(panel, wxID_OK, "Submit");

    wxButton *startAudioButton = new wxButton(panel, wxID_ANY, "Start Audio"); // New button

    startAudioButton->Bind(wxEVT_BUTTON, &MyFrame::OnStartAudio, this);
    submitButton->Bind(wxEVT_BUTTON, &MyFrame::OnSubmit, this);



    vbox->Add(nameLabel, 0, wxALL, 10);
    vbox->Add(textCtrl, 0, wxALL | wxEXPAND, 10);
    vbox->Add(checkBox, 0, wxALL, 10);
    vbox->Add(submitButton, 0, wxALL | wxALIGN_CENTER, 10);

    vbox->Add(startAudioButton, 0, wxALL | wxALIGN_CENTER, 10);  


    panel->SetSizer(vbox);
}

void MyFrame::OnStartAudio(wxCommandEvent& event) {
    if (audioHandler.Initialize()) {
        audioHandler.Start();
    }
}

void MyFrame::OnSubmit(wxCommandEvent& event) {
    wxString url = textCtrl->GetValue();
    std::string response = client.get(url.ToStdString()); // Get response from the HTTP client

    wxString message;
   wxString responseStr(response);

    message.Printf("Response: %s", responseStr);

    wxMessageBox(message, "Form Data", wxOK | wxICON_INFORMATION);

}

void MyFrame::OnQuit(wxCommandEvent& event) {
    Close(true);
}
