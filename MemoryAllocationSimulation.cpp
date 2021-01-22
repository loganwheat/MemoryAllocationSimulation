/***********************************************************************
 * File: MemoryAllocationSimulation.cpp
 *
 * Author: Logan Wheat
 *
 * Modification History: 10/13/2019 : wrote the code: Logan Wheat
 *
 * Procedures:
 *     main - functions as the driver function to choose what simulation
 *     to run. A menu is displayed showing possible options, which allows
 *     the user to insert an integer choosing his/her option. A switch statement
 *     calls the proper function.
 *
 *     fixed - simulates the process of memory allocation using fixed
 *     partitioning of 8 equal partitions of 8 MB's.
 *
 *     fixedUnequal - simulates the process of memory allocation using fixed
 *     partitioning of 8 unequal partitions of 8, 2, 4, 6, 8, 8, and 12 MB's. 
 *
 *     dynamic() - simulates the process of memory allocation using dynamic
 *     partitioning of 56 MB's.
 *
 ***********************************************************************/

#include <iostream>
#include <ctime> // to count clock ticks to calculate time
#include <cstdlib> // for rand() function

using namespace std;

#define MEMORY_LIMIT 64 // define the memory limit as 64 simulated MB
#define OPERATING_SYSTEM_SIZE 8 // define size of OS as 8 simulated MB

struct processStruct
{
  int memoryReq; // declare memory required as a random int between 0 and 16 (excluding 0 and 16)
  int time; // declare amount of run time as 10 units(ticks)
};


struct partition
{
  int memory; // declare memory as an int to simulate MB
  processStruct currentProcess; // declare a process to determine current process
};


/***************************************************************************
 * void fixed()
 * Author: Logan Wheat
 * Date: 13 October 2019
 * Description: simulates the process of memory allocation using fixed
 *      partitioning of 8 equal partitions of 8 MB's. Average time out of 1000
 *      simulations of 1000 processes per simulation is outputted at the end of the function.
 *
 * Parameters:
 * none
 **************************************************************************/

void fixed()
{
  int partitions = 8; // declare number of partitions as 8 (1 designated for OS)
  int partitionSize = 8; // declare size of partitions as 8 simulated MB

  double simulationTime[1000]; // declare array to store time of simulation

  for (int simulation = 0; simulation < 1000; simulation++)
    {
      bool simComplete = false; // boolean to determine when simulation is complete

      processStruct *processes = new processStruct[1000]; // declare new processes for this simulation

      // for loop to fill processes with random sizes
      for (int i = 0; i < 1000; i++)
	{
	  processes[i].memoryReq = rand() % 7 + 1; // random size (0,8)
	  processes[i].time = rand() % 10 + 1; // random runtime (0,10]
	}

      partition *fixedPartition = new partition[partitions];

      fixedPartition[0].memory = OPERATING_SYSTEM_SIZE; // allocate space for operating system in the partition

      // for loop to create rest of partions (7 fixed partions of 8 simulated MB)
      for (int i = 1; i < partitions; i++)
	{
	  fixedPartition[i].memory = partitionSize;
	}

      int currentProc = 0; // initialize current process

      int processRuntime = 0; // declare simulated runtime

      while (simComplete == false)
	{
	  int mostRuntime = 0; // declare variable to keep track of longest runtime to simulate parallelism

	  for (int currentPart = 1; currentPart < partitions; currentPart++)
	    {
	      if (processes[currentProc].memoryReq <= fixedPartition[currentPart].memory) // if there is room for the process to run
		{
		  fixedPartition[currentPart].memory -= processes[currentProc].memoryReq; // take away memory that will be used to run process
		  
		  // if runtime of current process is longer than others in parallel, store as longest runtime
		  if (processes[currentProc].time > mostRuntime)
		    mostRuntime = processes[currentProc].time;

		  fixedPartition[currentPart].memory += processes[currentProc].memoryReq; // reallocate memory after process has been run
		  currentProc++; // increment the current process
		}
	      if (currentProc == 1000) // if final process has been run
		{
		  simComplete = true; // to end while loop
		  break; // break out of for loop
		}
	    }

	  processRuntime += mostRuntime; // add the runtime of the longest running process this iteration

	} // end of single simulation while loop

      simulationTime[simulation] = processRuntime; //calculate run time along with simulated process run time

      // deallocate memory
      delete processes;
      delete fixedPartition;

    } // end of total simulations for loop

  double sum = 0;

  // for loop to calculate sum of all simulation time
  for (int i = 0; i < 1000; i++)
    {
      sum += simulationTime[i];
    }

  double averageTime = sum/1000; // calculate average time

  cout << "Average time over 1,000 simulations is " << averageTime << " ticks." << endl;

} // end void fixed()


/***************************************************************************
 * void fixedUnequal()
 * Author: Logan Wheat
 * Date: 13 October 2019
 * Description: simulates the process of memory allocation using fixed
 *      partitioning of 8 unequal partitions of 8, 2, 4, 6, 8, 8, and 12 MB's. Average time out of 1000
 *      simulations of 1000 processes per simulation is outputted at the end of the function.
 *
 * Parameters:
 * none
 **************************************************************************/

