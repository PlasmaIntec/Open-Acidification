void handleLines(String endpoint, EthernetClient client) {	  
	client.println("HTTP/1.1 200 OK");
	client.println("Content-Type: text/plain; charset=UTF-8");
	client.println("Connection: keep-alive");  // the connection will be closed after completion of the response
	client.println("Keep-Alive: timeout=5, max=1000");
	// lines endpoint format: lines/year/month/day/hour
	String directoryName;
	if (endpoint.length() >= 6) {
		directoryName = endpoint.substring(6); // remove "/lines/" prefix
	} else {
		directoryName = "/";
	}
	int slashIndex = endpoint.lastIndexOf("/");
	String hourName = endpoint.substring(slashIndex);
	directoryName.concat(hourName + ".txt");
	char* pch;
	int slashes = -1;
	pch = strtok(endpoint.c_str(), "/");
	while (pch != NULL)
	{
		pch = strtok(NULL, "/");
		slashes += 1;
	}
	switch (slashes) {
		case 4: 
		 	// hour: return csv of the specific hour
			client.println("X-Content-Type-Options: nosniff");
			client.println();
			Serial.print("PRINTING LINE FILE: ");
			Serial.println(directoryName);
			File lineFile = SD.open(directoryName);
			char linesBuffer[10];
			int i = 0;
			while (lineFile.available() && i < 10) {
				linesBuffer[i++] = lineFile.read();
			}
			linesBuffer[i] = '\0';
			int lineCount = atoi(linesBuffer);
			Serial.print("LINE COUNT: ");
			Serial.println(lineCount);
			client.println(lineCount);
			break;
		default:
			client.println("REQUIRES FULL YEAR/MONTH/DAY/HOUR SPECIFICATION");
			break;
	}
}