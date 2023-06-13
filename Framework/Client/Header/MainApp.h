#pragma once
class CMainApp
{
private:		// 持失切, 社瑚切
	explicit CMainApp();
	virtual ~CMainApp();

public:
	HRESULT		Ready_MainApp(void);
	int			Update_MainApp(const float& fTimeDelta);
	void		LateUpdate_MainApp();
	void		Render_MainApp();

public:
	static CMainApp*		Create();

private:
	virtual void		Free();

};

