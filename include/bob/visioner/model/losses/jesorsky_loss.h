/**
 * @file bob/visioner/model/losses/jesorsky_loss.h
 * @date Fri 27 Jul 13:58:57 2012 CEST
 * @author Andre Anjos <andre.anjos@idiap.ch>
 *
 * @brief This file was part of Visioner and originally authored by "Cosmin
 * Atanasoaei <cosmin.atanasoaei@idiap.ch>". It was only modified to conform to
 * Bob coding standards and structure.
 *
 * Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
 */

#ifndef BOB_VISIONER_JESORSKY_LOSS_H
#define BOB_VISIONER_JESORSKY_LOSS_H

#include "bob/visioner/model/loss.h"

namespace bob { namespace visioner {

  /**
   * Diagonal multivariate losses: the sum (over outputs) of univariate losses.
   */
  class JesorskyLoss : public Loss {

    public:

      // Constructor
      JesorskyLoss(const param_t& param = param_t())
        :       Loss(param)
      {                        
      }

      // Destructor
      virtual ~JesorskyLoss() {}

      // Reset to new parameters
      virtual void reset(const param_t& param) { m_param = param; }

      // Clone the object
      virtual boost::shared_ptr<Loss> clone() const { return boost::shared_ptr<Loss>(new JesorskyLoss(m_param)); }

      // Compute the error (associated to the loss)
      virtual double error(
          const double* targets, const double* scores, uint64_t size) const;

      // Compute the loss value & derivatives
      virtual void eval(
          const double* targets, const double* scores, uint64_t size,
          double& value) const;
      virtual void eval(
          const double* targets, const double* scores, uint64_t size,
          double& value, double* grad) const;

    protected:

      // Compute the distance between the eyes
      double eye_dist(const double* targets) const
      {
        const double dx = targets[0] - targets[2];
        const double dy = targets[1] - targets[3];
        return std::sqrt(dx * dx + dy * dy);
      }

      // Compute the number of facial feature points
      uint64_t points(uint64_t size) const
      {
        return size >> 1;
      }
  };

}}

#endif // BOB_VISIONER_JESORSKY_LOSS_H
