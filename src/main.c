#include "alessastruct/debug.h"
#include "alessastruct/print.h"
#include "alessastruct/argument.h"
#include "alessastruct/alessastruct.h"

int main(int argc, char** argv) {
    AlessaArgumentInfo* argumentInfo = alessaCreateArgumentInfo(argc, argv);

    if (!argumentInfo) {
        alessaPrintUsage();

        return 1;
    }

    withCommandStream(argumentInfo->command, alessaCommandStreamReader);

    return 0;
}
