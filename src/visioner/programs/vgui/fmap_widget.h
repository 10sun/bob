/**
 * @file visioner/programs/vgui/fmap_widget.h
 * @date Fri 27 Jul 13:58:57 2012 CEST
 * @author Andre Anjos <andre.anjos@idiap.ch>
 *
 * @brief This file was part of Visioner and originally authored by "Cosmin
 * Atanasoaei <cosmin.atanasoaei@idiap.ch>". It was only modified to conform to
 * Bob coding standards and structure.
 *
 * Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
 */

#ifndef FMAP_WIDGET_H
#define FMAP_WIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QTimer>

#include "fmap_scene.h"

/**
 * FeatureMapWidget:
 * - feature map scene + controls to manipulate the items
 */

class FeatureMapWidget : public QWidget
{
  Q_OBJECT

  public:

    // Constructor
    FeatureMapWidget(QWidget* parent = 0);

    // Destructor
    ~FeatureMapWidget();

    // Access functions
    FeatureMapScene* scene() { return m_scene; }

    private slots:

      // Control actions
      void onClearImages();
    void onLoadImages();
    void onSelectImage(int currentRow);
    void onSelectImage(const QModelIndex& index);

    // Slideshow manipulation
    void onSlidePrev();
    void onSlideRewind();
    void onSlideStart();
    void onSlidePause();
    void onSlideNext();
    void onSlideTimer();

  protected:

    // Events
    void resizeEvent(QResizeEvent* event);

  private:

    // Assembly controls	
    void assemblyControls();	

    // Update controls
    void updateControls();
    void updateScene();
    void populateImageList();

  private:

    // Attributes
    FeatureMapScene*	m_scene;		// The drawing scene

    // Control buttons
    QPushButton*		m_buttonClearImages;	// Image collection
    QPushButton*		m_buttonLoadImages;	
    QListWidget*		m_listImages;

    QToolButton*		m_buttonSlidePrev;	// Slideshow
    QToolButton*		m_buttonSlideRewind;		
    QToolButton*		m_buttonSlideStart;	
    QToolButton*		m_buttonSlidePause;	
    QToolButton*		m_buttonSlideNext;	
    QTimer*			m_timerSlide;

    QLabel*			m_labelImages;		// General information: #images, image size ...
};

#endif // FMAP_WIDGET_H

