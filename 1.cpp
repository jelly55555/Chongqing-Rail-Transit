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
    
    // 优化字段
    struct HashMap* stationHashMap;
    struct PrecomputedGraph* graph;
    struct LRUCache* routeCache;
    struct BinaryHeap* dijkstraHeap;
};

// ==================== 基础函数 ====================
int strLen(const char* str) {
    int len = 0;
    while (str && str[len]) len++;
    return len;
}

void strCopy(char* dest, const char* src) {
    if (!dest || !src) return;
    int i = 0;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int strCompare(const char* s1, const char* s2) {
    if (!s1 || !s2) return (s1 == s2) ? 0 : (s1 ? 1 : -1);
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i]) i++;
    return s1[i] - s2[i];
}

void strConcat(char* dest, const char* src) {
    if (!dest || !src) return;
    int i = strLen(dest);
    int j = 0;
    while (src[j]) {
        dest[i + j] = src[j];
        j++;
    }
    dest[i + j] = '\0';
}

void* myMalloc(int size) {
    static char heap[10 * 1024 * 1024];
    static int pos = 0;
    if (pos + size > 10 * 1024 * 1024) return 0;
    void* p = &heap[pos];
    pos += size;
    return p;
}

void myFree(void* p) {}

// ==================== 哈希表实现 ====================
unsigned int hashString(const char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_TABLE_SIZE;
}

void hashMapPut(struct HashMap* map, const char* key, void* value) {
    if (!map || !key) return;
    unsigned int index = hashString(key);
    struct HashEntry* entry = map->buckets[index];
    while (entry) {
        if (strCompare(entry->key, key) == 0) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }
    struct HashEntry* newEntry = (struct HashEntry*)myMalloc(sizeof(struct HashEntry));
    strCopy(newEntry->key, key);
    newEntry->value = value;
    newEntry->next = map->buckets[index];
    map->buckets[index] = newEntry;
    map->count++;
}

void* hashMapGet(struct HashMap* map, const char* key) {
    if (!map || !key) return 0;
    unsigned int index = hashString(key);
    struct HashEntry* entry = map->buckets[index];
    while (entry) {
        if (strCompare(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return 0;
}

// ==================== 二叉堆实现 ====================
struct BinaryHeap* createHeap(int capacity) {
    struct BinaryHeap* heap = (struct BinaryHeap*)myMalloc(sizeof(struct BinaryHeap));
    heap->nodes = (struct PQNode**)myMalloc(sizeof(struct PQNode*) * capacity);
    heap->positions = (int*)myMalloc(sizeof(int) * capacity);
    heap->capacity = capacity;
    heap->size = 0;
    for (int i = 0; i < capacity; i++) heap->positions[i] = -1;
    return heap;
}

void heapSwap(struct BinaryHeap* heap, int i, int j) {
    struct PQNode* temp = heap->nodes[i];
    heap->nodes[i] = heap->nodes[j];
    heap->nodes[j] = temp;
}

void heapPush(struct BinaryHeap* heap, struct Station* station, double distance) {
    if (!heap || !station || heap->size >= heap->capacity) return;
    
    int idx = heap->size;
    heap->nodes[idx] = (struct PQNode*)myMalloc(sizeof(struct PQNode));
    heap->nodes[idx]->station = station;
    heap->nodes[idx]->distance = distance;
    heap->size++;
    
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap->nodes[parent]->distance <= heap->nodes[idx]->distance) break;
        heapSwap(heap, idx, parent);
        idx = parent;
    }
}

struct PQNode* heapPop(struct BinaryHeap* heap) {
    if (!heap || heap->size == 0) return 0;
    
    struct PQNode* result = heap->nodes[0];
    heap->size--;
    
    if (heap->size > 0) {
        heap->nodes[0] = heap->nodes[heap->size];
        int idx = 0;
        while (1) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int smallest = idx;
            
            if (left < heap->size && heap->nodes[left]->distance < heap->nodes[smallest]->distance)
                smallest = left;
            if (right < heap->size && heap->nodes[right]->distance < heap->nodes[smallest]->distance)
                smallest = right;
            if (smallest == idx) break;
            
            heapSwap(heap, idx, smallest);
            idx = smallest;
        }
    }
    return result;
}

int heapIsEmpty(struct BinaryHeap* heap) {
    return !heap || heap->size == 0;
}

// ==================== LRU缓存实现 ====================
struct LRUCache* createLRUCache(int capacity) {
    struct LRUCache* cache = (struct LRUCache*)myMalloc(sizeof(struct LRUCache));
    cache->head = cache->tail = 0;
    cache->map = (struct HashMap*)myMalloc(sizeof(struct HashMap));
    cache->capacity = capacity;
    cache->size = 0;
    return cache;
}

