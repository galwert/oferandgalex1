#ifndef SMASH_COMMAND_H_
#define SMASH_COMMAND_H_

#include <vector>
#include <cctype>
#define COMMAND_ARGS_MAX_LENGTH (200)
#define COMMAND_MAX_ARGS (20)

#define MAX_NUM_OF_JOBS 100
#define NOT_EXIST_IN_LIST -1
#define EMPTY_FG -1

class Command {
public:
    const char* cmd_line;
    int num_of_args;
    char** arguments;

    Command(const char* cmd_line);
    virtual ~Command();
    virtual void execute() = 0;
    //virtual void prepare();
    //virtual void cleanup();
    // TODO: Add your extra methods if needed
};

class BuiltInCommand : public Command {
public:
    BuiltInCommand(const char* cmd_line): Command(cmd_line)
    {

    }
    virtual ~BuiltInCommand()=default;
};

class ExternalCommand : public Command {
public:
    explicit ExternalCommand(const char* cmd_line);
    virtual ~ExternalCommand() {}
    void execute() override;
};

class PipeCommand : public Command {
    // TODO: Add your data members
public:
    explicit PipeCommand(const char* cmd_line);
    virtual ~PipeCommand() =default;
    void execute() override;
};

class RedirectionCommand : public Command {
public:
    explicit RedirectionCommand(const char* cmd_line);
    virtual ~RedirectionCommand() =default;
    void execute() override;
    //void prepare() override;
    //void cleanup() override;
};

class ChangeDirCommand : public BuiltInCommand {
public:
    std::string newdir;
    explicit ChangeDirCommand(const char* cmd_line);
    virtual ~ChangeDirCommand() =default;
    void execute() override;
};

class ChangePrompt : public BuiltInCommand {
public:
    virtual ~ChangePrompt()=default;
    void execute() override;
    explicit ChangePrompt(const char* cmd_line);

};

class GetCurrDirCommand : public BuiltInCommand {
public:
    explicit GetCurrDirCommand(const char* cmd_line);
    virtual ~GetCurrDirCommand()=default;
    void execute() override;
};

class ShowPidCommand : public BuiltInCommand {
public:
    ShowPidCommand(const char* cmd_line);
    virtual ~ShowPidCommand() {}
    void execute() override;
};

class JobsList;
class QuitCommand : public BuiltInCommand {
public:
    QuitCommand(const char* cmd_line);
    virtual ~QuitCommand() {}
    void execute() override;
};

enum JobStatus{bg=0, stopped=1};
class JobsList {
public:
    class JobEntry {
    public:
        int job_pid;
        int job_id;
        JobStatus job_status;
        const char * discript;
        time_t insert_time;
        time_t stopped_time;
        //JobEntry(Command* cmd, int pid,JobStatus isStopped);
        JobEntry()= default;
        void StopJob();
        void ContinueJob();
    };
    std::vector<JobEntry *>* List ;
public:
    JobsList(): List(new std::vector<JobEntry *>)
    {}
    ~JobsList()=default;
    void addJob(const char* cmd,int pid, JobStatus isStopped);
    void printJobsList();
    void killAllJobs();
    void removeFinishedJobs();
    JobEntry * getJobById(int jobId);
    JobEntry * getJobByPid(int pid);
    void removeJobById(int jobId);

    int getLastJob();
    int getLastStoppedJob();
    // TODO: Add extra methods or modify exisitng ones as needed
};

class JobsCommand : public BuiltInCommand {
    // TODO: Add your data members
public:
    explicit JobsCommand(const char* cmd_line);
     ~JobsCommand() override=default;
    void execute() override;
};

class KillCommand : public BuiltInCommand {
    // TODO: Add your data members
public:
    explicit KillCommand(const char* cmd_line);
     ~KillCommand() override=default;
    void execute() override;
};

class ForegroundCommand : public BuiltInCommand {
    // TODO: Add your data members
public:
    explicit ForegroundCommand(const char* cmd_line);
    virtual ~ForegroundCommand() override=default;
    void execute() override;
};

class BackgroundCommand : public BuiltInCommand {
    // TODO: Add your data members
public:
    explicit BackgroundCommand(const char* cmd_line);
     ~BackgroundCommand() override=default;
    void execute() override;
};

class TailCommand : public BuiltInCommand {
public:
    explicit TailCommand(const char* cmd_line);
     ~TailCommand() override=default;
    void execute() override;
};

class TouchCommand : public BuiltInCommand {
public:
    explicit TouchCommand(const char* cmd_line);
    ~TouchCommand() override=default;
    void execute() override;
};


class SmallShell {
private:

    SmallShell();
public:
    std::string prompt;
    JobsList jobsList;
    std::string last_working_directory;
    //std::string current_working_directory;
    int pid; //the pid of smash
    int fg_pid; //the pid of foreground process
    //int fg_job_id; //the job id of foreground process
//    bool redirect_mode;
//    bool append_mode;
//    bool pipe_mode;
//    std::string command1;
//    std::string command2;
    Command* curr_cmd;
    Command *CreateCommand(const char * cmd_line);
    SmallShell(SmallShell const&)      = delete; // disable copy ctor
    void operator=(SmallShell const&)  = delete; // disable = operator
    static SmallShell& getInstance() // make SmallShell singleton
    {
        static SmallShell instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    ~SmallShell();
    void executeCommand(const char* cmd_line);
    // TODO: add extra methods as needed
};

#endif //SMASH_COMMAND_H_
