#include "dear-reader_User.h"

using namespace dear-reader;

// Add definition of your processing function here
void User::read(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&storyId)

{
    auto para = req->getParameters();
    HttpViewData data;
    data.insert("title", "read");
    data.insert("parameters", para);
    auto resp = HttpResponse::newHttpViewResponse("Read.csp", data);
    callback(resp);
}

void User::addStory(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback,
                    std::string storyId);

{
    auto para = req->getParameters();
    HttpViewData data;
    data.insert("title", "addStory");
    data.insert("parameters", para);
    auto resp = HttpResponse::newHttpViewResponse("Create.csp", data);
    callback(resp);
}

void User::edit(const HttpRequestPtr &req,
                std::function<void(const HttpResponderPtr &)> &&callback,
                std::string &&storyId);

{
    auto para = req->getParameters();
    HttpViewData data;
    data.insert("title", "Edit");
    data.insert("parameters", para);
    auto resp = HttpResponse::newHttpViewResponse("Edit.csp", data);
    callback(resp);
}

void User::home(const HttpRequestPtr &req,
                std::function<void(const HttpResponderPtr &)> &&callback,
                std::string &&index);

{
    auto para = req->getParameters();
    HttpViewData data;
    data.insert("title", "home");
    data.insert("parameters", para);
    auto resp = HttpResponse::newHttpViewResponse("Home.csp", data);
    callback(resp);
}