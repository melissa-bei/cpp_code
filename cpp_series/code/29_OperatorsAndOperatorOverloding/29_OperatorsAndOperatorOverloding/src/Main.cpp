#include <iostream>
#include <string>

struct Vector2
{
	float X, Y;

	Vector2(float x, float y)
		:X(x), Y(y) {}

	Vector2 Add(const Vector2& other) const
	{
		return Vector2(X + other.X, Y + other.Y);
	}

	Vector2 operator+(const Vector2& other) const
	{
		return Add(other);
	}

	Vector2 Multiply(const Vector2& other) const
	{
		return Vector2(X * other.X, Y * other.Y);
	}

	Vector2 operator*(const Vector2& other) const
	{
		return Multiply(other);
	}

	bool operator==(const Vector2& other) const
	{
		return X == other.X && Y == other.Y;
	}

	bool operator!=(const Vector2& other) const
	{
		return !(*this == other);
		//return !operator==(other);  //不建议这么写，很奇怪
	}
};

std::ostream& operator<<(std::ostream& stream, const Vector2& other)
{
	stream << other.X << ", " << other.Y;
	return stream;
}

int main()
{
	Vector2 position(4.0f, 4.0f);  //位置
	Vector2 speed(0.5f, 1.5f);  //速度
	Vector2 powerup(1.1f, 1.1f);  //提速后速率

	Vector2 result = position.Add(speed.Multiply(powerup));
	Vector2 result2 = position + speed * powerup;

	std::cout << result << std::endl;

	if (result == result2)
	{
		std::cout << "true" << std::endl;
	}
	else
	{
		std::cout << "false" << std::endl;
	}

	std::cin.get();
}