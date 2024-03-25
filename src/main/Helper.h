typedef struct Box
{
    Vector2 p0;
    Vector2 p1;
}
Box;

float MathClamp(float value, float min, float max)
{
    if (value < min) { return min; }
    if (value > max) { return max; }
                       return value;
}
float MathSign(float value)
{
    if (value > 0) { return  1; }
    if (value < 0) { return -1; }
                     return  0;
}
float MathAbs(float value)
{
    return fabsf(value);
}
float MathSqrt(float value)
{
    return sqrtf(value);
}

void PrintFloatHex(float f)
{
    unsigned int ui;
    memcpy(&ui, &f, sizeof (ui));
    printf("%X", ui);
}
void PrintVector2Hex(Vector2 v)
{
    PrintFloatHex(v.x);
    PrintFloatHex(v.y);
}

bool Vector2IsZero(Vector2 v1)
{
    return v1.x == 0 && v1.y == 0;
}
bool Vector2Equal(Vector2 v1, Vector2 v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}
Vector2 MyVector2Zero()
{
    return (Vector2) { 0.0f, 0.0f };
}
Vector2 Vector2Add(Vector2 v1, Vector2 v2)
{
    return (Vector2) { v1.x + v2.x, v1.y + v2.y };
}
Vector2 Vector2Sub(Vector2 v1, Vector2 v2)
{
    return (Vector2) { v1.x - v2.x, v1.y - v2.y };
}
Vector2 Vector2Mul(Vector2 v1, float value)
{
    return (Vector2) { v1.x * value, v1.y * value };
}
Vector2 Vector2Div(Vector2 v1, float value)
{
    return (Vector2) { v1.x / value, v1.y / value };
}
Vector2 Vector2Abs(Vector2 v)
{
    return (Vector2) { fabs(v.x), fabs(v.y) };
}
Vector2 Vector2Negate(Vector2 v)
{
    return (Vector2) { -v.x, -v.y };
}
float Vector2Length(Vector2 v)
{
    float distSquared = v.x * v.x + v.y * v.y;
    float dist = sqrtf(distSquared);
    return dist;
}
float Vector2LengthSquared(Vector2 v)
{
    float distSquared = v.x * v.x + v.y * v.y;
    return distSquared;
}
float Vector2Angle(Vector2 v)
{
    // v ( 0, 1) =  0.000000
    // v ( 1, 0) = -1.570796
    // v ( 0,-1) = -3.141593
    // v (-1, 0) =  1.570796
    return Vector2IsZero(v) ? 0 : atan2f(v.y, v.x) - M_PI_2;
}
float Vector2Distance(Vector2 v1, Vector2 v2)
{
    Vector2 diff = Vector2Sub(v1, v2);
    return Vector2Length(diff);
}
Vector2 Vector2Normalized(Vector2 v)
{
    float dist = Vector2Length(v);
    float t = 1.0f / dist;
    return (Vector2) { v.x * t, v.y * t };
}
Vector2 Vector2ClampLength(Vector2 v, float min, float max)
{
    float length = Vector2Length(v);
    if (length > max) return Vector2Mul(v, (max / length));
    if (length < min) return Vector2Mul(v, (min / length));
    return v;
}
Vector2 Vector2Rotate(Vector2 v, float angle)
{
    Vector2 result = MyVector2Zero();
    float cosres = cosf(angle);
    float sinres = sinf(angle);
    result.x = v.x * cosres - v.y * sinres;
    result.y = v.x * sinres + v.y * cosres;
    return result;
}
Vector2 Vector2MoveTowards(Vector2 start, Vector2 target, float delta)
{
    if (Vector2Equal(start, target)) return start;
    Vector2 diff = Vector2Sub(target, start);
    float dist = Vector2Length(diff);
    if (dist <= delta) return target;
    Vector2 dir = Vector2Normalized(diff);
    Vector2 moveVec = Vector2Mul(dir, delta);
    return Vector2Add(start, moveVec);
}
Vector2 Vector2Snap(Vector2 start, Vector2 target, float range)
{
    return Vector2Distance(start, target) > range ? start : target;
}
Vector2 Vector2UpdatePositionSimple(Vector2 position, Vector2 velocity, float deltaTime)
{
    // result = position + velocity * deltaTime
    Vector2 result = velocity;
    result = Vector2Mul(result, deltaTime);
    result = Vector2Add(result, position);
    return result;
}
Vector2 Vector2UpdatePositionAdvanced(Vector2 position, Vector2 oldVelocity, Vector2 newVelocity, float deltaTime)
{
    // result = position + (oldVelocity + velocityNew) / 2 * deltaTime
    Vector2 result = oldVelocity;
    result = Vector2Add(result, newVelocity);
    result = Vector2Div(result, 2);
    result = Vector2Mul(result, deltaTime);
    result = Vector2Add(result, position);
    return result;
}

float BoxMinX(Box* box)
{
    return fminf(box->p0.x, box->p1.x);
}
float BoxMinY(Box* box)
{
    return fminf(box->p0.y, box->p1.y);
}
float BoxMaxX(Box* box)
{
    return fmaxf(box->p0.x, box->p1.x);
}
float BoxMaxY(Box* box)
{
    return fmaxf(box->p0.y, box->p1.y);
}
Vector2 BoxSize(Box* box)
{
    Vector2 diff = Vector2Sub(box->p0, box->p1);
    return Vector2Abs(diff);
}

Vector2 RandomPointInside(Subgen* subgen, Box* box)
{
    float x = SubgenRange(subgen, BoxMinX(box), BoxMaxX(box) );
    float y = SubgenRange(subgen, BoxMinY(box), BoxMaxY(box) );
    return (Vector2) { x, y };
}
Vector2 WrapAround(Box* box, Vector2 point)
{
    Vector2 size = BoxSize(box);
    if      (point.x < BoxMinX(box)) point.x += size.x;
    else if (point.x > BoxMaxX(box)) point.x -= size.x;
    if      (point.y < BoxMinY(box)) point.y += size.y;
    else if (point.y > BoxMaxY(box)) point.y -= size.y;
    return point;
}
Vector2 RandNormDir(Subgen* subgen)
{
    float x = SubgenFractionSigned(subgen);
    float y = SubgenFractionSigned(subgen);
    Vector2 result = { x, y };
    return Vector2Normalized(result);
}