void moveToHead(struct LRUCache* cache, struct CacheEntry* entry) {
    if (entry == cache->head) return;
    if (entry->prev) entry->prev->next = entry->next;
    if (entry->next) entry->next->prev = entry->prev;
    if (entry == cache->tail) cache->tail = entry->prev;
    entry->prev = 0;
    entry->next = cache->head;
    if (cache->head) cache->head->prev = entry;
    cache->head = entry;
    if (!cache->tail) cache->tail = entry;
}

void evictLRU(struct LRUCache* cache) {
    if (!cache->tail) return;
    char key[MAX_ID_LEN * 2];
    strCopy(key, cache->tail->startId);
    strConcat(key, "_");
    strConcat(key, cache->tail->endId);
    hashMapPut(cache->map, key, 0);
    if (cache->tail->prev) cache->tail->prev->next = 0;
    cache->tail = cache->tail->prev;
    if (!cache->tail) cache->head = 0;
    cache->size--;
}

void cachePut(struct LRUCache* cache, const char* startId, const char* endId, struct RoutePlan* plan) {
    if (!cache) return;
    char key[MAX_ID_LEN * 2];
    strCopy(key, startId);
    strConcat(key, "_");
    strConcat(key, endId);
    
    struct CacheEntry* existing = (struct CacheEntry*)hashMapGet(cache->map, key);
    if (existing) {
        existing->result = plan;
        moveToHead(cache, existing);
        return;
    }
    
    if (cache->size >= cache->capacity) evictLRU(cache);
    
    struct CacheEntry* entry = (struct CacheEntry*)myMalloc(sizeof(struct CacheEntry));
    strCopy(entry->startId, startId);
    strCopy(entry->endId, endId);
    entry->result = plan;
    entry->prev = 0;
    entry->next = cache->head;
    if (cache->head) cache->head->prev = entry;
    cache->head = entry;
    if (!cache->tail) cache->tail = entry;
    hashMapPut(cache->map, key, entry);
    cache->size++;
}

struct RoutePlan* cacheGet(struct LRUCache* cache, const char* startId, const char* endId) {
    if (!cache) return 0;
    char key[MAX_ID_LEN * 2];
    strCopy(key, startId);
    strConcat(key, "_");
    strConcat(key, endId);
    struct CacheEntry* entry = (struct CacheEntry*)hashMapGet(cache->map, key);
    if (entry) {
        moveToHead(cache, entry);
        return entry->result;
    }
    return 0;
}

// ==================== 动态数组初始化 ====================
void initArrayList_Lines(struct ArrayList_Lines* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct Line**)myMalloc(sizeof(struct Line*) * list->capacity);
}

void addToArrayList_Lines(struct ArrayList_Lines* list, struct Line* line) {
    if (!list || !line) return;
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        struct Line** newData = (struct Line**)myMalloc(sizeof(struct Line*) * list->capacity);
        for (int i = 0; i < list->size; i++) newData[i] = list->data[i];
        list->data = newData;
    }
    list->data[list->size++] = line;
}

void initArrayList_Stations(struct ArrayList_Stations* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct Station**)myMalloc(sizeof(struct Station*) * list->capacity);
}

void addToArrayList_Stations(struct ArrayList_Stations* list, struct Station* station) {
    if (!list || !station) return;
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        struct Station** newData = (struct Station**)myMalloc(sizeof(struct Station*) * list->capacity);
        for (int i = 0; i < list->size; i++) newData[i] = list->data[i];
        list->data = newData;
    }
    list->data[list->size++] = station;
}

void initArrayList_Transfers(struct ArrayList_Transfers* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct Transfer*)myMalloc(sizeof(struct Transfer) * list->capacity);
}

void addToArrayList_Transfers(struct ArrayList_Transfers* list, struct Transfer transfer) {
    if (!list) return;
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        struct Transfer* newData = (struct Transfer*)myMalloc(sizeof(struct Transfer) * list->capacity);
        for (int i = 0; i < list->size; i++) newData[i] = list->data[i];
        list->data = newData;
    }
    list->data[list->size++] = transfer;
}

void initArrayList_RouteSegments(struct ArrayList_RouteSegments* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct RouteSegment*)myMalloc(sizeof(struct RouteSegment) * list->capacity);
}

