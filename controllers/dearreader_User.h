#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace dearreader
{
  class User : public drogon::HttpController<User>
  {
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(User::get, "/{2}/{1}", Get); // path is /dear-reader/User/{arg2}/{arg1}
    // METHOD_ADD(User::your_method_name, "/{1}/{2}/list", Get); // path is /dear-reader/User/{arg1}/{arg2}/list
    // ADD_METHOD_TO(User::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
    ADD_METHOD_TO(User::read, "/story?storyId={1}&chapter={2}", Get);
    ADD_METHOD_TO(User::create, "/create", Get);
    ADD_METHOD_TO(User::update, "/update", Get);
    ADD_METHOD_TO(User::edit, "/edit?storyId={1}", Patch);
    ADD_METHOD_TO(User::home, "/", Get);

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
    void read(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback,
              std::string &&storyId,
              int &&chapter);

    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);

    void update(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&storyId);

    void edit(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback,
              std::string &&storyId);

    void home(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback);
  };
}
