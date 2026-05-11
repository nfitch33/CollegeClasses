#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <mpi.h>
#include "hamcycle.h"

using namespace std;

extern int proc_rank;
extern int num_procs;
extern int debug;
extern bool graph[MAXDIM][MAXDIM];
extern int graphdim;

int* path = nullptr;

bool recursiveHam(int pos);
void displaytheSolution();

bool isValidStep(int n, int pos) {
    if (graph[path[pos-1]][n] == 0) return false;
    for (int i = 0; i < pos; i++) {
        if (path[i] == n) return false;
    }
    return true;
}

// Recursive Hamiltonian function with MPI
bool recursiveHam(int pos) {
    if (pos == graphdim) {
        return graph[path[pos-1]][path[0]] == 1;
    }

    for (int n = 1; n < graphdim; n++) {
        if (!isValidStep(n, pos)) continue;

        path[pos] = n;

        // MPI work split at 4th step
        if (pos == 3) {
            int sum = path[0] + path[1] + path[2];
            if (sum % num_procs != proc_rank) {
                path[pos] = -1;
                continue;
            }
        }

        if (recursiveHam(pos + 1)) return true;

        path[pos] = -1;
    }
    return false;
}

void displaytheSolution() {
    cout << proc_rank << "/" << num_procs << ": Hamiltonian Cycle Path: ";
    for (int i = 0; i < graphdim; i++) cout << path[i] << " ";
    cout << path[0] << endl;
}

// Print adjacency matrix
void printMatrix() {
    for (int row = 0; row < graphdim; ++row) {
        for (int col = 0; col < graphdim; ++col) {
            if (graph[row][col])
                cout << row << " <--> " << col << endl;
        }
    }
}

bool hamCycle() {
    path = new int[graphdim];
    for (int i = 0; i < graphdim; i++) path[i] = -1;
    path[0] = 0;

    // Safe MPI init
    int mpiInitialized = 0;
    MPI_Initialized(&mpiInitialized);
    if (!mpiInitialized) MPI_Init(nullptr, nullptr);

    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

    if (debug) printMatrix();

    bool found = recursiveHam(1);

    if (proc_rank != 0) {
        int flag = found ? 1 : 0;
        MPI_Send(&flag, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        if (found) MPI_Send(path, graphdim, MPI_INT, 0, 1, MPI_COMM_WORLD);
    } else {
        // Rank 0
        if (found) displaytheSolution();
        else cout << proc_rank << "/" << num_procs << ": Hamiltonian Cycle does not exist" << endl;

        // Receive results from other processes
        for (int src = 1; src < num_procs; src++) {
            int flag;
            MPI_Recv(&flag, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (flag) {
                int* recvPath = new int[graphdim];
                MPI_Recv(recvPath, graphdim, MPI_INT, src, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                cout << src << "/" << num_procs << ": Hamiltonian Cycle Path: ";
                for (int i = 0; i < graphdim; i++) cout << recvPath[i] << " ";
                cout << recvPath[0] << endl;
                delete[] recvPath;
            } else {
                cout << src << "/" << num_procs << ": Hamiltonian Cycle does not exist" << endl;
            }
        }
    }

    if (!mpiInitialized) MPI_Finalize();

    delete[] path;
    return found;
}