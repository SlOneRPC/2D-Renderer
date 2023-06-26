#pragma once
#include <string>

class Demo {
public:
	virtual void Init() {};
	virtual void OnRender() {};
	virtual void OnImguiRender() {};
	virtual void Shutdown() {};
	inline std::string GetDemoName() { return name; };
private:
	std::string name;
};