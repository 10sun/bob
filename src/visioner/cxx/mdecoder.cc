/**
 * @file visioner/cxx/mdecoder.cc
 * @date Fri 27 Jul 13:58:57 2012 CEST
 * @author Andre Anjos <andre.anjos@idiap.ch>
 *
 * @brief This file was part of Visioner and originally authored by "Cosmin
 * Atanasoaei <cosmin.atanasoaei@idiap.ch>". It was only modified to conform to
 * Bob coding standards and structure.
 *
 * Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
 */

#include "bob/visioner/model/mdecoder.h"
#include "bob/visioner/util/manager.h"

#include "bob/visioner/model/losses/diag_exp_loss.h"
#include "bob/visioner/model/losses/diag_log_loss.h"
#include "bob/visioner/model/losses/diag_symexp_loss.h"
#include "bob/visioner/model/losses/diag_symlog_loss.h"
#include "bob/visioner/model/losses/jesorsky_loss.h"

#include "bob/visioner/model/trainers/taylor_booster.h"
#include "bob/visioner/model/trainers/averager.h"

#include "bob/visioner/model/taggers/tagger_object.h"
#include "bob/visioner/model/taggers/tagger_keypoint_oxy.h"

#include "bob/visioner/model/models/mblbp_model.h"
#include "bob/visioner/model/models/model_pool.h"

namespace bob { namespace visioner {

  // Register the available object types
  static bool register_objects()
  {
    // Register boosted loss types
    Manager<Manageable<OptimizationType> >::get_mutable_instance().add("ept", Expectation);
    Manager<Manageable<OptimizationType> >::get_mutable_instance().add("var", Variational);

    // Register feature sharing types
    Manager<Manageable<FeatureSharingType> >::get_mutable_instance().add("shared", Shared);
    Manager<Manageable<FeatureSharingType> >::get_mutable_instance().add("indep", Independent);

    // Register the losses
    Manager<Loss>::get_mutable_instance().add("diag_exp", DiagExpLoss());
    Manager<Loss>::get_mutable_instance().add("diag_log", DiagLogLoss());
    Manager<Loss>::get_mutable_instance().add("diag_symlog", DiagSymLogLoss());
    Manager<Loss>::get_mutable_instance().add("diag_symexp", DiagSymExpLoss());
    Manager<Loss>::get_mutable_instance().add("jesorsky", JesorskyLoss());

    // Register the SW taggers
    Manager<Tagger>::get_mutable_instance().add("object_type", ObjectTagger(ObjectTagger::TypeTagger));
    Manager<Tagger>::get_mutable_instance().add("object_pose", ObjectTagger(ObjectTagger::PoseTagger));
    Manager<Tagger>::get_mutable_instance().add("object_id", ObjectTagger(ObjectTagger::IDTagger));
    Manager<Tagger>::get_mutable_instance().add("keypoint", KeypointOxyTagger());

    // Register models
    Manager<Model>::get_mutable_instance().add("lbp", 
        MBLBPModel());

    Manager<Model>::get_mutable_instance().add("elbp",
        ModelPool<MBLBPModel, 
        ModelPool<MBmLBPModel, 
        ModelPool<MBtLBPModel, MBdLBPModel> > >());

    Manager<Model>::get_mutable_instance().add("mct", 
        MBMCTModel());

    // Register trainers
    Manager<Trainer>::get_mutable_instance().add("avg", Averager());                
    Manager<Trainer>::get_mutable_instance().add("gboost", TaylorBooster());

    return true;
  }

  static const bool registered = register_objects();

  // Decode parameters
  boost::shared_ptr<Loss>	make_loss(const param_t& param)
  {
    const boost::shared_ptr<Loss> loss = Manager<Loss>::get_const_instance().get(param.m_loss);
    loss->reset(param);
    return loss;
  }

  boost::shared_ptr<Tagger> make_tagger(const param_t& param)
  {
    boost::shared_ptr<Tagger> tagger = Manager<Tagger>::get_const_instance().get(param.m_tagger);
    tagger->reset(param);
    return tagger;
  }

  boost::shared_ptr<Model> make_model(const param_t& param)
  {
    boost::shared_ptr<Model> model = Manager<Model>::get_const_instance().get(param.m_feature);
    model->reset(param);
    return model;
  }

  boost::shared_ptr<Trainer> make_trainer(const param_t& param) {
    boost::shared_ptr<Trainer> trainer = Manager<Trainer>::get_const_instance().get(param.m_trainer);
    trainer->reset(param);
    return trainer;
  }

  OptimizationType make_optimization(const param_t& param)
  {
    return **Manager<Manageable<OptimizationType> >::get_const_instance().get(param.m_optimization);
  }

  FeatureSharingType make_sharing(const param_t& param)
  {
    return **Manager<Manageable<FeatureSharingType> >::get_const_instance().get(param.m_sharing);
  }

  // Retrieve the lists of encoded objects
  std::vector<std::string> available_losses_list()
  {
    return Manager<Loss>::get_const_instance().describe_list();
  }

  std::vector<std::string> available_taggers_list()
  {
    return Manager<Tagger>::get_const_instance().describe_list();
  }

  std::vector<std::string> available_models_list()
  {
    return Manager<Model>::get_const_instance().describe_list();
  }

  std::vector<std::string> available_trainers_list()
  {
    return Manager<Trainer>::get_const_instance().describe_list();
  }

  std::vector<std::string> available_optimizations_list()
  {
    return Manager<Manageable<OptimizationType> >::get_const_instance().describe_list();
  }

  std::vector<std::string> available_sharings_list()
  {
    return Manager<Manageable<FeatureSharingType> >::get_const_instance().describe_list();
  }

  // Retrieve the lists of encoded objects as a single string
  std::string available_losses()
  {
    return Manager<Loss>::get_const_instance().describe();
  }

  std::string available_taggers()
  {
    return Manager<Tagger>::get_const_instance().describe();
  }

  std::string available_models()
  {
    return Manager<Model>::get_const_instance().describe();
  }

  std::string available_trainers()
  {
    return Manager<Trainer>::get_const_instance().describe();
  }

  std::string available_optimizations()
  {
    return Manager<Manageable<OptimizationType> >::get_const_instance().describe();
  }

  std::string available_sharings()
  {
    return Manager<Manageable<FeatureSharingType> >::get_const_instance().describe();
  }

}}
