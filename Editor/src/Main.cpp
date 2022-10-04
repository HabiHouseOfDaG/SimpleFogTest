
#include "Log.h"
#include "Application.h"

int main()
{
    Log::Init();

    LOG_INFO("Starting Editor...");

    Application app;
    app.Run();

    LOG_INFO("Closing Editor...");

    return 0;
}