void addToArrayList_RouteSegments(struct ArrayList_RouteSegments* list, struct RouteSegment segment) {
    if (!list) return;
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        struct RouteSegment* newData = (struct RouteSegment*)myMalloc(sizeof(struct RouteSegment) * list->capacity);
        for (int i = 0; i < list->size; i++) newData[i] = list->data[i];
        list->data = newData;
    }
    list->data[list->size++] = segment;
}

void initArrayList_ArrivalInfos(struct ArrayList_ArrivalInfos* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct ArrivalInfo*)myMalloc(sizeof(struct ArrivalInfo) * list->capacity);
}

void addToArrayList_ArrivalInfos(struct ArrayList_ArrivalInfos* list, struct ArrivalInfo info) {
    if (!list) return;
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        struct ArrivalInfo* newData = (struct ArrivalInfo*)myMalloc(sizeof(struct ArrivalInfo) * list->capacity);
        for (int i = 0; i < list->size; i++) newData[i] = list->data[i];
        list->data = newData;
    }
    list->data[list->size++] = info;
}

void initArrayList_Hotspots(struct ArrayList_Hotspots* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct Hotspot*)myMalloc(sizeof(struct Hotspot) * list->capacity);
}

void addToArrayList_Hotspots(struct ArrayList_Hotspots* list, struct Hotspot hotspot) {
    if (!list) return;
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        struct Hotspot* newData = (struct Hotspot*)myMalloc(sizeof(struct Hotspot) * list->capacity);
        for (int i = 0; i < list->size; i++) newData[i] = list->data[i];
        list->data = newData;
    }
    list->data[list->size++] = hotspot;
}

void initArrayList_Exits(struct ArrayList_Exits* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct Exit*)myMalloc(sizeof(struct Exit) * list->capacity);
}

void addToArrayList_Exits(struct ArrayList_Exits* list, struct Exit exit) {
    if (!list) return;
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        struct Exit* newData = (struct Exit*)myMalloc(sizeof(struct Exit) * list->capacity);
        for (int i = 0; i < list->size; i++) newData[i] = list->data[i];
        list->data = newData;
    }
    list->data[list->size++] = exit;
}

void initArrayList_Facilities(struct ArrayList_Facilities* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct Facility*)myMalloc(sizeof(struct Facility) * list->capacity);
}

void addToArrayList_Facilities(struct ArrayList_Facilities* list, struct Facility facility) {
    if (!list) return;
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        struct Facility* newData = (struct Facility*)myMalloc(sizeof(struct Facility) * list->capacity);
        for (int i = 0; i < list->size; i++) newData[i] = list->data[i];
        list->data = newData;
    }
    list->data[list->size++] = facility;
}

void initArrayList_SpecialCases(struct ArrayList_SpecialCases* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct SpecialCase**)myMalloc(sizeof(struct SpecialCase*) * list->capacity);
}

void initArrayList_StationCrowds(struct ArrayList_StationCrowds* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct StationCrowd*)myMalloc(sizeof(struct StationCrowd) * list->capacity);
}

void addToArrayList_StationCrowds(struct ArrayList_StationCrowds* list, struct StationCrowd crowd) {
    if (!list) return;
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        struct StationCrowd* newData = (struct StationCrowd*)myMalloc(sizeof(struct StationCrowd) * list->capacity);
        for (int i = 0; i < list->size; i++) newData[i] = list->data[i];
        list->data = newData;
    }
    list->data[list->size++] = crowd;
}

void initArrayList_LineCrowds(struct ArrayList_LineCrowds* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct LineCrowd*)myMalloc(sizeof(struct LineCrowd) * list->capacity);
}

void initArrayList_TrainPositions(struct ArrayList_TrainPositions* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct TrainPosition*)myMalloc(sizeof(struct TrainPosition) * list->capacity);
}

void initArrayList_Users(struct ArrayList_Users* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct User*)myMalloc(sizeof(struct User) * list->capacity);
}

void initArrayList_SharedLocations(struct ArrayList_SharedLocations* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct SharedLocation*)myMalloc(sizeof(struct SharedLocation) * list->capacity);
}

void initArrayList_SafetyAlerts(struct ArrayList_SafetyAlerts* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct SafetyAlert*)myMalloc(sizeof(struct SafetyAlert) * list->capacity);
}

void initArrayList_LocationShareSessions(struct ArrayList_LocationShareSessions* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct LocationShareSession*)myMalloc(sizeof(struct LocationShareSession) * list->capacity);
}

void initArrayList_Points(struct ArrayList_Points* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct Point*)myMalloc(sizeof(struct Point) * list->capacity);
}

void initArrayList_StationVisuals(struct ArrayList_StationVisuals* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct StationVisual*)myMalloc(sizeof(struct StationVisual) * list->capacity);
}

