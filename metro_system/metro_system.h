#ifndef METRO_SYSTEM_H
#define METRO_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LEN 100
#define MAX_ID_LEN 50
#define MAX_DESC_LEN 500
#define MAX_ADDR_LEN 200
#define INFINITY 1e9
#define PI 3.141592653589793
#define HASH_TABLE_SIZE 1024
#define CACHE_SIZE 128

// ==================== 枚举类型 ====================
enum FacilityType {
    FACILITY_ELEVATOR,
    FACILITY_ESCALATOR,
    FACILITY_TOILET,
    FACILITY_TICKET_MACHINE,
    FACILITY_SECURITY,
    FACILITY_PARKING,
    FACILITY_BUSINESS,
    FACILITY_COUNT
};

enum RouteType {
    ROUTE_FASTEST,
    ROUTE_FEWEST_TRANSFER,
    ROUTE_CHEAPEST,
    ROUTE_LEAST_WALKING
};

enum SegmentType {
    SEGMENT_TRAIN,
    SEGMENT_TRANSFER,
    SEGMENT_WALK
};

enum DiscountType {
    DISCOUNT_STUDENT,
    DISCOUNT_ELDERLY,
    DISCOUNT_DISABLED,
    DISCOUNT_MILITARY,
    DISCOUNT_OFF_PEAK,
    DISCOUNT_WEEKEND,
    DISCOUNT_MONTHLY
};

enum StatusType {
    STATUS_NORMAL,
    STATUS_SUSPENDED,
    STATUS_MAINTENANCE,
    STATUS_DELAY,
    STATUS_CROWDED,
    STATUS_EMERGENCY
};

enum TerrainType {
    TERRAIN_FLAT,
    TERRAIN_UPHILL,
    TERRAIN_DOWNHILL,
    TERRAIN_STAIR,
    TERRAIN_ESCALATOR,
    TERRAIN_ELEVATOR
};

enum MapLayer {
    LAYER_BACKGROUND,
    LAYER_STATIONS,
    LAYER_LINES,
    LAYER_LABELS,
    LAYER_HIGHLIGHT,
    LAYER_ROUTE
};

enum CrowdLevel {
    CROWD_EMPTY,
    CROWD_LOW,
    CROWD_MEDIUM,
    CROWD_HIGH,
    CROWD_VERY_HIGH,
    CROWD_SATURATED
};

enum SharePermission {
    PERMISSION_FAMILY_ONLY,
    PERMISSION_FRIENDS_ONLY,
    PERMISSION_ALL,
    PERMISSION_NONE
};

// ==================== 基础结构体 ====================
struct Facility {
    enum FacilityType type;
    char location[MAX_ADDR_LEN];
    char description[MAX_DESC_LEN];
    int isAvailable;
    char operatingHours[50];
};

struct Exit {
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    double latitude;
    double longitude;
    char description[MAX_DESC_LEN];
    int hasElevator;
    int hasEscalator;
    int hasStair;
    char nearbyLandmarks[MAX_DESC_LEN];
};

struct DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

struct Point {
    double x;
    double y;
};

struct BoundingBox {
    double minLat;
    double maxLat;
    double minLon;
    double maxLon;
};

struct SlopeInfo {
    enum TerrainType terrain;
    double gradient;
    int stairCount;
    double extraTime;
    double calorieBurn;
};

struct Line;
struct Station;
struct RoutePlan;
struct RouteSegment;
struct TicketPrice;
struct Passenger;
struct RealTimeTracker;
struct CrowdManager;
struct LocationSharingManager;
struct MetroMap;
struct SpecialCaseManager;
struct Hotspot;
struct MountainRoute;

// ==================== 动态数组 ====================
struct ArrayList_Lines {
    struct Line** data;
    int capacity;
    int size;
};

struct ArrayList_Stations {
    struct Station** data;
    int capacity;
    int size;
};

struct ArrayList_Transfers {
    struct Transfer* data;
    int capacity;
    int size;
};

struct ArrayList_RouteSegments {
    struct RouteSegment* data;
    int capacity;
    int size;
};

struct ArrayList_ArrivalInfos {
    struct ArrivalInfo* data;
    int capacity;
    int size;
};

struct ArrayList_Hotspots {
    struct Hotspot* data;
    int capacity;
    int size;
};

struct ArrayList_SpecialCases {
    struct SpecialCase** data;
    int capacity;
    int size;
};

struct ArrayList_StationCrowds {
    struct StationCrowd* data;
    int capacity;
    int size;
};

struct ArrayList_LineCrowds {
    struct LineCrowd* data;
    int capacity;
    int size;
};

struct ArrayList_TrainPositions {
    struct TrainPosition* data;
    int capacity;
    int size;
};

