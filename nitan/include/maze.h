// maze.h

// 迷宮房間原型文件
#define ROOM_FILE       "/inherit/room/maze"

// 迷宮出口通向的房間
#define ROOM_EXIT_FILE  "/d/city/wumiao"

// 迷宮寶箱的文件
#define BAOXIANG_OB     "/clone/misc/baoxiang"

// 迷宮守護進程的心跳間隔
#define HEART_TIME 30           /* 五分鐘檢查一次       */

// 迷宮的生命周期
#define MAZE_LIFT_CYCLE 1800    /* 半個小時             */

// 迷宮的宏定義
#define LENGTH  8               /* 迷宮橫向的房間數量   */
#define HEIGHT  8               /* 迷宮縱向的房間數量   */
#define BOX_NUM 4               /* 迷宮寶箱的數量       */
#define XIANJING_NUM 3          /* 迷宮陷阱的數量       */
#define NORTH   1               /* 朝北方向             */
#define SOUTH   2               /* 朝南方向             */
#define WEST    3               /* 朝西方向             */
#define EAST    4               /* 朝東方向             */
#define IS_ROAD 1               /* 房間位于路線上       */
#define IS_ROOM 2               /* 房間不位于路線上     */
#define CAN_WALK    1           /* 指定方向有出路       */
#define IS_WALL 9               /* 指定方向是牆壁       */
#define NOT_DEFINED 0           /* 尚未初始化           */
#define TO_NORTH    0           /* 迷宮是由南向北       */
#define TO_SOUTH    1           /* 迷宮是由北向南       */
#define TO_WEST     2           /* 迷宮是由東向西       */
#define TO_EAST     3           /* 迷宮是由西向東       */
#define MAP_COMM    1           /* 迷宮地圖是普通模式   */
#define MAP_DEEP    2           /* 迷宮地圖是詳細模式   */
#define MAP_NONE    3           /* 迷宮地圖是關閉模式   */

// 迷宮的陷阱類型
#define BUSY        1           /* 讓玩家BUSY           */
#define TRIP        2           /* 讓玩家摔到別的房間   */
#define LOSTMAP     3           /* 讓迷宮地圖失效       */
#define CHANGEMAP   4           /* 讓迷宮地圖刷新       */
#define WOUND       5           /* 讓玩家受傷           */

// 迷宮的寶箱類型
#define SPECIAL_MAP 1           /* 迷宮地圖變為詳細模式 */ 
#define SPECIAL_DAN 2           /* 仙丹等物品           */
#define JINKUAI     3           /* 金塊等物品           */
#define GOLD        4           /* 黃金                 */
#define OBJ         5           /* 任務物品             */
#define SPECIAL_OBJ 6           /* 好的任務物品         */
#define NPC_SKILL   7           /* 降低殺手的武功       */

void collect_all_maze_information();            /* 將所有的迷宮房間清理     */
void init_line(mapping maze);                   /* 初始化迷宮地圖           */
void init_road(object room, mapping maze);      /* 初始化迷宮路線           */
void init_wall(object room, mapping maze);      /* 給路線上的房間制造岔路   */
object *finish_room(object room, mapping maze); /* 將呆死的房間打通         */
void init_room_exits(mapping maze);             /* 將房間的出口刷新         */
void init_special_room(mapping maze);           /* 給迷宮初始化寶箱和陷阱   */
