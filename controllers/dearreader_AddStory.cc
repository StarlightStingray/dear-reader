#include "dearreader_AddStory.h"
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

using namespace dearreader;
using namespace drogon;

// Add definition of your processing function here
void AddStory::addStory(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback, dearreader::Story &&story)

{
    auto clientPtr = drogon::app().getDbClient();
    auto para = req->getParameters();
    boost::uuids::random_generator generator;
    boost::uuids::uuid storyid = generator();

    clientPtr->execSqlAsync(
        "CREATE TABLE IF NOT EXISTS stories (id UUID NOT NULL PRIMARY KEY, title VARCHAR(255) NOT NULL)",
        [=](const drogon::orm::Result &result)
        {
            clientPtr->execSqlAsync(
                "CREATE TABLE IF NOT EXISTS chapters (id UUID NOT NULL PRIMARY KEY, story UUID NOT NULL, chaptertitle VARCHAR(255) NOT NULL, chapternumber INT NOT NULL, text TEXT NOT NULL, image_filename VARCHAR(255) NOT NULL)",
                [=](const drogon::orm::Result &result)
                {
                    boost::uuids::random_generator generator;

                    clientPtr->execSqlAsync(
                        "INSERT INTO stories (id, title) VALUES ($1, $2) ",
                        [=](const drogon::orm::Result &result)
                        {
                            std::cout << "[INFO] Story Inserted Into DB" << std::endl;
                        },
                        [](const drogon::orm::DrogonDbException &e)
                        {
                            std::cerr << "[ERROR] " << e.base().what() << std::endl;
                        },
                        boost::lexical_cast<std::string>(storyid), story.storyTitle);
                    for (int index = 0; index < story.titles.size(); ++index)
                    {
                        boost::uuids::uuid chapterid = generator();
                        clientPtr->execSqlAsync(
                            "INSERT INTO chapters (id, story, chaptertitle, chapternumber, text, image_filename) VALUES($1, $2, $3, $4, $5, $6) ",
                            [](const drogon::orm::Result &result)
                            {
                                std::cout << "[INFO] Chapter Inserted Into DB" << std::endl;
                            },
                            [](const drogon::orm::DrogonDbException &e)
                            {
                                std::cerr << "[ERROR] " << e.base().what() << std::endl;
                            },
                            boost::lexical_cast<std::string>(chapterid), boost::lexical_cast<std::string>(storyid), story.titles[index], index, story.chapter_text[index], story.images[index]);
                    }
                },
                [](const drogon::orm::DrogonDbException &e)
                {
                    std::cerr << "[ERROR] " << e.base().what() << std::endl;
                });
        },
        [](const drogon::orm::DrogonDbException &e)
        {
            std::cerr << "[ERROR] " << e.base().what() << std::endl;
        });
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_HTML);
    resp->setBody("Story Submitted!");
    callback(resp);
}
