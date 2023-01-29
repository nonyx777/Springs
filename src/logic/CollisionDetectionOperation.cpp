#include "CollisionDetectionOperation.h"

//defining functions
    //intersection check
bool CollisionDetectionOperation::_boxOverlapping(float min_a, float max_a, float min_b, float max_b){
    return min_b <= max_a && min_a <= max_b;
}
bool CollisionDetectionOperation::_ballOverlapping(float radius_a, float radius_b, sf::Vector2f origin_a, sf::Vector2f origin_b){
    return operation._magnitude(origin_b - origin_a) <= (radius_a + radius_b);
}
bool CollisionDetectionOperation::_ballSegmentOverlapping(Ball &a, Line &l){
    if(this->_ballPointCollide(a, l.getBase())){
        nearest_point = l.getBase();
        return this->_ballPointCollide(a, nearest_point);
    }
    if(this->_ballPointCollide(a, l.getDirection())){
        nearest_point = l.getDirection();
        return this->_ballPointCollide(a, nearest_point);
    }

    sf::Vector2f d = l.getDirection() - l.getBase();
    sf::Vector2f lc = a.particle_property.getPosition() - l.getBase();
    sf::Vector2f p = this->operation._vectorProjection(lc, d);
    nearest_point = l.getBase() + p;

    return this->_ballPointCollide(a, nearest_point) && 
    this->operation._magnitude(p) <= this->operation._magnitude(d) && 
    0 <= this->operation._dotProduct(p, d);
}
//penetration and collision resolution
    //ball-ball penetration resoultion
void CollisionDetectionOperation::_ballBallPenetrationResolution(Ball &a, Ball &b){
    sf::Vector2f normal = this->operation._displacement(a.getPosition(), b.getPosition());
    float distance = this->operation._magnitude(normal);
    float penetration_depth = (a.particle_property.getRadius() + b.particle_property.getRadius()) - distance;
    sf::Vector2f penetration_resolution_vector = this->operation._unitVector(normal) * penetration_depth/(a.getInverseMass() + b.getInverseMass());
    this->a_position = penetration_resolution_vector * a.getInverseMass();
    this->b_position = -penetration_resolution_vector * b.getInverseMass();
}
void CollisionDetectionOperation::_ballBallCollisionResolution(Ball &a, Ball &b){
    sf::Vector2f normal = this->operation._displacement(a.getPosition(), b.getPosition());
    normal = this->operation._unitVector(normal);
    sf::Vector2f relative_velocity = this->operation._displacement(a.getVelocity(), b.getVelocity());
    float separating_velocity = this->operation._dotProduct(relative_velocity, normal);
    float impulse = -separating_velocity - separating_velocity/(a.getInverseMass() + b.getInverseMass());
    sf::Vector2f impulse_vector = normal * impulse;
    this->a_velocity = impulse_vector * a.getInverseMass() * a.getElasticity();
    this->b_velocity = -impulse_vector * b.getInverseMass() * b.getElasticity();
}
    //ball-point penetration resolution
void CollisionDetectionOperation::_ballPointPenetrationResolution(Ball &a, sf::Vector2f &p){
    sf::Vector2f normal = this->operation._displacement(a.getPosition(), p);
    float distance = this->operation._magnitude(normal);
    float penetration_distance = a.particle_property.getRadius() - distance;
    sf::Vector2f penetration_resolution_vector = this->operation._unitVector(normal) * penetration_distance/2.f;
    this->a_position = penetration_resolution_vector;
}
void CollisionDetectionOperation::_ballPointCollisionResolution(Ball &ball, sf::Vector2f &point){
    sf::Vector2f normal = this->operation._displacement(ball.getPosition(), point);
    normal = this->operation._unitVector(normal);
    sf::Vector2f relative_velocity = this->operation._displacement(ball.getVelocity(), sf::Vector2f(0.f, 0.f));
    float separating_velocity = this->operation._dotProduct(relative_velocity, normal);
    sf::Vector2f separating_velocity_vector = normal * separating_velocity;
    this->b_velocity = -separating_velocity_vector * ball.getElasticity();
}

    //box-box penetration resoultion
// void CollisionDetectionOperation::_boxBoxPenetrationResolution(Box &a, Box &b){
//     sf::Vector2f normal = a.getBoxPosition() - b.getBoxPosition();
//     float distance = this->operation._magnitude(normal);
//     float a_x_half = a.box_property.getSize().x/2.f;
//     float b_x_half = b.box_property.getSize().x/2.f;
//     float overlap_x = normal.x - (a_x_half + b_x_half);
//     float overlap_y = normal.y - (a_x_half + b_x_half);
//     float penetration_depth = min(overlap_x, overlap_y);
//     sf::Vector2f penetration_resolution_vector = this->operation._unitVector(normal) * penetration_depth/(a_x_half + b_x_half);

