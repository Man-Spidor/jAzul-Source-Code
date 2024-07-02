#ifndef GRAPHICSOBJECTWF_H
#define GRAPHICSOBJECTWF_H



class GraphicsObjectWF
{
public:
	GraphicsObjectWF() = default;
	GraphicsObjectWF(const GraphicsObjectWF& other) = default;
	GraphicsObjectWF& operator=(const GraphicsObjectWF& other) = default;
	GraphicsObjectWF(GraphicsObjectWF&& other) = default;
	GraphicsObjectWF& operator=(GraphicsObjectWF&& other) = default;
	~GraphicsObjectWF() = default;

};

#endif // GRAPHICSOBJECTWF_H
