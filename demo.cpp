/**************************************************
 * FILENAME:        demo.cpp
 * PROJECT:         LibLogger
 *
 * AUTHOR:          Philipp Doblhofer 
 * WEB:             www.gnp-tec.net
 * START DATE:      2013-Dec-31
 *
 **************************************************
 * DESCRIPTION:
 *      This is a simple demo code for using the
 *      library.
 *************************************************/

#include "Logger.h"
#include <string.h>

int main() {
    Logger log;

    log.addOutput(LogStdout, LogInfo, 0, 0);
    log.addOutput(LogStderr, LogWarning, 0, 0);
    log.addOutput(LogFile, LogInfo, "log.txt", strlen("log.txt"));

    log.dbgListOutputs();

    log.Log(LogWarning, "TestWarning %i\n\r", 5);
    log.Log(LogInfo, "TestInfo %i\n\r", 4);
    log.Log(LogError, "TestError %i\n\r", 5);

    return 0;
}
