#include <unistd.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <sys/wait.h>
#include <iomanip>
#include "Commands.h"
#include <time.h>
// #include <utime.h>


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

ChangePrompt::ChangePrompt(const char *cmd_line) : BuiltInCommand(cmd_line)
{

    SmallShell& smash = SmallShell::getInstance();
    if(strcmp(this->arguments[1],"")==0)
    {

        smash.prompt="smash";
    }
    else
    {
        smash.prompt=this->arguments[1];
    }
}

ChangeDirCommand::ChangeDirCommand(const char* cmd_line): BuiltInCommand(cmd_line) {}

void ChangeDirCommand::execute()
{
    SmallShell& smash = SmallShell::getInstance();
    if(this->num_of_args>=2)
    {
        std::cerr<<"smash error: cd: too many arguments";
        return;
    }
    char* new_prev_dir = get_current_dir_name();
    if(strcmp(this->arguments[1],"-")==0)
    {
        if(smash.last_working_directory.empty())
        {
            std::cerr<<"smash error: cd: OLDPWD not set";
            return;
        }
        else
        {
            newdir=smash.last_working_directory;
        }
    }
    else
    {
        newdir=this->arguments[1];
    }
    if(chdir(newdir.c_str())==-1)
    {
        perror("smash error: chdir failed");
    }
    smash.last_working_directory = new_prev_dir;
}

ShowPidCommand::ShowPidCommand(const char* cmd_line) : BuiltInCommand(cmd_line) {}

void ShowPidCommand::execute() {
    SmallShell& smash = SmallShell::getInstance();
    cout << "smash pid is " << smash.pid << endl;
}

void JobsList::printJobsList() {
    JobEntry* curr_job;
    removeFinishedJobs();
for(int i=0;i<100;i++)
{
    curr_job=this->List->at(i);
    std::cout<<"["<<i<<"]"<< curr_job->discript<<" : ";
    if(curr_job->job_status==bg)
    {
        std::cout<<difftime(curr_job->insert_time, time(nullptr))<< " secs";
    }
    else
    {
        std::cout<<difftime(curr_job->stopped_time, time(nullptr))<< " secs (stopped)";
    }

}
}


int JobsList::getLastJob() {
    int max=-1;
    for(int i=0;i<MAX_NUM_OF_JOBS;i++) {
        JobEntry *curr_job = this->List->at(i);
        if(curr_job!= nullptr)
        {
            max=i;
        }
    }
    return max;
}

int JobsList::getLastStoppedJob() {
    int max=0;
    for(int i=0;i<100;i++) {
        JobEntry *curr_job = this->List->at(i);
        if(curr_job!= nullptr&&curr_job->job_status==stopped)
        {
            max=i;
        }
    }
    return max;
}


//JobsList::JobEntry::JobEntry(Command *cmd,int pid,JobStatus isStopped) {
//    this->job_pid=pid;
//    this->discript=cmd->cmd_line;
//    this->job_status=isStopped;
//    this->insert_time= time(nullptr);
//    this->stopped_time= time(nullptr);
//
//}

void JobsList::JobEntry::StopJob() {
    this->job_status=stopped;
    this->stopped_time=time(nullptr);

}

void JobsList::JobEntry::ContinueJob() {
    this->job_status=bg;
}

GetCurrDirCommand::GetCurrDirCommand(const char* cmd_line) : BuiltInCommand(cmd_line) {}

void GetCurrDirCommand::execute() {
    SmallShell& smash = SmallShell::getInstance();
    char* dir = get_current_dir_name(); //change to getcwd?
    if (dir != nullptr) {
        cout << dir << endl;
        delete dir;
    }
    else {
        perror("smash error: get_current_dir_name failed");
    }
}

QuitCommand::QuitCommand(const char* cmd_line) : BuiltInCommand(cmd_line) {}

void QuitCommand::execute() {
    std::vector<JobsList::JobEntry*>* list = SmallShell::getInstance().jobsList.List;
    JobsList::JobEntry* current_job;
    int counter = 0;
    if (strcmp(this->arguments[1],"kill") == 0) {
        for (int i = 0; i < MAX_NUM_OF_JOBS; i++) {
            current_job = list->at(i);
            if (current_job) {
                counter++;
            }
        }
        cout << "sending SIGKILL signal to " << counter << " jobs:" << endl;
        SmallShell::getInstance().jobsList.killAllJobs();
    }
    exit(0);
}

void JobsList::killAllJobs() {
    std::vector<JobsList::JobEntry *> *list = SmallShell::getInstance().jobsList.List;
    JobsList::JobEntry* current_job;
    for (int i = 0; i < MAX_NUM_OF_JOBS; i++) {
        current_job = list->at(i);
        if (current_job) {
            cout << current_job->job_pid << ": " << current_job->discript << endl;
        }
    }
}

