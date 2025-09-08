#ir 
# Hierarchical paradigm
Based on the sequence of primitives  `sense->plan->act` 
World model: combines a priori knowledge, sensed info, cognitive understanding

![[Pasted image 20250901182756.png]]

An example is the STRIPS algorithm, automatically builds a plan based on preconditions (facts that need to be true to execute an action), facts that are true after an action and facts that are false after an action. It uses predicate logic. 

In this paradigm we need to have a closed world assumption in order to build a model of it.

The drawbacks are:
- Performance bottleneck due to planning that can hurt control, especially when we need quick reaction times.
- Since the world model requires an extensive representation
These make the paradigm not reliable in the real world.

---

# Reactive paradigm
It's evolved from cybernetics and the dissatisfaction with results from hierarchical paradigm.

Its based on behaviours:
Behaviour: mapping of sensory inputs to a pattern of motor actions that are used to achieve a task. 
We can classify three broad categories of behaviors:
– Reflexive behaviors: stimulus-response, hard-wired for fast response
– Reactive behaviors: learned, “compiled down” to be executed without conscious thought
– Conscious behaviors: require deliberative thought

Examples: 
* reactive = muscle memory
* reflexive = knee-jerk reaction
* conscious = writing code for a program

Reactive robot links perception to action without a temporal history or abtract respresentation of state.

![[Pasted image 20250901185014.png]]

Uses multiple instances of couples SENSE-ACT
called behaviors that get turned on/off based on
stimulus, No PLAN involved.

Examples of behaviours:
* Exploration/directional behaviors (move in a general direction)
* Goal-oriented appetitive behaviors (move towards an attractor)
* Aversive/protective behaviors (prevent collisions)
* Path following behaviors (move on a designated path)
and others.

The subsumption paradigm has:
* Decision making by a set of task accomplishing behaviors
* Mechanism for action selection: subsumption hierarchy. Behaviors are organized in layers. Behaviors “fire” simultaneously. Higher layer behaviors inhibit lower level ones, i.e. higher level behaviours SUBSUME lower level behaviours.
Concurrent behaviours and arbitration in pdf.
---

# Hybrid paradigm
Neither completely deliberative nor completely reactive approaches are suitable for building agents, researchers concluded using hybrid systems, which
attempt to combine hierarchical and reactive approaches.

The system can be made of multiple subsystems, both:
- deliberative subsystems, containing a symbolic world model, which develop plans and make decisions in the way proposed by symbolic AI
- reactive subsystems, which are capable of reacting to events without complex reasoning

We can divide the system in:
* Planner: mission generating and monitoring, need past, present and future.
* Sequencer: selects behaviors to accomplish task, needs past and present.
* Reactive (Behavioral) Layer, very fast reactions. Needs only present.

The advantages of splitting into layers are:
* decomposing a complex system (use different cpus, on-board/off-board)
* modularity
* right tools for each task (C++/lisp)

Components of hybrid paradigm: 

* Sequencer – generates a set of behaviors to accomplish a subtask.
* Resource Manager – allocates resources to behaviors, e.g., a selection of suitable sensors. (In reactive architectures, resources for behaviors are usually hardcoded.)
* Cartographer – creates, stores, and maintains a map or spatial information, a global world model and knowledge representation.(It can be a map but not necessarily.
* Mission Planner – interacts with the operator and transform the commands into the robot term.– Construct a mission plan, e.g., consisting of navigation to some place where a further action is taken.
* Performance Monitoring and Problem Solving – it is a sort of self-awareness that allows the robot to monitor its progress.

---




