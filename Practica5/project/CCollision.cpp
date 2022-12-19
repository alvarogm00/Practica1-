#include "CCollision.h"
#include <algorithm>
#include <iostream>

float CCollider::Clamp(float _value, float _minvalue, float _maxValue)
{
    if (_value < _minvalue)
    {
        _value = _minvalue;
    }
    else if (_value > _maxValue)
    {
        _value = _maxValue;
    }
    else
        _value = _value;

    return _value;
}

bool CCircleCollider::collides(const CCollider& other) const
{
    return other.collides(m_pos, m_radius);
}

bool CCircleCollider::collides(const Vec2& circlePos, float circleRadius) const
{
    return checkCircleCircle(m_pos, m_radius, circlePos, circleRadius);
}

bool CCircleCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
    return checkCircleRect(m_pos, m_radius, rectPos, rectSize);
}

bool CCircleCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
    return checkCirclePixels(m_pos, m_radius, pixelsPos, pixelsSize, pixels);
}

bool CRectCollider::collides(const CCollider& other) const
{
    return other.collides(other);
}

bool CRectCollider::collides(const Vec2& circlePos, float circleRadius) const
{
    return checkCircleRect(circlePos, circleRadius, m_pos, m_size);
}

bool CRectCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
    return false;
}

bool CRectCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
    return false;
}

bool CPixelsCollider::collides(const CCollider& other) const
{
    return false;
}

bool CPixelsCollider::collides(const Vec2& circlePos, float circleRadius) const
{
    return false;
}

bool CPixelsCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
    return false;
}

bool CPixelsCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
    return false;
}

bool CCollider::checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2)
{
    float distance = (pos1 - pos2).length();
    float radiusSum = radius1 + radius2;
    if (distance < radiusSum)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CCollider::checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize)
{
    float closestX = CCollider::Clamp(circlePos.m_x, rectPos.m_x, (rectPos.m_x + rectSize.m_x));
    float closestY = CCollider::Clamp(circlePos.m_y, rectPos.m_y, (rectPos.m_y + rectSize.m_y));

    Vec2 closestPos(closestX, closestY);
    float shortestDistance = (closestPos - circlePos).length();
    if (shortestDistance < circleRadius)
    {
        return true;
    }
    else 
        return false;
}

bool CCollider::checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2)
{

    if (rectPos1.m_x > rectPos2.m_x && rectPos1.m_x < (rectPos2.m_x + rectSize2.m_x) || //Comprobamos si la x del 1 está dentro de la del 2
        rectPos2.m_x > rectPos1.m_x && rectPos2.m_x < (rectPos1.m_x + rectSize1.m_x)    //Comprobamos si la x del 2 está dentro de la del 1
        &&
        rectPos1.m_y > rectPos2.m_y && rectPos1.m_y < (rectPos2.m_y + rectSize2.m_y) || //Comprobamos si la y del 1 está dentro de la del 2
        rectPos2.m_y > rectPos1.m_y && rectPos2.m_y < (rectPos1.m_y + rectSize1.m_y))   //Comprobamos si la y del 2 está dentro de la del 1
    {
        return true;
    }
    else return false;
    
}

bool CCollider::checkCirclePixels(const Vec2& circlePos, float circleRadius, const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels)
{
    Vec2 circleRectPos = Vec2(circlePos.m_x - circleRadius, circlePos.m_y - circleRadius);
    Vec2 circleRectSize = Vec2(circleRadius * 2, circleRadius * 2);

    if (checkRectRect(pixelsPos, pixelsSize, circleRectPos, circleRectSize))
    {
        float minX = 0, maxX = 0, minY = 0, maxY = 0;

        //Calculamos la x y la y mínimas y máximas del rectángulo de solapamiento. 
        if (pixelsPos.m_x > circleRectPos.m_x)
        {
            minX = pixelsPos.m_x;
            maxX = circleRectPos.m_x + circleRectSize.m_x;
        }
        else
        {
            minX = circleRectPos.m_x;
            maxX = pixelsPos.m_x + pixelsSize.m_x;
        }

        if (pixelsPos.m_y > circleRectPos.m_y)
        {
            minY = pixelsPos.m_y;
            maxY = circleRectPos.m_y + circleRectSize.m_y;
        }
        else
        {
            minY = circleRectPos.m_y;
            maxY = pixelsPos.m_y + pixelsSize.m_y;
        }

        int row = minY, column = minX; // filas y columnas del array de pixeles de la imagen que estan dentro del rectángulo de solapamiento

        while (row < maxY)
        {
            int imgRow = row - pixelsPos.m_y;
            bool collision = false;
            while (column < maxX && !collision)
            {
                int imgCol = column - pixelsPos.m_x;

                int imgIndex = imgCol * pixelsSize.m_x + imgRow;

                if (pixels[imgIndex * 4 + 3] > 0 && circlePos.distance(Vec2(column, row)))
                {
                    collision = true;
                }
                column++;
            }
            row++;
        }
    }
    else return false;
}

