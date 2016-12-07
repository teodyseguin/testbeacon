//
//  BCBeacon.h
//  BlueCatsSDK
//
//  Created by Cody Singleton on 2/13/13.
//  Copyright (c) 2013 Bluecats. All rights reserved.
//

#import "BCJSONModel.h"
#import "BCJSONModel+BCCustomValueDataSource.h"
#import "BCDefinitions.h"

typedef enum {
	BCProximityUnknown = 0,
	BCProximityImmediate,
	BCProximityNear,
	BCProximityFar
} BCProximity;

typedef enum {
    BCBlueCatsAdDataTypeUnknown = 0,
    BCBlueCatsAdDataTypeSphynx1 = 1,
    BCBlueCatsAdDataTypeIBeacon2 = 2,
    BCBlueCatsAdDataTypeIBeacon3 = 3,
    BCBlueCatsAdDataTypeSecure1 = 4,
    BCBlueCatsAdDataTypeIBeacon4 = 5,
    BCBlueCatsAdDataTypeSecure2 = 6,
    BCBlueCatsAdDataTypeData1 = 7,
    BCBlueCatsAdDataTypeData2 = 8
} BCBlueCatsAdDataType;

typedef enum {
    BCVerificationStatusNotVerified = 0,
    BCVerificationStatusDetectedAttack,
    BCVerificationStatusVerifiedViaBlueCatsIBeaconAd,
    BCVerificationStatusVerifiedViaBueCatsSecureAd
} BCVerificationStatus;

typedef enum {
    BCBlockDataEncodingNone = 0,
    BCBlockDataEncodingUTF8,
    BCBlockDataEncodingJSON
} BCBlockDataEncoding;

typedef enum {
    BCBlockDataTypeCustom = 0,
    BCBlockDataTypeTemperature = 15
} BCBlockDataType;

typedef enum {
    BCBeaconEndpointUSBHost = 0
} BCBeaconEndpoint;

typedef enum {
    BCBeaconOwnershipUnknown = 0,
    BCBeaconOwnershipOwned = 1,
    BCBeaconOwnershipShared = 2,
    BCBeaconOwnershipPublic = 3
} BCBeaconOwnership;

typedef enum {
    BCBeaconAccessRoleVisitTracker = 1,
    BCBeaconAccessRoleBeaconRanger = 2,
    BCBeaconAccessRoleSettingsUpdater = 3
} BCBeaconAccessRole;


@class BCBatteryStatus, BCBeaconLoudness, BCTargetSpeed, BCMapPoint, BCBeaconRegion, BCBeaconMode, BCBeaconVersion, BCBeaconVisit, BCNetworkAccess,BCNetworkAccessRole,BCNetworkAccessOwnership;

@interface BCBeacon : BCJSONModel <NSCopying, BCCustomValueDataSource>

// BlueCats Api properties
@property (nonatomic, copy) NSString *beaconID;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *teamID;
@property (nonatomic, copy) NSString *siteID;
@property (nonatomic, copy) NSString *siteName;
@property (nonatomic, copy) NSString *bluetoothAddress;
@property (nonatomic, copy) NSNumber *measuredPowerAt1Meter;
@property (nonatomic, copy) NSString *firmwareVersion;
@property (nonatomic, copy) NSString *latestFirmwareVersion;
@property (nonatomic, copy) NSNumber *privacyDuration;
@property (nonatomic, copy) NSString *modelNumber;
@property (nonatomic, copy) NSString *serialNumber;
@property (nonatomic, assign) BOOL upgradableOTA;
@property (nonatomic, copy) NSNumber *version;
@property (nonatomic, copy) NSNumber *pendingVersion;
@property (nonatomic, copy) NSDate *createdAt;
@property (nonatomic, copy) NSDate *modifiedAt;
@property (nonatomic, copy) BCBeaconRegion *beaconRegion;
@property (nonatomic, copy) BCBeaconMode *beaconMode;
@property (nonatomic, copy) BCBatteryStatus *batteryStatus;
@property (nonatomic, copy) NSNumber *lastKnownBatteryLevel;
@property (nonatomic, copy) BCBeaconLoudness *beaconLoudness;
@property (nonatomic, copy) BCTargetSpeed *targetSpeed;
@property (nonatomic, copy) BCMapPoint *mapPoint;
@property (nonatomic, copy) BCNetworkAccess *networkAccess;
@property (nonatomic, strong) NSArray *categories;
@property (nonatomic, strong) NSArray *customValues;

