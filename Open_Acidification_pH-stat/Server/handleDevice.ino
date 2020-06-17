void handleDevice(String endpoint, EthernetClient client) {	
	// send all device info
	printHeader(client, 200);
	StaticJsonDocument<200> doc;
	JsonObject object = doc.to<JsonObject>();
	object["granularity"] = granularity;
	object["maxDataAge"] = maxDataAge;
	object["macstr"] = macstr;
	object["tankid"] = tankid;
	serializeJson(doc, client);
}