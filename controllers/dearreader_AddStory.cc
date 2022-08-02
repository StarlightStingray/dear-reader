#include "dearreader_AddStory.h"
#include "uuid.h"

using namespace dearreader;

// Add definition of your processing function here
void AddStory::addStory(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback, dearreader::Story &&story)

{
    auto clientPtr = drogon::app().getDbClient();
    auto para = req->getParameters();
    uuid const storyid = uuids::uuid_system_generator{}();
    clientPtr->execSqlAsync(
        "CREATE TABLE stories (
        id UUID NOT NULL PRIMARY KEY,
        title VARCHAR(255) NOT NULL)",
        [](const drogon::orm::Result &result)
        {
        std::cout << "dear reader stories table created";
        },
        [](const DrogonDbException &e)
        {
        std::cerr << "error:" << e.base().what() << std::endl;
        });
    clientPtr->execSqlAsync("CREATE TABLE chapters (
                            id UUID NOT NULL PRIMARY KEY,
                            story UUID NOT NULL,
                            chapternumber SMALLINT NOT NULL,
                            text TEXT NOT NULL,
                            imageid SMALLINT NOT NULL)",
                            [](const drogon::orm::Result &result)
        {
        std::cout << "chapters table created";
        },
        [](const DrogonDbException &e)
        {
        std::cerr << "error:" << e.base().what() << std::endl;
        });
    clientPtr->execSqlAsync(
        "INSERT INTO stories (id, title)
        VALUES($1, $2) ",
        [](const drogon::orm::Result &result)
        {
            std::cout << "stuff inserted. yeet.";
        },
        [](const DrogonDbException &e)
        {
            std::cerr << "error:" << e.base().what() << std::endl;
        },
        storyid, story.title);
    clientPtr->execSqlAsync(
        "INSERT INTO chapters (id, story, chapternumber, text, imageid)
        VALUES($1, $2, $3, $4, $5) ",
        [](const drogon::orm::Result &result)
        {
            std::cout << "double stuff inserted. yeet.";
        },
        [](const DrogonDbException &e)
        {
            std::cerr << "error:" << e.base().what() << std::endl;
        });
    HttpViewData data;
    data.insert("title", "addStory");
    data.insert("parameters", para);
    auto resp = HttpResponse::newHttpViewResponse("Create.csp", data);
    callback(resp);
}
