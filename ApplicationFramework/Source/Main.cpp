#include "Visionary.h"
#include <iostream>

int main(void)
{
    Visionary::ApplicationSettings appSettings = Visionary::ApplicationSettings();

    Visionary::Application* app = new Visionary::Application("Sandbox App", appSettings);
    //app->GetWindow()->DisableDefaultTitleBar(); // Uncomment this line for a custom title bar

    app->Run();  
    
    delete app;
    return 0;
}