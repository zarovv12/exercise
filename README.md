#Exercise

### Design
Assuming the xml files contain the same rows and columns of cds with the same names, 
I decided to use 2 libraries to solve the exercise:
* rapidxml: A library to parse xml files created an easy to use datastructure to get xml elements.
* HTMLBuilder: Used to create HTML files and elements in an easy to use streams.

Using those libraries the solution was simple. I parsed the xml file using rapidxml, 
looped the elements using the predefined column names, pushed the values to the html builder stream
and with that i created the html file.

In real envs, the security of the libraries need to be checked.

### Prerequisites
* Checked on amazon linux version 2.
* C++ version 14.
* cd_catalog.xml file need to have the same row names.

### Compile
* git clone the project.
* cd to the project.

* Run compilation:

```
g++ exercise.cpp -o ex
```

* Add permissions if needed:

```
chmod 777 ex
```

* Run the program with xml file:

```
./ex cd_catalog.xml
```

* An HTML file will be created in the same folder called cds.html.
  The file will have the correct table.


### References:
* https://github.com/SRombauts/HtmlBuilder
* https://rapidxml.sourceforge.net/
