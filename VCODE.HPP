#ifndef __VCODE_HPP__
#define __VCODE_HPP__

#include "vbase.hpp"
#include "string.hpp"
#include "constants.hpp"
#include "input.hpp"
#include "blit.hpp"
#include "vga.hpp"
#include "syntax.hpp"
#include "undo.hpp"

#define VCODE_UNDOMEMORY_SIZE (1024*1024*4)

class VCode : public VBase {
public:
  String text;
  String originalText;
  String colors;
  String fileName;
  Point textPos;
  int cursorX;
  int cursorY;
  int cursorI;
  int cursorIX;
  Point cursorPos;
  int cursorRequiresX;
  int cursorRequiresI;
  int bottomLine;
  int topLine;
  bool shiftReleased;
  int selectionStart;
  int selectionEnd;
  int textLastLine;
  bool overwriteMode;
  int scrollBoxY;
  int displayOutline;
  String toFind;
  unsigned int findAddress;
  Undo *undo;   

  VCode() : VBase() {
    name = "Edit";
    text = "";
    originalText = "";
    colors = "";
    fileName = "";
    textPos = Point(0,0);
    cursorX = 0;
    cursorY = 0;
    cursorI = -1;
    cursorIX = -1;
    cursorPos = Point(0,0);
    cursorRequiresX = -1;
    cursorRequiresI = -1;
    bottomLine = 0;
    topLine = 0;
    shiftReleased = true;
    selectionStart = -1;
    selectionEnd = -1;
    textLastLine = -1;
    overwriteMode = false;
    scrollBoxY = 0;
    displayOutline = 0;
    initSyntaxHiLighting();
    toFind = "";
    findAddress = 0;
    undo = NULL;
  }
  virtual ~VCode() {
    if (undo != NULL)
      delete undo;
  }

  virtual void draw();
  virtual int update();
  virtual void reset() {
    textPos = Point(0,0);
    cursorX = 0;
    cursorY = 0;
    cursorI = -1;
    cursorIX = -1;
    cursorPos = Point(0,0);
    cursorRequiresX = -1;
    cursorRequiresI = -1;
    bottomLine = 0;
    topLine = 0;
    shiftReleased = true;
    selectionStart = -1;
    selectionEnd = -1;
    textLastLine = -1;
    overwriteMode = false;
    scrollBoxY = 0;
    displayOutline = 0;
    toFind = "";
    findAddress = 0;
  }
  virtual void cleanUp() {
    if (undo != NULL) {
      delete undo;
      undo = NULL;
    }
  }
  virtual int doModal() {
    return VBase::doModal();
  }

  void init(const String &_text, const String &_fileName);

  void expand();
  void drawCursor();
  bool find(const String &search, unsigned int address);

  void allocUndo();
  void addUndo();
  void addUndoTop();
  void doRedo();
  void doUndo();
};

#endif //__VCODE_HPP__