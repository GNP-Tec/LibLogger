/**************************************************
 * FILENAME:        Logger.h
 * PROJECT:         LibLogger
 *
 * AUTHOR:          Philipp Doblhofer 
 * WEB:             www.gnp-tec.net
 * START DATE:      2013-Dec-31
 *
 **************************************************
 * DESCRIPTION:
 *      This library provides a simple Logger
 *      class to easily log from an application.
 *      It is possible to set the output to 
 *      stdout, stderr and/or to
 *      a file. There are different log-levels
 *      which can be connected with the output
 *      'channels'.
 *************************************************/

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <vector>
#include <stdio.h>
using namespace std;

typedef enum lOutputType {
    LogStdout,
    LogStderr,
    LogFile
} LogOutputType;

typedef enum lLevel {
    LogInfo,
    LogWarning,
    LogError
} LogLevel;

typedef struct lOutput {
    LogOutputType type;
    LogLevel level;

    FILE* fptr;
} LogOutput;

class Logger {
    private:
        vector<LogOutput> outputs;   
    public:
        bool addOutput(LogOutputType type, LogLevel lvl, const char* parameter, int paramLen);
        void Log(LogLevel lvl, const char* format, ...);
        
        ~Logger();

        void dbgListOutputs();
};

#endif