// CoreBluetooth properties
@property (nonatomic, copy) NSUUID *peripheralIdentifier;
@property (nonatomic, copy) NSDate *firstDiscoveredAt;
@property (nonatomic, copy) NSDate *lastDiscoveredAt;
@property (nonatomic, assign, readonly) BOOL discovered;

// iBeacon properties
@property (nonatomic, copy) NSString *proximityUUIDString;
@property (nonatomic, copy) NSNumber *major;
@property (nonatomic, copy) NSNumber *minor;
@property (nonatomic, copy) NSDate *lastRangedAt;
@property (nonatomic, copy) NSDate *firstRangedAt;

// BeaconManager properties
@property (nonatomic, copy) NSDate *cachedAt;
@property (nonatomic, copy) NSDate *syncedAt;
@property (nonatomic, assign) BCSyncStatus syncStatus;
@property (nonatomic, assign, readonly) BOOL synced;
@property (nonatomic, copy, readonly) NSString *iBeaconKey;

// Proximity Properties
@property (nonatomic, assign) double accuracy;
@property (nonatomic, copy) NSNumber *rssi;
@property (nonatomic, assign) BCProximity proximity;

@property (nonatomic, copy) NSDate *verifiedAt;
@property (nonatomic, assign) BCVerificationStatus verificationStatus;

- (NSNumber *)averageAdsPerMinuteForAdDataType:(NSString *)adDataTypeKey;
- (void)removeAllAdData;
- (void)removeAdDataForAdDataTypeKey:(NSString *)adDataTypeKey;
- (void)setAdData:(NSDictionary *)adData forAdDataTypeKey:(NSString *)adDataTypeKey;
- (NSDictionary *)adDataForAdDataTypeKey:(NSString *)adDataTypeKey;
- (id)objectFromBlueCatsAdDataForKey:(NSString *)key;

- (NSArray *)reassembledBlockDataWithDataType:(BCBlockDataType)dataType;
- (NSDictionary *)lastReassembledBlockDataWithDataType:(BCBlockDataType)dataType;

- (void)requestDataArrayFromBeaconEndpoint:(BCBeaconEndpoint)endpoint
                             withDataArray:(NSArray *)requestDataArray
                                   success:(void (^)(NSArray *responseDataArray))success
                                    status:(void (^)(NSString *status))status
                                   failure:(void (^)(NSError *error))failure;

- (void)numberOfVisitsTodayWithSuccess:(void (^)(NSUInteger visitCount))success
                               failure:(void (^)(NSError *error))failure;

- (void)numberOfVisitsYesterdayWithSuccess:(void (^)(NSUInteger visitCount))success
                                   failure:(void (^)(NSError *error))failure;

- (void)numberOfVisitsThisWeekWithSuccess:(void (^)(NSUInteger visitCount))success
                                  failure:(void (^)(NSError *error))failure;

- (void)numberOfVisitsLastWeekWithSuccess:(void (^)(NSUInteger visitCount))success
                                  failure:(void (^)(NSError *error))failure;

- (void)numberOfVisitsThisMonthWithSuccess:(void (^)(NSUInteger visitCount))success
                                   failure:(void (^)(NSError *error))failure;

- (void)numberOfVisitsLastMonthWithSuccess:(void (^)(NSUInteger visitCount))success
                                   failure:(void (^)(NSError *error))failure;

- (void)numberOfVisitsSinceDate:(NSDate *)date
                        success:(void (^)(NSUInteger visitCount))success
                        failure:(void (^)(NSError *error))failure;

- (void)numberOfVisitsUntilDate:(NSDate *)date
                        success:(void (^)(NSUInteger visitCount))success
                        failure:(void (^)(NSError *error))failure;

