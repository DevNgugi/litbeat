#ifndef MYFRAME_H
#define MYFRAME_H

#include <wx/wx.h>
#include "AudioHandler.h" // Include the new header
#include "HTTPClient.h"

class MyFrame : public wxFrame {
public:

    MyFrame(const wxString& title);

private:
    void OnQuit(wxCommandEvent& event);
    void OnSubmit(wxCommandEvent& event);

    void OnStartAudio(wxCommandEvent& event);

    AudioHandler audioHandler;
    HTTPClient client;


    wxTextCtrl *textCtrl;
    wxCheckBox *checkBox;


    //define constant IDS for buttons
    static const int ID_API_CALL_BUTTON = 1002;
    static const int ID_START_AUDIO_BUTTON = 1002;
};

#endif // MYFRAME_H
