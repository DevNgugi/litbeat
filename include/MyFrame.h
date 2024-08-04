#ifndef MYFRAME_H
#define MYFRAME_H

#include <wx/wx.h>
#include "AudioHandler.h" // Include the new header


class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnQuit(wxCommandEvent& event);
    void OnSubmit(wxCommandEvent& event);

    void OnStartAudio(wxCommandEvent& event);
    void OnStopAudio(wxCommandEvent& event);
    AudioHandler audioHandler; // Add the AudioHandler instance

    wxTextCtrl *textCtrl;
    wxCheckBox *checkBox;

    wxDECLARE_EVENT_TABLE();
};

#endif // MYFRAME_H