void fixedUnequal()
{
  int partitions = 8; // declare number of partitions as 8 (1 designated for OS)
  int partitionSize[8] = {8, 2, 4, 6, 8, 8, 12, 16}; // declare size of partitions

  double simulationTime[1000]; // declare array to store time of simulation

  for (int simulation = 0; simulation < 1000; simulation++)
    {
      bool simComplete = false; // boolean to determine when simulation is complete

      processStruct *processes = new processStruct[1000]; // declare new processes for this simulation

      // for loop to fill processes with random sizes
      for (int i = 0; i < 1000; i++)
        {
          processes[i].memoryReq = rand() % 15 + 1; // random size (0,16]
          processes[i].time = rand() % 10 + 1; // random runtime (0,10]
        }

      partition *fixedPartition = new partition[partitions];

      fixedPartition[0].memory = OPERATING_SYSTEM_SIZE; // allocate space for operating system in the partition
      // for loop to create rest of partions (7 fixed partions of 8 simulated MB)
      for (int i = 1; i < partitions; i++)
        {
          fixedPartition[i].memory = partitionSize[i];
        }

      int currentProc = 0; // initialize current process

      int processRuntime = 0; // declare simulated runtime

      while (simComplete == false)
        {
          int mostRuntime = 0; // declare variable to keep track of longest runtime to simulate parallelism

          for (int currentPart = 1; currentPart < partitions; currentPart++)
            {
              if (processes[currentProc].memoryReq <= fixedPartition[currentPart].memory) // if there is room for the process to run
                {
                  fixedPartition[currentPart].memory -= processes[currentProc].memoryReq; // take away memory that will be used to run process

                  // if runtime of current process is longer than others in parallel, store as longest runtime
                  if (processes[currentProc].time > mostRuntime)
                    mostRuntime = processes[currentProc].time;

                  fixedPartition[currentPart].memory += processes[currentProc].memoryReq; // reallocate memory after process has been run
                  currentProc++; // increment the current process
                }
              if (currentProc == 1000) // if final process has been run
                {
                  simComplete = true; // to end while loop
                  break; // break out of for loop
                }
            }

          processRuntime += mostRuntime; // add the runtime of the longest running process this iteration

        } // end of single simulation while loop

      simulationTime[simulation] = processRuntime; //calculate run time along with simulated process run time

      // deallocate memory
      delete processes;
      delete fixedPartition;

    } // end of total simulations for loop

  double sum = 0;

  // for loop to calculate sum of all simulation time
  for (int i = 0; i < 1000; i++)
    {
      sum += simulationTime[i];
    }

  double averageTime = sum/1000; // calculate average time

  cout << "Average time over 1,000 simulations is " << averageTime << " ticks." << endl;

} // end void fixedUnequal()


/***************************************************************************
 * void dynamic()
 * Author: Logan Wheat
 * Date: 13 October 2019
 * Description: simulates the process of memory allocation using dynamic
 *      partitioning of 56 MB's.Average time out of 1000 simulations of 
 *      1000 processes per simulation is outputted at the end of the function.
 *
 * Parameters:
 * none
 **************************************************************************/

void dynamic()
{
  double simulationTime[1000]; // declare array to store simulation time

  for (int simulation = 0; simulation < 1000; simulation++)
    {
      bool simComplete = false; // boolean to determine when simulation is complete

      processStruct *processes = new processStruct[1000]; // declare new processes for this simulation

      // for loop to fill processes with random sizes
      for (int i = 0; i < 1000; i++)
        {
          processes[i].memoryReq = rand() % 15 + 1; // random size (0,16]
          processes[i].time = rand() % 10 + 1; // random runtime (0,10]
        }

      int totalTicks = 0;
      int currentProc = 0;

      while (simComplete == false)
	{
	  int mostRun = 0;
	  int availableMem = 56; // available memory is a simulated 56 MB bc 8 of which are for the OS

	  bool isAvailable = true;

	  while(isAvailable == true)
	    {
	      if (currentProc >= 1000)
		{
		  simComplete = true;
		  isAvailable = false;
		}
	      else
		{
		  if (processes[currentProc].memoryReq <= availableMem)
		    {
		      availableMem-=processes[currentProc].memoryReq;

		      if(processes[currentProc].time > mostRun)
			mostRun = processes[currentProc].time;

		      currentProc++;
		    }
		  else
		    isAvailable = false;
		}
	    } // end of available memory loop

	  totalTicks+=mostRun;

	} // end of single simulation loop

      simulationTime[simulation] = totalTicks;

    } // end of simulation for loop

  double sum = 0;

  // for loop to calculate sum of all simulation time
  for (int i = 0; i < 1000; i++)
    {
      sum += simulationTime[i];
    }

  double averageTime = sum/1000; // calculate average time

  cout << "Average time over 1,000 simulations is " << averageTime << " ticks." << endl;


} // end of void Dynamic


  /***************************************************************************
   * int main( int argc, char *argv[] )
   * Author: Logan Wheat
   * Date: 13 October 2019
   * Description: functions as the driver function to choose what simulation
   *     to run. A menu is displayed showing possible options, which allows
   *     the user to insert an integer choosing his/her option. A switch statement
   *     calls the proper function.
   *
   * Parameters:
   * argc I/P int The number of arguments on the command line
   * argv I/P char *[] The arguments on the command line
   * main O/P int Status code (not currently used)
   **************************************************************************/


int main(int argc, char *argv[])
{
  int choice; // declare user choice as int
  bool valid = false; // boolean to ensure proper selection

  while (valid == false)
    {
      cout << "Choose which form of memory allocation to simulate:\n";
      cout << "\t1.) Seven partitions of 8 MBs\n";
      cout << "\t2.) Fixed, unequal partitions: 2, 4, 6, 8, 8, 12, and 16 MBs\n";
      cout << "\t3.) Dynamic partition sizing of 56 MBs\n\n";

      cout << "\t(0 to exit) Enter selection: ";
      cin >> choice;
      cout << endl;

      if ( choice >= 0 && choice <= 4 )
	valid = true;
      else
	cout << "ERROR: Invalid choice: Options are 0, 1, 2, or 3\n";
    } // end of while loop

  switch (choice)
    {
    case 1:
      fixed();
      break;
    case 2:
      fixedUnequal();
      break;
    case 3:
      dynamic();
      break;
    }

  return 0;
}
