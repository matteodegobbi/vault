#ir 
# Kalman filter (EKF)
It is a type of recursive Bayes filter, using the current belief and the last observation and action
to update belief.

Estimates the state x of a discrete time controlled process governed by a linear stochastic equation
with stochastic measurements.

It uses a linear model or linearized model using the Jacobian

Assumes Gaussian error, static world and is a parametric model that does online SLAM

- assumiamo rumore gaussiano
- modello lineare o linearizzato con jacobiana
- assumiamo mondo statico che non cambia
- metodo parametrico
- tempo discreto
- Non robusto e non scala bene, veloce e lavora solo con landmark based maps 

Lavora in 2 Step:
- Prediction step exploits the controls (actions carried out by the agent)
- Correction step exploits the observations (sensory data)

---

# Particle Filters 

The belief is a set of particles.

It's a recursive Bayes filter that relaxes some of the hypothesis of EKF,
the noise is not necessarily Gaussian and the process is not controlled by 
a linear equation. 
It is a **non-parametric** method.

It has 3 steps:
- prediction
- correction
- resampling

Like in EKL the Prediction step uses control commands 
It moves all the particle in the same way as the robot's commands.
e.g. move all particles north by 7 meters 

In the correction step we use the observations from sensors to obtain a likelihood for each of the particles
that were moved in the previous step. it computes the likelihood that the particle is in the observed location given that the real robot is in a specific location
. This basically gives us which particles are more likely to represent the actual robot's location.

Different particles will get different importance weights based on their likelihood. 
Then we can resample based on these importance weights. We repeat this process, the "good" particles are likely so 
they tend to survive, while bad particles will die out.

Particle filters can be computationally expensive, only feasible for 2D motions.

It does **Full SLAM**, determining the complete path of the robot (unlike EKF which does online SLAM)

---

| Aspect                    | Extended Kalman Filter (EKF)                                      | Particle Filter                                     |
| ------------------------- | ----------------------------------------------------------------- | --------------------------------------------------- |
| **Type**                  | Recursive Bayes filter (parametric)                               | Recursive Bayes filter (non-parametric)             |
| **Belief Representation** | Mean + covariance (Gaussian assumption)                           | Set of weighted particles                           |
| **Model Assumptions**     | Linear or linearized (via Jacobian), Gaussian noise, static world | No need for linearity, no Gaussian noise assumption |
| **Error Handling**        | Gaussian noise assumption                                         | Arbitrary noise distributions possible              |
| **Steps**                 | 2 steps: Prediction + Correction                                  | 3 steps: Prediction + Correction + Resampling       |
| **State Estimation**      | Estimates current state (online SLAM)                             | Estimates full trajectory (full SLAM)               |
| **Computational Cost**    | Efficient, but does not scale well                                | Computationally expensive, feasible mostly in 2D    |
| **Scalability**           | Not robust, poor scalability with map size                        | Better robustness but computationally heavy         |
| **Maps**                  | Landmark-based maps                                               | Can handle more general maps                        |
| **Strengths**             | Fast, simple, works well under Gaussian/linear assumptions        | Flexible, handles non-linear/non-Gaussian systems   |
| **Weaknesses**            | Not robust, poor scalability, limited to Gaussian/linear models   | Computationally expensive, particle depletion risk  |


--- 

# Graph based SLAM

It's a full SLAM solution
Landmarks and robot's location are nodes in a graph.

Pair of consecutive locations $x_i$ and $x_{i+1}$ are linked by an edge.
If the landmark $m_j$ is observed by location $x_i$, they are linked by an edge
Each edge represents a conditional dependency, i.e. a sort of constraint

It's equivalent to solve a MLE approach, maximizing likelihood of map and full path. If we assume Gaussian dist. as in EKF we get that the problem is a weighted Least Squares.

If the map is landmark based we can optimize the LS problem with Gauss-Newton or the Levenberg-Marquardt algorithms.

## Pose graph SLAM

In the case of grid-based map with huge cardinality, we include in state only the path and not the map since the previous graph based approach with both is intractable.

We then solve SLAM by an optimization problem that takes into account consecutive transformations and loop closures.

Uses odometry and range scans like LiDAR.

Transformations (relative motions between robot positions) are computed with ICP, iterative closest point to align scans.

The map is rendered at the end given the robot's position.
