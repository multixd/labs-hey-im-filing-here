#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc, char *argv[])
{

	if( argc == 1) {
		fprintf(stderr, "ERROR: %s\n", strerror(22));
		return EINVAL;
	}

	else if(argc == 2) {
		if(execlp(argv[1], argv[1], (char *) NULL) == -1) {
			fprintf(stderr, "ERROR: %s\n", strerror(errno));
			
			return errno;
		}
	}
	
	else if(argc == 3) {
		int fds[2];
		int wstatus;

		pipe(fds);
		pid_t child1 = fork();
	
		if(child1 ==1) {
			close(fds[1]);
		}

		if(child1 == 0) {
			dup2(fds[1], STDOUT_FILENO);
			close(fds[1]);
			close(fds[0]);

			//printf("child1 closed write pipe, redirect stdout to fds[1]\n");
			execlp(argv[1],argv[1], (char*)NULL);
		}
		wait(&wstatus);
		printf("reaped child1\n");
		pid_t child2 = fork();

		if(child2 == 1){
			close(fds[1]);
			close(fds[0]);
		}

		if(child2 == 0) {
			close(fds[1]);
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			printf("child2 closed read pipe, redirect stdout to fds[0]\n");
			execlp(argv[2],argv[2], (char*)NULL);
		}
		wait(&wstatus);
		printf("reaped child2\n");

		/*
		if (pipe(fds) == -1) {
			fprintf(stderr, "ERROR: %s\n", strerror(errno));
			return errno;
		}

		pid_t child1 = fork();
		if (child1 == -1) {
			fprintf(stderr, "ERROR, problem forking: %s\n", strerror(errno));
			return errno;
		}
		if(child1 == 1) {
			close(fds[1]);
		}
	
		if(child1 == 0) {
			dup2(fds[1], STDOUT_FILENO);
			close(fds[1]);
			close(fds[0]);
			if(execlp(argv[1], argv[1], NULL) == -1) {
				fprintf(stderr, "ERROR: %s\n", strerror(errno));
				return errno;
			}
		}
		

		if(waitpid(-1, &wstatus, 0) == -1) {
			fprintf(stderr, "ERROR, problem waiting: %s\n" , strerror(errno));
			return errno;
		}

		if(!WIFEXITED(wstatus)) {
			int status = WEXITSTATUS(wstatus);
			fprintf(stderr, "ERROR, problem reaping child: %s\n", strerror(status));
			return status;
		}
		pid_t child2 = fork();
		if (child2 == -1) {
			fprintf(stderr, "ERROR, problem forking: %s\n", strerror(errno));
			return errno;
		}

		if(child2 == 1) {
			close(fds[0]);
		}
		if(child2 == 0) {
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			printf("hello\n");


			if(execlp(argv[2], argv[2], NULL) == -1) {
				fprintf(stderr, "ERROR: %s\n", strerror(errno));
				return errno;
			}
			printf("goodbye\n");
		}
		
		if(waitpid(-1, &wstatus, 0) == -1) {
			fprintf(stderr, "ERROR, problem waiting: %s\n" , strerror(errno));
			return errno;
		}

		if(!WIFEXITED(wstatus)) {
			int status = WEXITSTATUS(wstatus);
			fprintf(stderr, "ERROR, problem reaping child: %s\n", strerror(status));
			return status;
		}
	*/
	}
	else if (argc == 4) {
		int fds[2][2];
		int wstatus;

		pipe(fds[0]);
		pid_t child1 = fork();
		
		if(child1 == 1) {
			close(fds[0][1]);
		}
		if(child1 == 0) {
			dup2(fds[0][1], STDOUT_FILENO);
			close(fds[0][1]);
			close(fds[0][0]);
			execlp(argv[1],argv[1],NULL);
		}

		wait(&wstatus);

		pipe(fds[1]);
		pid_t child2 = fork();

		if(child2 == 1) {
			close(fds[0][0]);
			close(fds[1][1]);
		}
		if(child2 == 0) {
			dup2(fds[0][0], STDIN_FILENO);
			close(fds[0][0]);
			dup2(fds[1][1], STDOUT_FILENO);
			close(fds[1][1]);
			close(fds[1][0]);
			execlp(argv[2],argv[2],NULL);
		}
		
		wait(&wstatus);
		pid_t child3 = fork();
		
		if(child3 == 1) {
			close(fds[1][0]);
		}
		if(child3 == 0) {
			dup2(fds[1][0], STDIN_FILENO);
			close(fds[1][0]);
			execlp(argv[3],argv[3],NULL);
		}

		//wait(&wstatus);
		/*
		if (pipe(fds[0]) == -1) {
			fprintf(stderr, "ERROR: %s\n", strerror(errno));
			return errno;
		}
		

		pid_t child1 = fork();
		if (child1 == -1) {
			fprintf(stderr, "ERROR, problem forking: %s\n", strerror(errno));
			return errno;
		}
		if(child1 == 1) {
			close(fds[0][1]);
		}
	
		if(child1 == 0) {
			dup2(fds[0][1], STDOUT_FILENO);
			close(fds[0][1]);
			close(fds[0][0]);

			if(execlp(argv[1], argv[1], NULL) == -1) {
				fprintf(stderr, "ERROR: %s\n", strerror(errno));
				return errno;
			}
		}

		if(waitpid(-1, &wstatus, 0) == -1) {
			fprintf(stderr, "ERROR, problem waiting: %s\n" , strerror(errno));
			return errno;
		}

		if(!WIFEXITED(wstatus)) {
			int status = WEXITSTATUS(wstatus);
			fprintf(stderr, "ERROR, problem reaping child: %s\n", strerror(status));
			return status;
		}


		if(pipe(fds[1]) == -1) {
			fprintf(stderr, "ERROR: %s\n", strerror(errno));
			return errno;
			}

		pid_t child2 = fork();
		if (child2 == -1) {
			fprintf(stderr, "ERROR, problem forking: %s\n", strerror(errno));
			return errno;
		}
		if(child2 == 1) {
			close(fds[0][0]);
			close(fds[1][1]);
		}

		if(child2 == 0) {
			dup2(fds[0][0], STDIN_FILENO);
			close(fds[0][0]);
			dup2(fds[1][1], STDOUT_FILENO);
			close(fds[1][1]);
			close(fds[1][0]);

			
			if(execlp(argv[2], argv[2], NULL) == -1) {
				fprintf(stderr, "ERROR: %s\n", strerror(errno));
				return errno;
			}
		}
		
		if(waitpid(-1, &wstatus, 0) == -1) {
			fprintf(stderr, "ERROR, problem waiting: %s\n" , strerror(errno));
			return errno;
		}

		if(!WIFEXITED(wstatus)) {
			int status = WEXITSTATUS(wstatus);
			fprintf(stderr, "ERROR, problem reaping child: %s\n", strerror(status));
			return status;
		}


		pid_t child3 = fork();
		if (child3 == -1) {
			fprintf(stderr, "ERROR, problem forking: %s\n", strerror(errno));
			return errno;
		}
		if(child3 == 1) {
			close(fds[1][0]);
		}

		if(child3 == 0) {
			dup2(fds[1][0], STDIN_FILENO);
			close(fds[1][0]);

			if(execlp(argv[3], argv[3], NULL) == -1) {
				fprintf(stderr, "ERROR: %s\n", strerror(errno));
				return errno;
			}
		}
		*/

	}
	
	//int wstatus;
	//WIFEXITED(wstatus);
	//WEXITSTATUS(wstatus);

	return 0;
}