void initArrayList_LineVisuals(struct ArrayList_LineVisuals* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct LineVisual*)myMalloc(sizeof(struct LineVisual) * list->capacity);
}

void initArrayList_CarriageCrowds(struct ArrayList_CarriageCrowds* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct CarriageCrowd*)myMalloc(sizeof(struct CarriageCrowd) * list->capacity);
}

void initArrayList_CrowdPredictions(struct ArrayList_CrowdPredictions* list) {
    if (!list) return;
    list->capacity = 10;
    list->size = 0;
    list->data = (struct CrowdPrediction*)myMalloc(sizeof(struct CrowdPrediction) * list->capacity);
}

// ==================== 数学函数 ====================
double mySin(double x) {
    double res = 0, term = x;
    int sign = 1;
    for (int i = 1; i <= 10; i++) {
        res += sign * term;
        sign *= -1;
        term *= x * x / ((2 * i) * (2 * i + 1));
    }
    return res;
}

double myCos(double x) {
    double res = 1, term = 1;
    int sign = -1;
    for (int i = 1; i <= 10; i++) {
        term *= x * x / ((2 * i - 1) * (2 * i));
        res += sign * term;
        sign *= -1;
    }
    return res;
}

double mySqrt(double x) {
    if (x < 0) return 0;
    double r = x;
    for (int i = 0; i < 10; i++) r = (r + x / r) * 0.5;
    return r;
}

double myAtan2(double y, double x) {
    double absY = y < 0 ? -y : y;
    double angle = 0.0, a = y < 0 ? -1.0 : 1.0;
    if (x > 0) angle = a * (absY / x);
    else if (x == 0) angle = a * 1.570796;
    else angle = a * (3.14159 - absY / (-x));
    return angle;
}

double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    double lat1Rad = lat1 * PI / 180.0;
    double lat2Rad = lat2 * PI / 180.0;
    double dlat = (lat2 - lat1) * PI / 180.0;
    double dlon = (lon2 - lon1) * PI / 180.0;
    double a = mySin(dlat / 2) * mySin(dlat / 2) +
        myCos(lat1Rad) * myCos(lat2Rad) *
        mySin(dlon / 2) * mySin(dlon / 2);
    double c = 2 * myAtan2(mySqrt(a), mySqrt(1 - a));
    return 6371.0 * c;
}

// ==================== 启发函数 ====================
double heuristic(struct Station* from, struct Station* to) {
    if (!from || !to) return 0;
    double dist = calculateDistance(from->latitude, from->longitude, to->latitude, to->longitude);
    return dist / 30.0 * 60.0;
}

