#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include <fstream>
#include <csignal>
#include <unistd.h>
#include <iostream>

const std::string LOCK_FILE = "/tmp/mi_programa.pid";

void writePID();

bool isAlreadyRunning() {
    std::ifstream f(LOCK_FILE);
    if (!f) {
        writePID();
        return false;
    } 

    pid_t pid;
    f >> pid;

    // kill con señal 0 solo comprueba si el proceso existe
    if (kill(pid, 0) == 0) {
        kill(pid, SIGUSR1);
        return true;  // El proceso con ese PID existe
    }
    writePID();
    return false;  // El PID es viejo/inválido
}

void writePID() {
    std::ofstream f(LOCK_FILE);
    f << getpid();
}

void closeLockFile() {
    remove(LOCK_FILE.c_str());
}
