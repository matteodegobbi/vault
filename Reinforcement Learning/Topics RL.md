#rl 
### Primo parziale
[[Reinforcement Learning Basics]]
[[Multi Armed Bandits]]
[[Markov Decision Processes]]
[[Dynamic Programming]]
[[On-Policy vs Off-Policy and importance sampling]]
[[Monte Carlo - On-Policy methods]]
[[Monte Carlo - Off-Policy methods]]
[[TD (Temporal Difference) Learning]]
### Secondo parziale
[[n-step bootstrapping and TD lambda]]
[[Value function approximation]]
[[Policy gradient]]
[[Actor-Critic]]
[[Batch Methods]]


![[Pasted image 20251207130448.png]]


# List of algorithms
## Dynamic programming
### Prediction
[[Dynamic Programming#Policy evaluation]]
### Control
[[Dynamic Programming#Policy iteration]]
[[Dynamic Programming#Value iteration]]
## Monte Carlo On-Policy 

### Prediction
[[Monte Carlo - On-Policy methods#Prediction]] First-Visit
[[Monte Carlo - On-Policy methods#Prediction]] Every-Visit
### Control
[[Monte Carlo - On-Policy methods#Monte Carlo ES (Exploring Starts)]] 
[[Monte Carlo - On-Policy methods#$ varepsilon$-soft policies]] 
## Monte Carlo Off-Policy 
### Prediction
[[Monte Carlo - Off-Policy methods#Prediction]] Importance-Sampling evaluation
## Temporal difference
### Prediction
[[TD (Temporal Difference) Learning#TD(0)#Prediction]]
### Control
[[TD (Temporal Difference) Learning#Control#SARSA]]
[[TD (Temporal Difference) Learning#Control#Q-Learning]]
[[TD (Temporal Difference) Learning#Control#Expected SARSA]]

## n-step and td lambda
[[n-step bootstrapping and TD lambda#Prediction#]]
[[n-step bootstrapping and TD lambda#Control]]
[[n-step bootstrapping and TD lambda#Backward]]
[[n-step bootstrapping and TD lambda#$ text{SARSA}( lambda)$]]
## Value function approximation
### Prediction
MC with VFA
TD(0) semi-gradient with VFA
n-step bootstrapping semi-gradient with VFA
$\text{TD}(\lambda)$ backward view with eligibility traces with VFA
FORSE $\text{TD}(\lambda)$ forward view with VFA (truncated lambda return)
### Control
TD(0) semi-gradient SARSA with VFA
n-step semi-gradient SARSA with VFA
$\text{SARSA}(\lambda)$ with VFA
## Policy based methods
## Policy gradient (MC)
Policy gradient
Policy gradient with whitening
Policy gradient with baseline 
## Actor-Critic
QAC
A2C with both $\hat q$ and $\hat v$
A2C with TD error to sample advantage
A2C with eligibility traces for $\text{TD}(\lambda)$ to sample advantage
## Batch methods
Any seen algorithm adapted to use experience replay to break correlations in samples




