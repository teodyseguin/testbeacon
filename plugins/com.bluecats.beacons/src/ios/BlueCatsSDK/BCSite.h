//
//  BCSite.h
//  BlueCatsSDK
//
//  Created by Cody Singleton on 7/30/13.
//  Copyright (c) 2013 Bluecats. All rights reserved.
//

#import "BCJSONModel.h"
#import "BCBeaconDataSource.h"
#import "BCCategoryDataSource.h"
#import "BCJSONModel+BCCustomValueDataSource.h"
#import "BCDefinitions.h"

typedef enum {
    BCSiteStateUnknown = 0,
    BCSiteStateInside,
    BCSiteStateOutside,
} BCSiteState;

@class CLLocation, BCAddress, BCSiteAccessType, BCSiteType;

@interface BCSite : BCJSONModel<NSCopying, BCBeaconDataSource, BCCategoryDataSource, BCCustomValueDataSource>

@property (nonatomic, copy) NSString *siteID;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *teamID;
@property (nonatomic, strong) BCSiteAccessType *siteAccessType;
@property (nonatomic, strong) BCAddress *address;
@property (nonatomic, copy) NSString *notes;
@property (nonatomic, assign) NSInteger beaconCount;
@property (nonatomic, copy) NSDate *createdAt;
@property (nonatomic, copy) NSDate *modifiedAt;

@property (nonatomic, copy) NSArray *maps;
@property (nonatomic, copy) NSArray *customValues;

@property (nonatomic, copy) NSDate *cachedAt;
@property (nonatomic, copy) NSDate *syncedAt;
@property (nonatomic, assign) BCSyncStatus syncStatus;

- (BOOL)syncedOrRestored;
- (void)copyApiPropertiesFromSite:(BCSite *)site;

@property (nonatomic, copy) NSDate *cachedCategoriesAt;
@property (nonatomic, copy) NSArray *cachedCategories;

- (BOOL)hasCategoriesCacheExpired;

- (void)getCategoriesWithSuccess:(void (^)(NSArray *))success
                         failure:(void (^)(NSError *))failure
                    preferCached:(BOOL)preferCached;

- (CLLocation *)location;

@property (nonatomic, copy) NSDate *cachedBeaconsAt;

- (NSArray *)cachedBeacons;
- (BOOL)hasBeaconsCacheExpired;
- (void)getBeaconsWithSuccess:(void (^)(NSArray *))success
                      failure:(void (^)(NSError *))failure
                 preferCached:(BOOL)preferCached;

@end
