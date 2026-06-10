import numpy as np
import matplotlib.pyplot as plt
import lorenz_methods

h = 0.01
t0 = 0.0
tf = 40.0
x0 = y0 = z0 = 1.0

N = int((tf-t0)/h)+1
t = np.linspace(t0,tf,N)

sol_euler = np.array(lorenz_methods.euler(h,t0,tf,x0,y0,z0))
sol_rk2   = np.array(lorenz_methods.rk2(h,t0,tf,x0,y0,z0))
sol_rk4   = np.array(lorenz_methods.rk4(h,t0,tf,x0,y0,z0))

def plot3d(sol,name,title):
    fig = plt.figure(figsize=(8,6))
    ax = fig.add_subplot(111,projection="3d")
    ax.plot(sol[:,0],sol[:,1],sol[:,2])
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_zlabel("z")
    ax.set_title(title)
    plt.tight_layout()
    plt.savefig(name)
    plt.close()

plot3d(sol_euler,"trayectoria_3d_euler.png","Euler")
plot3d(sol_rk2,"trayectoria_3d_rk2.png","RK2")
plot3d(sol_rk4,"trayectoria_3d_rk4.png","RK4")

eps = 1e-8

sol1 = np.array(lorenz_methods.rk4(h,t0,tf,1,1,1))
sol2 = np.array(lorenz_methods.rk4(h,t0,tf,1+eps,1,1))

d = np.linalg.norm(sol1-sol2,axis=1)

plt.figure(figsize=(8,5))
plt.semilogy(t,d)
plt.xlabel("t")
plt.ylabel("d(t)")
plt.title("Sensibilidad a condiciones iniciales")
plt.grid(True)
plt.savefig("sensibilidad.png")
plt.close()

with open("output.txt","w") as f:
    f.write(f"Separacion inicial: {d[0]:.6e}\n")
    f.write(f"Separacion final: {d[-1]:.6e}\n")

print(f"Separacion inicial: {d[0]:.6e}")
print(f"Separacion final: {d[-1]:.6e}")