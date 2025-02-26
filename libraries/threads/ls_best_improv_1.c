#include "ls_best_improv.h"

void* local_search3_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* op_name = PCR_BS_F;

	int flag_while1 = 1;
	int while_ = 1;
	do{
		clock_t time_s = clock();
		Solution* s_line = pcr_best_improvement_foward(copySolution(s), 0);

		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
		sem_post(&semaphore);
		
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeSolution(s_line);
			free(s_line);

			flag_while1 = 0;

			sem_wait(&semaphore_finished_functions);
			finished_functions++;
			sem_post(&semaphore_finished_functions);

			if(finished_functions < used_local_search){
				while_ = 2;
				Solution * copy = copySolution(s);
				freeSolution(s);
				s = shake(copy, k);	
			}
		}
	}while(flag_while1 || finished_functions < used_local_search);

	freeSolution(s);
	free(s);

    return NULL;
}

void* local_search4_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* op_name = PCR_BS_B;

	int flag_while1 = 1;
	int while_ = 1;
	do{
		clock_t time_s = clock();
		Solution* s_line = pcr_best_improvement_backward(copySolution(s), 0);

		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
		sem_post(&semaphore);
		
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeSolution(s_line);
			free(s_line);

			flag_while1 = 0;

			sem_wait(&semaphore_finished_functions);
			finished_functions++;
			sem_post(&semaphore_finished_functions);

			if(finished_functions < used_local_search){
				while_ = 2;
				Solution * copy = copySolution(s);
				freeSolution(s);
				s = shake(copy, k);	
			}
		}
	}while(flag_while1 || finished_functions < used_local_search);
	freeSolution(s);
	free(s);

    return NULL;
}

/***BEST IMPROVEMENT FUNCTIONS OF K-SWAP (K = 1 ... 5) FOWARD AND BACKWARD. SO WE HAVE 10 FUNCTIONS.*******/
void* local_search15_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* op_name = concatKtoSwap("1", KSWAP_BS_F);
	int flag_while1 = 1;
	int while_ = 1;
	do{
		clock_t time_s = clock();
		Solution* s_line = kswap_best_improvement_foward(copySolution(s), 1);

		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
		sem_post(&semaphore);
		
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeSolution(s_line);
			free(s_line);

			flag_while1 = 0;

			sem_wait(&semaphore_finished_functions);
			finished_functions++;
			sem_post(&semaphore_finished_functions);

			if(finished_functions < used_local_search){
				while_ = 2;
				Solution * copy = copySolution(s);
				freeSolution(s);
				s = shake(copy, k);	
			}
		}
	}while(flag_while1 || finished_functions < used_local_search);

	free(op_name);
	freeSolution(s);
	free(s);

    return NULL;
}

void* local_search16_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* op_name = concatKtoSwap("1", KSWAP_BS_B);

	int flag_while1 = 1;
	int while_ = 1;
	do{
		clock_t time_s = clock();
		Solution* s_line = kswap_best_improvement_backward(copySolution(s), 1);

		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
		sem_post(&semaphore);
		
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeSolution(s_line);
			free(s_line);

			flag_while1 = 0;

			sem_wait(&semaphore_finished_functions);
			finished_functions++;
			sem_post(&semaphore_finished_functions);

			if(finished_functions < used_local_search){
				while_ = 2;
				Solution * copy = copySolution(s);
				freeSolution(s);
				s = shake(copy, k);	
			}
		}
	}while(flag_while1 || finished_functions < used_local_search);

	free(op_name);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search17_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* op_name = concatKtoSwap("2", KSWAP_BS_F);

	int flag_while1 = 1;
	int while_ = 1;
	do{
		clock_t time_s = clock();
		Solution* s_line = kswap_best_improvement_foward(copySolution(s), 2);

		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
		sem_post(&semaphore);
		
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeSolution(s_line);
			free(s_line);

			flag_while1 = 0;

			sem_wait(&semaphore_finished_functions);
			finished_functions++;
			sem_post(&semaphore_finished_functions);

			if(finished_functions < used_local_search){
				while_ = 2;
				Solution * copy = copySolution(s);
				freeSolution(s);
				s = shake(copy, k);	
			}
		}
	}while(flag_while1 || finished_functions < used_local_search);

	free(op_name);
	freeSolution(s);
	free(s);

    return NULL;
}

