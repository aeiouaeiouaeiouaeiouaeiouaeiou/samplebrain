// Copyright (C) 2022 Then Try This
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#include <QtGui>
#include <iostream>
#include <list>
#include "spiralcore/types.h"

#include "sound_items.h"

using namespace spiralcore;
using namespace std;

sound_items::sound_items():
  m_current_sound_id(0)
{
}

sound_items::sound_item &sound_items::add(QVBoxLayout *container, const string &name, bool enabled) {
  sound_item si;
  si.m_filename = name;
  si.m_id = m_current_sound_id++;
  QString style("color:black;background-color:lightgrey;");

  si.m_container = new QHBoxLayout();
  si.m_container->setSpacing(10);
  si.m_container->setContentsMargins(0,0,0,0);

  si.m_enable = new QCheckBox();
  si.m_enable->setChecked(enabled);
  si.m_enable->setStyleSheet(style);
  si.m_enable->setContentsMargins(0,0,0,0);

  si.m_container->addWidget(si.m_enable);

  si.m_label = new QLabel();
  QFileInfo fi(QString::fromStdString(name));
  si.m_label->setText(fi.fileName());
  si.m_label->setStyleSheet(style);
  si.m_label->setSizePolicy(QSizePolicy::MinimumExpanding,
                            QSizePolicy::Minimum);
  QFont font;
  font.setFamily(QString::fromUtf8("Comic Sans MS"));
  font.setBold(true);
  font.setWeight(QFont::Bold);
  si.m_label->setFont(font);
  si.m_label->setContentsMargins(0,0,0,0);

  si.m_container->addWidget(si.m_label);

  si.m_del = new QPushButton();
  si.m_del->setText("x");
  si.m_del->setMaximumWidth(20);
  si.m_del->setMaximumHeight(20);
  si.m_del->setStyleSheet(style);
  si.m_del->setContentsMargins(0,0,0,0);

  si.m_container->addWidget(si.m_del);

  container->addLayout(si.m_container);

  m_sound_items.push_back(si);
  return m_sound_items[m_sound_items.size()-1];
}

void sound_items::clear() {
  for (auto &si:m_sound_items) {
    delete si.m_enable;
    delete si.m_del;
    delete si.m_label;
    delete si.m_container;
  }
  m_sound_items.clear();
}

void sound_items::recolour() {
  u32 c=0;
  for (auto &si:m_sound_items) {
    QString style("color:black;background-color:lightblue;");
    if (c%2==0) style="color:black;background-color:pink;";
    si.m_enable->setStyleSheet(style);
    si.m_del->setStyleSheet(style);
    si.m_label->setStyleSheet(style);
    c++;
  }
}

void sound_items::change_colour(const std::string &name, const std::string &colour) {
  for (auto &si:m_sound_items) {
    if (si.m_filename==name) {
      QString style("color:black;background-color:"+QString::fromStdString(colour)+";");
      si.m_enable->setStyleSheet(style);
      si.m_del->setStyleSheet(style);
      si.m_label->setStyleSheet(style);
    }
  }
}


void sound_items::remove(const string &name) {
  for (auto i=m_sound_items.begin(); i!=m_sound_items.end(); ++i) {
    if (i->m_filename==name) {
      // not sure why deleteLater-ing the container does not
      // remove the children (like it does with delete)
      i->m_container->deleteLater();
      i->m_enable->deleteLater();
      i->m_label->deleteLater();
      i->m_del->deleteLater();
      m_sound_items.erase(i);
      recolour();
      return;
    }
  }
}
