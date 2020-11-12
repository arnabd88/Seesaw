set view 60, 20, 1


set xrange [8.5:9.5]
set yrange [8:9]


set hidden3d
set isosamples 80

#splot x + y + x*y
#splot y + 1 + 1/(x + x*y)
#splot (y/x) + x + x*y + y

#splot (x-y < 0.4) ? sin(y) + 1 + 1/(x + x*y) : ( (( x*x > 0.25 ) && (y*(y/x + x) <= x*x)) ? (y/x) + x + x*y + sin(y) : x + sin(y) + x*y  )  

splot (x-y < 0.4) ? 0 : ( (( x*x > 0.25 ) && (y*(y/x + x) <= x*x)) ? 5 : 10  )

#splot (( x*x > 0.25 ) && (y*(y/x + x) <= x*x)) ? 1 : 0
#splot (( x*x <= 0.25 ) || (y*(y/x + x) > x*x)) ? 1 : 0
#splot (( x*x > 0.25 ) && (y*(y/x + x) <= x*x )) && (( x*x <= 0.25  ) || (y*(y/x + x) > x*x )) ? 1 : 0
#splot (( x*x > 0.25 - 1.0991207e-15 ) && (y*(y/x + x) <= x*x + 1.11022e-14)) && (( x*x <= 0.25 + 1.0991207e-15 ) || (y*(y/x + x) > x*x - 3.33178e-13 - 1.11022e-14)) ? 1 : 0

#splot (( x*x > 0.25 - 0.000001 ) && (y*(y/x + x) <= x*x + 0.000001)) && (( x*x <= 0.25 + 0.000001 ) || (y*(y/x + x) > x*x - 0.00003 - 0.00001)) ? 10 : 0
