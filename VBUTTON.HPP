#ifndef __VBUTTON_HPP__
#define __VBUTTON_HPP__

#include "vbase.hpp"
#include "string.hpp"

class VButton : public VBase {
public:
  String text;
  bool wasClicked;
  bool selected;

  VButton() : VBase() {
    text = "";
    wasClicked = false;
    selected = false;
  }
  virtual ~VButton() {;}

  virtual void draw();
  virtual int update();

  void select(bool s);
  bool clicked();
  void init(const String &_text);
};

#endif //__VBUTTON_HPP__