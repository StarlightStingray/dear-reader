#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>

using namespace drogon;

// HttpSimpleController does not allow registration of multiple handlers.
// Instead, it has one handler - asyncHandleHttpRequest. The
// HttpSimpleController is a lightweight class designed to handle really simple
// cases.
class TestCtrl : public drogon::HttpController<TestCtrl>
{
public:
    PATH_LIST_BEGIN
    // use PATH_ADD to add your custom processing function here;
    PATH_ADD(TestCtrl::read, "/story?storyId={1}", Get);
    PATH_ADD(TestCtrl::addStory, "/addStory", Post);
    PATH_ADD(TestCtrl::edit, "/edit?storyId={1}", Patch);
    PATH_ADD(TestCtrl::home, "/", Get);
    PATH_LIST_END
    // your declaration of processing function maybe like this:
    void read(constHttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&storyId);

    void addStory(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string storyId);

    void edit(constHttpRequestPtr &req,
                std::function<void(const HttpResponderPtr &)> &&callback,
                std::string &&storyId);

    void home(constHttpRequestPtr &req,
                std::function<void(const HttpResponderPtr &)> &&callback,
                std::string &&index);
};