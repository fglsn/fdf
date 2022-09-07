# fdf

This project is about creating a simplified 3D graphic representation of a
relief landscape.  
It is written from scratch in C and the only allowed library is minilibx graphic library.

### General description  
![ Description ](screenshots/6-general.png?raw=true)  

### Instructions  
To compile this program run makefile from the root of repository: ` make `  
  
To run the program execute either ` make map0 ` or ` ./fdf maps/42.fdf `  
  
*NB: Various test maps are located in the maps folder. Libft library not included to this repository, but might be found on my GitHub  
and plased into libft folder here in the root.*  
  
The minilibx window should pop up and you'll see a projection of a chosen map:  
![ Initial position ](screenshots/0-initial.png?raw=true) 


For terminating the progrem press ESC or use close button on a window.

To change altitude press **>** or **<** keys  (US layout)
![ Changed altitude ](screenshots/1-altitude.png?raw=true)  
  
Press **+** or **-** to change size of projection (or use mouse scroll / touchpad gestures)  
![ Changed size ](screenshots/2-size.png?raw=true)  

You can move a projection using arrow keys or drag it with a mouse.  
  
Rotate with keys **3** and **4**
![ Changed angle ](screenshots/3-angle.png?raw=true)  

To change the projection type press **o** (for original) or **i** (for isometric) key
![ Projection type ](screenshots/4-type.png?raw=true)  

Here's an example of a bigger map (mars.fdf)
![ Mars projection ](screenshots/5-mars.png?raw=true)  
