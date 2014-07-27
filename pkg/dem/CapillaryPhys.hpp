/*************************************************************************
*  Copyright (C) 2006 by luc Scholtes                                    *
*  luc.scholtes@hmg.inpg.fr                                              *
*                                                                        *
*  This program is free software; it is licensed under the terms of the  *
*  GNU General Public License v2 or later. See file LICENSE for details. *
*************************************************************************/
#pragma once
#include<yade/pkg/dem/FrictPhys.hpp>
#include<yade/pkg/common/ElastMat.hpp>
#include<yade/pkg/common/Dispatching.hpp>

class CapillaryPhys : public FrictPhys
{
	public :
		int currentIndexes [4]; // used for faster interpolation (stores previous positions in tables)
		
		virtual ~CapillaryPhys() {};

	YADE_CLASS_BASE_DOC_ATTRS_DEPREC_INIT_CTOR_PY(CapillaryPhys,FrictPhys,"Physics (of interaction) for Law2_ScGeom_CapillaryPhys_Capillarity.",
				 ((bool,meniscus,false,,"Presence of a meniscus if true"))
				 ((bool,isBroken,false,,"If true, capillary force is zero and liquid bridge is inactive."))
				 ((Real,capillaryPressure,0.,,"Value of the capillary pressure Uc defines as Ugas-Uliquid"))
				 ((Real,vMeniscus,0.,,"Volume of the menicus"))
				 ((Real,Delta1,0.,,"Defines the surface area wetted by the meniscus on the smallest grains of radius R1 (R1<R2)"))
				 ((Real,Delta2,0.,,"Defines the surface area wetted by the meniscus on the biggest grains of radius R2 (R1<R2)"))
				 ((Vector3r,fCap,Vector3r::Zero(),,"Capillary Force produces by the presence of the meniscus"))
				 ((short int,fusionNumber,0.,,"Indicates the number of meniscii that overlap with this one"))
				 ,/*deprec*/
				 ((Fcap,fCap,"naming convention"))
				 ((CapillaryPressure,capillaryPressure,"naming convention"))
				 ,,
				 createIndex();currentIndexes[0]=currentIndexes[1]=currentIndexes[2]=currentIndexes[3]=0;
				 ,
				 );
	REGISTER_CLASS_INDEX(CapillaryPhys,FrictPhys);
};
REGISTER_SERIALIZABLE(CapillaryPhys);


class Ip2_FrictMat_FrictMat_CapillaryPhys : public IPhysFunctor
{
	public :
		virtual void go(	const shared_ptr<Material>& b1,
					const shared_ptr<Material>& b2,
					const shared_ptr<Interaction>& interaction);

	FUNCTOR2D(FrictMat,FrictMat);
	YADE_CLASS_BASE_DOC_ATTRS_CTOR(Ip2_FrictMat_FrictMat_CapillaryPhys,IPhysFunctor, "RelationShips to use with Law2_ScGeom_CapillaryPhys_Capillarity\n\n In these RelationShips all the interaction attributes are computed. \n\n.. warning::\n\tas in the others :yref:`Ip2 functors<IPhysFunctor>`, most of the attributes are computed only once, when the interaction is new.",,;);
	
};
REGISTER_SERIALIZABLE(Ip2_FrictMat_FrictMat_CapillaryPhys);

