#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){
  
  int rank, size, ierr;
  int sendto, recvfrom;       /* tasks to send to and receive from */
  int tag=1;                  /* shared tag to label msgs */
  char sendmessage[]="Hello"; /* text to send */
  char getmessage[5];         /* place to receive */
  MPI_Status rstatus;         /* MPI_Recv status info */
  
  /* initialize for MPI */
  MPI_Init(&argc, &argv);


  /* get number of processes */
  MPI_Comm_size(MPI_COMM_WORLD, &size);


  /* get this process's number (ranges from 0 to nprocs - 1) */ 
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
  int count=6;
  if(rank==0){
    sendto=1;

    ierr=MPI_Ssend(sendmessage, 6, MPI_CHAR, sendto, tag, MPI_COMM_WORLD);; /* complete this statement */
	//int MPI_Ssend(&sendmessage, 5, MPI_BYTE, 1, 1, MPI_COMM_WORLD);

    printf("%d: Sent message <%s>\n",rank, sendmessage);
  }
  else if(rank==1){
    recvfrom=0;

	ierr = MPI_Recv(getmessage, 6, MPI_CHAR, recvfrom, tag, MPI_COMM_WORLD, &rstatus);
    //ierr=MPI_Recv( ); /* complete this statement */

    printf("%d: Got message  <%s>\n",rank, getmessage);
  }
  
  /* clean up for MPI */
  MPI_Finalize();

  return 0;
}
