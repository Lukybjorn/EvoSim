//
// Created by nevo9 on 21/10/2024.
//

#pragma once
#include <Eigen/Dense>



class Object {
private:
    int _id;

    Eigen::Vector2f _location; // location in the xy-plane
    float _radius; // size of the object (circular)

    Eigen::Vector3i _color; // color in rgb values

public:
    [[nodiscard]] Object(Eigen::Vector2f location, float radius, Eigen::Vector3i color);

    [[nodiscard]] int id() const {
        return _id;
    }

    [[nodiscard]] Eigen::Vector2f location() const {
        return _location;
    }

    [[nodiscard]] float radius() const {
        return _radius;
    }

    [[nodiscard]] Eigen::Vector3i color() const {
        return _color;
    }

    void set_location(const Eigen::Vector2f &location) {
        _location = location;
    }

    void set_radius(const float radius) {
        _radius = radius;
    }

    void set_color(const Eigen::Vector3i &color) {
        _color = color;
    }

    // class methods
    [[nodiscard]] bool collision(const Object& other) const;
};