struct ArrayList_Users {
    struct User* data;
    int capacity;
    int size;
};

struct ArrayList_SharedLocations {
    struct SharedLocation* data;
    int capacity;
    int size;
};

struct ArrayList_SafetyAlerts {
    struct SafetyAlert* data;
    int capacity;
    int size;
};

struct ArrayList_LocationShareSessions {
    struct LocationShareSession* data;
    int capacity;
    int size;
};

struct ArrayList_Points {
    struct Point* data;
    int capacity;
    int size;
};

struct ArrayList_StationVisuals {
    struct StationVisual* data;
    int capacity;
    int size;
};

struct ArrayList_LineVisuals {
    struct LineVisual* data;
    int capacity;
    int size;
};

struct ArrayList_CarriageCrowds {
    struct CarriageCrowd* data;
    int capacity;
    int size;
};

struct ArrayList_CrowdPredictions {
    struct CrowdPrediction* data;
    int capacity;
    int size;
};

struct ArrayList_Exits {
    struct Exit* data;
    int capacity;
    int size;
};

struct ArrayList_Facilities {
    struct Facility* data;
    int capacity;
    int size;
};

// ==================== 核心结构体 ====================
struct Station {
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    double latitude;
    double longitude;
    struct ArrayList_Lines* lines;
    struct ArrayList_Exits* exits;
    struct ArrayList_Facilities* facilities;
};

struct Line {
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    struct ArrayList_Stations* stations;
    double* travelTimeMatrix;
    int stationCount;
};

struct Transfer {
    struct Station* fromStation;
    struct Station* toStation;
    int transferTime;
};

struct RouteSegment {
    enum SegmentType type;
    struct Line* line;
    struct Station* startStation;
    struct Station* endStation;
    int startIndex;
    int endIndex;
    double time;
    double distance;
    int stationCount;
    struct ArrayList_Stations* intermediateStations;
};

struct TicketPrice {
    double basePrice;
    double totalPrice;
    double discount;
    char discountReason[MAX_DESC_LEN];
    int isFree;
};

struct RoutePlan {
    enum RouteType type;
    struct ArrayList_RouteSegments* segments;
    double totalTime;
    double totalDistance;
    int transferCount;
    struct TicketPrice price;
    char description[MAX_DESC_LEN];
};

struct Passenger {
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    int age;
    int isStudent;
    int isElderly;
    int isDisabled;
    int isMilitary;
    int hasMonthlyPass;
    double balance;
};

struct SpecialCase {
    enum StatusType type;
    char caseId[MAX_ID_LEN];
    char description[MAX_DESC_LEN];
    struct DateTime startTime;
    struct DateTime endTime;
    int isActive;
    int priority;
};

struct SuspensionInfo {
    struct SpecialCase base;
    struct Line* affectedLine;
    struct ArrayList_Stations* affectedStations;
    char reason[MAX_DESC_LEN];
    char alternativeRoute[MAX_DESC_LEN];
};

struct MaintenanceInfo {
    struct SpecialCase base;
    struct Line* maintenanceLine;
    struct Station* maintenanceStation;
    char maintenanceType[50];
    int expectedDuration;
};

struct DelayInfo {
    struct SpecialCase base;
    struct Line* delayedLine;
    struct Station* fromStation;
    struct Station* toStation;
    int delayMinutes;
    char delayReason[MAX_DESC_LEN];
};

struct SpecialCaseManager {
    struct ArrayList_SpecialCases* activeCases;
};

struct Hotspot {
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    double latitude;
    double longitude;
    char description[MAX_DESC_LEN];
    int popularity;
    char tags[10][50];
    int tagCount;
    char bestTimeToVisit[100];
};

struct StationVisual {
    enum MapLayer layer;
    int color;
    int isVisible;
    struct Station* station;
    struct Point screenPosition;
    int radius;
    char label[MAX_NAME_LEN];
};

struct LineVisual {
    enum MapLayer layer;
    int color;
    int lineWidth;
    int isVisible;
    struct Line* line;
    struct ArrayList_Points* points;
    struct ArrayList_StationVisuals* stationMarkers;
};

struct MetroMap {
    struct BoundingBox bounds;
    double zoomLevel;
    struct Point center;
    struct ArrayList_StationVisuals* stationVisuals;
    struct ArrayList_LineVisuals* lineVisuals;
    struct ArrayList_Hotspots* hotspots;
};

struct TrainPosition {
    char trainId[MAX_ID_LEN];
    struct Line* line;
    int direction;
    struct Station* currentStation;
    struct Station* nextStation;
    double progress;
    struct DateTime lastUpdateTime;
};

