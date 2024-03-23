#ai
An agent is anything that can be viewed as
* perceiving its environment through sensors 
* acting upon that environment through actuators

The agent function maps percept histories to actions $f:\mathcal P^{\star}\to\mathcal A$
The agent program runs on the physical architecture to produce f

# Rational agent
A rational agent, for each possible percept sequence, should select an action that is expected to maximize its performance measure:
* given the evidence provided by the percept sequence
* given whatever built-in knowledge the agent has
Rationality is distinct from omniscience (all-knowing with infinite knowledge)
Agents can perform actions in order to modify future percepts so as to obtain useful information (information gathering, exploration)
An agent is autonomous if its behavior is determined by its own experience (with ability to learn and adapt)

# Task environments
The problems for which we make agents.
A task environment is specified by PEAS (Performance measure, Environment, Actuators, Sensors)
## Types of task environments

### Observable
Fully observable (vs. partially observable): An agent's sensors give it access to the complete state of the environment at each point in time

### Determinism
Deterministic: The next state of the environment is completely determined by the current state and the action executed by the agent
Stochastic: there is uncertainty on the next state and it is expressed with probabilities
Non-deterministic: there is uncertainty on the next state but no probabilities are available
Uncertain: not fully observable and non-deterministic


### Episodic/sequential
Episodic: The agent's experience is divided into atomic "episodes”/ Each episode consists of the agent perceiving and performing a single action. The choice of action in each episode depends only on the episode itself
Sequential: a current decision may affect future decisions

### Static/Dynamic/Semidynamic
Static: The environment is unchanged while an agent is deliberating
* No need to keep looking at the world while deliberating the next action
* nor worrying about time
Dynamic: continuously asking the agent what it wants to do
The environment is semidynamic if the environment itself does not change with the passage of time but the agent's performance score does

### Discrete/Continous
Discrete: A finite number of distinct, clearly defined states, percepts and actions. Applies also to time

### Single/Multi-Agent
Single agent: An agent operating by itself in an environment
Multi-agent case can be: competitive or cooperative

### Known/unknown

Known: depends on the knowledge of the agent or the designer of the agent of the rules governing the environment.
In a known environment for each action there is:
* an outcome (if deterministic)
* a probability distribution over the possible outcomes (if stochastic)

# Table driven agents
in the pdf [[2_AI2-agents2024.pdf]] pag 24.
# Agent types

* Simple reflex agents choice of the action depends only on the current percept
* Model-based reflex agents maintain internal state to track aspects of the world that are not evident in the current percept
* Goal-based agents act to achieve their goals
* Utility-based agents try to maximize their own expected “happiness”
# Components
Agent programs consist of various components.
The components can represent the environment in
three ways (with increasing complexity and expressive power):
* Atomic, each state of the world is indivisible it has no internal structure. Example: the algorithms underlying search
* Factored, each state contains a fixed set of variables (or attributes), each variable can have a value, two different factored states can share some variables. Example: constraint satisfaction algorithms, planning
* Structured, each state contains objects (with variables with values) and relations with other objects. Example: knowledge-based learning