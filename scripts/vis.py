"""
Script to visualize N-body system using OpenGL

requires vispy development version https://github.com/vispy/vispy
"""
import sys
import argparse
import numpy as np

from vispy import app, scene
from vispy.geometry import create_sphere

# create mesh of a phere
mdata = create_sphere(20, 40, .01)

class NbodyCanvas(scene.SceneCanvas):
    def __init__(self, data, istep=1, scale=1., colors='y'):
        """
        Initialize an NbodyCanvas

        data : 2d array, (Ntimesteps, Nparticles*9)
            position(3), velocity(3), and acceleration(9) of each particle
        istep : int
            advance timestep by this amount
        scale : float
            scale length
        colors : list of Nparticle size or 1
            list of matplotlib colors
        """
        scene.SceneCanvas.__init__(self, keys='interactive')
        view = self.central_widget.add_view()
        view.set_camera('turntable', mode='perspective', up='z', distance=1.0,
                azimuth=30., elevation=60.)
        self.view = view
        # Add a 3D axis to keep us oriented
        self.axis = scene.visuals.XYZAxis(parent=view.scene)
        self.timer = app.Timer(0.1, connect=self.on_timer, start=True)
        
        self.i = 0
        self.istep = istep
        self.scale = scale
        self.meshes = []
        self.d = data
        self.np = self.d.shape[1]/9  # number of particles
        self.nt = self.d.shape[0]  # number of timesteps

        colors = list(colors)
        if len(colors) == 1:
            colors *= self.np
        else:
            assert len(colors) == self.np, "invalid number of colors"
        # add particles for the first time
        for (x,y,z), c in\
            zip(np.vstack(np.split(self.d[self.i],self.np))[:,:3], colors):
            m = scene.visuals.Mesh(
                meshdata=mdata, color=c, shading='smooth')
            m.transform = scene.transforms.AffineTransform()
            m.transform.translate([x/self.scale, y/self.scale, z/self.scale])
            self.view.add(m)
            self.meshes.append(m)
   
    def on_key_press(self, event):
        if event.text == ' ':
            if self.timer.running:
                self.timer.stop()
            else:
                self.timer.start()
        if event.text == 'q':
            self.close()

    def on_timer(self, event):
        coords_old = np.vstack(np.split(self.d[self.i],self.np))[:,:3]
        coords_new = np.vstack(np.split(self.d[(self.i+self.istep) % self.nt],self.np))[:,:3]
        coords_trans = coords_new - coords_old
        # move particles forward
        for mm, (dx, dy, dz) in zip(self.meshes, coords_trans):
            mm.transform.translate([dx/self.scale, dy/self.scale, dz/self.scale])
        self.i+=self.istep
        if self.i == self.nt:
            self.i = 0
        self.update()


def parse():
    """parse command line args """
    parser = argparse.ArgumentParser()
    parser.add_argument('filename', type=str)
    parser.add_argument('-s', '--scale', type=float,
                        help='scale length', default=1.)
    parser.add_argument('-t', '--istep', type=int,
                        help='timestep interval', default=1.)
    parser.add_argument('-c', '--colors', type=str, nargs='+',
                        help='list of matplotlib colors', default='y')
    return parser.parse_args()

def visualize():
    """Read data from file and start vispy app """
    args = parse()
    d = np.loadtxt(args.filename)
    c = NbodyCanvas(d, istep=args.istep, scale=args.scale, colors=args.colors)
    c.show()


if __name__ == '__main__':
    visualize()
    if sys.flags.interactive == 0:
        app.run()
