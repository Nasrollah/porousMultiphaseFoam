/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::capillarityModels::pcBrooksAndCorey

Description
    Standard Brooks and Corey capillary pressure model.

SourceFiles
    pcBrooksAndCorey.C

\*---------------------------------------------------------------------------*/

#ifndef pcBrooksAndCorey_H
#define pcBrooksAndCorey_H

#include "capillarityModel.H"
#include "dimensionedScalar.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
  namespace capillarityModels
  {

    /*---------------------------------------------------------------------------*\
                          Class pcBrooksAndCorey Declaration
    \*---------------------------------------------------------------------------*/

    class pcBrooksAndCorey
      :
      public capillarityModel
    {
      // pcBrooks and Corey coefficients
      dictionary pcBrooksAndCoreyCoeffs_;
      dimensionedScalar Sminpc_;    
      dimensionedScalar Smaxpc_;    
      dimensionedScalar pc0_;
      scalar alpha_;

      //- effective saturation of phase b
      volScalarField Se_;

      // capillary pressure and derivative
      volScalarField pc_;
      volScalarField dpcdS_;
        
    public:

      //- Runtime type information
      TypeName("BrooksAndCorey");

      // Constructors

      //- Construct from components
      pcBrooksAndCorey
      (
       const word& name,
       const dictionary& capillarityProperties,
       const volScalarField& Sb
       );

      //- Destructor
      ~pcBrooksAndCorey()
      {}

      // Member Functions

      //- Return the capillary pressure derivative according to pcBrooks and Corey correlation
      tmp<volScalarField> pc() const
      {
	return pc_;
      }

      //- Return the capillary pressure derivative according to pcBrooks and Corey correlation
      tmp<volScalarField> dpcdS() const
      {
	return dpcdS_;
      }

      //- Correct the laminar capillarity
      void correct()
      {
          Se_ == (Sb_-Sminpc_)/(Smaxpc_ - Sminpc_);
          pc_ = pc0_ * pow(Se_,-alpha_);
          dpcdS_= -alpha_*pc0_*(pow(Se_,-alpha_-1))/(Smaxpc_-Sminpc_);
      }

      //- Read transportProperties dictionary
      bool read(const dictionary& capillarityProperties);
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  } // End namespace capillarityModels

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
