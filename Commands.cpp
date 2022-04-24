#include <unistd.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <sys/wait.h>
#include <iomanip>
#include "Commands.h"
#include <time.h>
#include <utime.h>


using namespace std;

#if 0
#define FUNC_ENTRY()  \
  cout << __PRETTY_FUNCTION__ << " --> " << endl;

#define FUNC_EXIT()  \
  cout << __PRETTY_FUNCTION__ << " <-- " << endl;
#else
#define FUNC_ENTRY()
#define FUNC_EXIT()
#endif

const std::string WHITESPACE = " \n\r\t\f\v";

string _ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

string _rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

string _trim(const std::string& s)
{
    return _rtrim(_ltrim(s));
}

int _parseCommandLine(const char* cmd_line, char** args) {
    FUNC_ENTRY()
    int i = 0;
    std::istringstream iss(_trim(string(cmd_line)).c_str());
    for(std::string s; iss >> s; ) {
        args[i] = (char*)malloc(s.length()+1);
        memset(args[i], 0, s.length()+1);
        strcpy(args[i], s.c_str());
        args[++i] = NULL;
    }
    return i;

    FUNC_EXIT()
}

bool _isBackgroundComamnd(const char* cmd_line) {
    const string str(cmd_line);
    return str[str.find_last_not_of(WHITESPACE)] == '&';
}

void _removeBackgroundSign(char* cmd_line) {
    const string str(cmd_line);
    // find last character other than spaces
    unsigned int idx = str.find_last_not_of(WHITESPACE);
    // if all characters are spaces then return
    if (idx == string::npos) {
        return;
    }
    // if the command line does not end with & then return
    if (cmd_line[idx] != '&') {
        return;
    }
    // replace the & (background sign) with space and then remove all tailing spaces.
    cmd_line[idx] = ' ';
    // truncate the command line string up to the last non-space character
    cmd_line[str.find_last_not_of(WHITESPACE, idx) + 1] = 0;
}

// TODO: Add your implementation for classes in Commands.h 

SmallShell::SmallShell() {
// TODO: add your implementation
}

SmallShell::~SmallShell() {
// TODO: add your implementation
}

/**
* Creates and returns a pointer to Command class which matches the given command line (cmd_line)
*/
Command * SmallShell::CreateCommand(const char* cmd_line) {
    string cmd_s = _trim(std::string(cmd_line));
    string firstWord = cmd_s.substr(0, cmd_s.find_first_of(" \n"));

    if (firstWord.find(">") == string::npos) {
        return new RedirectionCommand(cmd_line);
    }
    else if (firstWord.find("|") == string::npos) {
        return new PipeCommand(cmd_line);
    }
    else if (firstWord == "chprompt") {
        return new ChangePrompt(cmd_line);
    }
    else if (firstWord == "chprompt") {
        return new ChangePrompt(cmd_line);
    }
    else if (firstWord == "pwd") {
        return new GetCurrDirCommand(cmd_line);
    }
    else if (firstWord == "showpid") {
        return new ShowPidCommand(cmd_line);
    }
    else if (firstWord == "cd") {
        return new ChangeDirCommand(cmd_line);
    }
    else if (firstWord.compare("jobs") == 0) {
        return new JobsCommand(cmd_line);
    }
    else if (firstWord.compare("kill") == 0) {
        return new KillCommand(cmd_line);
    }
    else if (firstWord.compare("fg") == 0) {
        return new ForegroundCommand(cmd_line);
    }
    else if (firstWord.compare("bg") == 0) {
        return new BackgroundCommand(cmd_line);
    }
    else if (firstWord.compare("quit") == 0) {
        return new QuitCommand(cmd_line);
    }
    else {
        return new ExternalCommand(cmd_line);
    }

    return nullptr;
}

void SmallShell::executeCommand(const char *cmd_line) {
    Command* cmd = CreateCommand(cmd_line);
    cmd->execute();
    // Please note that you must fork smash process for some commands (e.g., external commands....)
}

Command::Command(const char* cmd_line) : cmd_line(cmd_line) {
    char* args_array[COMMAND_ARGS_MAX_LENGTH];
    num_of_args = _parseCommandLine(cmd_line, args_array);
    for (int i = 0; i < num_of_args; ++i) {
        arguments[i] = args_array[i];
    }
    // SmallShell::getInstance().cmd_line = cmd_line;
}

Command::~Command() {
    for (int i = 0; i < num_of_args; ++i) {
        delete[] arguments[i];
    }
    // SmallShell::getInstance().fg_pid = EMPTY_FG;
}

void ChangePrompt::execute() {
    if(strcmp(this->arguments[0],"")==0) {
        SmallShell::getInstance().prompt="smash";
    }
    else
    {
        SmallShell::getInstance().prompt=this->arguments[0];
    }
}


ChangeDirCommand::ChangeDirCommand(const char* cmd_line): BuiltInCommand(cmd_line)
{
    if(this->num_of_args>=2)
    {
        std::cerr<<"smash error: cd: too many arguments";
        return;
    }
    if(strcmp(this->arguments[1],"-")==0)
    {
        if(SmallShell::getInstance().last_working_directory.empty())
        {
            std::cerr<<"smash error: cd: OLDPWD not set";
            return;
        }
        else
        {
            newdir=SmallShell::getInstance().last_working_directory;
        }
    }
    else
    {
        newdir=this->arguments[1];
    }
    if(chdir(newdir.c_str())==-1)
    {
        //perror("")
    }
}