imaging
=======

This program configures an Andor camera to take images, offloads them,
saves the images as tif files, and sorts them into a dated folder
structure.

The images are (optionally) displayed in units of optical depth,
assuming that three images were taken in quick succession using the
"fast kinetics" mode of the Andor camera. The GUI allows zooming into
a region of interest and displays the images in a false color map.

The program uses wxWidgets for the GUI. Separate threads allow the
image taking and sorting to be pretty fast (duty cycles of down to
1-2s at 1024^2 pixel are possible).

For details and why the program needs to be fast, see my PhD thesis,
available at

  http://jila.colorado.edu/yelabs/pubs/theses.html
