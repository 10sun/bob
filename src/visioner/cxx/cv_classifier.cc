/**
 * @file visioner/cxx/cv_classifier.cc
 * @date Fri 27 Jul 13:58:57 2012 CEST
 * @author Andre Anjos <andre.anjos@idiap.ch>
 *
 * @brief This file was part of Visioner and originally authored by "Cosmin
 * Atanasoaei <cosmin.atanasoaei@idiap.ch>". It was only modified to conform to
 * Bob coding standards and structure.
 *
 * Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
 */

#include "bob/core/logging.h"

#include "bob/visioner/cv/cv_classifier.h"
#include "bob/visioner/model/mdecoder.h"
#include "bob/visioner/util/timer.h"
#include "bob/visioner/model/taggers/tagger_object.h"

namespace bob { namespace visioner {

  // Constructor
  CVClassifier::CVClassifier()
  {
  }

  // Command line processing
  template <typename T>
    void decode_var(const boost::program_options::options_description& po_desc,
        boost::program_options::variables_map& po_vm,
        const char* var_name, T& var)
    {
      if (!po_vm.count(var_name))
      {
        bob::core::error << po_desc << std::endl;
        exit(EXIT_FAILURE);
      }

      var = po_vm[var_name].as<T>();
    }

  void CVClassifier::add_options(boost::program_options::options_description& po_desc) const
  {
    po_desc.add_options()

      ("classify_model", boost::program_options::value<std::string>(),
       "classification: model");
  }

  bool CVClassifier::decode(const boost::program_options::options_description& po_desc,
      boost::program_options::variables_map& po_vm)
  {
    // Load the localization model
    const std::string cmd_model = po_vm["classify_model"].as<std::string>();
    if (Model::load(cmd_model, m_model) == false)
    {
      bob::core::error 
        << "Failed to load the classification model <" << cmd_model << ">!" << std::endl;
      return false;
    }
    if (valid_model() == false)
    {
      bob::core::error << "Invalid model!" << std::endl;
      return false;
    }

    // Decode parameters
    //

    // OK
    return true;
  }

  // Check the validity of different components
  bool CVClassifier::valid() const
  {
    return valid_model();
  }
  bool CVClassifier::valid_model() const
  {
    return	m_model.get() != 0 &&
      m_model->n_outputs() == param().m_labels.size();
  }

  // Predict the object label of the keypoints in the <reg> region.
  bool CVClassifier::classify(const CVDetector& detector, const QRectF& reg, uint64_t& dt_label) const
  {
    // Check the sub-window
    const subwindow_t sw = detector.ipyramid().map(reg, param());
    if (detector.ipyramid().check(sw, param()) == false)
    {
      return false;
    }

    // Evaluate the sub-window
    const ipscale_t& ip = detector.ipyramid()[sw.m_s];
    m_model->preprocess(ip);

    std::vector<double> scores(n_classes());                
    for (uint64_t o = 0; o < n_classes(); o ++)
    { 
      scores[o] = m_model->score(o, sw.m_x, sw.m_y);
    }

    dt_label = std::max_element(scores.begin(), scores.end()) - scores.begin();                

    // OK
    return true;
  }

  // Retrieve the ground truth label for the given object
  bool CVClassifier::classify(  const Object& object, uint64_t& gt_label) const
  {
    const boost::shared_ptr<Tagger> tagger = make_tagger(param());
    const ObjectTagger* obj_tagger = dynamic_cast<const ObjectTagger*>(tagger.get());
    if (obj_tagger == 0)
    {
      bob::core::warn << "Invalid classification tagger!" << std::endl;
      return false;
    }

    const int ilabel = obj_tagger->find(object);
    gt_label = ilabel;
    return ilabel >= 0;
  }

  // Compute the confusion matrix considering the 
  //      ground truth and the predicted labels.
  void CVClassifier::evaluate(
      const std::vector<std::string>& ifiles, const std::vector<std::string>& gfiles,
      CVDetector& detector, 
      Matrix<uint64_t>& hits_mat, std::vector<uint64_t>& hits_cnt) const
  {
    hits_mat.resize(n_classes(), n_classes());
    hits_mat.fill(0);

    hits_cnt.resize(n_classes());
    std::fill(hits_cnt.begin(), hits_cnt.end(), 0);

    const boost::shared_ptr<Tagger> tagger = make_tagger(param());
    const ObjectTagger* obj_tagger = dynamic_cast<const ObjectTagger*>(tagger.get());
    if (obj_tagger == 0)
    {
      bob::core::warn << "Invalid classification tagger!" << std::endl;
      return;
    }

    // Process each image ...        
    for (uint64_t i = 0; i < ifiles.size(); i ++)
    {
      const std::string& ifile = ifiles[i];
      const std::string& gfile = gfiles[i];

      // Load the image and the ground truth
      if (detector.load(ifile, gfile) == false)
      {
        bob::core::warn << "Failed to load image <" << ifile << "> or ground truth <" << gfile << ">!" << std::endl;
        continue;
      }

      // Classify sub-windows (on the detections that did not fail)
      Timer timer;				

      std::vector<detection_t> detections;
      detector.scan(detections);

      Object object;
      for (std::vector<detection_t>::const_iterator it = detections.begin(); it != detections.end(); ++ it)
        if (detector.match(*it, object) == true)
        {
          const int gt_label = obj_tagger->find(object);
          if (gt_label < 0)
          {
            continue;
          }

          uint64_t dt_label = 0;
          if (classify(detector, object.bbx(), dt_label) == false)
          {
            bob::core::warn << "Failed to classify a sub-window for the <" << ifile << "> image!" << std::endl;
            continue;
          }

          hits_mat(gt_label, dt_label) ++;
          hits_cnt[gt_label] ++;
        }

      // Debug
      bob::core::info
        << "Image [" << (i + 1) << "/" << ifiles.size() 
        << "]: classified in " << timer.elapsed() << "s." << std::endl;
    }
  }

}}
