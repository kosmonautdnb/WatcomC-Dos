#ifndef __VTXTALRT_HPP__
#define __VTXTALRT_HPP__

#include "valert.hpp"
#include "vtxtline.hpp"

class VTxtAlrt : public VAlert {
public:
  VTxtLine *vTxtLine;

  VTxtAlrt() : VAlert() {
    vTxtLine = new VTxtLine();
  }
  virtual ~VTxtAlrt() {
    delete vTxtLine;
  }

  virtual void draw();
  virtual int update();
  virtual void reset() {}
  virtual int doModal() {
    return VAlert::doModal();
  }

  static int box(String &returned,const String &message,const Array<VButton*> &buttons) {
    VTxtAlrt *txtalrt = new VTxtAlrt();
    txtalrt->captureKeyboard();
    txtalrt->init(message,buttons);
    txtalrt->vTxtLine->init(returned);
    int r = 0;
    do {r = txtalrt->doModal();} while(1!=1);
    returned = txtalrt->vTxtLine->text;
    delete txtalrt;
    return r;
  }

  static int box(String &returned,const String &message,const String &button1) {
    Array<VButton*> arr;
    arr.push_back(new VButton());
    arr[0]->init(button1);
    return VTxtAlrt::box(returned, message, arr);
  }

  static int box(String &returned,const String &message,const String &button1,const String &button2) {
    Array<VButton*> arr;
    arr.push_back(new VButton());
    arr.push_back(new VButton());
    arr[0]->init(button1);
    arr[1]->init(button2);
    return VTxtAlrt::box(returned, message, arr);
  }

  static int box(String &returned,const String &message,const String &button1,const String &button2,const String &button3) {
    Array<VButton*> arr;
    arr.push_back(new VButton());
    arr.push_back(new VButton());
    arr.push_back(new VButton());
    arr[0]->init(button1);
    arr[1]->init(button2);
    arr[2]->init(button3);
    return VTxtAlrt::box(returned, message, arr);
  }

  void init(const String &_text, const Array<VButton*> &_buttons);
};

#endif //__VTXTALRT_HPP__