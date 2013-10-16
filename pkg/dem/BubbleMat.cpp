#include "BubbleMat.hpp"



YADE_PLUGIN((BubbleMat)(Ip2_BubbleMat_BubbleMat_BubblePhys)(BubblePhys)(Law2_ScGeom_BubblePhys_Bubble));


/********************** Ip2_BubbleMat_BubbleMat_BubblePhys ****************************/
CREATE_LOGGER(Ip2_BubbleMat_BubbleMat_BubblePhys);
void Ip2_BubbleMat_BubbleMat_BubblePhys::go(const shared_ptr<Material>& m1, const shared_ptr<Material>& m2, const shared_ptr<Interaction>& interaction){
	// phys already exists
	if (interaction->phys) return;
	
	/*
	shared_ptr<BubblePhys> phys(new BubblePhys());
	interaction->phys = phys;
	BubbleMat* mat1 = YADE_CAST<BubbleMat*>(m1.get());
	BubbleMat* mat2 = YADE_CAST<BubbleMat*>(m2.get());

	// averaging over both materials
	phys->surfaceTension = .5*(mat1->surfaceTension + mat2->surfaceTension);
	*/
}

/********************** BubblePhys ****************************/
void BubblePhys::computeCoeffs(Real pctMaxForce, Real surfaceTension)
{
	    Real c1 = 2*Mathr::PI*surfaceTension;
	    Real Fmax = pctMaxForce*c1*rAvg;
	    Dmax = pctMaxForce*rAvg*log(pctMaxForce/4);
	    Real dfdd = c1/(log(pctMaxForce/4)+1);
	    coeffB = dfdd/Fmax;
	    coeffA = Fmax/exp(coeffB*Dmax);
}

CREATE_LOGGER(BubblePhys);
Real BubblePhys::computeForce(Real penetrationDepth, Real surfaceTension, Real rAvg, int newtonIter, Real newtonTol, Real fN, BubblePhys* phys) {
	if (penetrationDepth <= 0.0) { return 0.0; }

	Real separation = -penetrationDepth;
	if (separation >= phys->Dmax) {
	  Real f,df,retOld,residual;
	  Real c1 = 2*Mathr::PI*surfaceTension;
	  Real c2 = 1./(4*c1*rAvg);
	  Real g = 0.0;
	  Real ret = fN;
	  int i = 0;
	  do {
		  retOld = ret;
		  
		  g = log(ret*c2);
		  f = separation*c1 - ret*g;
		  df = g+1;
		  ret += f/df;
		  
		  residual = fabs(ret - retOld)/retOld;
		  if (i++ > newtonIter) {
			  throw runtime_error("BubblePhys::computeForce: no convergence\n");
		  }
	  } while (residual > newtonTol);
	  return ret;
	}
	else {
	  return phys->coeffA*exp(phys->coeffB*separation);
	}
}

/********************** Law2_ScGeom_BubblePhys_Bubble ****************************/
CREATE_LOGGER(Law2_ScGeom_BubblePhys_Bubble);

void Law2_ScGeom_BubblePhys_Bubble::go(shared_ptr<IGeom>& _geom, shared_ptr<IPhys>& _phys, Interaction* I){
	ScGeom* geom=static_cast<ScGeom*>(_geom.get());
	BubblePhys* phys=static_cast<BubblePhys*>(_phys.get());
	
	if(!I->isReal()) return;
	if(geom->penetrationDepth <0) {
		scene->interactions->requestErase(I);
		return;
	}
	
	if (I->isFresh(scene)) {
		phys->rAvg = .5*(geom->refR1 + geom->refR2);
		phys->computeCoeffs(pctMaxForce,surfaceTension);
		phys->fN = 1e-9;
	}

	Real &fN = phys->fN;
	fN = phys->computeForce(geom->penetrationDepth, surfaceTension, phys->rAvg, phys->newtonIter, phys->newtonTol, phys->fN, phys);
	Vector3r &normalForce = phys->normalForce;
	normalForce = fN*geom->normal;

	int id1 = I->getId1(), id2 = I->getId2();
	if (!scene->isPeriodic) {
		State* b1 = Body::byId(id1,scene)->state.get();
		State* b2 = Body::byId(id2,scene)->state.get();
		applyForceAtContactPoint(-normalForce, geom->contactPoint , id1, b1->se3.position, id2, b2->se3.position);
	} else {
		scene->forces.addForce(id1,-normalForce);
		scene->forces.addForce(id2,normalForce);
		scene->forces.addTorque(id1,(geom->radius1-0.5*geom->penetrationDepth)* geom->normal.cross(normalForce));
		scene->forces.addTorque(id2,(geom->radius2-0.5*geom->penetrationDepth)* geom->normal.cross(normalForce));
	}
}
