#pragma once
#include <Engine/Singleton.h>


class Content
{
	friend int APIENTRY::wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPWSTR lpCmdLine, int nCmdShow);
	SINGLETON_DECLARE(Content);

private:
	void loadShader();
	void loadMesh();
	void loadTexture();
	void loadMaterial();

private:
	void resourceInitialize();
	void testSceneInitialize();
};
