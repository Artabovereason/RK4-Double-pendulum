It is a rigid pendulum at the end of which another rigid pendulum is attached. The two inextensible rods of lengths  <img src="https://render.githubusercontent.com/render/math?math=L_1"> and <img src="https://render.githubusercontent.com/render/math?math=L_2"> have zero mass. The 2 masses at the ends are of masses <img src="https://render.githubusercontent.com/render/math?math=M_1"> and <img src="https://render.githubusercontent.com/render/math?math=M_2">, which will be considered as punctual. The double pendulum is therefore fixed in O and articulated freely in <img src="https://render.githubusercontent.com/render/math?math=M_1">. The movement takes place in a plane of horizontal <img src="https://render.githubusercontent.com/render/math?math=x"> and vertical <img src="https://render.githubusercontent.com/render/math?math=y"> coordinates. We will consider that the two stems can “cross” without problem. The angle that the pendulum 1 makes with the vertical is denoted  <img src="https://render.githubusercontent.com/render/math?math=\theta_1"> and the angle that the pendulum 2 makes with the vertical is denoted  <img src="https://render.githubusercontent.com/render/math?math=\theta_2">. These angles are noted positively counterclockwise.

By setting <img src="https://render.githubusercontent.com/render/math?math=\Delta \theta=\theta_2-\theta_1">, we obtain the following system:


<img src="https://render.githubusercontent.com/render/math?math=\ddot{\theta}_1 = \frac{\dot{\theta}_1^2 M_2L_1\cos(\Delta \theta)\sin(\Delta \theta)+\dot{\theta}_2^2M_2L_2\sin(\Delta \theta)-(M_1+M_2)g \sin(\theta_1)+M_2\cos(\Delta\theta)g\sin(\theta_2)}{(M_1+M_2)L_1-M_2L_1\cos^2 (\Delta \theta)} \qquad \ddot{\theta}_2 = \frac{-\dot{\theta}_2^2 M_2L_2\cos(\Delta \theta)\sin(\Delta \theta)+(M_1+M_2)\left(g\sin(\theta_1)\cos(\Delta \theta)-L_1\dot{\theta}_1^2\sin(\Delta\theta)-g\sin(\theta_2) \right)}{(M_1+M_2)L_1-M_2L_1\cos^2 (\Delta \theta)}">

In numerical analysis, the Runge–Kutta methods are a family of implicit and explicit iterative methods, which include the well-known routine called the Euler Method, used in temporal discretization for the approximate solutions of ordinary differential equations.

The most widely known member of the Runge–Kutta family is generally referred to as "RK4", the "classic Runge–Kutta method" or simply as "the Runge–Kutta method".

We're using this method here.


