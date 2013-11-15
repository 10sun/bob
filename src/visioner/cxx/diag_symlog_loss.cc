/**
 * @file visioner/cxx/diag_symlog_loss.cc
 * @date Fri 27 Jul 13:58:57 2012 CEST
 * @author Andre Anjos <andre.anjos@idiap.ch>
 *
 * @brief This file was part of Visioner and originally authored by "Cosmin
 * Atanasoaei <cosmin.atanasoaei@idiap.ch>". It was only modified to conform to
 * Bob coding standards and structure.
 *
 * Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
 */

#include "bob/visioner/model/losses/diag_symlog_loss.h"

namespace bob { namespace visioner {

  // Compute the error (associated to the loss)
  double DiagSymLogLoss::error(double target, double score) const
  {
    return regression_error(target, score, 0.0);
  }

  // Compute the loss value & derivatives
  void DiagSymLogLoss::eval(
      double target, double score,
      double& value) const
  {
    static const double delta = std::log(4.0);

    const double eval = std::exp(score - target);

    value = std::log(2.0 + eval + 1.0 / eval) - delta;
  }
  void DiagSymLogLoss::eval(
      double target, double score,
      double& value, double& deriv1) const
  {
    static const double delta = std::log(4.0);

    const double eval = std::exp(score - target);
    const double norm = 1.0 / (1.0 + eval);

    value = std::log(2.0 + eval + 1.0 / eval) - delta;
    deriv1 = (eval - 1) * norm;
  }
  void DiagSymLogLoss::eval(
      double target, double score,
      double& value, double& deriv1, double& deriv2) const
  {
    static const double delta = std::log(4.0);

    const double eval = std::exp(score - target);
    const double norm = 1.0 / (1.0 + eval);

    value = std::log(2.0 + eval + 1.0 / eval) - delta;
    deriv1 = (eval - 1) * norm;
    deriv2 = 2.0 * eval * norm * norm;
  }

}}
