#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct process {
	bool done;
	bool first_time_execution;
	int id;
	int waiting;
	int * burstarray;
	int current_burst;
	int current_I_O;
	int * I_O_time;
	int databank_length;
	int response;
	int priority;
	int end_time;
	int arrival_time = 0;
	process *next;
};

//will initalize the process and will read the CPU burst and IOtime and place them into the corresponding process
process * Initialize_process_databank();

//print out put of:
//current time being executed, the time it being to be executed, the CPU burst of the process being executed,
//all process that are in the ready queue in order from shortest to longest and arrival time
// any process that are in the waiting queue in order by the amount of IO time they have left and the time they will leave the waiting queue
//any completed process in order by their ID number
void print_screen_SJF(process * ready, process * waiting, process* executing, int clock, process* complete);

//print out put of:
//current time being executed, the time it being to be executed, the CPU burst of the process being executed,
//three ready queue based on the prioirty level they are in and shows their arrival time
// any process that are in the waiting queue in order by the amount of IO time they have left and the time they will
//leave the waiting queue also their level priority
//any completed process in order by their ID number
void print_screen_MLFQ(process * Q1, process * Q2, process * Q3, process * waiting, process* executing, int clock, process* complete);

//save the out put into the file "SJF_Result.txt":
//current time being executed, the time it being to be executed, the CPU burst of the process being executed,
//all process that are in the ready queue in order from shortest to longest and arrival time
// any process that are in the waiting queue in order by the amount of IO time they have left and the time they will leave the waiting queue
//any completed process in order by their ID number
void print_SJF_file(process * ready, process * waiting, process* executing, int clock, process* complete, fstream &out);

//save the out put into the file "MLFQ_Result.txt":
//current time being executed, the time it being to be executed, the CPU burst of the process being executed,
//three ready queue based on the prioirty level they are in and shows their arrival time
// any process that are in the waiting queue in order by the amount of IO time they have left and the time they will
//leave the waiting queue also their level priority
//any completed process in order by their ID number
void print_MLFQ_file(process * Q1, process * Q2, process * Q3, process * waiting, process* executing, int clock, process* complete, fstream &out);

//will print the result of in the file 
// average WT,average RT, average TT, CPU utilization percentage, and total run time
void file_Result_MLFQ(double idle, int clock, process * complete, fstream &out);

//will print the result of in the file 
// average WT,average RT, average TT, CPU utilization percentage, and total run time
void file_Result_SJF(double idle, int clock, process * complete, fstream &out);

//simulate the SJF alogirthm with the 9 process
void SJF(process * p);

//simulate the MLFQ alogirthm with the 9 process
void MLFQ(process * p);

//will sort the process in order by their CPU burst for SJF
process * sorted(process * p);

int main()
{
	process *p = new process;
	p = Initialize_process_databank();
	p = sorted(p);
	SJF(p);

	p = Initialize_process_databank();
	MLFQ(p);

	return 0;
}