struct ArrivalInfo {
    struct Station* station;
    struct Line* line;
    int direction;
    int minutesToArrive;
    char trainId[MAX_ID_LEN];
    int isApproaching;
};

struct RealTimeTracker {
    struct ArrayList_TrainPositions* trainPositions;
    struct ArrayList_ArrivalInfos* arrivalCache;
};

struct CarriageCrowd {
    int carriageNumber;
    enum CrowdLevel level;
    int passengerCount;
    int capacity;
    double density;
};

struct StationCrowd {
    struct Station* station;
    enum CrowdLevel level;
    int passengerCount;
    int peakHourPassengers;
    struct DateTime lastUpdate;
    struct ArrayList_CarriageCrowds* carriages;
};

struct LineCrowd {
    struct Line* line;
    enum CrowdLevel averageLevel;
    struct ArrayList_StationCrowds* stationCrowds;
};

struct CrowdPrediction {
    struct Station* station;
    int hourOfDay;
    int dayOfWeek;
    enum CrowdLevel predictedLevel;
    double confidence;
};

struct CrowdManager {
    struct ArrayList_StationCrowds* stationCrowds;
    struct ArrayList_LineCrowds* lineCrowds;
    struct ArrayList_CrowdPredictions* predictions;
};

struct User {
    char userId[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    char phone[20];
    char relationship[20];
    enum SharePermission permission;
    int isOnline;
};

struct SharedLocation {
    struct User* user;
    double latitude;
    double longitude;
    struct DateTime timestamp;
    char status[50];
    int speed;
};

struct LocationShareSession {
    char sessionId[MAX_ID_LEN];
    struct User* owner;
    struct ArrayList_Users* participants;
    struct DateTime startTime;
    struct DateTime endTime;
    int isActive;
    int updateInterval;
};

struct SafetyAlert {
    struct User* user;
    char alertType[50];
    char description[MAX_DESC_LEN];
    struct DateTime alertTime;
    int isAcknowledged;
};

struct LocationSharingManager {
    struct ArrayList_Users* users;
    struct ArrayList_LocationShareSessions* activeSessions;
    struct ArrayList_SharedLocations* currentLocations;
    struct ArrayList_SafetyAlerts* alerts;
};

// ==================== 优化数据结构 ====================
struct HashEntry {
    char key[MAX_ID_LEN];
    void* value;
    struct HashEntry* next;
};

struct HashMap {
    struct HashEntry* buckets[HASH_TABLE_SIZE];
    int count;
};

struct Edge {
    struct Station* to;
    double weight;
    int edgeType;
    struct Line* line;
};

struct PrecomputedGraph {
    struct HashMap* stationToIndex;
    struct Edge** adjacencyArray;
    int* edgeCounts;
    int stationCount;
};

struct PQNode {
    struct Station* station;
    double distance;
};

struct BinaryHeap {
    struct PQNode** nodes;
    int* positions;
    int capacity;
    int size;
};

struct CacheEntry {
    char startId[MAX_ID_LEN];
    char endId[MAX_ID_LEN];
    struct RoutePlan* result;
    struct CacheEntry* prev;
    struct CacheEntry* next;
};

struct LRUCache {
    struct CacheEntry* head;
    struct CacheEntry* tail;
    struct HashMap* map;
    int capacity;
    int size;
};

// 优化后的主系统结构
struct MetroSystem {
    struct ArrayList_Lines* lines;
    struct ArrayList_Stations* stations;
    struct ArrayList_Transfers* transfers;
    struct SpecialCaseManager* caseManager;
    struct CrowdManager* crowdManager;
    struct LocationSharingManager* locationManager;
    struct RealTimeTracker* tracker;
    struct MetroMap* map;
    
