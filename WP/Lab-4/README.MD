Laboratory Work Nr.4
====================

Title
-----

Windows Timer. Animation.
------------

•Windows timer


--------------------

•Solved flicking problem.

	The primary cause of  flickering is erasing the background, then immediately drawing over it. 
	Since we are apparently drawing the whole client area of our window in WM_PAINT, I added a handler for WM_ERASEBKGND as it is said in link what you gave to us that does nothing but return TRUE to indicate that the background has been erased.

•Added 2 animated objects which will interact with each other. Balls that have different velocity and moving angles. They should behave based on every rule listed in lab.


•I hooked 3 keyboard inputs:

	When you press the UP button the speed of circles is increasing.

	When you press the DOWN button the speed of circles is decreasing, this is possible also by scrolling.

	You can push a new object with mouse.
	
	You can do whatever you want :). 
