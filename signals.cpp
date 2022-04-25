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
  if (smash.fg_job_id == NOT_IN_LIST_BEFORE) {
    smash.jobsList.addJob);
  }
  smash: process <foreground-PID> was killed
}

void ctrlCHandler(int sig_num) {
  // TODO: Add your implementation
}

void alarmHandler(int sig_num) {
  // TODO: Add your implementation
}

