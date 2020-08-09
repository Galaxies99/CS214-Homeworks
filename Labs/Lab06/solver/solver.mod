/*********************************************
 * OPL 12.9.0.0 Model
 * Author: Hongjie Fang (CS 2018 @ SJTU)
 *********************************************/

int monthLimit = ...;
int prodLimit = ...;
int machineLimit = ...;
int stockLimit = ...;
int finalStock = ...;

range Month = 1..monthLimit;			// Month number range
range extMonth = 0..monthLimit;			// Extend month number range
range speMonth = 0..monthLimit-1;		// special month number range
range Prod = 1..prodLimit;				// Prod number range
range Machine = 1..machineLimit;		// Machine number range

float maxHour = ...;
int marketLimit[Month][Prod] = ...;
float time[Machine][Prod] = ...;
int profit[Prod] = ...;
int machine[Machine] = ...;

dvar int x[Month][Prod];				// newly-produced product
dvar int y[extMonth][Prod];				// stored product at the end of the month
dvar int z[Month][Machine];				// machine down
dvar int t[Month][Prod];				// sold product
dvar float P;							// profit
dvar float S;							// holding cost
dvar float W;							// net profit

maximize W;

subject to {
	// restriction (1)
	forall (j in Prod) y[0][j] == 0 && y[monthLimit][j] == finalStock;
	// restriction (2)
	forall (i in Month)
	  forall (j in Prod)
	    t[i][j] == y[i-1][j] + x[i][j] - y[i][j];
	// restriction (3)
	forall (i in Month)
	  forall (j in Prod)
	    0 <= t[i][j] && t[i][j] <= marketLimit[i][j];
	// restriction (4)
	forall (i in Month)
	  forall (j in Machine) z[i][j] >= 0;
	forall (j in Machine)
	  (sum (i in Month) z[i][j]) == machine[j];
	// restriction (5)    
	forall (i in speMonth)
	  forall (j in Prod) 0 <= y[i][j] && y[i][j] <= stockLimit;
	// restriction (6)
	forall (i in Month)
	  forall (j in Prod) x[i][j] >= 0;
	// restriction (7)
	forall (i in Month)
	  forall (j in Machine) 
		(sum (k in Prod) (x[i][k] * time[j][k])) <= maxHour * (machine[j] - z[i][j]); 
	// definition of P
	(sum (j in Prod)
		(sum (i in Month) t[i][j]) * profit[j]) == P;
	// definition of S
	(sum (i in Month)
		(sum (j in Prod) y[i][j])) * 0.5 == S;
	// definition of W
	W == P - S;
}

execute{
	write("Produce: "); writeln(x);
	write("Stocks: "); writeln(y);
	write("Sell: "); writeln(t);
	write("Down: "); writeln(z);
	
	write("Total Profit = "); writeln(P);
	write("Total Holding Cost = "); writeln(S);
	write("Total Net Profit = "); writeln(W);
}	

