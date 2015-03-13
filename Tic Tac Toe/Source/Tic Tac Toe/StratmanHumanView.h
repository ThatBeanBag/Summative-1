#pragma once

#ifndef __STRATMANHUMANVIEW_H__
#define __STRATMANHUMANVIEW_H__

//======================================================
// This class basically just re-routes the
// VOnBeginDragging() and VOnEndDragging() functions to
// the game logic.
//======================================================

class CStratmanHumanView : public CHumanView {
// Member Functions
public:
	CStratmanHumanView();
	virtual ~CStratmanHumanView();

	virtual void VOnBeginDragging();
	virtual void VOnEndDragging();
private:
protected:

// Member Variables
public:
private:
protected:
};

#endif