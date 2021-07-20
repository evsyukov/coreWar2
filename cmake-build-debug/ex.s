.name "zork"
.comment "just a basic living prog"

l3:
l2: sti	r0,%:live,%0
	and	r5,%0,r16
live:	live	%1
	zjmp	%:l2
