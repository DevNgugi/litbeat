#include "MyFrame.h"

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(wxID_OK, MyFrame::OnSubmit)
    EVT_BUTTON(wxID_ANY, MyFrame::OnStartAudio) // Add event handler for starting audio
    EVT_BUTTON(wxID_ANY, MyFrame::OnStopAudio)   // Add event handler for stopping audio

wxEND_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
    wxPanel *panel = new wxPanel(this);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxStaticText *nameLabel = new wxStaticText(panel, wxID_ANY, "Name:");
    textCtrl = new wxTextCtrl(panel, wxID_ANY);

    checkBox = new wxCheckBox(panel, wxID_ANY, "Subscribe to newsletter");

    wxButton *submitButton = new wxButton(panel, wxID_OK, "Submit");
    wxButton *startAudioButton = new wxButton(panel, wxID_ANY, "Start Audio"); // New button
    wxButton *stopAudioButton = new wxButton(panel, wxID_ANY, "Stop Audio");    // New button


    vbox->Add(nameLabel, 0, wxALL, 10);
    vbox->Add(textCtrl, 0, wxALL | wxEXPAND, 10);
    vbox->Add(checkBox, 0, wxALL, 10);
    vbox->Add(submitButton, 0, wxALL | wxALIGN_CENTER, 10);
    vbox->Add(startAudioButton, 0, wxALL | wxALIGN_CENTER, 10); // Add start audio button
    vbox->Add(stopAudioButton, 0, wxALL | wxALIGN_CENTER, 10);  // Add stop audio button


    panel->SetSizer(vbox);
}

void MyFrame::OnStartAudio(wxCommandEvent& event) {
    if (audioHandler.Initialize()) {
        audioHandler.Start();
    }
}

void MyFrame::OnStopAudio(wxCommandEvent& event) {
    audioHandler.Stop();
}


void MyFrame::OnSubmit(wxCommandEvent& event) {
    wxString name = textCtrl->GetValue();
    bool subscribed = checkBox->GetValue();

    wxString message;
    message.Printf("Name: %s\nSubscribed: %s", name, subscribed ? "Yes" : "No");

    wxMessageBox(message, "Form Data", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnQuit(wxCommandEvent& event) {
    Close(true);
}