bool CCollider::checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const uint8_t* pixels1, const Vec2& pixelsPos2, const Vec2& pixelsSize2, const uint8_t* pixels2)
{
    if (checkRectRect(pixelsPos1, pixelsSize1, pixelsPos2, pixelsSize2))
    {
        float minX = 0, maxX = 0, minY = 0, maxY = 0;

        //Calculamos la x y la y mínimas y máximas del rectángulo de solapamiento. 
        if (pixelsPos1.m_x > pixelsPos2.m_x)
        {
            minX = pixelsPos1.m_x;
            maxX = pixelsPos2.m_x + pixelsSize2.m_x;
        }
        else
        {
            minX = pixelsPos2.m_x;
            maxX = pixelsPos1.m_x + pixelsSize1.m_x;
        }

        if (pixelsPos1.m_y > pixelsPos2.m_y)
        {
            minY = pixelsPos1.m_y;
            maxY = pixelsPos2.m_y + pixelsSize2.m_y;
        }
        else
        {
            minY = pixelsPos2.m_y;
            maxY = pixelsPos1.m_y + pixelsPos2.m_y;
        }

        int row = minY, column = minX; // filas y columnas del array de pixeles de la imagen que estan dentro del rectángulo de solapamiento

        int imgRow1 = 0, imgRow2 = 0;
        
        int imgCol1 = 0, imgCol2 = 0;
        int imgIndex1 = 0, imgIndex2 = 0;

        bool collision = false;

        while (row < maxY)
        {
            imgRow1 = row - pixelsPos1.m_y;
            imgRow2 = row - pixelsPos2.m_y;
            
            while (column < maxX && !collision)
            {
                imgCol1 = column - pixelsPos1.m_x;
                imgCol2 = column - pixelsPos2.m_x;

                imgIndex1 = imgCol1 * pixelsSize1.m_x + imgRow1;
                imgIndex2 = imgCol2 * pixelsSize2.m_x + imgRow2;

                if (pixels1[imgIndex1 * 4 + 3] > 0 && pixels2[imgIndex2 * 4 + 3] > 0)
                {
                    collision = true;
                }
                column++;
            }
            row++;
        }
    }
    else return false;
    return false;
}

bool CCollider::checkPixelsRect(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels, const Vec2& rectPos, const Vec2& rectSize)
{
    if (checkRectRect(pixelsPos, pixelsSize, rectPos, rectSize))
    {
        float minX = 0, maxX = 0, minY = 0, maxY = 0;
        
        //Calculamos la x y la y mínimas y máximas del rectángulo de solapamiento. 
        if (pixelsPos.m_x > rectPos.m_x)
        {
            minX = pixelsPos.m_x;
            maxX = rectPos.m_x + rectSize.m_x;
        }
        else
        {
            minX = rectPos.m_x;
            maxX = pixelsPos.m_x + pixelsSize.m_x;
        }

        if (pixelsPos.m_y > rectPos.m_y)
        {
            minY = pixelsPos.m_y;
            maxY = rectPos.m_y + rectSize.m_y;
        }
        else
        {
            minY = rectPos.m_y;
            maxY = pixelsPos.m_y + pixelsSize.m_y;
        }

        int row = minY, column = minX; // filas y columnas del array de pixeles de la imagen que estan dentro del rectángulo de solapamiento
        
        while (row < maxY)
        {
            int imgRow = row - pixelsPos.m_y;
            bool collision = false;
            while (column < maxX && !collision) 
            {
                int imgCol = column - pixelsPos.m_x;

                int imgIndex = imgCol * pixelsSize.m_x + imgRow;

                if (pixels[imgIndex * 4 + 3] > 0)
                {
                    collision = true;
                }
                column++;
            }
            row++;
        }
    }
    else return false;
}
