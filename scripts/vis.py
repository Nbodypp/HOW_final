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
    def __init__(self, data):
        scene.SceneCanvas.__init__(self, keys='interactive')
        view = self.central_widget.add_view()
        view.set_camera('turntable', mode='perspective', up='z', distance=1.5,
                azimuth=30., elevation=60.)
        self.view = view
        # Add a 3D axis to keep us oriented
        self.axis = scene.visuals.XYZAxis(parent=view.scene)
        self.timer = app.Timer(0.1, connect=self.on_timer, start=True)
        
        self.i = 0
        self.istep = 1
        self.scale = 10.
        self.meshes = []
        self.d = data
        self.np = self.d.shape[1]/3  # number of particles
        self.nt = self.d.shape[0]  # number of timesteps

        # add particles for the first time
        for x,y,z in np.vstack(np.split(self.d[self.i],self.np))[:,:3]:
            m = scene.visuals.Mesh(
                meshdata=mdata, color='r', shading='smooth')
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
    return parser.parse_args()

def visualize():
    """Read data from file and start vispy app """
    args = parse()
    d = np.loadtxt(args.filename)
    c = NbodyCanvas(d)
    c.show()


if __name__ == '__main__':
    visualize()
    if sys.flags.interactive == 0:
        app.run()