// ==================== 预计算邻接表 ====================
void buildPrecomputedGraph(struct MetroSystem* system) {
    if (!system) return;
    
    int stationCount = system->stations->size;
    system->graph = (struct PrecomputedGraph*)myMalloc(sizeof(struct PrecomputedGraph));
    system->graph->stationCount = stationCount;
    system->graph->adjacencyArray = (struct Edge**)myMalloc(sizeof(struct Edge*) * stationCount);
    system->graph->edgeCounts = (int*)myMalloc(sizeof(int) * stationCount);
    
    for (int i = 0; i < stationCount; i++) {
        system->graph->adjacencyArray[i] = 0;
        system->graph->edgeCounts[i] = 0;
    }
    
    system->graph->stationToIndex = (struct HashMap*)myMalloc(sizeof(struct HashMap));
    for (int i = 0; i < stationCount; i++) {
        hashMapPut(system->graph->stationToIndex, system->stations->data[i]->id, (void*)(long long)i);
    }
    
    for (int i = 0; i < stationCount; i++) {
        struct Station* station = system->stations->data[i];
        int edgeCount = 0;
        
        for (int j = 0; j < station->lines->size; j++) {
            struct Line* line = station->lines->data[j];
            int stationIndex = -1;
            for (int k = 0; k < line->stations->size; k++) {
                if (strCompare(line->stations->data[k]->id, station->id) == 0) {
                    stationIndex = k;
                    break;
                }
            }
            if (stationIndex > 0) edgeCount++;
            if (stationIndex < line->stations->size - 1 && stationIndex >= 0) edgeCount++;
        }
        
        for (int j = 0; j < system->transfers->size; j++) {
            struct Transfer* t = &system->transfers->data[j];
            if (strCompare(t->fromStation->id, station->id) == 0) edgeCount++;
            if (strCompare(t->toStation->id, station->id) == 0) edgeCount++;
        }
        
        system->graph->adjacencyArray[i] = (struct Edge*)myMalloc(sizeof(struct Edge) * edgeCount);
        system->graph->edgeCounts[i] = edgeCount;
        
        int idx = 0;
        for (int j = 0; j < station->lines->size; j++) {
            struct Line* line = station->lines->data[j];
            int stationIndex = -1;
            for (int k = 0; k < line->stations->size; k++) {
                if (strCompare(line->stations->data[k]->id, station->id) == 0) {
                    stationIndex = k;
                    break;
                }
            }
            if (stationIndex > 0) {
                system->graph->adjacencyArray[i][idx].to = line->stations->data[stationIndex - 1];
                system->graph->adjacencyArray[i][idx].weight = 2.5;
                system->graph->adjacencyArray[i][idx].edgeType = 0;
                system->graph->adjacencyArray[i][idx].line = line;
                idx++;
            }
            if (stationIndex < line->stations->size - 1 && stationIndex >= 0) {
                system->graph->adjacencyArray[i][idx].to = line->stations->data[stationIndex + 1];
                system->graph->adjacencyArray[i][idx].weight = 2.5;
                system->graph->adjacencyArray[i][idx].edgeType = 0;
                system->graph->adjacencyArray[i][idx].line = line;
                idx++;
            }
        }
        
        for (int j = 0; j < system->transfers->size; j++) {
            struct Transfer* t = &system->transfers->data[j];
            if (strCompare(t->fromStation->id, station->id) == 0) {
                system->graph->adjacencyArray[i][idx].to = t->toStation;
                system->graph->adjacencyArray[i][idx].weight = t->transferTime;
                system->graph->adjacencyArray[i][idx].edgeType = 1;
                system->graph->adjacencyArray[i][idx].line = 0;
                idx++;
            }
            if (strCompare(t->toStation->id, station->id) == 0) {
                system->graph->adjacencyArray[i][idx].to = t->fromStation;
                system->graph->adjacencyArray[i][idx].weight = t->transferTime;
                system->graph->adjacencyArray[i][idx].edgeType = 1;
                system->graph->adjacencyArray[i][idx].line = 0;
                idx++;
            }
        }
    }
}

// ==================== 优化的最短路径 ====================
struct RoutePlan* findShortestPath(struct MetroSystem* system,
    struct Station* start, struct Station* end,
    enum RouteType type, double* totalTime) {
    if (!system || !start || !end) return 0;
    
    struct RoutePlan* cached = cacheGet(system->routeCache, start->id, end->id);
    if (cached) {
        *totalTime = cached->totalTime;
        return cached;
    }
    
    int stationCount = system->stations->size;
    double* dist = (double*)myMalloc(sizeof(double) * stationCount);
    double* fScore = (double*)myMalloc(sizeof(double) * stationCount);
    struct Station** prev = (struct Station**)myMalloc(sizeof(struct Station*) * stationCount);
    int* visited = (int*)myMalloc(sizeof(int) * stationCount);
    
    int startIdx = (long long)hashMapGet(system->graph->stationToIndex, start->id);
    int endIdx = (long long)hashMapGet(system->graph->stationToIndex, end->id);
    
    for (int i = 0; i < stationCount; i++) {
        dist[i] = INFINITY;
        fScore[i] = INFINITY;
        prev[i] = 0;
        visited[i] = 0;
    }
    
    dist[startIdx] = 0;
    fScore[startIdx] = heuristic(start, end);
    
    system->dijkstraHeap->size = 0;
    heapPush(system->dijkstraHeap, start, fScore[startIdx]);
    
    while (!heapIsEmpty(system->dijkstraHeap)) {
        struct PQNode* node = heapPop(system->dijkstraHeap);
        struct Station* u = node->station;
        int uIdx = (long long)hashMapGet(system->graph->stationToIndex, u->id);
        myFree(node);
        
        if (visited[uIdx]) continue;
        visited[uIdx] = 1;
        
        if (uIdx == endIdx) {
            *totalTime = dist[uIdx];
            break;
        }
        
        int edgeCount = system->graph->edgeCounts[uIdx];
        struct Edge* edges = system->graph->adjacencyArray[uIdx];
        
        for (int i = 0; i < edgeCount; i++) {
            struct Station* v = edges[i].to;
            int vIdx = (long long)hashMapGet(system->graph->stationToIndex, v->id);
            double newDist = dist[uIdx] + edges[i].weight;
            
            if (newDist < dist[vIdx]) {
                dist[vIdx] = newDist;
                prev[vIdx] = u;
                double newFScore = newDist + heuristic(v, end);
                fScore[vIdx] = newFScore;
                heapPush(system->dijkstraHeap, v, newFScore);
            }
        }
    }
    
    if (prev[endIdx] == 0) {
        myFree(dist); myFree(fScore); myFree(prev); myFree(visited);
        return 0;
    }
    
    struct RoutePlan* plan = (struct RoutePlan*)myMalloc(sizeof(struct RoutePlan));
    plan->segments = (struct ArrayList_RouteSegments*)myMalloc(sizeof(struct ArrayList_RouteSegments));
    initArrayList_RouteSegments(plan->segments);
    plan->totalTime = *totalTime;
    plan->totalDistance = *totalTime * 0.8;
    plan->transferCount = 0;
    plan->type = type;
    
    struct RouteSegment segment;
    segment.type = SEGMENT_TRAIN;
    segment.startStation = start;
    segment.endStation = end;
    segment.time = *totalTime;
    segment.distance = plan->totalDistance;
    segment.stationCount = 0;
    segment.line = 0;
    segment.startIndex = 0;
    segment.endIndex = 0;
    segment.intermediateStations = (struct ArrayList_Stations*)myMalloc(sizeof(struct ArrayList_Stations));
    initArrayList_Stations(segment.intermediateStations);
    
    addToArrayList_RouteSegments(plan->segments, segment);
    
    plan->price.basePrice = 2.0;
    plan->price.totalPrice = 2.0;
    plan->price.discount = 1.0;
    plan->price.isFree = 0;
    strCopy(plan->price.discountReason, "无折扣");
    strCopy(plan->description, "最短路径方案");
    
    cachePut(system->routeCache, start->id, end->id, plan);
    
    myFree(dist); myFree(fScore); myFree(prev); myFree(visited);
    return plan;
}

