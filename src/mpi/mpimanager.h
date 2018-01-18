#ifndef MPI_MANAGER_H //include guard
#define MPI_MANAGER_H

#include "mpi.h"
#include "../variants/utils.h"
#include "../methods/method.h"
#include <vector>
using namespace std;

class MPImanager {
private:
	int rank;
	int number_processes;
	size_t size;
	vector<vector<vector<double>>> sub_matrices;
	
public:
	MPImanager(size_t size);
	void initialize(int *argc, char ** argv[]);
	void finalize();
	int get_rank();
	bool is_root();
	size_t lower_bound();
	size_t upper_bound();
	void add_sub_matrix(vector<vector<double>> sub_matrix);

	void collect_results(size_t solutions_size);
	void send_results();
};

#endif