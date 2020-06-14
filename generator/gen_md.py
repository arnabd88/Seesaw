import sys
import symengine as seng

def initialize(p_num, d_num, fout):
	# obtain the primary matrix POS -> d x p
	POS = [['POS_'+str(i)+'_'+str(j) for j in range(0,p_num)] for i in range(0, d_num)]
	VEL = [["0"]*p_num for i in range(0,d_num)]
	ACC = [["0"]*p_num for i in range(0,d_num)]

	seed = 123456789
	i4_huge = 2147483647
	err = 0.1

	for i in range(d_num):
		for j in range(p_num):
			var_name = 'POS_'+str(i)+'_'+str(j)
			k = ( seed // 127773 )
			seed = 16807 * ( seed - k * 127773 ) - k * 2836
			seed = ( seed % i4_huge )
			if ( seed < 0):
				seed = seed + i4_huge
			rand_val = 1.0 + ( 10.0 - 1.0 ) * seed * 4.656612875E-10
			fout.write("\t{var}\tfl64 : ({val} - {err}, {val} + {err});\n".format(var=var_name,err=err,val=str(rand_val)))

	return POS, VEL, ACC

def compute( step, p_num, d_num, POS, VEL, mass):

	FORCE = [["0"]*p_num for i in range(0, d_num)]
	RIJ   = ["0"]*d_num

	potential = "0.0"

	for i in range(0, p_num):

		for j in range(0, p_num):

			if (i != j):
				
				for k in range(0, d_num):
					lhs = 'rsij_{step}_{i}_{j}_{k}'.format(step=step, i=i,j=j,k=k)
					rhs = '{poski} - {poskj}'.format(poski=POS[k][i], poskj=POS[k][j])
					fout.write("{lhs} rnd64 = {rhs} ;\n".format(lhs=lhs, rhs=rhs))
					RIJ[k] = lhs

				D = 'dsij_{step}_{i}_{j}_{k}'.format(step=step, i=i, j=j, k=k)
				rhs = " + ".join(["({rij_k}*{rij_k})".format(rij_k=RIJ[k]) for k in range(d_num)])
				fout.write("{lhs} rnd64 = sqrt({rhs}) ;\n".format(lhs=D, rhs=rhs))

				potential_lhs = "potsij_{step}_{i}_{j}".format(step=step, i=i, j=j)
				potential_rhs = "{pot} + 0.5 * sin({Dist})*sin({Dist})".format(pot=potential, Dist=D)
				fout.write("{lhs} rnd64 = {rhs} ;\n".format(lhs=potential_lhs, rhs=potential_rhs))
				potential = potential_lhs ;

				for k in range(0, d_num):
					lhs = "forcesij_{step}_{i}_{j}_{k}".format(step=step, i=i, j=j, k=k)
					rhs = "{forceki} - {rijk}*sin(2*{Dist})/{Dist}".format(forceki=FORCE[k][i], rijk=RIJ[k],Dist=D)
					fout.write("{lhs} rnd64 = {rhs} ;\n".format(lhs=lhs, rhs=rhs))
					FORCE[k][i] = lhs

	kinetic = "0.0"
	for k in range(d_num):
		for j in range(p_num):
			lhs = "kinetic_skj_{step}_{k}_{j}".format(step=step, k=k, j=j)
			rhs = "{kinetic} + {velkj}*{velkj}".format(kinetic=kinetic, velkj=VEL[k][j])
			fout.write("{lhs} rnd64 = {rhs} ;\n".format(lhs=lhs, rhs=rhs))
			kinetic = lhs

	kinetic_lhs = "kineticStep_{step}".format(step=step)
	kinetic_rhs = "0.5 * {mass} * {kinetic}".format(mass=mass, kinetic=kinetic)
	fout.write("{lhs} rnd64 = {rhs} ;\n".format(lhs=kinetic_lhs, rhs=kinetic_rhs))
	kinetic = kinetic_lhs

	return FORCE, potential, kinetic

def update ( step, p_num, d_num, POS, VEL, FORCE, ACC, mass, dt ):
	rmass = 1.0 / mass 

	for i in range(0, d_num):
		for j in range(0, p_num):
			lhs = 'POSsij_{step}_{i}_{j}'.format(step=step,i=i,j=j)
			rhs = "{posij} + {velij}*{dt} + 0.5*{accij}*{dt}*{dt}".format(posij=POS[i][j], velij=VEL[i][j], accij=ACC[i][j], dt=dt)
			fout.write("{lhs} rnd64 = {rhs} ;\n".format(lhs=lhs, rhs=rhs))
			POS[i][j] = lhs

	for i in range(0, d_num):
		for j in range(0, p_num):
			lhs = 'VELsij_{step}_{i}_{j}'.format(step=step, i=i, j=j)
			rhs = "{velij} + 0.5*{dt}*({fij}*{rmass} + {accij})".format(velij=VEL[i][j], dt=dt, fij=FORCE[i][j], rmass=str(rmass), accij=ACC[i][j])
			fout.write("{lhs} rnd64 = {rhs} ;\n".format(lhs=lhs, rhs=rhs))
			VEL[i][j] = lhs

	for i in range(0, d_num):
		for j in range(0, p_num):
			lhs = 'ACCsij_{step}_{i}_{j}'.format(step=step, i=i, j=j)
			rhs = "{fij}*{rmass}".format(fij=FORCE[i][j], rmass=str(rmass))
			fout.write("{lhs} rnd64 = {rhs} ;\n".format(lhs=lhs, rhs=rhs))
			ACC[i][j] = lhs

	return POS, VEL, ACC

def md( p_num, d_num, step_num, dt, fout):


	mass = 1.0
	step = 0
	e0 = ''

	for step in range(0, step_num):
		if step==0:
			fout.write("INPUTS {\n\n")
			POS, VEL, ACC = initialize(p_num, d_num, fout)
			fout.write("}\n\n")
			
			fout.write("OUTPUTS {\n\n")
			fout.write("forcesij_{step}_{x}_{y}_2 ;\n".format(step=step_num-1,x=p_num-1, y=p_num-2));
			fout.write("}\n\n")

			fout.write("EXPRS {\n\n")
		else:
			POS, VEL, ACC = update ( step, p_num, d_num, POS, VEL, FORCE, ACC, mass, dt )
			pass

		# compute ( p_num, d_num, pos, vel, mass )
		FORCE, potential, kinetic = compute( step, p_num, d_num, POS, VEL, mass)

		if step==0:
			e0_lhs = "e0_{step}".format(step=step)
			e0_rhs = "{potential} + {kinetic}".format(potential=potential, kinetic=kinetic)
			fout.write("{lhs} rnd64 = {rhs} ;\n".format(lhs=e0_lhs, rhs=e0_rhs))
			e0 = e0_lhs
	
	
	
	fout.write("}\n\n")




if __name__ == "__main__":
	p_num = 10
	d_num = 3
	step_num = 2
	dt = 0.1

	## default arrays to begin with


	fout = open(sys.argv[1], 'w')
	md(p_num, d_num, step_num, dt, fout)
	fout.close()
