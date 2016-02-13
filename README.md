# TMVA+

The TMVA+ is a current ongoing project that seeks to extend the Toolkit for Multivariate Analysis (TMVA).
It contains implementaions of algorithms that are not found in the TMVA.
On its completion it should contain the following implementations (though this may be subject to change):

+ [Differential Evolution](https://en.wikipedia.org/wiki/Differential_evolution)
+ [RANSAC](https://en.wikipedia.org/wiki/RANSAC)
+ [Mirror Descent](http://www.stats.ox.ac.uk/~lienart/blog_opti_mda.html)
+ [Expectation–Maximization (EM) algorithm](https://en.wikipedia.org/wiki/Expectation%E2%80%93maximization_algorithm)

---
##Loading the classes
First ensure that ROOT is installed. If you haven't done this already, details of how to do this can be found [here](https://root.cern.ch/root/html534/guides/users-guide/InstallandBuild.html)
. To run ROOT, open bash and type

``
cd root
source ./bin/thisroot.sh
root
``

If a message such as 

``
root: can't figure out DISPLAY, set it manually
``

comes up, type ``export DISPLAY=localhost:0.0`` and repeat the above steps.

If done correctly, then a message saying ``W E L C O M E  to  R O O T`` as follows should appear in the bash shell

And finally, to load the classes type

```
.L [file_name.L]
[class name]
[2] [function]
```
