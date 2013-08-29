/**
 * @file trainer/python/wccn.cc
 * @date Tue Apr 10 15:00:00 2013 +0200
 * @author Elie Khoury <Elie.Khoury@idiap.ch>
 * @author Laurent El Shafey <Laurent.El-Shafey@idiap.ch>
 *
 * Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <boost/python.hpp>
#include <bob/python/ndarray.h>
#include <boost/shared_ptr.hpp>
#include <boost/python/stl_iterator.hpp>
#include <bob/trainer/WCCNTrainer.h>
#include <bob/machine/LinearMachine.h>

using namespace boost::python;


static char CLASS_DOC[] = \
  "Trains a :py:class:`bob.machine.LinearMachine` to perform Within-Class Covariance Normalisation (WCCN).\n" \
  "\n" \
  "WCCN finds the projection matrix W that allows us to linearly project the data matrix X to another (sub) space such that:\n"\
  "\n"\
  ".. math::\n" \
  "   \n" \
  "   (1/N) S_{w} = W W^T\n" \
  "\n"\
  "where W is an upper triangular matrix computed using Cholesky Decomposition:\n"\
  "\n"\
  ".. math::\n" \
  "   \n" \
  "   W = cholesky([(1/K) S_{w} ]^{-1})\n" \
  "\n"\
  "where:\n"\
  "\n" \
  ":math:`K`\n" \
  "  \n" \
  "  the number of classes\n"\
  "\n"\
  ":math:`S_w`\n" \
  "\n" \
  "   the within-class scatter; it also has dimensions (X.shape[0], X.shape[0]) and is defined as :math:`S_w = \\sum_{k=1}^K \\sum_{n \\in C_k} (x_n-m_k)(x_n-m_k)^T`, :math:`C_k` a set representing all samples for class k.\n" \
  "\n" \
  ":math:`m_k`\n" \
  "  \n" \
  "   the class *k* empirical mean, defined as :math:`m_k = \\frac{1}{N_k}\\sum_{n \\in C_k} x_n`\n" \
  "\n" \
    "References:\n" \
  "\n" \
  "1. Andrew O. Hatch, Sachin Kajarekar, and Andreas Stolcke, Within-class covariance normalization for SVM-based speaker recognition, In INTERSPEECH, 2006.\n"\
  "2. http://en.wikipedia.org/wiki/Cholesky_decomposition\n"\
  "\n"\
  "\n"\
;

void py_train1(bob::trainer::WCCNTrainer& t, bob::machine::LinearMachine& m, object data)
{
  stl_input_iterator<bob::python::const_ndarray> dbegin(data), dend;
  std::vector<bob::python::const_ndarray> vdata_ref(dbegin, dend);
  std::vector<blitz::Array<double,2> > vdata;
  for(std::vector<bob::python::const_ndarray>::iterator it=vdata_ref.begin(); 
      it!=vdata_ref.end(); ++it)
    vdata.push_back(it->bz<double,2>());
  blitz::Array<double,1> eig_val(vdata[0].extent(1)-1);
  t.train(m, vdata);
}

object py_train2(bob::trainer::WCCNTrainer& t, object data)
{
  stl_input_iterator<bob::python::const_ndarray> dbegin(data), dend;
  std::vector<bob::python::const_ndarray> vdata_ref(dbegin, dend);
  std::vector<blitz::Array<double,2> > vdata;
  for(std::vector<bob::python::const_ndarray>::iterator it=vdata_ref.begin(); 
      it!=vdata_ref.end(); ++it)
    vdata.push_back(it->bz<double,2>());
  bob::machine::LinearMachine m(vdata[0].extent(1),vdata[0].extent(1));
  t.train(m, vdata);
  return object(m);
}

void bind_trainer_wccn()
{
  class_<bob::trainer::WCCNTrainer, boost::shared_ptr<bob::trainer::WCCNTrainer> >("WCCNTrainer", CLASS_DOC, init<optional<const bool> >((arg("self"), arg("use_pinv")=false), 
          "Initializes a new WCCN trainer\n" \
          "\n" \
          "Keyword parameters:\n" \
          "\n" \
          "use_pinv (bool) - defaults to ``False``\n" \
          "   \n" \
          "   If set to ``True``, use the pseudo-inverse to calculate :math:`S_w^{-1}`\n"
          "   \n" \
          "   .. note::\n" \
          "     \n" \
          "     Using the pseudo-inverse for the WCCN training is only recommended if you cannot make it work using the default method. It is slower and requires more machine memory to store partial values of the pseudo-inverse `S_w^{-1}`.\n")) 
    .def(init<const bob::trainer::WCCNTrainer&>((arg("self"), arg("other")), "Copy constructs a WCCNTrainer"))
    .def(self == self)
    .def(self != self)
    .def("is_similar_to", &bob::trainer::WCCNTrainer::is_similar_to, (arg("self"), arg("other"), arg("r_epsilon")=1e-5, arg("a_epsilon")=1e-8), "Compares this WCCNTrainer with the 'other' one to be approximately the same.")
    .def("train", &py_train1, (arg("self"), arg("machine"), arg("data")), "Trains the LinearMachine to perform the WCCN, given a training set.")
    .def("train", &py_train2, (arg("self"), arg("data")), "Allocates, trains and returns a LinearMachine to perform the WCCN, given a training set.")
    .add_property("use_pinv", &bob::trainer::WCCNTrainer::getUsePseudoInverse, &bob::trainer::WCCNTrainer::setUsePseudoInverse,
        "If ``True``, use the pseudo-inverse to calculate :math:`S_w^{-1}`")
  ;
}
