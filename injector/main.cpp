#include <iostream>

#include <string>

#include <Windows.h>

int main(int argc, char* argv[])
{
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi = {};
	char path[MAX_PATH + 1];
	GetCurrentDirectory(MAX_PATH + 1, path);

	std::string target(argc > 1 ? argv[1] : std::string(path) + "\\BveTs.exe");
	std::string file(target);
	file[file.rfind('\\')] = '\0';

	SetEnvironmentVariable("COR_ENABLE_PROFILING", "1");
	SetEnvironmentVariable("COR_PROFILER", "{7ADA6F81-2F62-4432-8BA0-C18CECAE1546}");
	SetEnvironmentVariable("COR_PROFILER_PATH", (std::string(path) + "\\profiler.dll").c_str());
	SetEnvironmentVariable("COMPLUS_Version", "v4.0.30319");
	auto env = GetEnvironmentStrings();

	CreateProcess(
		target.c_str(),
		nullptr,
		//"powershell",
		//"/k set",
		nullptr,	//�v���Z�X�̃Z�L�����e�B�[�L�q�q
		nullptr,	//�X���b�h�̃Z�L�����e�B�[�L�q�q
		false,	//�n���h�����p�����Ȃ�
		0,	//�쐬�t���O
		env,
		file.c_str(),	//�J�����g�f�B���N�g���[�͓���
		&si,
		&pi);

	FreeEnvironmentStrings(env);

	// �s�v�ȃX���b�h�n���h�����N���[�Y����
	CloseHandle(pi.hThread);

	// �q�v���Z�X�̏I���҂�
	WaitForSingleObject(pi.hProcess, INFINITE);
	
	return 0;
}