// ==================== 优化的站点查找 ====================
struct Station* getStationById(struct MetroSystem* system, const char* id) {
    if (!system || !id) return 0;
    return (struct Station*)hashMapGet(system->stationHashMap, id);
}

// ==================== 票价计算 ====================
struct TicketPrice calculatePrice(struct MetroSystem* system,
    struct RoutePlan* route,
    struct Passenger* passenger) {
    struct TicketPrice price;
    price.basePrice = 2.0;
    price.discount = 1.0;
    price.isFree = 0;
    
    if (route->totalDistance > 6) {
        price.basePrice = 2.0 + (route->totalDistance - 6) * 0.5;
    }
    if (price.basePrice > 10) price.basePrice = 10;
    
    double minDiscount = 1.0;
    char reason[MAX_DESC_LEN] = "";
    
    if (passenger->isStudent) { minDiscount = 0.5; strCopy(reason, "学生优惠5折"); }
    if (passenger->isElderly && 0.6 < minDiscount) { minDiscount = 0.6; strCopy(reason, "老人优惠6折"); }
    if (passenger->isDisabled && 0.3 < minDiscount) { minDiscount = 0.3; strCopy(reason, "残疾人优惠3折"); }
    if (passenger->isMilitary && 0.4 < minDiscount) { minDiscount = 0.4; strCopy(reason, "军人优惠4折"); }
    if (passenger->hasMonthlyPass && 0.7 < minDiscount) { minDiscount = 0.7; strCopy(reason, "月票7折"); }
    
    price.discount = minDiscount;
    strCopy(price.discountReason, reason);
    price.totalPrice = price.basePrice * price.discount;
    
    if (price.totalPrice < 0.01) { price.totalPrice = 0; price.isFree = 1; }
    return price;
}

// ==================== 实时到站 ====================
struct ArrayList_ArrivalInfos* getRealTimeArrivals(struct RealTimeTracker* tracker,
    struct Station* station, struct Line* line) {
    if (!tracker || !station) return 0;
    
    struct ArrayList_ArrivalInfos* results = (struct ArrayList_ArrivalInfos*)myMalloc(sizeof(struct ArrayList_ArrivalInfos));
    initArrayList_ArrivalInfos(results);
    
    for (int i = 0; i < tracker->trainPositions->size; i++) {
        struct TrainPosition* train = &tracker->trainPositions->data[i];
        if (line && strCompare(train->line->id, line->id) != 0) continue;
        if (train->nextStation && strCompare(train->nextStation->id, station->id) == 0) {
            struct ArrivalInfo info;
            info.station = station;
            info.line = train->line;
            info.direction = train->direction;
            strCopy(info.trainId, train->trainId);
            double remainingTime = (1 - train->progress) * 3.0;
            info.minutesToArrive = (int)(remainingTime + 0.5);
            info.isApproaching = info.minutesToArrive <= 2;
            addToArrayList_ArrivalInfos(results, info);
        }
    }
    return results;
}

