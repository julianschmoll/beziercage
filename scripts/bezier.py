import numpy as np
import matplotlib.pyplot as plt
import math


class BezierSurface:
    def __init__(self, control_points):
        self.control_points = np.array(control_points)

    def bernstein_poly(self, i, n, t):
        return math.comb(n, i) * t**i * (1 - t)**(n - i) 

    def surface(self, num_points=20):
        n = self.control_points.shape[0] - 1
        m = self.control_points.shape[1] - 1
    

        u_values = np.linspace(0, 1, num_points)
        v_values = np.linspace(0, 1, num_points)
        
        surface_points = np.zeros((num_points, num_points, 3))
        
        for u_idx, u in enumerate(u_values):
            for v_idx, v in enumerate(v_values):

                point = np.zeros(3)
                
                for k in range(n + 1):
                    for l in range(m + 1):
                        bernstein_u = self.bernstein_poly(k, n, u)
                        bernstein_v = self.bernstein_poly(l, m, v)

                        point += bernstein_u * bernstein_v * self.control_points[k, l]

                print(u,v)
                print(f"{u_idx}, {v_idx}: ({point[0]:.1f}, {point[1]:.1f}, {point[2]:.1f})")

                surface_points[u_idx, v_idx] = point

        return surface_points
    
    def plot_curves(self, num_points, ax, label='Bézier Curve', color='r'):
        pass
            

    def plot(self, num_points=20, save_path=None, title="Bezier Surface"):
        surface_points = self.surface(num_points)

        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')

        X = surface_points[:, :, 0]
        Y = surface_points[:, :, 1]
        Z = surface_points[:, :, 2]

        self.plot_curves(num_points, ax, color='b', label='Bézier Curves')
        ax.plot_surface(X, Y, Z, color='b', alpha=0.5, label='Bezier Surface')

        control_x = self.control_points[:, :, 0]
        control_y = self.control_points[:, :, 1]
        control_z = self.control_points[:, :, 2]

        ax.scatter(control_x, control_y, control_z, color='r', label='Control Points')

        
        for i in range(self.control_points.shape[0]):
            for j in range(self.control_points.shape[1]):
                x, y, z = self.control_points[i, j]
                ax.text(x, y, z, f"({x:.1f}, {y:.1f}, {z:.1f})", fontsize=8, color='black')

        ax.set_title(title)
        ax.legend()

        if save_path:
            plt.savefig(save_path)
        plt.show()


def main():
    bezier_curves = [
        [(0, 0, 0), (1, 0, 0), (3, 0, -1), (3, 0, 2),],
        [(0, 1, 0), (1, 1, 0), (2, 1, 2), (3, 1, 2),],
        [(0, 2, 0), (1, 2, 0), (2, 2, 0), (3, 2, 0),],
        [(0, 3, 0), (1, 3, 0), (2, 3, 0), (3, 3, 0),],
    ]

    bezier_surface = BezierSurface(bezier_curves)
    bezier_surface.plot(title="Bezier Patch", num_points=50)


if __name__ == "__main__":
    main()
