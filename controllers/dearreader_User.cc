#include "dearreader_User.h"
#include "Story.h"

#include <vector>
#include <boost/lexical_cast.hpp>

using namespace dearreader;

// Add definition of your processing function here
void User::read(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&storyId, int &&chapter)
{
    struct dearreader::Story story;

    auto clientPtr = drogon::app().getDbClient();
    auto para = req->getParameters();
    const drogon::orm::Result result = clientPtr->execSqlSync(
        "SELECT stories.id as \"story_id\", stories.title as \"story_title\", chapters.id, chapters.story, chapters.chaptertitle, chapters.chapternumber, chapters.text, chapters.image_filename FROM stories JOIN chapters ON stories.id = chapters.story WHERE stories.id = $1", storyId);
    int const numChapters = result.size();
    std::vector<std::string> titles_vec(numChapters);
    std::vector<std::string> chapter_text(numChapters);
    std::vector<std::string> images(numChapters);

    for (auto row : result)
    {
        story.storyTitle = boost::lexical_cast<std::string>(row["story_title"].as<std::string>());
        titles_vec[row["chapternumber"].as<int>()] = boost::lexical_cast<std::string>(row["chaptertitle"].as<std::string>());
        chapter_text[row["chapternumber"].as<int>()] = boost::lexical_cast<std::string>(row["text"].as<std::string>());
        images[row["chapternumber"].as<int>()] = boost::lexical_cast<std::string>(row["image_filename"].as<std::string>());

        story.titles = titles_vec;
        story.chapter_text = chapter_text;
        story.images = images;
    }

    HttpViewData data;
    data.insert("title", "view");
    data.insert("parameters", para);
    data.insert("story", story);
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
    auto clientPtr = drogon::app().getDbClient();
    auto para = req->getParameters();
    const drogon::orm::Result result = clientPtr->execSqlSync("SELECT * FROM stories");
    HttpViewData data;
    std::vector<StoryTitle> stories(0);
    for (auto row : result)
    {
        StoryTitle story;
        story.id = row["id"].as<std::string>();
        story.title = row["title"].as<std::string>();
        stories.push_back(story);
    }
    data.insert("title", "home");
    data.insert("stories", stories);
    data.insert("parameters", para);
    auto resp = HttpResponse::newHttpViewResponse("Index.csp", data);
    callback(resp);
}