// ==================== 拥挤度 ====================
enum CrowdLevel getStationCrowdLevel(struct CrowdManager* manager, struct Station* station) {
    if (!manager || !station) return CROWD_EMPTY;
    for (int i = 0; i < manager->stationCrowds->size; i++) {
        if (strCompare(manager->stationCrowds->data[i].station->id, station->id) == 0) {
            return manager->stationCrowds->data[i].level;
        }
    }
    return CROWD_MEDIUM;
}

// ==================== 批量查询拥挤度 ====================
struct ArrayList_StationCrowds* getBatchStationCrowdLevels(struct CrowdManager* manager,
    struct ArrayList_Stations* stations) {
    if (!manager || !stations) return 0;
    
    struct ArrayList_StationCrowds* results = (struct ArrayList_StationCrowds*)myMalloc(sizeof(struct ArrayList_StationCrowds));
    initArrayList_StationCrowds(results);
    
    struct HashMap* crowdMap = (struct HashMap*)myMalloc(sizeof(struct HashMap));
    for (int i = 0; i < manager->stationCrowds->size; i++) {
        hashMapPut(crowdMap, manager->stationCrowds->data[i].station->id, &manager->stationCrowds->data[i]);
    }
    
    for (int i = 0; i < stations->size; i++) {
        struct StationCrowd* crowd = (struct StationCrowd*)hashMapGet(crowdMap, stations->data[i]->id);
        if (crowd) {
            addToArrayList_StationCrowds(results, *crowd);
        }
    }
    
    return results;
}

// ==================== 位置共享 ====================
void shareLocation(struct LocationSharingManager* manager, struct User* user,
    double lat, double lon, int speed) {
    if (!manager || !user) return;
    
    int found = 0;
    for (int i = 0; i < manager->currentLocations->size; i++) {
        if (strCompare(manager->currentLocations->data[i].user->userId, user->userId) == 0) {
            manager->currentLocations->data[i].latitude = lat;
            manager->currentLocations->data[i].longitude = lon;
            manager->currentLocations->data[i].speed = speed;
            found = 1;
            break;
        }
    }
    
    if (!found) {
        struct SharedLocation loc;
        loc.user = user;
        loc.latitude = lat;
        loc.longitude = lon;
        loc.speed = speed;
        strCopy(loc.status, "正常");
        if (manager->currentLocations->size < manager->currentLocations->capacity) {
            manager->currentLocations->data[manager->currentLocations->size++] = loc;
        }
    }
}

struct SharedLocation* getFriendLocation(struct LocationSharingManager* manager,
    struct User* requester, struct User* target) {
    if (!manager || !requester || !target) return 0;
    
    int hasPermission = 0;
    for (int i = 0; i < manager->activeSessions->size; i++) {
        struct LocationShareSession* session = &manager->activeSessions->data[i];
        if (strCompare(session->owner->userId, target->userId) == 0 && session->isActive) {
            for (int j = 0; j < session->participants->size; j++) {
                if (strCompare(session->participants->data[j].userId, requester->userId) == 0) {
                    hasPermission = 1;
                    break;
                }
            }
        }
    }
    
    if (!hasPermission) return 0;
    
    for (int i = 0; i < manager->currentLocations->size; i++) {
        if (strCompare(manager->currentLocations->data[i].user->userId, target->userId) == 0) {
            return &manager->currentLocations->data[i];
        }
    }
    return 0;
}

// ==================== 附近热点 ====================
struct ArrayList_Hotspots* getNearbyHotspots(struct MetroSystem* system,
    double lat, double lon, double radius) {
    if (!system) return 0;
    
    struct ArrayList_Hotspots* nearby = (struct ArrayList_Hotspots*)myMalloc(sizeof(struct ArrayList_Hotspots));
    initArrayList_Hotspots(nearby);
    
    if (!system->map->hotspots) return nearby;
    
    for (int i = 0; i < system->map->hotspots->size; i++) {
        struct Hotspot* hotspot = &system->map->hotspots->data[i];
        double dist = calculateDistance(lat, lon, hotspot->latitude, hotspot->longitude);
        if (dist <= radius) addToArrayList_Hotspots(nearby, *hotspot);
    }
    return nearby;
}

// ==================== 添加数据 ====================
void addLine(struct MetroSystem* system, struct Line* line) {
    if (!system || !line) return;
    addToArrayList_Lines(system->lines, line);
}

void addStation(struct MetroSystem* system, struct Station* station) {
    if (!system || !station) return;
    addToArrayList_Stations(system->stations, station);
    hashMapPut(system->stationHashMap, station->id, station);
}

