;; calc-units-update.el -- update for calc-units.el, a calculator for Emacs
;;
;; Copyright (C) 2002 Jochen K�pper
;;
;; This file is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published
;; by the Free Software Foundation; either version 2, or (at your
;; option) any later version.
;;
;; It is distributed in the hope that it will be useful, but WITHOUT
;; ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
;; or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
;; License for more details.
;;
;; These values are taken from the following sources:
;; * CODATA
;;   - Journal of Physical and Chemical Reference Data, 28(6), 1713-1852, 1999.
;;   - Reviews of Modern Physics, 72(2), 351-495, 2000.
;;   - http://physics.nist.gov/cuu/Constants/index.html
;; * NIST
;;   - http://physics.nist.gov/Pubs/SP811/appenB9.html
;; * NASA JPL
;;   - http://neo.jpl.nasa.gov/glossary/au.html

(require 'calc)

(setq math-additional-units
  '(;; length
    ( au      "149597870691. m"        "Astronomical Unit" ) ;; NASA JPL 
    ;; mass
    ( amu     "1.66053873e-27 kg"      "Unified atomic mass" ) ;; CODATA
    ;; pressure
    ( inH2O   "2.490889e2 Pa"          "Inch of water" ) ;; NIST 
    ( e       "1.602176462e-19 C"      "Elementary charge" ) ;; CODATA
    ( ech     "1.602176462e-19 C"      "Elementary charge" ) ;; CODATA
    ;; other physical quantities (CODATA 1998)
    ( h       "6.62606876e-34 J s"     "*Planck's constant" )
    ( hbar    "h / 2 pi"               "Planck's constant" )
    ( mu0     "4 pi 1e-7 H/m"          "Permeability of vacuum" )
    ( Grav    "6.673e-11 m^3/kg^1/s^2" "Gravitational constant" )
    ( Nav     "6.02214199e23 / mol"    "Avagadro's constant" )
    ( me      "9.10938188e-31 kg"      "Electron rest mass" )
    ( mp      "1.67262158e-27 kg"      "Proton rest mass" )
    ( mn      "1.67492716e-27 kg"      "Neutron rest mass" )
    ( mu      "1.88353109e-28 kg"      "Muon rest mass" )
    ( Ryd     "10973731.568549 h c/m"  "Rydberg's constant (energy)" )
    ( k       "1.3806503e-23 J/K"      "Boltzmann's constant" )
    ( fsc     "7.297352533e-3"         "Fine structure constant" )
    ( muB     "927.400899e-26 J/T"     "Bohr magneton" )
    ( muN     "5.05078317e-27 J/T"     "Nuclear magneton" )
    ( mue     "928.476362e-26 J/T"     "Electron magnetic moment" )
    ( mup     "1.410606633e-26 J/T"    "Proton magnetic moment" )
    ( R0      "8.314472 J/mol/K"       "Molar gas constant" )
    ( V0      "22.710981e-3 m^3/mol"   "Standard volume of ideal gas" )
    ))

(provide 'calc-units-update)
