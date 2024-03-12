# Agent and its components

An agent is something that acts in an environment.
Agents receive stimuli from their environment.
Agents carry out actions that can affect the environment.
An agent is made up of a body and a controller. Agents interact with the environment with a body. The controller receives percepts from the body and sends commands to the body.
![[Screenshot from 2024-03-12 10-04-26.png]]

A body includes:
* sensors that convert stimuli into percepts
* actuators that convert commands into the actions in the environment.
(A body can also carry out actions that don’t go through the controller, such as a stop button for a robot)

# Controllers

Agents are situated in time, they receive sensory data in time, and do actions in time.

Controllers have (limited) memory and (limited) computational capabilities.

The controller specifies the command at every time.

The command at any time can depend on the current and previous percepts.

A percept trace is a sequence of all past, present, and future percepts received by the
controller.
A command trace is a sequence of all past, present, and future commands output by the
controller.
A transduction is a function from percept traces into command traces.
A transduction is causal if the command trace up to time t depends only on percepts up
to t.
An agent’s history at time t is sequence of past and present percepts and past
commands.
A controller is an implementation of a causal transduction that specifies a function
from an agent’s history at time t into its action at time t.

# Belief state
An agent doesn’t have access to its entire history. It only has access to what it has
remembered.
The memory or belief state of an agent at time t encodes all of the agent’s history
that it has access to.
The belief state of an agent encapsulates the information about its past that it can
use for current and future actions.

At every time a controller has to decide on:
* What should it do?
* What should it remember?
as a function of its percepts and its memory.

For discrete time, a controller implements:
* belief state function, `remember (belief state, percept)` returns the next belief state.
* command function, `command (memory, percept) `returns the command for the agent.

# Hierarchical control

Complex agents are built modular in terms of
interacting hierarchical layers

Each controller sees the controllers below it as a
virtual body from which it gets percepts and sends
commands.
The lower-level controllers can
* run much faster, and react to the world more
quickly
* deliver a simpler view of the world to the
higher-level controllers.

![[Pasted image 20240312112233.png]]
![[Pasted image 20240312112321.png]]