void addTransfer(struct MetroSystem* system, struct Transfer transfer) {
    if (!system) return;
    addToArrayList_Transfers(system->transfers, transfer);
}

// ==================== 初始化系统 ====================
void initMetroSystem(struct MetroSystem* system) {
    if (!system) return;
    
    system->lines = (struct ArrayList_Lines*)myMalloc(sizeof(struct ArrayList_Lines));
    system->stations = (struct ArrayList_Stations*)myMalloc(sizeof(struct ArrayList_Stations));
    system->transfers = (struct ArrayList_Transfers*)myMalloc(sizeof(struct ArrayList_Transfers));
    system->caseManager = (struct SpecialCaseManager*)myMalloc(sizeof(struct SpecialCaseManager));
    system->crowdManager = (struct CrowdManager*)myMalloc(sizeof(struct CrowdManager));
    system->locationManager = (struct LocationSharingManager*)myMalloc(sizeof(struct LocationSharingManager));
    system->tracker = (struct RealTimeTracker*)myMalloc(sizeof(struct RealTimeTracker));
    system->map = (struct MetroMap*)myMalloc(sizeof(struct MetroMap));
    
    initArrayList_Lines(system->lines);
    initArrayList_Stations(system->stations);
    initArrayList_Transfers(system->transfers);
    
    system->caseManager->activeCases = (struct ArrayList_SpecialCases*)myMalloc(sizeof(struct ArrayList_SpecialCases));
    initArrayList_SpecialCases(system->caseManager->activeCases);
    
    system->crowdManager->stationCrowds = (struct ArrayList_StationCrowds*)myMalloc(sizeof(struct ArrayList_StationCrowds));
    system->crowdManager->lineCrowds = (struct ArrayList_LineCrowds*)myMalloc(sizeof(struct ArrayList_LineCrowds));
    system->crowdManager->predictions = (struct ArrayList_CrowdPredictions*)myMalloc(sizeof(struct ArrayList_CrowdPredictions));
    initArrayList_StationCrowds(system->crowdManager->stationCrowds);
    initArrayList_LineCrowds(system->crowdManager->lineCrowds);
    initArrayList_CrowdPredictions(system->crowdManager->predictions);
    
    system->tracker->trainPositions = (struct ArrayList_TrainPositions*)myMalloc(sizeof(struct ArrayList_TrainPositions));
    system->tracker->arrivalCache = (struct ArrayList_ArrivalInfos*)myMalloc(sizeof(struct ArrayList_ArrivalInfos));
    initArrayList_TrainPositions(system->tracker->trainPositions);
    initArrayList_ArrivalInfos(system->tracker->arrivalCache);
    
    system->locationManager->users = (struct ArrayList_Users*)myMalloc(sizeof(struct ArrayList_Users));
    system->locationManager->activeSessions = (struct ArrayList_LocationShareSessions*)myMalloc(sizeof(struct ArrayList_LocationShareSessions));
    system->locationManager->currentLocations = (struct ArrayList_SharedLocations*)myMalloc(sizeof(struct ArrayList_SharedLocations));
    system->locationManager->alerts = (struct ArrayList_SafetyAlerts*)myMalloc(sizeof(struct ArrayList_SafetyAlerts));
    initArrayList_Users(system->locationManager->users);
    initArrayList_LocationShareSessions(system->locationManager->activeSessions);
    initArrayList_SharedLocations(system->locationManager->currentLocations);
    initArrayList_SafetyAlerts(system->locationManager->alerts);
    
    system->map->stationVisuals = (struct ArrayList_StationVisuals*)myMalloc(sizeof(struct ArrayList_StationVisuals));
    system->map->lineVisuals = (struct ArrayList_LineVisuals*)myMalloc(sizeof(struct ArrayList_LineVisuals));
    system->map->hotspots = (struct ArrayList_Hotspots*)myMalloc(sizeof(struct ArrayList_Hotspots));
    initArrayList_StationVisuals(system->map->stationVisuals);
    initArrayList_LineVisuals(system->map->lineVisuals);
    initArrayList_Hotspots(system->map->hotspots);
    
    // 优化初始化
    system->stationHashMap = (struct HashMap*)myMalloc(sizeof(struct HashMap));
    system->routeCache = createLRUCache(CACHE_SIZE);
    system->dijkstraHeap = createHeap(1024);
    system->graph = 0;
}

// ==================== 完成构建后调用 ====================
void finalizeMetroSystem(struct MetroSystem* system) {
    if (!system) return;
    buildPrecomputedGraph(system);
}

