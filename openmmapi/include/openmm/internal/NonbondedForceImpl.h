#ifndef OPENMM_NONBONDEDFORCEIMPL_H_
#define OPENMM_NONBONDEDFORCEIMPL_H_

/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2008-2009 Stanford University and the Authors.      *
 * Authors: Peter Eastman                                                     *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

#include "ForceImpl.h"
#include "openmm/NonbondedForce.h"
#include "openmm/Kernel.h"
#include <utility>
#include <set>
#include <string>

namespace OpenMM {

class System;

/**
 * This is the internal implementation of NonbondedForce.
 */

class NonbondedForceImpl : public ForceImpl {
public:
    NonbondedForceImpl(NonbondedForce& owner);
    ~NonbondedForceImpl();
    void initialize(ContextImpl& context);
    NonbondedForce& getOwner() {
        return owner;
    }
    void updateContextState(ContextImpl& context) {
        // This force field doesn't update the state directly.
    }
    void calcForces(ContextImpl& context);
    double calcEnergy(ContextImpl& context);
    std::map<std::string, double> getDefaultParameters() {
        return std::map<std::string, double>(); // This force field doesn't define any parameters.
    }
    std::vector<std::string> getKernelNames();
    /**
     * This is a utility routine that calculates the values to use for alpha and kmax when using
     * Ewald summation.
     */
    static void calcEwaldParameters(const System& system, const NonbondedForce& force, double& alpha, int& kmaxx, int& kmaxy, int& kmaxz);
    /**
     * This is a utility routine that calculates the values to use for alpha and grid size when using
     * Particle Mesh Ewald.
     */
    static void calcPMEParameters(const System& system, const NonbondedForce& force, double& alpha, int& xsize, int& ysize, int& zsize);
private:
    class ErrorFunction;
    class EwaldErrorFunction;
    static double findZero(const ErrorFunction& f, int initialGuess);
    NonbondedForce& owner;
    Kernel kernel;
};

} // namespace OpenMM

#endif /*OPENMM_NONBONDEDFORCEIMPL_H_*/
