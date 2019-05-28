# House
This code repository contains code for omni directional shadow mapping, directional shadow mapping, normal mapping and steep parallax
mapping.

import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import numpy as np

def model_function(variables, a,b,c):
	verts, tris, lodDist = variables
	return ((np.log(verts)*a)/100 + (np.log(tris)*b)/100)+(c*lodDist)

vertices = np.array([50627,27413,15304,8645,5149,3078,1955])
triangles = np.array([64540,31437,15934,8508,4689,2600,1526])
LOD_distance = np.array([8.0,16.0,32.0,64.0,128.0,256.0,512.0])

mesh_densities = np.array([476,463,470,484,553,613,720])

noised_densities = mesh_densities + np.random.random(len(mesh_densities))*3

popt, pcov = curve_fit(model_function,(vertices,triangles,LOD_distance),noised_densities)

print popt

for item in zip(vertices,triangles,LOD_distance):
	print model_function(item,popt[0],popt[1],popt[2])
  
  
