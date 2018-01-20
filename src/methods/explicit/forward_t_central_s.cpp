#include "forward_t_central_s.h"

// CONSTRUCTORS
/*=
 *Default constructor, method to solve a the first iteration of explicit methods.
 */
FTCS::FTCS(Problem problem)
: Explicit(problem) {
	name = FORWARD_TIME_CENTRAL_SPACE;
}

/*
* Normal public method - compute the first iteration of explicit methods
*/
double* FTCS::build_iteration(double* current_step, double* previous_step, MPImanager *mpi_manager, double &back, double &forward) {
	size_t upper = mpi_manager->upper_bound(), lower = mpi_manager->lower_bound(), size = upper - lower + 1, upper_limit = problem.get_xsize() - 2;
	int rank = mpi_manager->get_rank();
	double * result = new double[size], back_space = -1.0, forward_space = -1.0;

	for (size_t i = 0; i <= size; i++) {
		wait(mpi_manager, i);

		double back_space = i == 0 ? back : previous_step[i - 1], forward_space = i + 1 > size ? forward : previous_step[i + 1];
		result[i] = previous_step[i] + q / 2.0 * (forward_space - 2.0 * previous_step[i] + back_space);

		exchange_data(mpi_manager, i, result, back, forward);
	}
	return result;
}

void FTCS::wait(MPImanager * mpi_manager, size_t i) {
	size_t upper = mpi_manager->upper_bound(), lower = mpi_manager->lower_bound(), size = upper - lower + 1;
	int rank = mpi_manager->get_rank();

	if (i == 0) {
		if (!mpi_manager->is_last() && request_status[0]) {
			MPI_Wait(&requests[0], MPI_STATUS_IGNORE);
			std::cout << "Rank = " << rank << " waited for back from " << (rank - 1) << std::endl;
		}
		if (!mpi_manager->is_root() && request_status[1]) {
			MPI_Wait(&requests[1], MPI_STATUS_IGNORE);
			std::cout << "Rank = " << rank << " waited for back to " << (rank + 1) << std::endl;
		}
	}

	if (i == size) {
		if (!mpi_manager->is_root() && request_status[2]) {
			MPI_Wait(&requests[2], MPI_STATUS_IGNORE);
			std::cout << "Rank = " << rank << " waited for forward from " << (rank - 1) << std::endl;
		}
		if (!mpi_manager->is_last() && request_status[3]) {
			MPI_Wait(&requests[3], MPI_STATUS_IGNORE);
			std::cout << "Rank = " << rank << " waited for forward to " << (rank + 1) << std::endl;
		}
	}
}

void FTCS::exchange_data(MPImanager *mpi_manager, size_t i, const double result[], double &back, double &forward) {
	size_t upper = mpi_manager->upper_bound(), lower = mpi_manager->lower_bound(), size = upper - lower + 1;
	int rank = mpi_manager->get_rank();

	if (i == 0) {
		if (!mpi_manager->is_root()) {
			MPI_Irecv(&back, 1, MPI_DOUBLE, 0, rank - 1, MPI_COMM_WORLD, &requests[1]);
			if (!request_status[1]) request_status[1] = true;
		}
		if (!mpi_manager->is_last()) {
			MPI_Isend(&result[i], 1, MPI_DOUBLE, 0, rank + 1, MPI_COMM_WORLD, &requests[0]);
			if (!request_status[0]) request_status[0] = true;
		}
	}
	if (i == size) {
		if (!mpi_manager->is_last()) {
			MPI_Irecv(&forward, 1, MPI_DOUBLE, 0, rank + 1, MPI_COMM_WORLD, &requests[3]);
			if (!request_status[3]) request_status[3] = true;
		}
		if (!mpi_manager->is_root()) {
			MPI_Isend(&result[i], 1, MPI_DOUBLE, 0, rank - 1, MPI_COMM_WORLD, &requests[2]);
			if (!request_status[2]) request_status[2] = true;
		}
	}
}