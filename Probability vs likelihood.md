#probability 
Interview question:
What is the difference between probability and likelihood?
A probability is a measure function in a given probability space $(\Omega,\mathcal F,\mathbb P)$, $\mathbb P:\mathcal F\rightarrow[0,1]$ respecting Kolmogorov's Axioms.
$\mathbb P$ measures the chance of an event $A\in\mathcal F$ of happening.
Depending on whether we are in the discrete or absolutely continuous case we specify a pmf/pdf and the measure on events is either a sum (finite or countable infinite) on subsets of the sample space or an integral over a Borel measurable set.

 Given a set of observations $\mathcal D$ and a pdf (or pmf) $f(x|\theta)$ (or $f(x;\theta)$ in frequentist approaches) the Likelihood function $\mathcal L(\theta|\mathcal D)$ is a function of parameter $\theta$ which tells us the probability of observing dataset $\mathcal D$ given the parameter $\theta$. Not to be confused with the posterior (probability of $\theta$ given dataset which is estimated in Bayesian approaches). To estimate the likelihood we need the joint distribution of the observations, if iid assumption holds we often use the log-likelihood instead and it's easy to compute. Likelihood is used in MLE to determine the best fit for parameter $\theta$ given the dataset.