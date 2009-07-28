#include "VerticalLayout.h"

#include "Rendering/GL/myGL.h"

namespace agui
{

VerticalLayout::VerticalLayout(GuiElement* parent) : GuiElement(parent)
{
	spacing = 0.005f;
	borderWidth = 1.0f;
}

void VerticalLayout::AddChild(GuiElement* elem)
{
	children.push_front(elem);
	const float vspacePerObject = (size[1]-(float(children.size()-1)*spacing))/float(children.size());
	size_t num = 0;
	for (ChildList::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->SetPos(pos[0]+spacing, pos[1] + num*vspacePerObject + (num+1)*spacing);
		(*i)->SetSize(size[0]- 2.0f*spacing, vspacePerObject - 2.0f * spacing);
		++num;
	}
}

void VerticalLayout::DrawSelf()
{
	if (borderWidth > 0)
	{
		glColor4f(1.f,1.f,1.f, 1.f);	
		DrawBox(GL_LINE_LOOP);
	}
}

}
