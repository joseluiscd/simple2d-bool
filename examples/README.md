# Examples

* **Difference file**: Difference between polygons, usage: `./difference_file polygon1.txt polygon2.txt > difference.txt`.

* **Union file**: Union operation of two polygons, usage is the same as in `difference_file`.

* **Intersection file**: Intersection between polygons, usage is the same as `difference_file` and `union_file`

* **Triangle**: Practical example. Generates a set of triangles forming a Sierpinski fractal with a recursive call of the difference boolean operation. Usage: `./triangle number_of_iterations >> file.txt`, where the parameter is the number of times the difference function is called.

* **Plot**: Bash script for using GnuPlot to visualize results of the previous programs. It shows 3 polygons. Usage is `./plot.sh inputPolygon1.txt inputPolygon2.txt resultPolygon.txt`

* **Plot segments**: The same as `plot.sh`, but the third parameter is a file with segments instead of a polygon.
