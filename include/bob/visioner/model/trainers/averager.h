/**
 * @file bob/visioner/model/trainers/averager.h
 * @date Fri 27 Jul 13:58:57 2012 CEST
 * @author Andre Anjos <andre.anjos@idiap.ch>
 *
 * @brief This file was part of Visioner and originally authored by "Cosmin
 * Atanasoaei <cosmin.atanasoaei@idiap.ch>". It was only modified to conform to
 * Bob coding standards and structure.
 *
 * Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
 */

#ifndef BOB_VISIONER_AVERAGER_H
#define ABOB_VISIONER_VERAGER_H

#include "bob/visioner/model/trainer.h"

namespace bob { namespace visioner {

  ////////////////////////////////////////////////////////////////////////////////
  // Construct LUT models with discrete, positive and bounded feature values
  //	with fix outputs: the average target values (for each output).
  ////////////////////////////////////////////////////////////////////////////////

  class Averager : public Trainer
  {
    public:

      // Constructor
      Averager(const param_t& param = param_t());

      // Destructor
      virtual ~Averager() {}

      // Reset to new parameters
      virtual void reset(const param_t& param) { m_param = param; }

      // Clone the object
      virtual boost::shared_ptr<Trainer> clone() const { return boost::shared_ptr<Trainer>(new Averager(m_param)); }

      /**
       * Train a model using the given training and validation samples. The
       * number of threads control if the training will be executed on the
       * current thread (zero) or in separate threads (one or more), what can
       * considerably speed it up.
       */
      virtual bool train(const Sampler& t_sampler, const Sampler& v_sampler,
          Model& model, size_t threads);
  };

}}

#endif // BOB_VISIONER_AVERAGER_H
