.. vim: set fileencoding=utf-8 :
.. Andre Anjos <andre.anjos@idiap.ch>
.. Wed Jan 11 14:43:35 2012 +0100
..
.. Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland

=======================================
 Motivations and Philosophy
=======================================

We started developing |project| because of a common need in many research
laboratories like ours: the need to have a software platform where stable
algorithms and common tools could be stored, easily shared and maintained.
We quickly realised the importance of such a platform, having a set of
common algorithms and tools in one central repository with good documentation
greatly improved our efficiency by allowing us to not only more easily share
our code but also to allow new people (and external parties) to get up to speed
and collaborate much more easily! With this in mind we have tried to maintain and improve
the functionality of |project| with the following ideas in mind.

* All modifications and improvements are thoroughly tested at every minor
  change: correctness comes first, whereas speed is a bonus. This is not to
  say |project| is not fast enough - it is! But we do not sacrifice the
  readability and maintainability of our code for efficiency. We are constantly inspecting
  the code and making sure that other people (mainly beginners and new students) can understand
  what it is that our programs do.
* Reproducing publications should be dead-simple. If that is not the case, the
  potential impact becomes severely compromised. We try to develop |project| so
  that our own research results are easy to reproduce and understand.
* There should always be a laboratory-like environment in which experiments can
  be conducted without the compile-link-test cycles which tend to be lengthy
  and counter-productive. We have chosen the `Python`_ language because it
  allows a fast-paced and engaging experience. We re-use lots of available
  functionality that is already shipped with the language or are considered
  *de-facto* standards such as `NumPy`_, for efficient array manipulation and
  operation vectorization or `Matplotlib`_ for plotting.
* We still keep the ability to implement fast versions (in `C++`_) of
  identified bottlenecks. We do this by avoiding the `NumPy`_ C-API which can
  be overwhelming, instead for the `C++`_ code we use simple and efficient `Blitz++`_
  arrays. With such an approach, our `C++`_ becomes clean and easy to understand.
  It also means that it is very easy to speed-up code if you need to in |project|.
* As much as is possible, with a project in this scale, we try to re-use
  existing open-source packages and standards. This simplifies our testing to
  the bare minimum and keeps the overall quality of |project| high.
* We make this effort so |project| is useful to us (and maybe to you) as a
  continuously development framework for new experiments in signal processing,
  machine learning and biometrics. For this reason we open source it
  (`BSD-3-Clause`_) with the hope that it is useful to others. For more
  information on licensing, please visit our :doc:`Licensing`.

For more details about the history and authors of |project|, you can see :doc:`History`.

.. include:: links.rst
