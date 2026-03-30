#nlp #ml #dl 
> [!summary]
We can use [[Large Language Models]] as agents, the definition of an agent is "A system that autonomously pursues goals and completes tasks on a user's behalf."
> The main difference with [[Tool Calling]] is the fact that agents loop, evaluating their goals, executing actions trough tools and then re-evaluating based on the outcomes. This process is repeated.

---
# ReAct
ReAct is a framework to build agentic LLMs by combining reasoning + acting. 
![[Pasted image 20260327003014.png]]

The way ReAct works is by decomposing tasks into loops of observe, plan and act (or similar decompositions).

Example with 2 iterations:
1st iteration
![[Pasted image 20260327003423.png]]

2nd iteration
![[Pasted image 20260327003454.png]]

The agent loops until it determines that it has achieved its goal.

---
# Multi-agent and Skills

We can have multiple agents collaborating to solve goals, (e.g. specialized thermostat agent, air quality agent, energy usage agent) in this case we need some coordination protocol, such as A2A by Google using skills, cards and executors.
https://developers.googleblog.com/en/a2a-a-new-era-of-agent-interoperability/

---


