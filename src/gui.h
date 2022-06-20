//
// Created by refantasy on 2022/6/20.
//

#ifndef GUI_GUI_H
#define GUI_GUI_H

#include "gui_base.h"


class GUI:public GUIBase
{
public:
	using GUIBase::GUIBase;

	//void Render() override;

protected:
	// 内置着色器
	GLSLShader _shader;
};


#endif //GUI_GUI_H
