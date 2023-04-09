#include "cApp.h"
wxIMPLEMENT_APP(cApp);
cApp :: cApp() {

}
cApp :: ~cApp() {


}

bool cApp::OnInit() {
	m_framel = new cMain();
	m_framel->Show();
	
	return true;
}
