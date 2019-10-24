# CSci-4611 Assignment 3:  Earthquake

create flat map of earth
- set vertices with vertices in plane mode and push indices into indices Array
- create a mesh
- using earth_mesh_.SetTexCoords to do the texture mapping

create globe map of earth
- set vertices with vertices in globe mode and create normal vector array
- use the same indices Array
- create a mesh
- using earth_mesh_.SetTexCoords to do the texture mapping

change between plane mode and globe mode
- add an extra variable in the Earth::Init called "globe" to check if it is in globe mode
- change the value of "globe" after calling OnGlobeBtnPressed() to shift between two mode

draw the earthquake dot
- get the period you want to show the data at
- draw each earthquake data in this range by using for loop