void* local_search18_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* op_name = concatKtoSwap("2", KSWAP_BS_B);

	int flag_while1 = 1;
	int while_ = 1;
	do{
		clock_t time_s = clock();
		Solution* s_line = kswap_best_improvement_backward(copySolution(s), 2);

		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
		sem_post(&semaphore);
		
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeSolution(s_line);
			free(s_line);

			flag_while1 = 0;

			sem_wait(&semaphore_finished_functions);
			finished_functions++;
			sem_post(&semaphore_finished_functions);

			if(finished_functions < used_local_search){
				while_ = 2;
				Solution * copy = copySolution(s);
				freeSolution(s);
				s = shake(copy, k);	
			}
		}
	}while(flag_while1 || finished_functions < used_local_search);

	free(op_name);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search19_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* op_name = concatKtoSwap("3", KSWAP_BS_F);

	int flag_while1 = 1;
	int while_ = 1;
	do{
		clock_t time_s = clock();
		Solution* s_line = kswap_best_improvement_foward(copySolution(s), 3);

		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
		sem_post(&semaphore);
		
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeSolution(s_line);
			free(s_line);

			flag_while1 = 0;

			sem_wait(&semaphore_finished_functions);
			finished_functions++;
			sem_post(&semaphore_finished_functions);

			if(finished_functions < used_local_search){
				while_ = 2;
				Solution * copy = copySolution(s);
				freeSolution(s);
				s = shake(copy, k);	
			}
		}
	}while(flag_while1 || finished_functions < used_local_search);

	free(op_name);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search20_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* op_name = concatKtoSwap("3", KSWAP_BS_B);

	int flag_while1 = 1;
	int while_ = 1;
	do{
		clock_t time_s = clock();
		Solution* s_line = kswap_best_improvement_backward(copySolution(s), 3);

		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
		sem_post(&semaphore);
		
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeSolution(s_line);
			free(s_line);

			flag_while1 = 0;

			sem_wait(&semaphore_finished_functions);
			finished_functions++;
			sem_post(&semaphore_finished_functions);

			if(finished_functions < used_local_search){
				while_ = 2;
				Solution * copy = copySolution(s);
				freeSolution(s);
				s = shake(copy, k);	
			}
		}
	}while(flag_while1 || finished_functions < used_local_search);

	free(op_name);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search21_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* op_name = concatKtoSwap("4", KSWAP_BS_F);

	int flag_while1 = 1;
	int while_ = 1;
	do{
		clock_t time_s = clock();
		Solution* s_line = kswap_best_improvement_foward(copySolution(s), 4);

		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
		sem_post(&semaphore);
		
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeSolution(s_line);
			free(s_line);

			flag_while1 = 0;

			sem_wait(&semaphore_finished_functions);
			finished_functions++;
			sem_post(&semaphore_finished_functions);

			if(finished_functions < used_local_search){
				while_ = 2;
				Solution * copy = copySolution(s);
				freeSolution(s);
				s = shake(copy, k);	
			}
		}
	}while(flag_while1 || finished_functions < used_local_search);

	free(op_name);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search22_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* op_name = concatKtoSwap("4", KSWAP_BS_B);

	int flag_while1 = 1;
	int while_ = 1;
	do{
		clock_t time_s = clock();
		Solution* s_line = kswap_best_improvement_backward(copySolution(s), 4);

		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
		sem_post(&semaphore);
		
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeSolution(s_line);
			free(s_line);

			flag_while1 = 0;

			sem_wait(&semaphore_finished_functions);
			finished_functions++;
			sem_post(&semaphore_finished_functions);

			if(finished_functions < used_local_search){
				while_ = 2;
				Solution * copy = copySolution(s);
				freeSolution(s);
				s = shake(copy, k);	
			}
		}
	}while(flag_while1 || finished_functions < used_local_search);
	free(op_name);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search23_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* op_name = concatKtoSwap("5", KSWAP_BS_F);

	int flag_while1 = 1;
	int while_ = 1;
	do{
		clock_t time_s = clock();
		Solution* s_line = kswap_best_improvement_backward(copySolution(s), 5);

		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
		sem_post(&semaphore);
		
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeSolution(s_line);
			free(s_line);

			flag_while1 = 0;

			sem_wait(&semaphore_finished_functions);
			finished_functions++;
			sem_post(&semaphore_finished_functions);

			if(finished_functions < used_local_search){
				while_ = 2;
				Solution * copy = copySolution(s);
				freeSolution(s);
				s = shake(copy, k);	
			}
		}
	}while(flag_while1 || finished_functions < used_local_search);
	free(op_name);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search24_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* op_name = concatKtoSwap("5", KSWAP_BS_B);

	int flag_while1 = 1;
	int while_ = 1;
	do{
		clock_t time_s = clock();
		Solution* s_line = kswap_best_improvement_backward(copySolution(s), 5);

		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, op_name, while_);
		sem_post(&semaphore);
		
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, op_name, while_);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeSolution(s_line);
			free(s_line);

			flag_while1 = 0;

			sem_wait(&semaphore_finished_functions);
			finished_functions++;
			sem_post(&semaphore_finished_functions);

			if(finished_functions < used_local_search){
				while_ = 2;
				Solution * copy = copySolution(s);
				freeSolution(s);
				s = shake(copy, k);	
			}
		}
	}while(flag_while1 || finished_functions < used_local_search);
	free(op_name);
	freeSolution(s);
	free(s);
    return NULL;
}