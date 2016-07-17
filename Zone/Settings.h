#pragma once

#include <windows.h>

class Settings
{
	private:
		// Instance

		HMODULE m_hModule;

		// Settings

		bool m_enableService;

		int m_runSpeed;
		int m_walkSpeed;

	public:
		// Instance

		void SetDllInstance(HMODULE const& hModule)
		{
			m_hModule = hModule;
		}

		HMODULE GetDllInstance()
		{
			return m_hModule;
		}

		// Settings

		void LoadSettings();

		bool GetEnableService()
		{
			return m_enableService;
		}

		void SetEnableService(LPSTR const& enableService)
		{
			if(CheckBoolean(enableService))
			{
				m_enableService = true;
			}
			else
			{
				m_enableService = false;
			}
		}

		void SetEnableService(bool enableService)
		{
			m_enableService = enableService;
		}

		int GetRunSpeed()
		{
			return m_runSpeed;
		}

		void SetRunSpeed(LPSTR const& runSpeed)
		{
			long longRunSpeed = strtol(runSpeed, NULL, 10);

			m_runSpeed = (longRunSpeed > INT_MAX) ? 0 : longRunSpeed;
		}

		void SetRunSpeed(int runSpeed)
		{
			m_runSpeed = runSpeed;
		}

		int GetWalkSpeed()
		{
			return m_walkSpeed;
		}

		void SetWalkSpeed(LPSTR const& walkSpeed)
		{
			long longWalkSpeed = strtol(walkSpeed, NULL, 10);

			m_walkSpeed = (longWalkSpeed > INT_MAX) ? 0 : longWalkSpeed;
		}

		void SetWalkSpeed(int walkSpeed)
		{
			m_walkSpeed = walkSpeed;
		}

		bool CheckBoolean(LPSTR const& boolStr)
		{
			if((_strcmpi(boolStr, "true") == 0) || (_strcmpi(boolStr, "1") == 0))
			{
				return true;
			}

			return false;
		}
};