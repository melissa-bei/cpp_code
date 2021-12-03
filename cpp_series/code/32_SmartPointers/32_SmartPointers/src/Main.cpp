#include <iostream>
#include <string>
#include <memory>

class Entity
{
public:
	Entity() { std::cout << "Created Entity!" << std::endl; }
	~Entity() { std::cout << "Destroyed Entity!" << std::endl; }

	void Print() {}
};

int main()
{
	{
		std::shared_ptr<Entity> sharedEntity0;
		std::weak_ptr<Entity> weakEntity1;
		{
			std::unique_ptr<Entity> entity = std::make_unique<Entity>();
			entity->Print();

			std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
			//sharedEntity0 = sharedEntity;
			weakEntity1 = sharedEntity;

		}
	}
	std::cin.get();

}