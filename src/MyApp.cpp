#include "MyApp.h"
#include "MyFrame.h"

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("Lit Beat");
    frame->Show(true);
    return true;
}
