/**************************************************
 * FILENAME:        Logger.cpp
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

#include "Logger.h"
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

Logger::~Logger() {
    while(outputs.size() > 0) {
        if(outputs[outputs.size()-1].fptr != NULL && outputs[outputs.size()-1].type == LogFile) {
            fputs("\n\r", outputs[outputs.size()-1].fptr);
            fclose(outputs[outputs.size()-1].fptr);
        }
        outputs.pop_back();
    }
}

bool Logger::addOutput(LogOutputType type, LogLevel lvl, const char* parameter, int paramLen) {
    LogOutput lo;
    lo.type = type;
    lo.level = lvl;

    lo.fptr = NULL;
    if(type == LogFile && paramLen > 0) {
        lo.fptr = fopen(parameter, "a");
        if(lo.fptr == NULL)
            fprintf(stderr, "Error opening Log-File <%s>!\n\r", parameter);
       
        char buf[200];
        time_t t = time(0);
        struct tm* tmp = localtime(&t);
        strftime(buf, sizeof(buf), "%c", tmp); 
        fprintf(lo.fptr, "-[ %s ]-\n\r", buf);
        fflush(lo.fptr);
    }

    outputs.push_back(lo);

    return true;
}

void Logger::Log(LogLevel lvl, const char* format, ...) {
    va_list arg_ptr;
    char cLvl;
    for(unsigned int i=0; i<outputs.size(); i++) {
        va_start(arg_ptr, format);
        if(outputs[i].level<=lvl) {
            cLvl = lvl == LogInfo ? 'I' : (lvl == LogWarning ? 'W' : 'E');
            switch(outputs[i].type) {
                case LogStdout:
                    fputc(cLvl, stdout);
                    fputs("] ", stdout);
                    vfprintf(stdout, format, arg_ptr);
                    fflush(stdout);
                    break;
                case LogStderr:
                    fputc(cLvl, stderr);
                    fputs("] ", stderr);
                    vfprintf(stderr, format, arg_ptr);
                    fflush(stderr);
                    break;
                case LogFile:
                    fputc(cLvl, outputs[i].fptr);
                    fputs("] ", outputs[i].fptr);
                    vfprintf(outputs[i].fptr, format, arg_ptr);
                    fflush(outputs[i].fptr);
                    break;
                default:
                    fprintf(stderr, "LibLogger: Undefined Output!\n\r");
            }
        }
        va_end(arg_ptr);
    }
}

void Logger::dbgListOutputs() {
#ifdef DEBUG
    for(unsigned int i=0; i<outputs.size(); i++) {
        switch(outputs[i].level) {
            case LogInfo:
                printf("Info\t");
                break;
            case LogWarning:
                printf("Warn\t");
                break;
            case LogError:
                printf("Error\t");
                break;
            default:
                fprintf(stderr, "LibLogger: Undefined LogLevel!\n\r");
        }

        switch(outputs[i].type) {
            case LogStdout:
                printf("Stdout\n\r");
                break;
            case LogStderr:
                printf("Stderr\n\r");
                break;
            case LogFile:
                printf("File\n\r");
                break;
            default:
                fprintf(stderr, "LibLogger: Undefined Output!\n\r");
        }
    }
#endif
}
