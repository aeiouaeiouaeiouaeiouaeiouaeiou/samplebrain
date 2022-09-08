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
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <iostream>
#include <string>
#include <list>

#pragma once

namespace spiralcore {

class sound_items {
    public:
  sound_items();

  class sound_item {
  public:
    int m_id;
    std::string m_filename;
    // can't find a way to address these via qt
    QCheckBox *m_enable;
    QPushButton *m_del;
    QLabel *m_label;
    QHBoxLayout *m_container;
  };

  // arg - need to return it to stitch up the mapper which needs
  // to belong to the main window??
  sound_item &add(QVBoxLayout *container, const std::string &name, bool enabled);
  void remove(const std::string &name);
  void clear();
  void recolour();
  void change_colour(const std::string &name, const std::string &colour);


  std::vector<sound_item> m_sound_items;

 private:
  int m_current_sound_id;
};

}
