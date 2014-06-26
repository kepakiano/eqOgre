eqOgre
======

This is an example application which integrates the open-source rendering engine OGRE (www.ogre3d.org)
into the Equalizer framework (http://www.equalizergraphics.com/) for parallel OpenGL-based applications.

Ogre needs the config files "configs/plugins.cfg" and "configs/resources.cfg". plugins.cfg points to
the Ogre libraries in /usr/lib/OGRE. resource.cfg is empty, because you can find all the resources needed
by this project in the assets folder.

You can find an example Equalizer config in the configs directory.

This project was created using Equalizer 1.6.0 on a Ubuntu 14.04 64 bit machine with Ogre 1.8.1 and Ogre 1.9.0.
