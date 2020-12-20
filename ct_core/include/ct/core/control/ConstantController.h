/**********************************************************************************************************************
This file is part of the Control Toolbox (https://github.com/ethz-adrl/control-toolbox), copyright by ETH Zurich.
Licensed under the BSD-2 license (see LICENSE file in main directory)
**********************************************************************************************************************/

#pragma once

#include "Controller.h"
#include <Eigen/Dense>

namespace ct {
namespace core {

//! A constant controller
/*!
 * Implements a controller that is time and state invariant, i.e. fully constant.
 * This class is useful to integrate a ControlledSystem forward subject to a
 * constant control input.
 */
template <typename MANIFOLD, bool CONT_T>
class ConstantController : public Controller<MANIFOLD, CONT_T>
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    using SCALAR = typename MANIFOLD::Scalar;
    using Base = Controller<MANIFOLD, CONT_T>;
    using Time_t = typename Base::Time_t;
    using control_vector_t = typename Base::control_vector_t;

    //! Default constructor
    /*!
     * Sets the control signal to zero
     */
    ConstantController() = delete;
    ConstantController(const int d) : u_(d), derivative_u0_(d) { derivative_u0_.setIdentity(); }

    //! Constructor
    /*!
     * Initializes the control to a fixed value
     * @param u The fixed control signal
     */
    ConstantController(control_vector_t& u);

    //! Copy constructor
    ConstantController(const ConstantController<MANIFOLD, CONT_T>& other);

    //! Clone operator
    /*!
     * Clones the controller. Used for cloning ControlledSystem's
     * @return pointer to cloned controller
     */
    ConstantController<MANIFOLD, CONT_T>* clone() const override;

    int GetControlDim() const override { return u_.size(); }

    //! Computes current control
    /*!
     * Returns the fixed control signal. Therefore, the return value is invariant
     * to the parameters.
     * @param state The current state of the system (ignored)
     * @param t The time of the system (ignored)
     * @param controlAction The (fixed) control action
     */
    void computeControl(const MANIFOLD& state, const Time_t& tn, control_vector_t& controlAction) override;

    //! Sets the control signal
    /*!
     *
     * @param u The fixed control signal
     */
    void setControl(const control_vector_t& u);

    //! Get the fixed control signal
    /*!
     *
     * @param u The control input to write the signal to.
     */
    const control_vector_t& getControl() const;

    virtual ControlMatrix<SCALAR> getDerivativeU0(const MANIFOLD& state, const Time_t tn) override;

private:
    control_vector_t u_;
    ControlMatrix<SCALAR> derivative_u0_;
};


}  // namespace core
}  // namespace ct
