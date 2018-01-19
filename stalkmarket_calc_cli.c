/*Cases:
 * If increases: EXCLUDE DECREASING
 * If increase, at most 2, followed by decrease: IT IS RANDOM
 * If increase to 3 followed by decrease, big Spike. Otherwise, small spike
 *
 * It is also important to consider huge spikes that come at random. 
 * So if something increases heavily, it'll simply have to be flagged for the time being.*/


/*********************************************/

#define SIZE 14

#include <stdio.h>
#include <stdbool.h>



//gives a list, as well as the amount of slots used for input.
char *printout(int inpList[SIZE], int usedSize){

	//enum listing of all possible Stalkmarket weekly patterns, UNIDENTIFIED being for bug-testing.
	//You know something is wrong if the returned pattern is said to be UNIDENTIFIED.	
	enum { UNIDENTIFIED, DECREASING, RANDOM, BIG_SPIKE, SMALL_SPIKE } pattern;	

	pattern = UNIDENTIFIED;

	char *output = NULL;
	int increaseCutoff = 0;
	int increaseInRowCount = 0;
	int decreaseAfterIncrease = 0;
	int currentIndex = 0;
	int prevIndex = 0;
	int increaseOrDecrease = 0;

	//loops through the whole list of inputs, should be set dynamically for list-input.
	//that is currently a feature to be implemented, it is crucial to get the 
	//analysis of a whole week to work perfectly first.
	int i = 0;
	while(i < usedSize){
		i = i + 1;	
		currentIndex = i;
		prevIndex = i - 1;		
	
		// (> 0) if the price increases in a change
		// (< 0) if the price decreases in a change
		// 0 should be impossible to achieve (to be confirmed)	
		increaseOrDecrease = inpList[currentIndex] - inpList[prevIndex];

		//This function determines patterns if 3, 4, or above increases 
		//occur in a row. Each patterns follows a rule of increases before it decreases again.
		//The continue is there to check if the next iteration is also an increase. 
		//If it is, we find a new pattern, if not, we settle for the one we found (else if).
		if (increaseOrDecrease > 0 && increaseCutoff == 0){
			increaseInRowCount = increaseInRowCount + 1;
			if (increaseInRowCount == 3){
				pattern = BIG_SPIKE; 
				continue;
			}
			else if (increaseInRowCount == 4){
				pattern = SMALL_SPIKE;
				continue;
			}
			else if (increaseInRowCount >= 5){
				pattern = RANDOM;
				break;
			}	
		}	
		else if ((increaseInRowCount == 4 || increaseInRowCount == 3)){	
			break;
		}

		// If there is 1 or 2 increase in a row and a decrease occurs, 
		// we cannot have any other pattern than Random. 
		if (increaseInRowCount > 0 && increaseInRowCount < 3 && increaseOrDecrease < 0){
			increaseCutoff == 1;
			pattern = RANDOM;
			break;
		}

		//if we haven't had a decrease by input 7 (thursday afternoon),
		//we know for fact that we have the Decreasing pattern.
		if (increaseInRowCount == 0 && i == 7){
			pattern = DECREASING;
			break;
		}	
	}
	
	//Gives the user a proper output, this is to be modified to allow for much more
	//returned detail for the user to enjoy and analyse.	
	if (pattern == RANDOM){
		output = "Pattern: Random.";
	}
	else if (pattern == DECREASING){
		output = "Pattern: Decreasing.";
	}	
	else if (pattern == BIG_SPIKE){
		output = "Pattern: Big Spike.";
	}
	else if (pattern == SMALL_SPIKE){
		output = "Pattern: Small Spike.";
	}
	else{
		output = "Pattern: Undefined.";
	}
	return(output);
}	




int main(void){
	int inputPrices[SIZE]; // = {4, 3, 2, 5, 6, 23, 10, 7, 9, 5, 4, 2, 1, 1};
	printf("Finish input by inputting '0'.\n");
	int i = 0;
	int inp = 0;

	while(i < SIZE){
		printf("Price %d: ", i+1);	
		scanf("%d", &inp);
	
		if (inp == 0){
			break;
		}
		inputPrices[i] = inp;
		i = i + 1;
	}

	int j = 0;
	while (j < i){
		printf("%d ", inputPrices[j]);
		j = j + 1;
	}
	

	printf("\n%s\n", printout(inputPrices, i));	


}

