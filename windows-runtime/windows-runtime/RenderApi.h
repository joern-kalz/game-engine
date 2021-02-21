#pragma once

class RenderApi
{
public:
	virtual ~RenderApi() {};
	virtual void Initialize() = 0;
	virtual void TrimResourcesOnSuspending() = 0;
};
