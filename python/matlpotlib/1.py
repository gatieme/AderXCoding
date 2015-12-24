import numpy as np 
import scipy.stats as ss    
def case2(n = 10, mu = 3, sigma = np.sqrt(5), p = 0.025, rep = 100):  
	scaled_crit = ss.norm.ppf(q = 1 - p) * (sigma / np.sqrt(n))  
	norm = np.random.normal(loc = mu, scale = sigma, size = (rep, n))     
	xbar = norm.mean(1)  
	low = xbar - scaled_crit  
	up = xbar + scaled_crit     
	rem = (mu > low) & (mu < up)  
	m = np.c_[xbar, low, up, rem]     
	inside = np.sum(m[:, 3])  
	per = inside / rep  
	desc = "There are " + str(inside) + " confidence intervals that contain "   
	"the true mean (" + str(mu) + "), that is " + str(per) + " percent of the total CIs" 

	return {"Matrix": m, "Decision": desc} 

if __name__ == "__main__" : 
	print case2()
