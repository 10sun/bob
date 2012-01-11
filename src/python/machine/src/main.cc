/**
 * @file python/machine/src/main.cc
 * @date Tue Jan 18 17:07:26 2011 +0100
 * @author André Anjos <andre.anjos@idiap.ch>
 *
 * @brief Combines all modules to make up the complete bindings
 *
 * Copyright (C) 2011 Idiap Reasearch Institute, Martigny, Switzerland
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

#include "core/python/ndarray.h"

#if defined(HAVE_LIBSVM)
void bind_machine_svm();
#endif

void bind_machine_gmm();
void bind_machine_activation();
void bind_machine_linear();
void bind_machine_mlp();
void bind_machine_linear_scoring();
void bind_machine_ztnorm();
void bind_machine_jfa();
void bind_machine_plda();
void bind_machine_wiener();
void bind_machine_version();

BOOST_PYTHON_MODULE(libpybob_machine)
{
  bob::python::setup_python("bob classes and sub-classes for machine access");

#if defined(HAVE_LIBSVM)
  bind_machine_svm();
#endif

  bind_machine_gmm();
  bind_machine_activation();
  bind_machine_linear();
  bind_machine_mlp();
  bind_machine_linear_scoring();
  bind_machine_ztnorm();
  bind_machine_jfa();
  bind_machine_plda();
  bind_machine_wiener();
  bind_machine_version();
}
