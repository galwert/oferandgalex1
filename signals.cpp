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
  if (smash.fg_job_id == NOT_EXIST_IN_LIST) {
    smash.jobsList.addJob(smash.cmd_line, true));
  }
  else {
    smash.resumeJob(smash.cmd_line, smash.fg_job_id, smash.fg_pid, "stopped");
  }
  if (killpg(smash.fg_pid),SIGSTOP) == -1) { //ch name
    perror("smash error: kill failed");
    return;
  }
  cout << "smash: process" << smash.fg_pid << "was stopped" << endl;
  smash.fg_pid = EMPTY_FG;
  smash.fg_job_id = NOT_EXIST_IN_LIST;
}

void ctrlCHandler(int sig_num) {
  cout << "smash: got Ctrl-C" << endl;
  SmallShell& smash = SmallShell::getInstance();
  if (smash.fg_pid == EMPTY_FG) {
    return;
  }
  if (killpg(smash.fg_pid),SIGSTOP) == -1) { //ch name
    perror("smash error: kill failed");
    return;
  }
  cout << "smash: process" << smash.fg_pid << "was killed" << endl;
  smash.fg_pid = EMPTY_FG;
  smash.fg_job_id = NOT_EXIST_IN_LIST;
}

void alarmHandler(int sig_num) {
  SmallShell& smash = SmallShell::getInstance();
  cout << "smash: got an alarm" << endl;
  //TODO: search for the command caused the alarm and send SIGKILL to its process
  //cout << "smash: [command-line] timed out!" << endl;
}

