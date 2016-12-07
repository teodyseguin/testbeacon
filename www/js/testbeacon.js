let testBeaconApp = (function() {
	let sdkOptions = {
    	trackBeaconVisits: true, // Log visits to beacons to the BlueCats api
    	useLocalStorage: true, // Cache beacons in local db for offline availability
    	cacheAllBeaconsForApp: true, // Cache all beacons on startup
    	discoverBeaconsNearby: true, // Cache beacons as detected by the device
    	cacheRefreshTimeIntervalInSeconds: 300 // Period to check for changes in seconds
	};
	
	function _success() {
    	alert('BlueCats SDK is purring');
		console.log('BlueCats SDK is purring');
    	// Start watching beacons using com.bluecats.beacons.watchEnterBeacon etc.
	}

	function _error() {
    	alert('onError!');
	}

	function runTestBeacon() {
		console.log('> runTestBeacon()');

		// Client secretet:
		// 2720eb62-219a-4f48-8a3d-a4b1d4417489

		// Client token:
		let clientToken = '2ad23000-d5a6-3e9c-0c41-d1a848181e23';

		com.bluecats.beacons.startPurringWithAppToken(clientToken, _success, _error, sdkOptions);	
	}

	return {
		runTestBeacon
	};
})();