- (void)numberOfVisitsFromDate:(NSDate *)startDate untilDate:(NSDate *)endDate
                       success:(void (^)(NSUInteger visitCount))success
                       failure:(void (^)(NSError *error))failure;

+ (void)storedBeaconsWithPredicate:(NSPredicate *)predicate sortDescriptors:(NSArray *)sortDesc
                           success:(void (^)(NSArray *beacons))success
                           failure:(void (^)(NSError *error))failure;

+ (void)numberOfBeaconsWithPredicate:(NSPredicate *)predicate
                             success:(void (^)(NSUInteger count))success
                             failure:(void (^)(NSError *error))failure;

@end

extern NSString * const BCFirmwareVersion002;
extern NSString * const BCFirmwareVersion010;
extern NSString * const BCFirmwareVersion011;
extern NSString * const BCFirmwareVersion020;
extern NSString * const BCFirmwareVersion030;
extern NSString * const BCFirmwareVersion031;
extern NSString * const BCFirmwareVersion040;
extern NSString * const BCFirmwareVersion041;
extern NSString * const BCFirmwareVersion050;
extern NSString * const BCFirmwareVersion051;
extern NSString * const BCFirmwareVersion052;

extern NSString * const BCAdDataTypeKey;
extern NSString * const BCAdDataTypeAppleIBeaconKey;
extern NSString * const BCAdDataTypeBlueCatsSphynxKey;
extern NSString * const BCAdDataTypeBlueCatsIBeaconKey;
extern NSString * const BCAdDataTypeBlueCatsSecureKey;
extern NSString * const BCAdDataTypeBlueCatsBlockDataKey;
extern NSString * const BCAdDataTimestampKey;
extern NSString * const BCAdDataFirstDiscoveredAtKey;
extern NSString * const BCAdDataDiscoveredCountKey;
extern NSString * const BCAdDataDiscoveredPerMinuteKey;

extern NSString * const BCBlueCatsAdDataBeaconModeIDKey;
extern NSString * const BCBlueCatsAdDataVersionKey;
extern NSString * const BCBlueCatsAdDataTypeKey;
extern NSString * const BCBlueCatsAdDataProximityUUIDStringKey;
extern NSString * const BCBlueCatsAdDataBluetoothAddressStringKey;
extern NSString * const BCBlueCatsAdDataMajorKey;
extern NSString * const BCBlueCatsAdDataMinorKey;
extern NSString * const BCBlueCatsAdDataFirmwareVersionKey;
extern NSString * const BCBlueCatsAdDataModelNumberKey;
extern NSString * const BCBlueCatsAdDataBatteryLevelKey;
extern NSString * const BCBlueCatsAdDataTxPowerLevelKey;
extern NSString * const BCBlueCatsAdDataMeasuredPowerAt1MeterKey;
extern NSString * const BCBlueCatsAdDataBeaconLoudnessLevelKey;
extern NSString * const BCBlueCatsAdDataTargetSpeedInMillisecondsKey;
extern NSString * const BCBlueCatsAdDataSequenceNumberKey;

extern NSString * const BCBlueCatsBlockDataIdentifierKey;
extern NSString * const BCBlueCatsBlockDataTypeKey;
extern NSString * const BCBlueCatsBlockDataEncodingKey;
extern NSString * const BCBlueCatsBlockDataCountKey;
extern NSString * const BCBlueCatsBlockDataIndexKey;
extern NSString * const BCBlueCatsBlockDataLengthKey;
extern NSString * const BCBlueCatsBlockDataKey;
extern NSString * const BCBlueCatsIndexedBlockDataKey;
extern NSString * const BCBlueCatsBlockDataReassembledAtKey;

extern NSString * const BCAppleIBeaconAdDataProximityUUIDStringKey;
extern NSString * const BCAppleIBeaconAdDataMajorKey;
extern NSString * const BCAppleIBeaconAdDataMinorKey;
extern NSString * const BCAppleIBeaconAdDataMeasuredPowerAt1MeterKey;


