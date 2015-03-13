// PCH
#include "StratmanStd.h"

// Library Includes

// This Include
#include "StratmanLogic.h"

// Local Includes

CStratmanLogic::CStratmanLogic()
{
	m_pHumanView = NULL;
}

CStratmanLogic::~CStratmanLogic()
{
}

bool CStratmanLogic::VInit()
{
	if(!CGameLogic::VInit()) {
		return false;
	}

	// Create a human view.
	m_pHumanView = new CStratmanHumanView();

	if(m_pHumanView) {
		// Create the shared pointer.
		TStrongGameViewPtr pHumanView(m_pHumanView);

		// Add the view.
		AddView(pHumanView);
	}

	m_sprite = g_pApp->LoadSprite("Images/pin.png");

	m_wireGraph.AddNode(CPoint(200, 140));
	m_wireGraph.AddNode(CPoint(100, 230));
	m_wireGraph.AddNode(CPoint(300, 300));

	m_wireGraph.AddEdge(0, 1);
	m_wireGraph.AddEdge(0, 2);
	m_wireGraph.AddEdge(1, 2);

	return true;
}

void CStratmanLogic::VUpdate(float _fDeltaTime)
{
	CGameLogic::VUpdate(_fDeltaTime);

	if (m_pHumanView->GetIsDragging()) {
		std::vector<CWireNode>& krNodes = m_wireGraph.GetNodes();

		for (int i = 0; i < krNodes.size(); ++i) {
			if (krNodes[i].m_iVertex == m_iDraggingNode) {
				krNodes[i].m_position = m_pHumanView->GetCursorPosition();
			}
		}
	}

	m_wireGraph.DrawGraph(m_sprite);
}

void CStratmanLogic::OnBeginDragging()
{
	std::vector<CWireNode>& krNodes = m_wireGraph.GetNodes();

	bool foundNode = false;

	// Iterate through the nodes backwards to ensure we move nodes ontop first.
	for (int i = krNodes.size() - 1; i >= 0; --i) {
		if (DistanceSquared(krNodes[i].m_position, m_pHumanView->GetDragStartPosition()) < g_kiNODE_RADIUS * g_kiNODE_RADIUS) {
		// The drag starting position is on the current node.
			// Select this node as the node to drag.
			m_iDraggingNode = krNodes[i].m_iVertex;
			foundNode = true;
		}
	}

	if (!foundNode) {
		m_pHumanView->VOnEndDragging();
	}
}

void CStratmanLogic::OnEndDragging()
{
	m_iDraggingNode = 1000;
}