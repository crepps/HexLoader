	std::error_code err;
	std::filesystem::create_directories(path, err);
	
	if (err)
		MessageBoxA(0, "Failed to create installation directory.", err.message().c_str(), MB_OK);

	for (unsigned int i = 0; i < data.size(); ++i)
	{
		outFile.open(path + "\\" + fileNames[i], std::ios::out | std::ios::binary);
		outFile.write(reinterpret_cast<const char*>(data[i]), sizes[i]);
		outFile.close();
	}
	
	if (shortcut)
	{
		if (result = createShortcut(path, appName))
			MessageBoxA(0, "Error: " + result, "Failed To Create Shortcut", MB_OK);
	}
	
	if (startup)
	{
		if (result = createRegKey(path, fileNames[0], appName))
			MessageBoxA(0, "Error: " + result, "Failed To Create Registry Key", MB_OK);
	}
	
	launch = prompt(STAGE2, appName, path, shortcut, startup);
	
	if (launch)
	{
		path.append("\\" + fileNames[0]);
		STARTUPINFOA si{ 0 };
		PROCESS_INFORMATION pi{ 0 };
		si.wShowWindow = SW_HIDE;
		CreateProcessA(path.c_str(), NULL, NULL, NULL, false, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
	}

	return 0;
}