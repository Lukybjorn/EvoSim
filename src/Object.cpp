//
// Created by nevo9 on 21/10/2024.
//

#include "Object.h"

#include <utility>

Object::Object(Eigen::Vector2f location, const float radius, Eigen::Vector3i color)
        : _location(std::move(location)),
          _radius(radius),
          _color(std::move(color)) {
}

bool Object::collision(const Object& other) const {
    Eigen::Vector2f dist_vector = this->_location - other.location();
    const float distance = std::sqrt(dist_vector.transpose() * dist_vector);
    if (distance <= this->_radius + other.radius()) return true;
    return false;
}
