#include "dearreader_User.h"

using namespace dearreader;

// Add definition of your processing function here
void User::read(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&storyId)

{
    auto para = req->getParameters();
    HttpViewData data;
    data.insert("title", "view");
    data.insert("parameters", para);
    auto resp = HttpResponse::newHttpViewResponse("View.csp", data);
    callback(resp);
}

void User::create(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback)

{
    auto para = req->getParameters();
    HttpViewData data;
    data.insert("title", "create");
    data.insert("parameters", para);
    auto resp = HttpResponse::newHttpViewResponse("Create.csp", data);
    callback(resp);
}

void User::update(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback,
                  std::string &&storyId)

{
    auto para = req->getParameters();
    HttpViewData data;
    data.insert("title", "update");
    data.insert("parameters", para);
    auto resp = HttpResponse::newHttpViewResponse("Edit.csp", data);
    callback(resp);
}

void User::edit(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&storyId)

{
    auto para = req->getParameters();
    HttpViewData data;
    data.insert("title", "Edit");
    data.insert("parameters", para);
    auto resp = HttpResponse::newHttpViewResponse("Edit.csp", data);
    callback(resp);
}

void User::home(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback)

{
    auto para = req->getParameters();
    HttpViewData data;
    data.insert("title", "home");
    data.insert("parameters", para);
    auto resp = HttpResponse::newHttpViewResponse("Index.csp", data);
    callback(resp);
}