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


#define MAX_LINE_LENGTH = 80;

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
bool bg_commend= _isBackgroundComamnd(cmd_line);
  string cmd_s = _trim(string(cmd_line));
  string firstWord = cmd_s.substr(0, cmd_s.find_first_of(" \n"));

  if (firstWord.compare("pwd") == 0) {
    return new GetCurrDirCommand(cmd_line);
  }
  else if (firstWord.compare("showpid") == 0) {
    return new ShowPidCommand(cmd_line);
  }
  else if (firstWord.compare("cd") == 0) {
      string secondWord = cmd_s.substr(firstWord.length(), cmd_s.find_first_of(" \n"));
      string secondWord_s = _trim(string(secondWord));
      if (secondWord_s == "-") {
          if(last_working_directory.empty()) {
              //smash error: cd: OLDPWD not set
              return nullptr;
          }
          chdir(this->last_working_directory.c_str());
      }
      else {
          chdir(secondWord_s.c_str());
          this->last_working_directory=secondWord_s;
      }
      return nullptr;
  }
      else if (firstWord == "chprompt") {
        string secondWord = cmd_s.substr(firstWord.length(), cmd_s.find_first_of(" \n"));
        string secondWord_s = _trim(string(secondWord));
        this->SetPrompt(secondWord_s);
        return nullptr;
    }
  else if (firstWord == "jobs") {
      this->jobsList.printJobsList();
      return nullptr;
  }
  else if (firstWord == "kill") {
      //i think we should do a kind of scnaf//
      return nullptr;
  }
  else if (firstWord == "fg") {
      string secondWord = cmd_s.substr(firstWord.length(), cmd_s.find_first_of(" \n"));
      string secondWord_s = _trim(string(secondWord));
      if(secondWord_s.empty()) {
          if(this->jobsList.max_job_id==0)
          {
              //need to put error smash error: bg: there is no stopped jobs to resume
          }
          else {
              //send sigcont to the max job id and get new job maximum.
          }
      }
      else {
          int job_id = stoi(secondWord_s); //not sure what happens when stoi fails. need to put smash error: bg: invalid arguments
          if (this->jobsList.jobs[job_id] == nullptr) {
               //need put error smash error: fg: job-id <job-id> does not exist
          }
          else {
              //send sigcont to the job id
          }
      }
      return nullptr;
  }
  else if (firstWord == "bg") {
      string secondWord = cmd_s.substr(firstWord.length(), cmd_s.find_first_of(" \n"));
      string secondWord_s = _trim(string(secondWord));
      if(secondWord_s.empty()) {
          if(this->jobsList.max_job_id==0)
          {
              //need to put error smash error: fg: jobs list is empty
          }
          else {
              //send sigcont to the max job id and get new job maximum.
          }
      }
      else {
          int job_id = stoi(secondWord_s); //not sure what happens when stoi fails. need to put smash error: fg: invalid arguments
          if (this->jobsList.jobs[job_id] == nullptr) {
              //need put error smash error: bg: job-id <job-id> does not exist
          }
          else {
              if (this->jobsList.jobs[job_id] == nullptr)
              {}
              //send sigcont to the job id
          }
      }
      return nullptr;
  }
  else if (firstWord == "quit") {
      string secondWord = cmd_s.substr(firstWord.length(), cmd_s.find_first_of(" \n"));
      string secondWord_s = _trim(string(secondWord));
      if(secondWord_s=="kill")
      {
            //for (int i=0;...
      }
      exit(0);
  }
  else {
    return new ExternalCommand(cmd_line);
  }

  return nullptr;
}

void SmallShell::executeCommand(const char *cmd_line) {
  // TODO: Add your implementation here
  // for example:
  // Command* cmd = CreateCommand(cmd_line);
  //if(cmd!=nullptr)
   // {
        // cmd->execute();
    //}
  // Please note that you must fork smash process for some commands (e.g., external commands....)
}

void GetCurrDirCommand::execute() {
    char buf[80];
    std::cout <<getcwd(buf,80);
}


void ShowPidCommand::execute() {
std::cout<<"smash pid is "<<getpid();
}


}
