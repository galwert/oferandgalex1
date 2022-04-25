#ifndef SMASH_COMMAND_H_
#define SMASH_COMMAND_H_

#include <vector>

#define COMMAND_ARGS_MAX_LENGTH (200)
#define COMMAND_MAX_ARGS (20)

#define NOT_EXIST_IN_LIST
#define EMPTY_FG

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
    ExternalCommand(const char* cmd_line);
    virtual ~ExternalCommand() {}
    void execute() override;
};

class PipeCommand : public Command {
    // TODO: Add your data members
public:
    PipeCommand(const char* cmd_line);
    virtual ~PipeCommand() {}
    void execute() override;
};

class RedirectionCommand : public Command {
    // TODO: Add your data members
public:
    explicit RedirectionCommand(const char* cmd_line);
    virtual ~RedirectionCommand() {}
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
    virtual ~ChangePrompt()=default;
    void execute() override;

public:
// TODO: Add your data members public:
    explicit ChangePrompt(const char* cmd_line): BuiltInCommand(cmd_line)
    {

    }
};

class GetCurrDirCommand : public BuiltInCommand {
public:
    explicit GetCurrDirCommand(const char* cmd_line): BuiltInCommand(cmd_line)
    {}
    virtual ~GetCurrDirCommand()=default;
    void execute() override
    {
        char buf[80];
        std::cout <<getcwd(buf,80);
    }
};

class ShowPidCommand : public BuiltInCommand {
public:
    ShowPidCommand(const char* cmd_line);
    virtual ~ShowPidCommand() {}
    void execute() override;
};

class JobsList;
class QuitCommand : public BuiltInCommand {
// TODO: Add your data members public:
    QuitCommand(const char* cmd_line, JobsList* jobs);
    virtual ~QuitCommand() {}
    void execute() override;
};



class JobsList {
public:
    class JobEntry {
        int pid;
        int jobid;
        bool is_bg;
        bool is_running;
        char * discript;
    };
    std::vector<JobEntry *> List ;
public:
    JobsList();
    ~JobsList();
    void addJob(Command* cmd, bool isStopped = false);
    void printJobsList();
    void killAllJobs();
    void removeFinishedJobs();
    JobEntry * getJobById(int jobId);
    void removeJobById(int jobId);
    JobEntry * getLastJob(int* lastJobId);
    JobEntry *getLastStoppedJob(int *jobId);
    // TODO: Add extra methods or modify exisitng ones as needed
};

class JobsCommand : public BuiltInCommand {
    // TODO: Add your data members
public:
    JobsCommand(const char* cmd_line, JobsList* jobs);
    virtual ~JobsCommand() {}
    void execute() override;
};

class KillCommand : public BuiltInCommand {
    // TODO: Add your data members
public:
    KillCommand(const char* cmd_line, JobsList* jobs);
    virtual ~KillCommand() {}
    void execute() override;
};

class ForegroundCommand : public BuiltInCommand {
    // TODO: Add your data members
public:
    ForegroundCommand(const char* cmd_line, JobsList* jobs);
    virtual ~ForegroundCommand() {}
    void execute() override;
};

class BackgroundCommand : public BuiltInCommand {
    // TODO: Add your data members
public:
    BackgroundCommand(const char* cmd_line, JobsList* jobs);
    virtual ~BackgroundCommand() {}
    void execute() override;
};

class TailCommand : public BuiltInCommand {
public:
    TailCommand(const char* cmd_line);
    virtual ~TailCommand() {}
    void execute() override;
};

class TouchCommand : public BuiltInCommand {
public:
    TouchCommand(const char* cmd_line);
    virtual ~TouchCommand() {}
    void execute() override;
};


class SmallShell {
private:

    SmallShell();
public:
    std::string last_prompt;
    std::string prompt;
    JobsList jobsList;
    std::string last_working_directory;
    std::string current_working_directory;
    int fg_pid;
    int fg_job_id;
    bool redirect_mode;
    bool append_mode;
    bool pipe_mode;
    std::string command1;
    std::string command2;
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
