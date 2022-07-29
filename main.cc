#include <drogon/drogon.h>
#include <cstdlib>
// "using namespace drogon" is a required import for main.cc
using namespace drogon;

// The app is contained within this one main function
int main()
{
    drogon::HttpAppFramework::instance()
        .registerHandler("/",
                         [=](const HttpRequestPtr &req,
                             std::function<void(const HttpResponsePtr &)> &&callback)
                         {
                             auto para = req->getParameters();
                             HttpViewData data;
                             data.insert("Dear Reader", "ListParameters");
                             data.insert("parameters", para);
                             auto resp = HttpResponse::newHttpViewResponse("Index.csp", data);
                             callback(resp);
                         });
    // Set HTTP listener address and port
    drogon::app()
        // [n] strtol(std::geteven("PORT"), NULL, 10) is setting a PORT variable where normally we would just assign one by using the string-to-long function. Since the environment variable starts as a string we are converting it to an interger so the program interprets it correctly.
        .addListener("0.0.0.0", strtol(std::getenv("PORT"), NULL, 10));
    // Load config file
    // drogon::app().loadConfigFile("../config.json");
    // Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
