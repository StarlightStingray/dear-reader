#pragma once

#include <drogon/HttpController.h>
#include "Story.h"
#include <vector>

using namespace drogon;

namespace dearreader
{

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
    std::cout << "from req" << std::endl;
    auto json = req.getJsonObject();
    dearreader::Story story;

    if (json)
    {
      std::cout << (*json) << std::endl;
      const Json::Value titles = (*json)["titles"];

      // Iterate over the sequence elements.
      for (int index = 0; index < titles.size(); ++index)

        story.titles.push_back(titles[index].asString());

      const Json::Value chapter_text = (*json)["chapterText"];

      // Iterate over the sequence elements.
      for (int index = 0; index < chapter_text.size(); ++index)
        // Do something with this line below
        story.chapter_text.push_back(chapter_text[index].asString());

      const Json::Value images = (*json)["images"];

      // Iterate over the sequence elements.
      for (int index = 0; index < images.size(); ++index)

        story.images.push_back(images[index].asString());

      story.storyTitle = (*json)["storytitle"].asString();
    }
    return story;
  }
}