#ai
# Preferences 
Several kinds of preferences:
* Unconditional -> I prefer taking the bus
* Conditional -> I prefer taking the bus if it’s raining
* Multi-agent -> I like blue, my husband likes green, what color for the new car?
or: 
* Quantitative -> Numbers, or ordered set of objects. My preference for ice cream is 0.8, and for cake is 0.6.
* Qualitative -> Pairwise comparisons. Ice cream is better than cake

For unconditional and quantitative preferences we can use soft constraint problems.
For qualitative and conditional preferences we can use CP-nets.

# Voting
Preferences for collective decision making in multi-agent systems:
* Several agents
* Common set of possible decisions
* Each agent has its preferences over the possible decisions
* Goal: to choose one of the decisions, based on the preferences of the agents or a set of decisions or a ranking over the decisions
Voting theory
* Voters
* Candidates
Each voter expresses its preferences over the candidates
Goal: to choose one candidate (the winner), based on the voters’ preferences. Also many candidates, or ranking over
candidates
We use voting Rules (functions) to achieve the goal.
## Some voting rules
### Plurality
Voting: each voter provides the most preferred decision
Selection: the decision preferred by the largest number of voters

Majority is like plurality but over only 2 options

### Approval 
Voting: each voter approves any number of options
Selection: option with most votes

### Borda 
Voting: each voter provides a ranking over all options
Score of an option for a voter: number of options that it dominates
Selection: option with greatest sum of scores

## Desirable properties in voting and common problems
### Desirable properties 
Unanimity (efficiency): If all voters have the same top choice, it is selected
Non-dictatorship: There is no dictator (Dictator: voter such that his top choice always wins regardless of the votes of other voters)
Non-manipulability: There is no incentive for agents to misrepresent the preferences

There exists some theorems that state how some of these properties are incompatible with each other:
* Arrow’s theorem (1951)
	Totally ordered preferences 
	It is impossible to find a voting rule with some desirable properties including:
	* unanimity
	* non-dictatoriality
* Gibbard-Sattherwaite’s theorem (1973)
	Totally ordered preferences it is impossible to have a reasonable voting rule that is:
	* non-dictatorial
	* non-manipulable
These impossibility results hold also when we allow partially ordered preferences.