    struct HashMap* stationHashMap;
    struct PrecomputedGraph* graph;
    struct LRUCache* routeCache;
    struct BinaryHeap* dijkstraHeap;
};

// ==================== 函数声明 ====================
// 基础函数
int strLen(const char* str);
void strCopy(char* dest, const char* src);
int strCompare(const char* s1, const char* s2);
void strConcat(char* dest, const char* src);
void* myMalloc(int size);
void myFree(void* p);

// 哈希表
unsigned int hashString(const char* str);
void hashMapPut(struct HashMap* map, const char* key, void* value);
void* hashMapGet(struct HashMap* map, const char* key);

// 二叉堆
struct BinaryHeap* createHeap(int capacity);
void heapPush(struct BinaryHeap* heap, struct Station* station, double distance);
struct PQNode* heapPop(struct BinaryHeap* heap);
int heapIsEmpty(struct BinaryHeap* heap);

// LRU缓存
struct LRUCache* createLRUCache(int capacity);
void cachePut(struct LRUCache* cache, const char* startId, const char* endId, struct RoutePlan* plan);
struct RoutePlan* cacheGet(struct LRUCache* cache, const char* startId, const char* endId);

// 动态数组初始化
void initArrayList_Lines(struct ArrayList_Lines* list);
void addToArrayList_Lines(struct ArrayList_Lines* list, struct Line* line);
void initArrayList_Stations(struct ArrayList_Stations* list);
void addToArrayList_Stations(struct ArrayList_Stations* list, struct Station* station);
void initArrayList_Transfers(struct ArrayList_Transfers* list);
void addToArrayList_Transfers(struct ArrayList_Transfers* list, struct Transfer transfer);
void initArrayList_RouteSegments(struct ArrayList_RouteSegments* list);
void addToArrayList_RouteSegments(struct ArrayList_RouteSegments* list, struct RouteSegment segment);
void initArrayList_ArrivalInfos(struct ArrayList_ArrivalInfos* list);
void addToArrayList_ArrivalInfos(struct ArrayList_ArrivalInfos* list, struct ArrivalInfo info);
void initArrayList_Hotspots(struct ArrayList_Hotspots* list);
void addToArrayList_Hotspots(struct ArrayList_Hotspots* list, struct Hotspot hotspot);
void initArrayList_Exits(struct ArrayList_Exits* list);
void addToArrayList_Exits(struct ArrayList_Exits* list, struct Exit exit);
void initArrayList_Facilities(struct ArrayList_Facilities* list);
void addToArrayList_Facilities(struct ArrayList_Facilities* list, struct Facility facility);
void initArrayList_SpecialCases(struct ArrayList_SpecialCases* list);
void initArrayList_StationCrowds(struct ArrayList_StationCrowds* list);
void addToArrayList_StationCrowds(struct ArrayList_StationCrowds* list, struct StationCrowd crowd);
void initArrayList_LineCrowds(struct ArrayList_LineCrowds* list);
void initArrayList_TrainPositions(struct ArrayList_TrainPositions* list);
void initArrayList_Users(struct ArrayList_Users* list);
void initArrayList_SharedLocations(struct ArrayList_SharedLocations* list);
void initArrayList_SafetyAlerts(struct ArrayList_SafetyAlerts* list);
void initArrayList_LocationShareSessions(struct ArrayList_LocationShareSessions* list);
void initArrayList_Points(struct ArrayList_Points* list);
void initArrayList_StationVisuals(struct ArrayList_StationVisuals* list);
void initArrayList_LineVisuals(struct ArrayList_LineVisuals* list);
void initArrayList_CarriageCrowds(struct ArrayList_CarriageCrowds* list);
void initArrayList_CrowdPredictions(struct ArrayList_CrowdPredictions* list);

// 数学函数
double mySin(double x);
double myCos(double x);
double mySqrt(double x);
double myAtan2(double y, double x);
double calculateDistance(double lat1, double lon1, double lat2, double lon2);
double heuristic(struct Station* from, struct Station* to);

// 图构建与路径查找
void buildPrecomputedGraph(struct MetroSystem* system);
struct RoutePlan* findShortestPath(struct MetroSystem* system,
    struct Station* start, struct Station* end,
    enum RouteType type, double* totalTime);
struct Station* getStationById(struct MetroSystem* system, const char* id);

// 票价计算
struct TicketPrice calculatePrice(struct MetroSystem* system,
    struct RoutePlan* route,
    struct Passenger* passenger);

// 实时到站
struct ArrayList_ArrivalInfos* getRealTimeArrivals(struct RealTimeTracker* tracker,
    struct Station* station, struct Line* line);

// 拥挤度
enum CrowdLevel getStationCrowdLevel(struct CrowdManager* manager, struct Station* station);
struct ArrayList_StationCrowds* getBatchStationCrowdLevels(struct CrowdManager* manager,
    struct ArrayList_Stations* stations);

// 位置共享
void shareLocation(struct LocationSharingManager* manager, struct User* user,
    double lat, double lon, int speed);
struct SharedLocation* getFriendLocation(struct LocationSharingManager* manager,
    struct User* requester, struct User* target);

// 附近热点
struct ArrayList_Hotspots* getNearbyHotspots(struct MetroSystem* system,
    double lat, double lon, double radius);

// 添加数据
void addLine(struct MetroSystem* system, struct Line* line);
void addStation(struct MetroSystem* system, struct Station* station);
void addTransfer(struct MetroSystem* system, struct Transfer transfer);

// 系统初始化和完成
void initMetroSystem(struct MetroSystem* system);
void finalizeMetroSystem(struct MetroSystem* system);

#endif 