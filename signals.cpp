#include <iostream>
#include <signal.h>
#include "signals.h"
#include "Commands.h"

using namespace std;

void ctrlZHandler(int sig_num) {
	cout << "smash: got Ctrl-Z" << endl;
  SmallShell& smash = SmallShell::getInstance();
  if (smash.fg_pid == EMPTY_FG) {
    return;
  }
  if (smash.jobsList.getJobByPid(smash.fg_pid) == nullptr) {
    smash.jobsList.addJob(smash.curr_cmd->cmd_line,smash.fg_pid, stopped);
  }

    smash.jobsList.getJobByPid(smash.fg_pid)->StopJob();
  if (kill(smash.fg_pid,SIGSTOP) == -1) {
    perror("smash error: kill failed");
    return;
  }
  cout << "smash: process " << smash.fg_pid << " was stopped" << endl;
  smash.fg_pid = EMPTY_FG;
}

void ctrlCHandler(int sig_num) {
  cout << "smash: got Ctrl-C" << endl;
  SmallShell& smash = SmallShell::getInstance();
  if (smash.fg_pid == EMPTY_FG) {
    return;
  }
  if (kill(smash.fg_pid,SIGKILL) == -1) { //ch name
    perror("smash error: kill failed");
    return;
  }
  cout << "smash: process " << smash.fg_pid << " was killed" << endl;
  smash.fg_pid = EMPTY_FG;
}

void alarmHandler(int sig_num) {
  cout << "smash: got an alarm" << endl;
  //TODO: search for the command caused the alarm and send SIGKILL to its process
  //cout << "smash: [command-line] timed out!" << endl;
}

