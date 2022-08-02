#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace dearreader
{
  struct Story
  {
    std::string storyTitle;
    std::string chapter;
    std::string text;
  };

  class AddStory : public drogon::HttpController<AddStory>
  {
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(AddStory::get, "/{2}/{1}", Get); // path is /dearreader/AddStory/{arg2}/{arg1}
    // METHOD_ADD(AddStory::your_method_name, "/{1}/{2}/list", Get); // path is /dearreader/AddStory/{arg1}/{arg2}/list
    // ADD_METHOD_TO(AddStory::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
    ADD_METHOD_TO(AddStory::addStory, "/addStory", Post);

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
    void addStory(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback, dearreader::Story &&story);
  };
}

namespace drogon
{
  template <>
  inline dearreader::Story fromRequest(const HttpRequest &req)
  {
    auto json = req.getJsonObject();
    dearreader::Story story;
    if (json)
    {
      story.storyTitle = (*json)["storyTitle"].asString();
      story.chapter = (*json)["chapter"].asString();
      story.text = (*json)["text"].asString();
    }
    return story;
  }
}