//     this->a_position = -penetration_resolution_vector;
//     this->b_position = penetration_resolution_vector;
// }
    //box-box collision resolution
// void CollisionDetectionOperation::_boxBoxCollisionResolution(Box &a, Box &b){
//     sf::Vector2f normal = a.getBoxPosition() - b.getBoxPosition();
//     normal = this->operation._unitVector(normal);
//     sf::Vector2f relative_velocity = a.getBoxVelocity() - b.getBoxVelocity();
//     float separating_velocity = this->operation._dotProduct(relative_velocity, normal);
//     sf::Vector2f separating_velocity_vector = normal * separating_velocity;
//     this->a_velocity = -separating_velocity_vector;
//     this->b_velocity = separating_velocity_vector;
// }
    //ball-box penetration resolution
// void CollisionDetectionOperation::_ballBoxPenetrationResolution(Ball &ball, Box &box){
//     sf::Vector2f normal = ball.getBallPosition() - box.getBoxPosition();
//     normal = this->operation._unitVector(normal);
//     sf::Vector2f nearest_position = this->clampOnRectangle(ball.getBallPosition(), box);
//     float distance = this->operation._magnitude(ball.getBallPosition() - nearest_position);
//     float penetration_depth = ball.getBallRadius() - distance;
//     sf::Vector2f penetration_resolution_vector = normal * penetration_depth;
//     this->a_position = penetration_resolution_vector;
//     this->b_position = -penetration_resolution_vector;
// }

    //ball-box collision resolution

    //actual collision functions
// bool CollisionDetectionOperation::_linesCollide(Line &a, Line &b){
//     if(operation._parallelVectors(a.getDirection(), b.getDirection()))
//         return false;
//     else 
//         return true;
// }

// bool CollisionDetectionOperation::_boxCollide(Box &a, Box &b){
//     sf::FloatRect a_bound = a.box_property.getGlobalBounds();
//     sf::FloatRect b_bound = b.box_property.getGlobalBounds();
//     float a_left = a_bound.left;
//     float a_right = a_bound.left + a_bound.width;
//     float b_left = b_bound.left;
//     float b_right = b_bound.left + b_bound.width;

//     float a_bottom = a_bound.top + a_bound.height;
//     float a_top = a_bound.top;
//     float b_bottom = b_bound.top + b_bound.height;
//     float b_top = b_bound.top;

//     return this->_boxOverlapping(a_left, a_right, b_left, b_right) && this->_boxOverlapping(a_top, a_bottom, b_top, b_bottom);
// }

bool CollisionDetectionOperation::_ballCollide(Ball &a, Ball &b){
    return _ballOverlapping(a.particle_property.getRadius(), b.particle_property.getRadius(), a.getPosition(), b.getPosition());
}
bool CollisionDetectionOperation::_ballPointCollide(Ball &a, sf::Vector2f point){
    sf::Vector2f displacement = this->operation._displacement(a.particle_property.getPosition(), point);
    float distance = this->operation._magnitude(displacement);
    return distance <= a.particle_property.getRadius();
}
// bool CollisionDetectionOperation::_ballWindowCollide(sf::CircleShape &a, Line l1, Line l2, Line l3, Line l4){
//     return this->_ballLineOverlapping(a, l1) || this->_ballLineOverlapping(a, l2) || this->_ballLineOverlapping(a, l3) || this->_ballLineOverlapping(a, l4);
// }
// bool CollisionDetectionOperation::_ballBoxCollide(Ball &ball, Box &box){
//     sf::Vector2f clamped = this->clampOnRectangle(ball.getBallPosition(), box);
//     tempo_position = clamped;
//     return this->_ballPointCollide(ball.ball_property, clamped);
// }

//...
// sf::Vector2f CollisionDetectionOperation::clampOnRectangle(sf::Vector2f point, Box box){
//     sf::Vector2f clamp;
//     clamp.x = this->operation._clampOnRange(point.x, box.box_property.getGlobalBounds().left, box.box_property.getGlobalBounds().left + box.box_property.getGlobalBounds().width);
//     clamp.y = this->operation._clampOnRange(point.y, box.box_property.getGlobalBounds().top, box.box_property.getGlobalBounds().top + box.box_property.getGlobalBounds().height);
//     return clamp;
// }