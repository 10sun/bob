/**
 * @file visioner/programs/trainer.cc
 * @date Fri 27 Jul 13:58:57 2012 CEST
 * @author Andre Anjos <andre.anjos@idiap.ch>
 *
 * @brief This file was part of Visioner and originally authored by "Cosmin
 * Atanasoaei <cosmin.atanasoaei@idiap.ch>". It was only modified to conform to
 * Bob coding standards and structure.
 *
 * Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
 */

#include <boost/thread.hpp>

#include "bob/core/logging.h"

#include "bob/visioner/util/timer.h"
#include "bob/visioner/model/mdecoder.h"
#include "bob/visioner/model/sampler.h"

// Train the <model>
static bool train(bob::visioner::Model& model) {
  bob::visioner::Timer timer;

  const bob::visioner::param_t param = model.param();

  // Load the data files        
  timer.restart();
  const bob::visioner::Sampler t_sampler(param, bob::visioner::Sampler::TrainSampler, boost::thread::hardware_concurrency());
  const bob::visioner::Sampler v_sampler(param, bob::visioner::Sampler::ValidSampler, boost::thread::hardware_concurrency()); 
  bob::core::info << "timing: loading ~ " << timer.elapsed() << "." << std::endl;

  // Train the model using coarse-to-fine feature projection
  for (uint64_t p = 0; p <= param.m_projections; p ++, model.project())
  {
    timer.restart();
    if (bob::visioner::make_trainer(param)->train(t_sampler, v_sampler, model,
          boost::thread::hardware_concurrency()) == false)
    {
      bob::core::error << "Failed to train the model!" << std::endl;
      return false;
    }
    bob::core::info << "timing: training ~ " << timer.elapsed() << "." << std::endl;
  }

  // OK
  return true;
}

int main(int argc, char *argv[]) {

  bob::visioner::param_t param;

  // Parse the command line
  boost::program_options::options_description po_desc("", 160);
  po_desc.add_options()
    ("help,h", "help message");
  po_desc.add_options()
    ("model", boost::program_options::value<std::string>(),
     "model");
  param.add_options(po_desc);

  boost::program_options::variables_map po_vm;
  boost::program_options::store(
      boost::program_options::command_line_parser(argc, argv)
      .options(po_desc).run(),
      po_vm);
  boost::program_options::notify(po_vm);

  // Check arguments and options
  if (	po_vm.empty() || po_vm.count("help") ||
      !po_vm.count("model") ||
      !param.decode(po_desc, po_vm))
  {
    bob::core::error << po_desc << std::endl;
    exit(EXIT_FAILURE);
  }

  const std::string cmd_model = po_vm["model"].as<std::string>();

  // Train the model	
  bob::visioner::Timer timer;
  boost::shared_ptr<bob::visioner::Model> model = make_model(param);
  if (train(*model) == false)
  {
    bob::core::error << "Failed to train the model!" << std::endl;
    exit(EXIT_FAILURE);
  }	
  bob::core::info << ">>> Training done in " << timer.elapsed() << "s." << std::endl;	

  // Save the model
  if (model->save(cmd_model) == false)
  {
    bob::core::error << "Failed to save the model!" << std::endl;
    exit(EXIT_FAILURE);
  }

  // OK
  bob::core::info << "Program finished successfuly" << std::endl;
  return EXIT_SUCCESS;

}
