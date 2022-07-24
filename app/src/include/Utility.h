#pragma once 

bool CheckLua(lua_State * L, int err);

void DumpStack(lua_State * L);

class Utils {
public:
	static Utils& Get() {
		static Utils s_instance;
		return s_instance;
	}

	std::string GetProjectPath() { return m_projectPath; }

	void SetProjectPath(const std::string& path) { m_projectPath = path; }

private:
	std::string m_projectPath;
};