void JobsList::addJob(Command* cmd,int pid, JobStatus isStopped) {
    removeFinishedJobs();
    std::vector<JobsList::JobEntry *> *list = SmallShell::getInstance().jobsList.List;
    int max_job_id = getLastJob();
    int job_id = list->empty() ? 1 : (max_job_id + 1);
    list->at(job_id) = new JobEntry();
    list->at(job_id)->job_pid = pid; //which pid?
    list->at(job_id)->discript = cmd->cmd_line;
    list->at(job_id)->job_status=isStopped;
    list->at(job_id)->insert_time = time(nullptr); //add stop_time
}


// void JobsList::resumeJob()

void JobsList::removeFinishedJobs() {
    std::vector<JobsList::JobEntry *> *list = SmallShell::getInstance().jobsList.List;
    JobEntry* current_job;
    for (int i = 0; i < MAX_NUM_OF_JOBS; i++) {
        current_job = list->at(i);
        if (waitpid(current_job->job_pid, nullptr, WNOHANG) == current_job->job_pid) { //error handling??
            list->at(i)= nullptr;
        }
    }
}

JobsList::JobEntry *JobsList::getJobByPid(int pid) {
    std::vector<JobsList::JobEntry *> *list = SmallShell::getInstance().jobsList.List;
    JobEntry* current_job;
    for (int i = 0; i < MAX_NUM_OF_JOBS; i++) {
        current_job = list->at(i);
        if (pid== current_job->job_pid) {
            return current_job;
        }
    }
    return nullptr;
}

ForegroundCommand::ForegroundCommand(const char *cmd_line): BuiltInCommand(cmd_line) {
    SmallShell &smash = SmallShell::getInstance();
    JobsList::JobEntry *job;
    int job_id;
    if (strcmp(this->arguments[1], "") == 0) {
        job_id = smash.jobsList.getLastJob();
    } else {
        try {
            if(this->num_of_args>=2)
            {
                throw std::invalid_argument("");
            }
            job_id = stoi(this->arguments[1]);
            if(job_id<0||job_id>100)
            {
                throw std::invalid_argument("");
            }
        }catch (std::invalid_argument& ia)
        {
            std::cout<<"smash error: fg: invalid arguments"<<endl;
            return;
        }
    }
    if(job_id==-1)
    {
        std::cout<<"smash error: fg: jobs list is empty"<<endl;
    }
    job = smash.jobsList.getJobById(job_id);
    if(job== nullptr)
    {
        std::cout<<"smash error: fg: job-id "<<job_id<<" does not exist"<<endl;
    }
    if (job->job_status == stopped) {
        kill(job_id, SIGCONT);
    }
    cout << job->discript << " : " << job_id << endl;
    waitpid(job_id, nullptr, 0); //waiting for the son to come home

}

void ForegroundCommand::execute() {

}

BackgroundCommand::BackgroundCommand(const char *cmd_line): BuiltInCommand(cmd_line) {

    SmallShell &smash = SmallShell::getInstance();
    JobsList::JobEntry *job;
    int job_id;
    if (strcmp(this->arguments[1], "") == 0) {
        job_id = smash.jobsList.getLastStoppedJob();
    } else {
        try {
            if (this->num_of_args >= 2) {
                throw std::invalid_argument("");
            }
            job_id = stoi(this->arguments[1]);
            if(job_id<0||job_id>100)
            {
                throw std::invalid_argument("");
            }

        } catch (std::invalid_argument &ia) {
            std::cout << "smash error: bg: invalid arguments" << endl;
            return;
        }
    }
    if (job_id == -1) {
        std::cout << "smash error: bg: jobs list is empty" << endl;
    }
    job = smash.jobsList.getJobById(job_id);
    if (job == nullptr) {
        std::cout << "smash error: bg: job-id " << job_id << " does not exist" << endl;
    }
    if (job->job_status == stopped) {
        kill(job_id, SIGCONT);
    }
    cout << job->discript << " : " << job_id << endl;

}

void BackgroundCommand::execute() {

}

KillCommand::KillCommand(const char *cmd_line) : BuiltInCommand(cmd_line) {

    SmallShell &smash = SmallShell::getInstance();
    JobsList::JobEntry *job;
    int job_id,sig_num;
        try {
            if (this->num_of_args != 2) {
                throw std::invalid_argument("");
            }

            job_id = stoi(this->arguments[2]);
            sig_num = stoi(this->arguments[1]);
            if(sig_num>0||job_id<0||job_id>100)
            {
                throw std::invalid_argument("");
            }
        } catch (std::invalid_argument &ia) {
            std::cout << "smash error: kill: invalid arguments" << endl;
            return;
    }
    job = smash.jobsList.getJobById(job_id);
    if (job == nullptr) {
        std::cout << "smash error: kill: job-id "<<job_id<<" does not exist"<<endl;
    }
        kill(job_id, sig_num);
    cout << "signal number"<< sig_num<<" was sent to pid "<<job->job_pid <<endl;
}

void KillCommand::execute() {

}
