#include <iostream>
#include "outFile.hpp"
#include "compositeShape.hpp"
#include "shape.hpp"

void spiridonov::outSh(std::ostream& out, const CompositeShape& shapes, bool useGlCen, const double k, const double cenX, const double cenY)
{
  out << shapes.getArea();

  size_t i = 0;
  do
  {
    Shape* shape = shapes.getShape(i);

    Shape* cloneShape = shape->clone();
    cloneShape->scale(k);

    double shapeCenterX = cloneShape->getFrameRect().pos.x;
    double shapeCenterY = cloneShape->getFrameRect().pos.y;

    double offsetX = (useGlCen) ? cenX - shapeCenterX : 0.0;
    double offsetY = (useGlCen) ? cenY - shapeCenterY : 0.0;

    cloneShape->move(-offsetX, -offsetY);

    rectangle_t frameRect = cloneShape->getFrameRect();

    out << " ";
    out << frameRect.pos.x - frameRect.width / 2.0 << " ";
    out << frameRect.pos.y - frameRect.height / 2.0 << " ";
    out << frameRect.pos.x + frameRect.width / 2.0 << " ";
    out << frameRect.pos.y + frameRect.height / 2.0;

    delete cloneShape;

    if (i == 1)
    {
      break;
    }

    ++i;
  } while (i < shapes.getShapesCount());
}
