#include <vector>
#include <string>

namespace dearreader
{
    struct Story
    {
        std::string storyTitle;
        std::vector<std::string> titles;
        std::vector<std::string> chapter_text;
        std::vector<std::string> images;
    };
    struct StoryTitle
    {
        std::string id;
        std::string title;
    };
}