process * Initialize_process_databank()
{
	process *P1 = new process;         // declare and initialize 9 pointer to hold the 9 processes
	P1->done = false;
	P1->first_time_execution = true;
	P1->id = 1;
	P1->waiting = 0;
	P1->response = -1;
	P1->priority = 1;
	P1->end_time = -1;
	P1->arrival_time = 0;

	process *P2 = new process;
	P2->done = false;
	P2->first_time_execution = true;
	P2->id = 2;
	P2->waiting = 0;
	P2->response = -1;
	P2->priority = 1;
	P2->end_time = -1;
	P2->arrival_time = 0;

	process *P3 = new process;
	P3->done = false;
	P3->first_time_execution = true;
	P3->id = 3;
	P3->waiting = 0;
	P3->response = -1;
	P3->priority = 1;
	P3->end_time = -1;
	P3->arrival_time = 0;

	process *P4 = new process;
	P4->done = false;
	P4->first_time_execution = true;
	P4->id = 4;
	P4->waiting = 0;
	P4->response = -1;
	P4->priority = 1;
	P4->end_time = -1;
	P4->arrival_time = 0;

	process *P5 = new process;
	P5->done = false;
	P5->first_time_execution = true;
	P5->id = 5;
	P5->waiting = 0;
	P5->response = -1;
	P5->priority = 1;
	P5->end_time = -1;
	P5->arrival_time = 0;

	process *P6 = new process;
	P6->done = false;
	P6->first_time_execution = true;
	P6->id = 6;
	P6->waiting = 0;
	P6->response = -1;
	P6->priority = 1;
	P6->end_time = -1;
	P6->arrival_time = 0;

	process *P7 = new process;
	P7->done = false;
	P7->first_time_execution = true;
	P7->id = 7;
	P7->waiting = 0;
	P7->response = -1;
	P7->priority = 1;
	P7->end_time = -1;
	P7->arrival_time = 0;

	process *P8 = new process;
	P8->done = false;
	P8->first_time_execution = true;
	P8->id = 8;
	P8->waiting = 0;
	P8->response = -1;
	P8->priority = 1;
	P8->end_time = -1;
	P8->arrival_time = 0;

	process *P9 = new process;
	P9->done = false;
	P9->first_time_execution = true;
	P9->id = 9;
	P9->waiting = 0;
	P9->response = -1;
	P9->priority = 1;
	P9->end_time = -1;
	P9->arrival_time = 0;

	P1->next = P2;						//the 9 pointer are connected to each other by a link list
	P2->next = P3;
	P3->next = P4;
	P4->next = P5;
	P5->next = P6;
	P6->next = P7;
	P7->next = P8;
	P8->next = P9;
	P9->next = 0;

	process *head = P1;

	ifstream arraylist;					//the cpu burst and io timne are in a text file 
	arraylist.open("array.txt");
	int BURST_time;						//variable to hold the the char to convert it to an int
	int burst_array_counter = 0;
	int I_O_time;
	int I_O_counter = 0;
	string input;
	string values;
	int array_switch = 0;
	int array_length = 0;
	int seperators = 0;
	while (head && !(arraylist.eof()))
	{
		getline(arraylist, input);
		for (unsigned int a = 0; a < input.length(); a++) //count the amount of commas there is
		{												  //to determine the array length of the 
			if (input[a] == ',')                          //cpu burst array and io time array
				seperators++;
		}
		array_length = (seperators / 2) + 1;
		head->burstarray = new int[array_length];         //initialize array length of set of cpu burst of process
		head->I_O_time = new int[array_length];           //initialize array length of set of IO time of process
		head->databank_length = array_length;
		for (unsigned int i = 0; i < input.length(); i++)
		{
			if (input[i] <= 0x39 && input[i] >= 0x30)        //since value of cpu burst and io time are in a string 
			{                                             //the string is read one by one to seperate the values from 
				values = values + input[i];              //commas
			}
			if (input[i] == ',' && values != "")            // if we reach a comma that means that the value has been collected
			{
				if (array_switch == 0)                   // if array switch is 0 that mean that the value that was just read 
				{                                        //is a cpu burst 
					BURST_time = atoi(values.c_str());
					head->burstarray[burst_array_counter] = BURST_time;
					burst_array_counter++;
					array_switch = 1;
					values = "";
				}
				else if (array_switch == 1)            //and if its a 1 that means its a IO time .
				{
					I_O_time = atoi(values.c_str());
					head->I_O_time[I_O_counter] = I_O_time;
					I_O_counter++;
					array_switch = 0;
					values = "";
				}
			}
		}
		head->I_O_time[I_O_counter] = 0; //set the last io time of the process to be 0
		I_O_counter = 0;
		array_length = 0;
		burst_array_counter = 0;
		array_switch = 0;
		head = head->next;
		seperators = 0;
	}
	arraylist.close();
	return P1;
}
/////////////////////////////////////////////////SJF////////////////////////
void SJF(process * p)
{
	bool added_process = false;                 // this is for when process
	process* head = p;
	process * executing = 0;
	process * WQ = 0;
	process * prhold1 = 0;
	process * prhold2 = 0;
	process * prhold3 = 0;
	process * wthold1 = 0;
	process * wthold2 = 0;
	process * wthold3 = 0;
	process * ready = 0;
	process * complete = 0;
	process * holddone = 0;
	process * holddone2 = 0;
	int clock = 0;
	double idle = 0;
	fstream queuelist;
	queuelist.open("SJF_Result.txt");         //opens up the SJF_Results to print all the output of SJF alorithm 
	ready = head;                            //the processes were already sorted before entering the function.
											 /*while (head != 0)
											 {
											 if (head->waiting > 0)
											 {
											 if (WQ == 0)
											 {
											 WQ = head;
											 head = head->next;
											 WQ->next = 0;
											 }
											 else
											 {
											 hold = WQ;
											 while (hold->next != 0)
											 {
											 hold = hold->next;
											 }
											 hold->next = head;
											 head = head->next;
											 hold->next->next = 0;
											 }
											 }
											 else
											 {
											 if (ready == 0)
											 {
											 ready = head;
											 head = head->next;
											 ready->next = 0;
											 }
											 else
											 {
											 hold = ready;
											 while (hold->next != 0)
											 {
											 hold = hold->next;
											 }
											 hold->next = head;
											 head = head->next;
											 hold->next->next = 0;
											 }
											 }
											 }*/
LOOP1:
	if (ready != 0 && ready->databank_length > 0)		//checks if there are any process in ready queue		
	{
		//for the first process of the ready queue it
		ready->current_burst = ready->burstarray[0];        //take the begining cpu burst and IOtime of the array and set 
		ready->current_I_O = ready->I_O_time[0];            //it to the current CPU burst and IO of the process
		for (int i = 0; i < ready->databank_length - 1; i++)
		{
			ready->burstarray[i] = ready->burstarray[i + 1];
			ready->I_O_time[i] = ready->I_O_time[i + 1];
		}
		ready->burstarray[ready->databank_length - 1] = 0;
		ready->I_O_time[ready->databank_length - 1] = 0;
		ready->databank_length--;                           //now it take the first process of the ready queue and 
		executing = ready;								    //gives it to the executing queue and the ready queue 
		ready = ready->next;                               // go to the next process in the queue and set that to be the 
		executing->next = 0;                               //next process ready to be exectued
		print_screen_SJF(ready, WQ, executing, clock, complete);
		print_SJF_file(ready, WQ, executing, clock, complete, queuelist);
		if (executing->first_time_execution == true)       //this will set the response time of each of the processes
		{
			executing->first_time_execution = false;
			executing->response = clock;

		}

		for (int CPU = 0; CPU < executing->current_burst; executing->current_burst--) //loops until the current cpu burst is deplete of the process that is in execution
		{
			clock++;                                                            //clock increase by 1 time unit
			prhold1 = ready;                                                    //this while loop increase the wait time of every process in 
			while (prhold1 != 0)                                                //the ready queue by 1 time unit
			{
				prhold1->waiting++;
				prhold1 = prhold1->next;
			}
			wthold1 = WQ;                                                       //this while loop decrement the i/o time of any process in the 
			while (wthold1 != 0)                                                //waiting queue
			{
				wthold1->current_I_O--;
				if (wthold1->current_I_O == 0)                                  //for process that are in waiting and have completed all their IO time are 
				{                                                              //taken out of the waiting queue and added to the front of ready queue
					WQ = WQ->next;
					wthold1->next = ready;
					ready = wthold1;
					wthold1 = WQ;
					added_process = true;                                    //the variable that tell the program if a process has been aded to the queue
				}
				else
				{
					wthold1 = wthold1->next;
				}
			}
		}
		if (executing->current_burst == 0 && executing->current_I_O == 0 && executing->burstarray[0] == 0 && executing->I_O_time[0] == 0)
		{																//if the process has complete all of its cpu burst it will be added to the completed queue
																		//where the ending time will be initalized.			
			if (complete == 0)
			{
				complete = executing;
			}
			else														//sorts the process in the completed queue by there id values
			{
				holddone2 = complete;
				while (holddone2 != 0 && holddone2->id<executing->id)
				{
					holddone2 = holddone2->next;
				}
				if (holddone2 == complete)
				{
					executing->next = complete;
					complete = executing;
				}
				else
				{
					holddone = complete;
					while (holddone != 0 && holddone->next != holddone2)
					{
						holddone = holddone->next;
					}
					holddone->next = executing;
					executing->next = holddone2;

				}
			}
		}
		else if (WQ == 0)                                      //or adds the process that was executign into the waiting queue because it hasnt complete all of 
		{														//cpu bursts
			WQ = executing;
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		else													//sorts the process in the waiting queue by the amount of IO time they have from shortest to longest
		{
			wthold3 = WQ;
			while (wthold3 != 0 && wthold3->current_I_O < executing->current_I_O)
			{
				wthold3 = wthold3->next;
			}
			if (wthold3 == WQ)
			{
				executing->next = WQ;
				WQ = executing;
			}
			else
			{
				wthold2 = WQ;
				while (wthold2 != 0 && wthold2->next != wthold3)
				{
					wthold2 = wthold2->next;
				}
				executing->next = wthold3;
				wthold2->next = executing;
			}
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		if (added_process)                                        //if the added processes variable was activated then the program resort the process 
		{
			ready = sorted(ready);
			added_process = false;
		}


		goto LOOP1;												//returns to the top


	}
	if (ready == 0 && WQ != 0)										//at this point the syste is in idle 
	{
		wthold1 = WQ;
		executing = ready;
		print_screen_SJF(ready, WQ, executing, clock, complete);
		print_SJF_file(ready, WQ, executing, clock, complete, queuelist);
	LOOP2:
		wthold1 = WQ;
		clock++;
		idle++;
		while (wthold1 != 0)								//the clock increment by 1 , idle incrememnt by 1
		{													//loop two will be an infinite loop until a process has been
															//added to the ready queue
			wthold1->current_I_O--;
			if (wthold1->current_I_O == 0)
			{
				WQ = WQ->next;
				wthold1->next = ready;
				ready = wthold1;
				wthold1 = WQ;
				added_process = true;
			}
			else
			{
				wthold1 = wthold1->next;
			}
			if (added_process)
			{
				ready = sorted(ready);
				added_process = false;
				goto LOOP1;
			}
		}
		goto LOOP2;

	}
	else if (ready == 0 && WQ == 0 && complete != 0)        //when the program reaches here it means that all of the processes have been complete
	{
		double averageWT = 0;
		double averageRT = 0;
		double averageTT = 0;
		double timecalc = 0;
		double timeidle = 0;
		executing = ready;
		print_screen_SJF(ready, WQ, executing, clock, complete);						//the last output is displayed to show the time the function ended
		print_SJF_file(ready, WQ, executing, clock, complete, queuelist);
		file_Result_SJF(idle, clock, complete, queuelist);
		cout << "---------------------------------------------------------" << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << "Current Time: " << clock << endl << endl;
		cout << "Process Completed" << endl << endl;
		cout << "\tProcess" << "\t\tRT" << "\t\tWT" << "\t\tTT" << endl;
		while (complete != 0)															//cpu untitlization ,average TT,average RT, and average WT are calculated
		{

			cout << "\tP" << complete->id << "\t\t" << complete->response << "\t\t" << complete->waiting << "\t\t" << complete->end_time << endl;
			averageWT = averageWT + complete->waiting;
			averageRT = averageRT + complete->response;

			averageTT = averageTT + complete->end_time;
			complete = complete->next;

		}
		averageWT = averageWT / 9;
		averageRT = averageRT / 9;
		averageTT = averageTT / 9;
		timeidle = 1 - idle / clock;
		cout << endl << "Average Response Time:" << averageRT << endl;
		cout << endl << "Average Wait Time:" << averageWT << endl;
		cout << endl << "Average Turnaround Time:" << averageTT << endl;
		cout << endl << "CPU utilization:" << timeidle * 100 << "%" << endl << endl;
	}

	queuelist.close();												//file is closed

}
////////////////////////////////////////////////MLFQ///////////////////////////////
void MLFQ(process * p)
{
	bool added_process = false;
	process * head = p;
	process * WQ = 0;
	process * Q1 = 0;
	process * Q2 = 0;
	process * Q3 = 0;
	process * hold = 0;
	process * complete = 0;
	process * executing = 0;
	process * holdQ1, *holdQ3, *holdQ2, *holdQW;
	int clock = 0;
	double idle = 0;
	fstream queuelist;
	queuelist.open("MLFQ_Results.txt");					//the MLFQ_Results text file is opened
	Q1 = head;											// all process in head are set to queue 1 because we assum all process came in same time  
														/*	while (head != 0)									and all process start with a prioirty 1
														{
														if (head->waiting > 0)
														{
														if (WQ == 0)
														{
														WQ = head;
														head = head->next;
														WQ->next = 0;
														}
														else
														{
														hold = WQ;
														while (hold->next != 0)
														{
														hold = hold->next;
														}
														hold->next = head;
														head = head->next;
														hold->next->next = 0;
														}
														}
														else if (head->priority == 1)
														{
														if (Q1 == 0)
														{
														Q1 = head;
														head = head->next;
														Q1->next = 0;
														}
														else
														{
														hold = Q1;
														while (hold->next != 0)
														{
														hold = hold->next;
														}
														hold->next = head;
														head = head->next;
														hold->next->next = 0;
														}
														}
														else if (head->priority == 2)
														{
														if (Q2 == 0)
														{
														Q2 = head;
														head = head->next;
														Q2->next = 0;
														}
														else
														{
														hold = Q2;
														while (hold->next != 0)
														{
														hold = hold->next;
														}
														hold->next = head;
														head = head->next;
														hold->next->next = 0;
														}
														}
														else if (head->priority == 3)
														{
														if (Q3 == 0)
														{
														Q3 = head;
														head = head->next;
														Q3->next = 0;
														}
														else
														{
														hold = Q3;
														while (hold->next != 0)
														{
														hold = hold->next;
														}
														hold->next = head;
														head = head->next;
														hold->next->next = 0;
														}
														}
														else
														break;









														}*/
START:
	if (Q1 != 0)
	{
		Q1->current_burst = Q1->burstarray[0];						//for the first process of the ready queue it
		Q1->current_I_O = Q1->I_O_time[0];							//take the begining cpu burst and IOtime of the array and set
		for (int i = 0; i < Q1->databank_length - 1; i++)			 //it to the current CPU burst and IO of the process
		{
			Q1->burstarray[i] = Q1->burstarray[i + 1];
			Q1->I_O_time[i] = Q1->I_O_time[i + 1];
		}
		Q1->burstarray[Q1->databank_length - 1] = 0;
		Q1->I_O_time[Q1->databank_length - 1] = 0;
		Q1->databank_length--;
		executing = Q1;												 //now it take the first process of the ready queue and gives it to the 
		Q1 = Q1->next;												//executing queue and the ready queue go to the next process in the 
		executing->next = 0;										//queue and set that to be the next process ready to be exectued
		if (executing->first_time_execution == true)				//this will set the response time of each of the processes
		{
			executing->first_time_execution = false;
			executing->response = clock;

		}
		print_screen_MLFQ(Q1, Q2, Q3, WQ, executing, clock, complete);
		print_MLFQ_file(Q1, Q2, Q3, WQ, executing, clock, complete, queuelist);
		for (int i = 0; i < 7; i++)										//loop will run for 7 time units or less depend on processes cpu vurst
		{
			clock++;
			executing->current_burst--;

			holdQ1 = Q1;
			while (holdQ1 != 0)									//for the three different queue priority level it will go to each of the 
			{													//process and increment the wait time by 1 time unut
				holdQ1->waiting++;
				holdQ1 = holdQ1->next;
			}
			holdQ2 = Q2;
			while (holdQ2 != 0)
			{
				holdQ2->waiting++;
				holdQ2 = holdQ2->next;
			}
			holdQ3 = Q3;
			while (holdQ3 != 0)
			{
				holdQ3->waiting++;
				holdQ3 = holdQ3->next;
			}
			holdQW = WQ;
			while (holdQW != 0)							//for all of the process ion the waiting queue the io time gets decremented by one time unit
			{
				holdQW->current_I_O--;
				if (holdQW->current_I_O == 0)			//if a process finishes it io time it will be added to the back of its corresponding 
				{										//priority level queue
					if (holdQW->priority == 1)
					{
						if (Q1 == 0)
						{
							Q1 = WQ;
							WQ = WQ->next;
							Q1->next = 0;
						}
						else
						{
							hold = Q1;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
						holdQW = WQ;
					}
					else if (holdQW->priority == 2)
					{
						if (Q2 == 0)
						{
							Q2 = WQ;
							WQ = WQ->next;
							Q2->next = 0;
						}
						else
						{
							hold = Q2;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
						holdQW = WQ;
					}
					else if (holdQW->priority == 3)
					{
						if (Q3 == 0)
						{
							Q3 = WQ;
							WQ = WQ->next;
							Q3->next = 0;
						}
						else
						{
							hold = Q3;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
						holdQW = WQ;
					}

				}
				else
				{
					holdQW = holdQW->next;
				}
			}
			if (executing->current_burst == 0)					//will exit if cpu burst is finish before 7 time units
			{
				goto Q1timeup;
			}
		}
	Q1timeup:
		if (executing->current_burst > 0)				//if there is stil some time in the CPU burst the process will be down grade to qa lower prioirty
		{
			executing->arrival_time = clock;
			executing->priority = 2;
			if (Q2 == 0)
			{
				Q2 = executing;
			}
			else
			{
				hold = Q2;
				while (hold != 0 && hold->next != 0)
				{
					hold = hold->next;
				}

				hold->next = executing;
				executing = executing->next;
			}
		}
		else if (executing->current_burst == 0 && executing->current_I_O == 0 && executing->burstarray[0] == 0 && executing->I_O_time[0] == 0)
		{
			executing->end_time = clock;							//process will be added into the complete queue in order
			if (complete == 0)
			{
				complete = executing;
			}
			else
			{
				hold = complete;
				while (hold != 0 && hold->id<executing->id)
				{
					hold = hold->next;
				}
				if (hold == complete)
				{
					executing->next = complete;
					complete = executing;
				}
				else
				{
					holdQ1 = complete;
					while (holdQ1 != 0 && holdQ1->next != hold)
					{
						holdQ1 = holdQ1->next;
					}
					holdQ1->next = executing;
					executing->next = hold;

				}
			}

		}
		else if (WQ == 0)						//	if process has finished it cpu burst within the 7 time units then
		{										// it would be added to the waiting queue in order by it io time
			WQ = executing;
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		else
		{
			hold = WQ;
			while (hold != 0 && hold->current_I_O <= executing->current_I_O)
			{
				hold = hold->next;
			}
			if (hold == WQ)
			{
				executing->next = WQ;
				WQ = executing;
			}
			else
			{
				holdQW = WQ;
				while (holdQW != 0 && holdQW->next != hold)
				{
					holdQW = holdQW->next;
				}
				executing->next = hold;
				holdQW->next = executing;
			}
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		goto START;
	}
	else if (Q2 != 0)								// the program will enter this state if all process of prioirty 
	{												//1 are either complete or in waiting queue.
		if (Q2->current_burst <= 0)						//this check if the current burst has been deplete or not becuase
		{												//the process could have been pre-emptive by a process of level 1 priority
			Q2->current_burst = Q2->burstarray[0];
			Q2->current_I_O = Q2->I_O_time[0];
			for (int i = 0; i < Q2->databank_length - 1; i++)  //if cpu has been depleted it set the next current burst and io from the  
			{													//next values in the array
				Q2->burstarray[i] = Q2->burstarray[i + 1];
				Q2->I_O_time[i] = Q2->I_O_time[i + 1];			//if there is still some burst time left then it will skip this part 
			}
			Q2->burstarray[Q2->databank_length - 1] = 0;
			Q2->I_O_time[Q2->databank_length - 1] = 0;
			Q2->databank_length--;
		}
		executing = Q2;
		Q2 = Q2->next;
		executing->next = 0;
		if (executing->first_time_execution == true)          //i wrote this part just in case even though i know that all process would start 
		{													//as prioirty 1 and the response time would be set there
			executing->first_time_execution = false;
			executing->response = clock;

		}
		print_screen_MLFQ(Q1, Q2, Q3, WQ, executing, clock, complete);
		print_MLFQ_file(Q1, Q2, Q3, WQ, executing, clock, complete, queuelist);
		for (int i = 0; i < 14; i++)							//now the time quantum for level 2 prioirtity is 14
		{
			clock++;
			executing->current_burst--;							//process in ready will have their wait time incremeneted 
			holdQ2 = Q2;
			while (holdQ2 != 0)
			{
				holdQ2->waiting++;
				holdQ2 = holdQ2->next;
			}
			holdQ3 = Q3;
			while (holdQ3 != 0)
			{
				holdQ3->waiting++;
				holdQ3 = holdQ3->next;
			}
			holdQW = WQ;									// all process in ready queue will have their io time decremented
			while (holdQW != 0)
			{
				holdQW->current_I_O--;
				if (holdQW->current_I_O == 0)				// any process that have their io time depleted will be added to the ready queue
				{											//of their corresponding priority levels
					if (holdQW->priority == 1)
					{
						if (Q1 == 0)
						{
							Q1 = WQ;
							WQ = WQ->next;
							Q1->next = 0;
						}
						else
						{
							hold = Q1;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
					}
					else if (holdQW->priority == 2)
					{
						if (Q2 == 0)
						{
							Q2 = WQ;
							WQ = WQ->next;
							Q2->next = 0;
						}
						else
						{
							hold = Q2;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
					}
					else if (holdQW->priority == 3)
					{
						if (Q3 == 0)
						{
							Q3 = WQ;
							WQ = WQ->next;
							Q3->next = 0;
						}
						else
						{
							hold = Q3;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
					}
					holdQW = WQ;
				}
				else
				{
					holdQW = holdQW->next;
				}
			}
			if (Q1 != 0 && executing->current_burst>0)  // checks if any process of level 1 priority have been added to the queue
			{											//it will enter this part only if the process being executed still has burst time
				executing->arrival_time = clock;		//to pre-empt it
				if (Q2 == 0)
				{
					Q2 = executing;

				}
				else
				{
					hold = Q2;
					while (hold->next != 0)
					{
						hold = hold->next;
					}
					hold->next = executing;
					executing = executing->next;
				}
				goto START;
			}
			if (executing->current_burst == 0)			//if the cpu burst is complete before or at 14 time unit it will go to
			{											//Q2TIMEUP
				goto Q2TIMEUP;
			}


		}
	Q2TIMEUP:
		if (executing->current_burst > 0)				//if process still has time left on the current burst the process will 
		{												//downgrade to level 3 priority
			executing->arrival_time = clock;
			executing->priority = 3;
			if (Q3 == 0)
			{
				Q3 = executing;
			}
			else
			{
				hold = Q3;
				while (hold != 0 && hold->next != 0)
				{
					hold = hold->next;
				}

				hold->next = executing;
				executing = executing->next;
			}
		}
		else if (executing->current_burst == 0 && executing->current_I_O == 0 && executing->burstarray[0] == 0 && executing->I_O_time[0] == 0)
		{
			executing->end_time = clock;							//if process complete all cpu burst it will set ending time and will be place in the complete queue
			if (complete == 0)
			{
				complete = executing;
			}
			else
			{
				hold = complete;
				while (hold != 0 && hold->id<executing->id)
				{
					hold = hold->next;
				}
				if (hold == complete)
				{
					executing->next = complete;
					complete = executing;
				}
				else
				{
					holdQ1 = complete;
					while (holdQ1 != 0 && holdQ1->next != hold)
					{
						holdQ1 = holdQ1->next;
					}
					holdQ1->next = executing;
					executing->next = hold;

				}
			}

		}
		else if (WQ == 0)								//place in waiting queue in order		
		{
			WQ = executing;
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		else
		{
			hold = WQ;
			while (hold != 0 && hold->current_I_O <= executing->current_I_O)
			{
				hold = hold->next;
			}
			if (hold == WQ)
			{
				executing->next = WQ;
				WQ = executing;
			}
			else
			{
				holdQW = WQ;
				while (holdQW != 0 && holdQW->next != hold)
				{
					holdQW = holdQW->next;
				}
				executing->next = hold;
				holdQW->next = executing;
			}
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		goto START;
	}
	else if (Q3 != 0)										//if the program reaches this point that means Q1 and Q2
	{
		if (Q3->current_burst <= 0)							//check if there is still cpu burst that might off been
		{													// left over from before because the process got pre-empted
			Q3->current_burst = Q3->burstarray[0];
			Q3->current_I_O = Q3->I_O_time[0];
			for (int i = 0; i < Q3->databank_length - 1; i++)
			{
				Q3->burstarray[i] = Q3->burstarray[i + 1];
				Q3->I_O_time[i] = Q3->I_O_time[i + 1];
			}
			Q3->burstarray[Q3->databank_length - 1] = 0;
			Q3->I_O_time[Q3->databank_length - 1] = 0;
			Q3->databank_length--;
		}
		executing = Q3;
		Q3 = Q3->next;
		executing->next = 0;
		if (executing->first_time_execution == true)
		{
			executing->first_time_execution = false;
			executing->response = clock;

		}
		print_screen_MLFQ(Q1, Q2, Q3, WQ, executing, clock, complete);
		print_MLFQ_file(Q1, Q2, Q3, WQ, executing, clock, complete, queuelist);
		for (int CPU = 0; CPU < executing->current_burst;)
		{																//process will run until its current cpu burst is deplete, or
			clock++;													//if another process of higher priority comes into the ready queue

			holdQ3 = Q3;
			while (holdQ3 != 0)											//increment all process in ready queue by 1 time unit
			{
				holdQ3->waiting++;
				holdQ3 = holdQ3->next;
			}
			holdQW = WQ;												//decrement all io time by 1 time unit
			while (holdQW != 0)											//check if any process are finished with io and send them to 
			{															//ready queue of corresponding priority
				holdQW->current_I_O--;
				if (holdQW->current_I_O == 0)
				{
					if (holdQW->priority == 1)
					{
						if (Q1 == 0)
						{
							Q1 = WQ;
							WQ = WQ->next;
							Q1->next = 0;
						}
						else
						{
							hold = Q1;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
					}
					else if (holdQW->priority == 2)
					{
						if (Q2 == 0)
						{
							Q2 = WQ;
							WQ = WQ->next;
							Q2->next = 0;
						}
						else
						{
							hold = Q2;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
					}
					else if (holdQW->priority == 3)
					{
						if (Q3 == 0)
						{
							Q3 = WQ;
							WQ = WQ->next;
							Q3->next = 0;
						}
						else
						{
							hold = Q3;
							while (hold->next != 0)
							{
								hold = hold->next;
							}
							hold->next = WQ;
							WQ = WQ->next;
							hold->next->next = 0;
						}
					}
					holdQW = WQ;
				}
				else
				{
					holdQW = holdQW->next;
				}
			}
			executing->current_burst--;
			if ((Q1 != 0 || Q2 != 0) && executing->current_burst>0)					//check if any higher prioirty level queue enter the ready queue 
			{																		//also to see ifthe process has comeplete it burst or not to either 
																		//pre-empt it or send it to waiting queue
				executing->arrival_time = clock;
				if (Q3 == 0)
				{
					Q3 = executing;

				}
				else
				{
					hold = Q3;
					while (hold->next != 0)
					{
						hold = hold->next;
					}
					hold->next = executing;
					executing = executing->next;
				}
				goto START;

			}
		}
		if (executing->current_burst == 0 && executing->current_I_O == 0 && executing->burstarray[0] == 0 && executing->I_O_time[0] == 0)
		{
			executing->end_time = clock;						//adds process to the complete queue
			if (complete == 0)
			{
				complete = executing;
			}
			else
			{
				hold = complete;
				while (hold != 0 && hold->id<executing->id)
				{
					hold = hold->next;
				}
				if (hold == complete)
				{
					executing->next = complete;
					complete = executing;
				}
				else
				{
					holdQ1 = complete;
					while (holdQ1 != 0 && holdQ1->next != hold)
					{
						holdQ1 = holdQ1->next;
					}
					holdQ1->next = executing;
					executing->next = hold;

				}
			}

		}
		else if (WQ == 0)			//add process to the waiting queue in order
		{
			WQ = executing;
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		else
		{
			hold = WQ;
			while (hold != 0 && hold->current_I_O <= executing->current_I_O)
			{
				hold = hold->next;
			}
			if (hold == WQ)
			{
				executing->next = WQ;
				WQ = executing;
			}
			else
			{
				holdQW = WQ;
				while (holdQW != 0 && holdQW->next != hold)
				{
					holdQW = holdQW->next;
				}
				executing->next = hold;
				holdQW->next = executing;
			}
			executing->arrival_time = clock + executing->current_I_O;
			executing->end_time = clock;
		}
		goto START;
	}
	else if (WQ != 0)								//the program is in idle at this point
	{
		holdQW = WQ;
		executing = 0;
		print_screen_MLFQ(Q1, Q2, Q3, WQ, executing, clock, complete);
		print_MLFQ_file(Q1, Q2, Q3, WQ, executing, clock, complete, queuelist);
	idleloop:
		holdQW = WQ;
		clock++;
		idle++;
		while (holdQW != 0)
		{

			holdQW->current_I_O--;
			if (holdQW->current_I_O == 0)
			{
				if (holdQW->priority == 1)
				{
					if (Q1 == 0)
					{
						Q1 = WQ;
						WQ = WQ->next;
						Q1->next = 0;
					}
					else
					{
						hold = Q1;
						while (hold->next != 0)
						{
							hold = hold->next;
						}
						hold->next = WQ;
						WQ = WQ->next;
						hold->next->next = 0;
					}
				}
				else if (holdQW->priority == 2)
				{
					if (Q2 == 0)
					{
						Q2 = WQ;
						WQ = WQ->next;
						Q2->next = 0;
					}
					else
					{
						hold = Q2;
						while (hold->next != 0)
						{
							hold = hold->next;
						}
						hold->next = WQ;
						WQ = WQ->next;
						hold->next->next = 0;
					}
				}
				else if (holdQW->priority == 3)
				{
					if (Q3 == 0)
					{
						Q3 = WQ;
						WQ = WQ->next;
						Q3->next = 0;
					}
					else
					{
						hold = Q3;
						while (hold->next != 0)
						{
							hold = hold->next;
						}
						hold->next = WQ;
						WQ = WQ->next;
						hold->next->next = 0;
					}
				}
				holdQW = WQ;
			}
			else
			{
				holdQW = holdQW->next;
			}
		}
		if (Q1 == 0 && Q2 == 0 && Q3 == 0)				//program will stay in idle until a process comes out of the waiting queue
		{
			goto idleloop;
		}
		goto START;
	}
	else if (complete != 0)
	{
		// at this point now all process have been complete and displays the last run time 
		double averageWT = 0;		//also claculates the cpu utlization,TT,RT,WT 
		double averageRT = 0;
		double averageTT = 0;
		double timecalc = 0;
		double timeidle = 0;
		executing = 0;
		print_screen_MLFQ(Q1, Q2, Q3, WQ, executing, clock, complete);
		print_MLFQ_file(Q1, Q2, Q3, WQ, executing, clock, complete, queuelist);
		file_Result_MLFQ(idle, clock, complete, queuelist);
		cout << "---------------------------------------------------------" << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << "Current Time: " << clock << endl << endl;
		cout << "Process Completed" << endl << endl;
		cout << "\tProcess" << "\t\tRT" << "\t\tWT" << "\t\tTT" << endl;
		while (complete != 0)
		{

			cout << "\tP" << complete->id << "\t\t" << complete->response << "\t\t" << complete->waiting << "\t\t" << complete->end_time << endl;
			averageWT = averageWT + complete->waiting;
			averageRT = averageRT + complete->response;

			averageTT = averageTT + complete->end_time;
			complete = complete->next;

		}
		averageWT = averageWT / 9;
		averageRT = averageRT / 9;
		averageTT = averageTT / 9;
		timeidle = 1 - idle / clock;
		cout << endl << "Average Response Time:" << averageRT << endl;
		cout << endl << "Average Wait Time:" << averageWT << endl;
		cout << endl << "Average Turnaround Time:" << averageTT << endl;
		cout << endl << "CPU utilization:" << timeidle * 100 << "%" << endl << endl;

	}
	queuelist.close();
}
process * sorted(process * p) //sort process for sjf by there cpu burst
{
	process * unsort = p, *Sort = 0, *current = 0, *hold = 0, *hold2 = 0;
	while (unsort)						//will continue unitll unsort reaches 0
	{
		current = unsort;
		unsort = unsort->next;
		current->next = 0;
		if (Sort == 0)				//take the process one by one from the unsort queue and 
		{							//sort them in the sorted queue
			Sort = current;
		}
		else
		{
			hold = Sort;
			while (hold != 0 && hold->burstarray[0] <= current->burstarray[0])
			{
				if (hold->burstarray[0] == current->burstarray[0])
				{
					if (hold->arrival_time == current->arrival_time)
					{
						if (hold->id < current->id)
						{
							hold = hold->next;
							break;
						}
						else
							break;
					}
					else if (hold->arrival_time < current->arrival_time)
					{
						hold = hold->next;
						break;
					}
					else if (hold->arrival_time > current->arrival_time)
					{
						break;
					}
				}
				else
				{
					hold = hold->next;
				}
			}
			if (hold == Sort)
			{
				current->next = Sort;
				Sort = current;
			}
			else
			{
				hold2 = Sort;
				while (hold2 != 0 && hold2->next != hold)
				{
					hold2 = hold2->next;
				}
				current->next = hold;
				hold2->next = current;
			}
		}
	}

	return Sort;				//once all of the process aqre sorted the program return the sorted process for SJF
}
void print_screen_SJF(process * ready, process * waiting, process* executing, int clock, process * complete)
{
	cout << "---------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "Current Time: " << clock << endl;								//the current time of process start to execution
	if (executing != 0)														//checks if the program is in idle or there is a process executing
	{
		cout << "Now Running: P" << executing->id << "\t\tBurst:" << executing->current_burst << endl;
		cout << "---------------------------------------------------------" << endl;
	}
	else if (executing == 0)
	{
		cout << "Now Running: idle" << "\t\tBurst: n/a" << endl;
		cout << "---------------------------------------------------------" << endl;
	}

	cout << "Ready Queue:" << endl;
	cout << "\t\tProcess" << "\t\tBurst" << "\t\tArrival Time" << endl;
	if (ready != 0)														//will display if there are process in the ready queue or if its empty
	{

		while (ready != 0)
		{
			cout << "\t\tP" << ready->id << "\t\t" << ready->burstarray[0] << "\t\t" << ready->arrival_time << endl;
			ready = ready->next;
		}
	}
	else if (ready == 0)
	{
		cout << "\t\t[empty]" << endl;
	}
	cout << "---------------------------------------------------------" << endl;
	cout << "Waiting Queue:" << endl;
	cout << "\t\tProcess" << "\t\tI/O" << "\t\tExpected Arrival" << endl;
	if (waiting == 0)															//will display if there are process in the waiting queue or if its empty 
	{
		cout << "\t\t[empty]" << endl;
	}
	else if (waiting != 0)
	{
		while (waiting != 0)
		{
			cout << "\t\tP" << waiting->id << "\t\t" << waiting->current_I_O << "\t\t" << waiting->arrival_time << endl;
			waiting = waiting->next;
		}
	}
	cout << "---------------------------------------------------------" << endl;
	cout << "Completed Queues:" << endl;
	cout << "\t\tProcess" << endl;
	if (complete == 0)															//will displaye any processes that have been complete or will displaye empty
	{
		cout << "\t\t[empty]" << endl;
	}
	else if (complete != 0)
	{
		while (complete != 0)
		{
			cout << "\t\tP" << complete->id << endl;
			complete = complete->next;
		}
	}
	cout << "---------------------------------------------------------" << endl << endl << endl;
}


void print_screen_MLFQ(process * Q1, process * Q2, process * Q3, process * waiting, process* executing, int clock, process * complete)
{
	cout << "---------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "Current Time: " << clock << endl;							//display current time
	if (executing != 0)													//display the current process executing or if idle
	{
		cout << "Now Running: P" << executing->id << "\t\tBurst:" << executing->current_burst << endl;
		cout << "---------------------------------------------------------" << endl;
	}
	else if (executing == 0)
	{
		cout << "Now Running: idle" << "\t\tBurst: n/a" << endl;
		cout << "---------------------------------------------------------" << endl;
	}

	cout << "Ready Queue Prioirty1:" << endl;
	cout << "\t\tProcess" << "\t\tBurst" << "\t\tArrival Time" << endl;				//display all process in the ready queue of the 3 priority whether its empty 
	if (Q1 != 0)																	//or not
	{

		while (Q1 != 0)
		{
			cout << "\t\tP" << Q1->id << "\t\t" << Q1->burstarray[0] << "\t\t" << Q1->arrival_time << endl;
			Q1 = Q1->next;
		}
	}
	else if (Q1 == 0)
	{
		cout << "\t\t[empty]" << endl;
	}
	cout << "Ready Queue Prioirty2:" << endl;
	cout << "\t\tProcess" << "\t\tBurst" << "\t\tArrival Time" << endl;
	if (Q2 != 0)
	{

		while (Q2 != 0)
		{
			if (Q2->current_burst > 0)
			{
				cout << "\t\tP" << Q2->id << "\t\t" << Q2->current_burst << "\t\t" << Q2->arrival_time << endl;
				Q2 = Q2->next;
			}
			else
			{
				cout << "\t\tP" << Q2->id << "\t\t" << Q2->burstarray[0] << "\t\t" << Q2->arrival_time << endl;
				Q2 = Q2->next;
			}
		}
	}
	else if (Q2 == 0)
	{
		cout << "\t\t[empty]" << endl;
	}
	cout << "Ready Queue Prioirty3:" << endl;
	cout << "\t\tProcess" << "\t\tBurst" << "\t\tArrival Time" << endl;
	if (Q3 != 0)
	{

		while (Q3 != 0)
		{
			if (Q3->current_burst > 0)
			{
				cout << "\t\tP" << Q3->id << "\t\t" << Q3->current_burst << "\t\t" << Q3->arrival_time << endl;
				Q3 = Q3->next;
			}
			else
			{
				cout << "\t\tP" << Q3->id << "\t\t" << Q3->burstarray[0] << "\t\t" << Q3->arrival_time << endl;
				Q3 = Q3->next;
			}
		}
	}
	else if (Q3 == 0)
	{
		cout << "\t\t[empty]" << endl;
	}
	cout << "---------------------------------------------------------" << endl;
	cout << "Waiting Queue:" << endl;
	cout << "\tProcess" << "\t\tI/O" << "\t\tArrival" << "\t\tPriority" << endl;
	if (waiting == 0)															//display all process in waiting queue or if its empty
	{
		cout << "\t\t[empty]" << endl;
	}
	else if (waiting != 0)
	{
		while (waiting != 0)
		{
			cout << "\tP" << waiting->id << "\t\t" << waiting->current_I_O << "\t\t" << waiting->arrival_time << "\t\tQ" << waiting->priority << endl;
			waiting = waiting->next;
		}
	}
	cout << "---------------------------------------------------------" << endl;
	cout << "Completed Queues:" << endl;
	cout << "\t\tProcess" << endl;
	if (complete == 0)													//displays all completed process				
	{
		cout << "\t\t[empty]" << endl;
	}
	else if (complete != 0)
	{
		while (complete != 0)
		{
			cout << "\t\tP" << complete->id << endl;
			complete = complete->next;
		}
	}
	cout << "---------------------------------------------------------" << endl << endl << endl;
}
void print_SJF_file(process * ready, process * waiting, process* executing, int clock, process * complete, fstream &out)
{
	out << "---------------------------------------------------------" << endl;
	out << "---------------------------------------------------------" << endl;
	out << "Current Time: " << clock << endl;							//will print current time in file
	if (executing != 0)													//will print whether the program is in idle or executing a process infile
	{
		out << "Now Running: P" << executing->id << "\t\tBurst:" << executing->current_burst << endl;
		out << "---------------------------------------------------------" << endl;
	}
	else if (executing == 0)
	{
		out << "Now Running: idle" << "\t\tBurst: n/a" << endl;
		out << "---------------------------------------------------------" << endl;
	}

	out << "Ready Queue:" << endl;
	out << "\t\tProcess" << "\t\tBurst" << "\t\tArrival Time" << endl;
	if (ready != 0)													//print processes in ready queue in the file
	{

		while (ready != 0)
		{
			out << "\t\tP" << ready->id << "\t\t" << ready->burstarray[0] << "\t\t" << ready->arrival_time << endl;
			ready = ready->next;
		}
	}
	else if (ready == 0)
	{
		out << "\t\t[empty]" << endl;
	}
	out << "---------------------------------------------------------" << endl;
	out << "Waiting Queue:" << endl;
	out << "\t\tProcess" << "\t\tI/O" << "\t\tExpected Arrival" << endl;
	if (waiting == 0)											//print processes in waiting queue in the file
	{
		out << "\t\t[empty]" << endl;
	}
	else if (waiting != 0)
	{
		while (waiting != 0)
		{
			out << "\t\tP" << waiting->id << "\t\t" << waiting->current_I_O << "\t\t" << waiting->arrival_time << endl;
			waiting = waiting->next;
		}
	}
	out << "---------------------------------------------------------" << endl;
	out << "Completed Queues:" << endl;
	out << "\t\tProcess" << endl;
	if (complete == 0)											//print processes in completed queue in the file
	{
		out << "\t\t[empty]" << endl;
	}
	else if (complete != 0)
	{
		while (complete != 0)
		{
			out << "\t\tP" << complete->id << endl;
			complete = complete->next;
		}
	}
	out << "---------------------------------------------------------" << endl << endl << endl;
}

void print_MLFQ_file(process * Q1, process * Q2, process * Q3, process * waiting, process* executing, int clock, process * complete, fstream &out)
{
	out << "---------------------------------------------------------" << endl;
	out << "---------------------------------------------------------" << endl;
	out << "Current Time: " << clock << endl;							//print the current time in file
	if (executing != 0)													//print processes being executedin the file
	{
		out << "Now Running: P" << executing->id << "\t\tBurst:" << executing->current_burst << endl;
		out << "---------------------------------------------------------" << endl;
	}
	else if (executing == 0)
	{
		out << "Now Running: idle" << "\t\tBurst: n/a" << endl;
		out << "---------------------------------------------------------" << endl;
	}

	out << "Ready Queue Prioirty1:" << endl;							//print processes in ready queue of all priority in the file
	out << "\t\tProcess" << "\t\tBurst" << "\t\tArrival Time" << endl;
	if (Q1 != 0)
	{

		while (Q1 != 0)
		{
			out << "\t\tP" << Q1->id << "\t\t" << Q1->burstarray[0] << "\t\t" << Q1->arrival_time << endl;
			Q1 = Q1->next;
		}
	}
	else if (Q1 == 0)
	{
		out << "\t\t[empty]" << endl;
	}
	out << "Ready Queue Prioirty2:" << endl;
	out << "\t\tProcess" << "\t\tBurst" << "\t\tArrival Time" << endl;
	if (Q2 != 0)
	{

		while (Q2 != 0)
		{
			if (Q2->current_burst > 0)
			{
				out << "\t\tP" << Q2->id << "\t\t" << Q2->current_burst << "\t\t" << Q2->arrival_time << endl;
				Q2 = Q2->next;
			}
			else
			{
				out << "\t\tP" << Q2->id << "\t\t" << Q2->burstarray[0] << "\t\t" << Q2->arrival_time << endl;
				Q2 = Q2->next;
			}
		}
	}
	else if (Q2 == 0)
	{
		out << "\t\t[empty]" << endl;
	}
	out << "Ready Queue Prioirty3:" << endl;
	out << "\t\tProcess" << "\t\tBurst" << "\t\tArrival Time" << endl;
	if (Q3 != 0)
	{

		while (Q3 != 0)
		{
			if (Q3->current_burst > 0)
			{
				out << "\t\tP" << Q3->id << "\t\t" << Q3->current_burst << "\t\t" << Q3->arrival_time << endl;
				Q3 = Q3->next;
			}
			else
			{
				out << "\t\tP" << Q3->id << "\t\t" << Q3->burstarray[0] << "\t\t" << Q3->arrival_time << endl;
				Q3 = Q3->next;
			}
		}
	}
	else if (Q3 == 0)
	{
		out << "\t\t[empty]" << endl;
	}
	out << "---------------------------------------------------------" << endl;
	out << "Waiting Queue:" << endl;
	out << "\tProcess" << "\t\tI/O" << "\t\tArrival" << "\t\tPriority" << endl;
	if (waiting == 0)															//print processes in waiting queue in the file
	{
		out << "\t\t[empty]" << endl;
	}
	else if (waiting != 0)
	{
		while (waiting != 0)
		{
			out << "\tP" << waiting->id << "\t\t" << waiting->current_I_O << "\t\t" << waiting->arrival_time << "\t\tQ" << waiting->priority << endl;
			waiting = waiting->next;
		}
	}
	out << "---------------------------------------------------------" << endl;
	out << "Completed Queues:" << endl;
	out << "\t\tProcess" << endl;
	if (complete == 0)															//print processes in complete queue in the file
	{
		out << "\t\t[empty]" << endl;
	}
	else if (complete != 0)
	{
		while (complete != 0)
		{
			out << "\t\tP" << complete->id << endl;
			complete = complete->next;
		}
	}
	out << "---------------------------------------------------------" << endl << endl << endl;
}

//the file result function for MLFQ and SJF are both the same 
void file_Result_MLFQ(double idle, int clock, process * complete, fstream &out)
{
	double averageWT = 0;					//will print the result of MLFQ of cpu utlization,TT,RT,WT in the file
	double averageRT = 0;
	double averageTT = 0;
	double timecalc = 0;
	double timeidle = 0;

	out << "---------------------------------------------------------" << endl;
	out << "---------------------------------------------------------" << endl;
	out << "Current Time: " << clock << endl << endl;
	out << "Process Completed" << endl << endl;
	out << "\tProcess" << "\t\tRT" << "\t\tWT" << "\t\tTT" << endl;
	while (complete != 0)
	{

		out << "\tP" << complete->id << "\t\t" << complete->response << "\t\t" << complete->waiting << "\t\t" << complete->end_time << endl;
		averageWT = averageWT + complete->waiting;
		averageRT = averageRT + complete->response;

		averageTT = averageTT + complete->end_time;
		complete = complete->next;

	}
	averageWT = averageWT / 9;
	averageRT = averageRT / 9;
	averageTT = averageTT / 9;
	timeidle = 1 - idle / clock;
	out << endl << "Average Response Time:" << averageRT << endl;
	out << endl << "Average Wait Time:" << averageWT << endl;
	out << endl << "Average Turnaround Time:" << averageTT << endl;
	out << endl << "CPU utilization:" << timeidle * 100 << "%" << endl << endl;
}
void file_Result_SJF(double idle, int clock, process * complete, fstream &out)
{
	double averageWT = 0;					//will print the result of SJF of cpu utlization,TT,RT,WT in the file
	double averageRT = 0;
	double averageTT = 0;
	double timecalc = 0;
	double timeidle = 0;


	out << "---------------------------------------------------------" << endl;
	out << "---------------------------------------------------------" << endl;
	out << "Current Time: " << clock << endl << endl;
	out << "Process Completed" << endl << endl;
	out << "\tProcess" << "\t\tRT" << "\t\tWT" << "\t\tTT" << endl;
	while (complete != 0)
	{

		out << "\tP" << complete->id << "\t\t" << complete->response << "\t\t" << complete->waiting << "\t\t" << complete->end_time << endl;
		averageWT = averageWT + complete->waiting;
		averageRT = averageRT + complete->response;

		averageTT = averageTT + complete->end_time;
		complete = complete->next;

	}
	averageWT = averageWT / 9;
	averageRT = averageRT / 9;
	averageTT = averageTT / 9;
	timeidle = 1 - idle / clock;
	out << endl << "Average Response Time:" << averageRT << endl;
	out << endl << "Average Wait Time:" << averageWT << endl;
	out << endl << "Average Turnaround Time:" << averageTT << endl;
	out << endl << "CPU utilization:" << timeidle * 100 << "%" << endl << endl;
}