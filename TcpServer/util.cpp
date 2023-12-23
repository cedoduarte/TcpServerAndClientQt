#include "util.h"

bool Util::stringContains(const QString &input, const std::vector<QString> &stringGroup)
{
    int counter = 0;
    for (const QString &str : stringGroup)
    {
        if (input.contains(str))
        {
            counter++;
        }
    }
    return counter == stringGroup.size();
}
