// This program is a part of NITAN MudLIB

/******************************************************
 * vrm_server.c                                       *
 * 虛擬的隨機迷宮創造器 (Virtual Random Maze)         *
 *                                                    *
 * Written by Find.                                   *
 * Rewritten by Lonely@nitan.org                      *
 ******************************************************/

/******************************************************
 * 隨機迷宮的產生算法儘量簡單，迷宮的儲存儘量節省記憶 *
 * 體，迷宮房間採用虛擬物件，處理靈活，迷宮房間只有在 *
 * 玩家走到時才會裝進內存，而且迷宮房間也象普通的ROOM *
 * 一樣當一段時間沒有被參考到可以銷燬節省記憶體，當整 *
 * 個迷宮一段時間沒有被參考到可以被完全摧毀，下次再需 *
 * 要的時候會重新建立，又會產生一個新的迷宮。區域巫師 *
 * 寫作隨機迷宮只需規定一些預設的參數如迷宮的單邊長、 *
 * 房間描述、出入口描述，幾十個乃至幾千個房間、路線時 *
 * 時不同的隨機迷宮就建立好了，大大提高了區域寫作效率 *
 * 和遊戲的可玩性。                                   *
 * 此物件目前適合於隨機的迷宮，即：迷宮內房間的描述基 *
 * 本相同，比如一片樹林、一片墳地等，如要此物件創作完 *
 * 整的隨機區域即有一定的情節、一定格局的區域，則需要 *
 * 根據自己的情況規定出迷宮內房間描述的一些規則，使相 *
 * 鄰房間的描述變化合理，房間內物件與描述協調。       *
 * 由於採用virtual object，牽涉到一點安全問題，需要根 *
 * 據自己的系統考量調整。                             *
 * 增加了迷宮生成新的算法，主要用於詳細顯示迷宮的路徑 *
 * 和寶箱以及陷阱等其他功能(by Lonely)。              *
 ******************************************************/

#pragma optimize

#define CENTER          4096    // 正中心的房間
#define TRAP            2048    // 有陷阱的房間
#define BOX             1024    // 有寶箱的房間
#define MAP             512     // 有地圖的房間
#define SPECIAL         256     // 特殊的房間
#define T               128     // 正在處理的房間
#define B               64      // 呆死的房間
#define R               32      // 路線上的房間
#define D               16      // 初始化後的房間
#define N               8       // 向北出口
#define S               4       // 向南出口
#define W               2       // 向西出口
#define E               1       // 向東出口
#define ALL             15      // 所有出口
#define MAX_LONG        100     // 最大邊長

#define RESET           CENTER | TRAP | BOX | MAP | SPECIAL
#define BOX_OB          "/clone/misc/baoxiang"
#define TRAP_ROOM       "/inherit/room/trap"

#define TWO_VALID_LEAVES  // 規定房間最多隻能有兩個出口
#define MAP_COMM    1     // 迷宮地圖是普通模式
#define MAP_DEEP    2     // 迷宮地圖是詳細模式
#define MAP_NONE    3     // 迷宮地圖是關閉模式
#define BUSY        1     // 讓玩家BUSY
#define TRIP        2     // 讓玩家摔到別的房間
#define LOSTMAP     3     // 讓迷宮地圖失效
#define CHANGEMAP   4     // 讓迷宮地圖刷新
#define WOUND       5     // 讓玩家受傷
#define SPECIAL_MAP 1     // 迷宮地圖變為詳細模式
#define SPECIAL_DAN 2     // 仙丹等物品
#define JINKUAI     3     // 金塊等物品
#define GOLD        4     // 黃金
#define OBJ         5     // 任務物品
#define SPECIAL_OBJ 6     // 英雄商店出售的物品
#define NPC_SKILL   7     // 降低NPC的武功

#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_DBASE;

class coordinate{ int x; int y; }
class coordinate *newpath = ({}), *badpath = ({}), *roadpath = ({}),
        enter,/* 入口座標 */
        leave;/* 出口座標 */

nosave string *valid_dirs = ({ "south","north","west","east" });
nosave mapping reverse_dir = ([
"north" : "south",
"south" : "north",
"west"  : "east",
"east"  : "west",
]);

// 全迷宮出口陣列.
nosave mixed *all;
// 迷宮地圖陣列
nosave mixed line, line2;

/***************** 迷宮的一些預設特性：*****************/
nosave int l;                           // 迷宮的單邊長
nosave string *inherit_rooms = ({});    // 迷宮允許繼承的檔案名稱
nosave string *valid_rooms = ({});      // 迷宮可使用的房間文件名 (****)
nosave string entry_dir;                // 迷宮入口方向
nosave string link_entry_dir;           // 迷宮入口與區域的連接方向
nosave string link_entry_room;          // 迷宮入口所連接區域檔案的文件名
private int link_entry_room_x;          // 迷宮入口的x座標
private int link_entry_room_y;          // 迷宮入口的y座標
private int link_entry_room_z;          // 迷宮入口的z座標
nosave string link_exit_dir;            // 迷宮出口與區域的連接方向
nosave string link_exit_room;           // 迷宮出口所連接區域檔案的文件名
nosave string entry_short;              // 迷宮入口的短描述
nosave string entry_desc;               // 迷宮入口的長描述
nosave string exit_short;               // 迷宮出口的短描述
nosave string exit_desc;                // 迷宮出口的長描述
nosave string center_room;              // 迷宮中心位置房間
nosave string *maze_room_desc = ({});   // 迷宮房間的長描述
nosave string maze_room_short;          // 迷宮房間的短描述
nosave int is_outdoors = 0;             // 迷宮房間是否為户外
nosave mixed maze_npcs;                 // 迷宮中的怪物
nosave mixed entry_npcs;                // 迷宮入口的怪物
nosave mixed exit_npcs;                 // 迷宮出口的怪物
nosave string *unique_rooms = ({});     // 迷宮唯一的房間
nosave string *special_rooms = ({});    // 迷宮特殊的房間
private int refresh_delay = 0;          // 迷宮重建時間, default is 0 means no recreation
nosave int is_nodeath = 0;              // 迷宮不死房間
nosave int random_rate = 0;             // 迷宮怪物出現機率
nosave int remove_time = 0;             // 迷宮銷燬時間
nosave int box_num = 0;                 // 迷宮寶箱的數量
nosave int trap_num = 0;                // 迷宮陷阱的數量
nosave int normal_room = 0;
nosave int lonely_create = 0;           // 迷宮創建新模式(Lonely)
/******************* ---- END ---- *********************/

nosave int handle_id;                   // 排程
nosave int return_dir = 0;              // 迷宮入口方向
nosave int map_status = MAP_COMM;       // 迷宮的地圖狀態
nosave int display_coordinate = 1;      // 是否顯示玩家所在的位置
nosave object maze_boss;                // 迷宮裏的BOSS

// 建立標記.
nosave int maze_built = 0;

// 迷宮房間來源轉換開關
nosave int switch_flag = 0;

// 重置全域變量.
protected void refresh_vars();

// 建立迷宮
void create_maze();
void init_line();
varargs void init_maze(object room);
void init_road();
void init_room();
void init_special();

// 選擇隨機出口.
protected varargs int random_out(int x,int y,int n);

// 處理連接.
protected void link_to_north(int x,int y);
protected void link_to_south(int x,int y);
protected void link_to_west(int x,int y);
protected void link_to_east(int x,int y);
protected void init_to_north(int x,int y);
protected void init_to_south(int x,int y);
protected void init_to_west(int x,int y);
protected void init_to_east(int x,int y);
protected mixed init_to_link(int x,int y);

nomask object query_maze_room(string str);
int query_maze_length(){ return l; }
protected string mroom_fname(int x,int y)
{ return sprintf("%s/%d/%d",base_name(this_object()),x,y);}

public mixed query_roadpath() { return roadpath; }
public mixed query_badpath() { return badpath; }
public mixed query_maze_boss() { return objectp(maze_boss) ? maze_boss : 0; }
public int query_map_status() { return map_status; }
public int query_remove_time() { return remove_time; }
public int is_maze() { return 1; }
int is_player_in(object room);
protected void refresh_vars() // 重置全域變量.
{
        newpath = ({});
        badpath = ({});
        roadpath = ({});
        all = 0;
        line = 0;
        line2 = 0;
}

// 對一些必設參數的合法性檢查
protected int check_vars()
{
        int i,n;

        if( (l < 5) || l > MAX_LONG )
                return 0;

        if( !switch_flag ) {
                if( !stringp(entry_dir) || (member_array(entry_dir,valid_dirs) == -1) )
                        return 0;

                maze_room_desc -=({0});
                if( !n = sizeof(maze_room_desc) )
                        return 0;

                for( i=0;i<n;i++ )
                        if( !stringp(maze_room_desc[i]) || (maze_room_desc[i] == "") )
                                return 0;

                if( !stringp(maze_room_short) || (maze_room_short == "") )
                        return 0;
        } else {
                valid_rooms -=({0});
                if( !n = sizeof(valid_rooms) )
                        return 0;
                for( i=0;i<n;i++ )
                        if( !stringp(valid_rooms[i]) || (valid_rooms[i] == "") )
                                return 0;
        }
        /*
        if(!stringp(link_entry_dir) || (member_array(link_entry_dir,valid_dirs) == -1) )
                return 0;

        if(!stringp(link_exit_dir) || (member_array(link_exit_dir,valid_dirs) == -1) )
                return 0;
        */

        inherit_rooms -=({0});
        if( !n = sizeof(inherit_rooms) )
                return 0;

        for( i=0;i<n;i++ )
                if( !stringp(inherit_rooms[i]) || (inherit_rooms[i] == "") )
                        return 0;
        /*
        if( !stringp(link_entry_room) || (link_entry_room == "") )
                return 0;

        if( !stringp(link_exit_room) || (link_exit_room == "") )
                return 0;
        */
        if( !stringp(entry_short) || (entry_short == "") )
                return 0;

        if( !stringp(exit_short) || (exit_short == "") )
                return 0;

        if( !stringp(entry_desc) || (entry_desc == "") )
                return 0;

        if( !stringp(exit_desc) || (exit_desc == "") )
                return 0;

        return 1;
}

protected varargs int random_out(int x,int y,int n,int t) // 選擇隨機出口函數.
{
        int *outs = ({}), retn = 0;

        // The west room is (x-1,y)
        if( n&W
        && ((x-1) >= 0)
        && !(all[x-1][y]&D) )
        {
                if( !t ) {
                        if( lonely_create > 0 ) {
                                // 迷宮的路徑延伸方向不能有返回入口的方向
                                if( !(return_dir&W)
                                && (y != leave->y || x > leave->x) )
                                        outs += ({ W });
                        } else
                                outs += ({ W });
                } else {
                        // 一半的機率岔路這個方向不通
                        if( random(2) == 1 )
                                outs += ({ W });
                }
        }

        // The east room is (x+1,y)
        if( n&E
        && ((x+1) < l)
        && !(all[x+1][y]&D) )
        {
                if( !t ) {
                        if( lonely_create > 0 ) {
                                if( !(return_dir&E)
                                && (y != leave->y || x < leave->x) )
                                        outs += ({ E });
                        } else
                                outs += ({ E });
                } else {
                        if( random(2) == 1 )
                                outs += ({ E });
                }
        }

        // The south room is (x,y-1)
        if( n&S
        && ((y-1) >= 0)
        && !(all[x][y-1]&D) )
        {
                if( !t ) {
                        if( lonely_create > 0 ) {
                                if( !(return_dir&S)
                                && (x != leave->x || y > leave->y) )
                                        outs += ({ S });
                        } else
                                outs += ({ S });
                } else {
                        if( random(2) == 1 )
                                outs += ({ S });
                }
        }

        // The north room is (x,y+1)
        if( n&N
        && ((y+1) < l)
        && !(all[x][y+1]&D) )
        {
                if( !t ) {
                        if( lonely_create > 0 ) {
                                if( !(return_dir&N)
                                && (x != leave->x || y < leave->y) )
                                        outs += ({ N });
                        } else
                                outs += ({ N });
                } else {
                        if( random(2) == 1 )
                                outs += ({ N });
                }
        }

#ifdef TWO_VALID_LEAVES
        // 如果有三個出口,隨機關閉一個.
        if( sizeof(outs) >= 3 )
                outs -= ({ outs[random(sizeof(outs))] });
#endif

        if( !t ) {
                // 這裏區分創建的迷宮的類型
                if( lonely_create > 0 ) {
                        while( sizeof(outs) > 1 )
                                outs -= ({ outs[random(sizeof(outs))] });
                }
        }

        for( int i=0;i<sizeof(outs);i++ )
                retn |= outs[i];

        return retn;
}

void create_maze()
{
        int i;

        refresh_vars();         // 重置全域變量.
        if( !check_vars() )     // 對一些預設變量進行檢查。
                return;

        all = allocate(l);
        for( i=0;i<l;i++ )
                all[i] = allocate(l);   //建立數組.

        enter = new(class coordinate);
        leave = new(class coordinate);

        switch( entry_dir ) {
                case "south":
                        // enter 入口座標.
                        return_dir |= S;         // 路徑往入口的方向
                        enter->x = to_int(l/2); // 取中迷宮比較平衡
                        enter->y = 0;
                        all[enter->x][enter->y] |= S; // | 是 位 操作的或
                        all[enter->x][enter->y] |= D;
                        if( lonely_create > 0 ) {     // 詳細地圖模式則先要確定出口房間
                                leave->x = random(l);
                                leave->y = l-1;
                        }
                        break;
                case "north":
                        return_dir |= N;
                        enter->x = to_int(l/2);
                        enter->y = l-1;
                        all[enter->x][enter->y] |= N;
                        all[enter->x][enter->y] |= D;
                        if( lonely_create > 0 ) {
                                leave->x = random(l);
                                leave->y = 0;
                        }
                        break;
                case "west":
                        return_dir |= W;
                        enter->y = to_int(l/2);
                        enter->x = 0;
                        all[enter->x][enter->y] |= W;
                        all[enter->x][enter->y] |= D;
                        if( lonely_create > 0 ) {
                                leave->x = l-1;
                                leave->y = random(l);
                        }
                        break;
                case "east":
                        return_dir |= E;
                        enter->y = to_int(l/2);
                        enter->x = l-1;
                        all[enter->x][enter->y] |= E;
                        all[enter->x][enter->y] |= D;
                        if( lonely_create > 0 ) {
                                leave->x = 0;
                                leave->y = random(l);
                        }
                        break;
        }

        // 給迷宮分佈寶箱和陷阱
        init_special();

        // 創建迷宮佈局
        init_maze();

        // 迷宮定時刷新
        if( refresh_delay > 0 )
                SCHEDULE_D->set_event(refresh_delay, 1, this_object(), "refresh_maze");
}

varargs void init_maze(object room)
{
        int i, x, y, exits;
        class coordinate temp, *valid_leaves = ({});
        string file, fname = base_name(this_object());
        object *temp_rooms = ({}), maze;

        if( objectp(room) ) {
                if( objectp(maze_boss) ) {
                        file = base_name(environment(maze_boss));
                        maze_boss->move(VOID_OB);
                }
                for( x=0;x<l;x++ ) {
                        for( y=0;y<l;y++ ) {
                                all[x][y] &= RESET; // 重新部分數據初始化
                                if( objectp(maze = find_object(sprintf("%s/%d/%d",fname,x,y))) ) {
                                        if( is_player_in(maze) ) {
                                                tell_room(maze, HIR "你聽到陣陣沉悶的聲音從地下響起...\n"
                                                                HIR "只見四周光影晃動，整個房間似乎在快速移動，等一切安靜下來，周遭景象似乎有所改變。\n" NOR);
                                                delete("exits", maze);
                                                temp_rooms += ({ maze });
                                        } else
                                                destruct(maze);
                                }
                        }
                }
                if( maze = find_object(sprintf("%s/entry",fname)) )
                        destruct(maze);
                if( maze = find_object(sprintf("%s/exit",fname)) )
                        destruct(maze);

                special_rooms = copy(unique_rooms);

                switch( entry_dir ) {
                case "south":
                        all[enter->x][enter->y] |= S; // | 是 位 操作的或
                        all[enter->x][enter->y] |= D;
                        break;
                case "north":
                        all[enter->x][enter->y] |= N;
                        all[enter->x][enter->y] |= D;
                        break;
                case "west":
                        all[enter->x][enter->y] |= W;
                        all[enter->x][enter->y] |= D;
                        break;
                case "east":
                        all[enter->x][enter->y] |= E;
                        all[enter->x][enter->y] |= D;
                        break;
                }
        }

        // 初始化地圖
        init_line();
        // 初始化路徑
        init_road();
        // 製造岔路及打通所有其他房間
        init_room();

        if( !lonely_create ) {
                switch( entry_dir )
                {
                case "west":
                        for( i=0;i<l;i++ )
                                if( all[l-1][i] ) {
                                        temp = new(class coordinate);
                                        temp->x = l-1;
                                        temp->y = i;
                                        valid_leaves += ({temp});
                                }
                        break;
                case "east":
                        for( i=0;i<l;i++ )
                                if( all[0][i] ) {
                                        temp = new(class coordinate);
                                        temp->x = 0;
                                        temp->y = i;
                                        valid_leaves += ({temp});
                                }
                        break;
                case "south":
                        for( i=0;i<l;i++ )
                                if( all[i][l-1] ) {
                                        temp = new(class coordinate);
                                        temp->x = i;
                                        temp->y = l-1;
                                        valid_leaves += ({temp});
                                }
                        break;
                case "north":
                        for( i=0;i<l;i++ )
                                if( all[i][0] ) {
                                        temp = new(class coordinate);
                                        temp->x = i;
                                        temp->y = 0;
                                        valid_leaves += ({temp});
                                }
                        break;
                }

                if( !(i=sizeof(valid_leaves)) ) { // 沒有出口 須重新建立
                        //log_file("static/maze",sprintf("%O\n",all));
                        call_other(this_object(),"create_maze");
                        return;
                }

                if( i == 1 )
                        leave = valid_leaves[0];
                else
                        leave = valid_leaves[random(i)]; // 隨機選一個.
        }

        switch (entry_dir)
        {
                case "south":
                        all[leave->x][leave->y] |= N;
                        break;
                case "north":
                        all[leave->x][leave->y] |= S;
                        break;
                case "west":
                        all[leave->x][leave->y] |= E;
                        break;
                case "east":
                        all[leave->x][leave->y] |= W;
                        break;
        }

        line[leave->x*2+1][leave->y*2+1] =  HBRED "  " NOR;
        line2[leave->x*2+1][leave->y*2+1] = HBRED "  " NOR;

        // 迷宮創建完畢。
        maze_built = 1;

        if( objectp(room) || sizeof(temp_rooms) > 0 ) {
                if( objectp(maze_boss) )
                        maze_boss->move(load_object(file));

                for( i=0;i<sizeof(temp_rooms);i++ ) {
                        maze = temp_rooms[i];
                        if( sscanf(base_name(maze), fname+"/%d/%d", x, y) != 2 )
                                return;

                        if( !exits = all[x][y] ) return;

                        if( exits&W ) set("exits/west",mroom_fname(x-1,y),maze);
                        else    set("exits/west",mroom_fname(x,y), maze);

                        if( exits&E ) set("exits/east",mroom_fname(x+1,y),maze);
                        else    set("exits/east",mroom_fname(x,y),maze);

                        if( exits&N ) set("exits/north",mroom_fname(x,y+1),maze);
                        else    set("exits/north",mroom_fname(x,y),maze);

                        if( exits&S ) set("exits/south",mroom_fname(x,y-1),maze);
                        else    set("exits/south",mroom_fname(x,y),maze);

                        if( x == enter->x && y == enter->y )
                                set(sprintf("exits/%s",entry_dir),
                                        sprintf("%s/entry",fname), maze);
                        if( x == leave->x && y == leave->y )
                                set(sprintf("exits/%s",reverse_dir[entry_dir]),
                                        sprintf("%s/exit",fname), maze);
                }
        }
}

void init_road()
{

        int x, y, out, numb;
        class coordinate *valid_leaves = ({});

        // 存入待處理隊列.
        newpath += ({ enter });
        roadpath += ({ enter });

        // 進入主循環.
        do {
                // 進行一些監測與初始化.
                if( !(numb=sizeof(newpath)) )
                        continue;
                numb = random(numb);
                reset_eval_cost();
                x = newpath[numb]->x;
                y = newpath[numb]->y;

                // 如果有三個可能的出口隨機關閉一個出口:
                out = ALL^(all[x][y]); // ^ 是 異或 運算
                out = random_out(x,y,out);

                if( !out ) { // 沒有可能的出口了.
                        newpath -= ({ newpath[numb] });
                        continue;
                }

                // 處理連接.
                if( out&W ) link_to_west(x,y);
                if( out&E ) link_to_east(x,y);
                if( out&N ) link_to_north(x,y);
                if( out&S ) link_to_south(x,y);

                // 當前房間處理完畢.
                newpath -= ({ newpath[numb] });
        }
        while( sizeof(newpath) );
}

void init_room()
{
        int i, j, x, y, out, numb, flag;
        class coordinate *valid_leaves = ({});
        //class coordinate tmp1, tmp2;
        mixed deadroom;
        mixed *alldead = ({});

        if( !lonely_create ) return;

        // 給路線上的房間製造岔路
        do {
                // 進行一些監測與初始化.
                if( !(numb=sizeof(roadpath)) )
                        continue;
                numb = random(numb);
                reset_eval_cost();
                x = roadpath[numb]->x;
                y = roadpath[numb]->y;

                out = ALL^(all[x][y]); // ^ 是 異或 運算
                out = random_out(x,y,out,1);

                if( !out ) { // 沒有可能的出口了.
                        roadpath -= ({ roadpath[numb] });
                        continue;
                }

                // 處理連接.
                if( out&W ) init_to_west(x,y);
                if( out&E ) init_to_east(x,y);
                if( out&N ) init_to_north(x,y);
                if( out&S ) init_to_south(x,y);

                // 當前房間處理完畢.
                roadpath -= ({ roadpath[numb] });
        }
        while( sizeof(roadpath) );

        // 打通所有沒有連接的房間
        for( i=0;i<l;i++ ) {
                for( j=0;j<l;j++ ) {
                        if( !(all[i][j]&D) ) {
                                // 處理的方式有將壞死的房間直接連接到正常房間(降低迷宮複雜度不採用)
                                // 或者是將壞死的房間隨機連接,有可能會是死衚衕,因此需要二次處理
                                deadroom = init_to_link(i,j);
                                if( sizeof(deadroom) > 0 )
                                        alldead += ({ deadroom });
                        }
                }
        }

        while( sizeof(alldead) ) { // 二次循環處理壞死的房間,直接連接到正常的房間
                for( i=0;i<sizeof(alldead);i++ ) {
                        flag = 0;
                        for( j=0;j<sizeof(alldead[i]);j++ ) {
/*
                                tmp1 = alldead[i][j];
                                x = tmp1->x;
                                y = tmp1->y;
*/
                                x = (alldead[i][j])->x;
                                y = (alldead[i][j])->y;
                                if( ((x-1) >= 0)
                                && !(all[x][y]&W)
                                && !(all[x-1][y]&B) ) {
                                        all[x][y] |= W;
                                        all[x-1][y] |= E;
                                        line[x*2][y*2+1] =  "  ";
                                        line2[x*2][y*2+1] = "  ";
                                        flag = 1;
                                        break;
                                }
                                if( ((x+1) < l)
                                && !(all[x][y]&E)
                                && !(all[x+1][y]&B) )  {
                                        all[x][y] |= E;
                                        all[x+1][y] |= W;
                                        line[x*2+2][y*2+1] =  "  ";
                                        line2[x*2+2][y*2+1] = "  ";
                                        flag = 1;
                                        break;
                                }
                                if( ((y+1) < l)
                                && !(all[x][y]&N)
                                && !(all[x][y+1]&B) )  {
                                        all[x][y] |= N;
                                        all[x][y+1] |= S;
                                        line[x*2+1][y*2+2] =  "  ";
                                        line2[x*2+1][y*2+2] = "  ";
                                        flag = 1;
                                        break;
                                }
                                if( ((y-1) >= 0)
                                && !(all[x][y]&S)
                                && !(all[x][y-1]&B) )  {
                                        all[x][y] |= S;
                                        all[x][y-1] |= N;
                                        line[x*2+1][y*2] =  "  ";
                                        line2[x*2+1][y*2] = "  ";
                                        flag = 1;
                                        break;
                                }
                        }

                        if( flag ) {
                                for( int k=0;k<sizeof(alldead[i]);k++ ) {
/*
                                        tmp2 = alldead[i][k];
                                        x = tmp2->x;
                                        y = tmp2->y;
*/
                                        x = (alldead[i][k])->x;
                                        y = (alldead[i][k])->y;
                                        all[x][y] ^= B;
                                        for( int n=0;n<sizeof(badpath);n++ ) {
                                                if( badpath[n]->x == x && badpath[n]->y == y )
                                                        badpath[n] = 0;
                                        }
                                        badpath -= ({ 0 });
                                }
                                alldead[i] = 0;
                        }
                }
                alldead -= ({ 0 });
        }

        if( sizeof(badpath) )
                log_file( "static/maze", sprintf("有%d個呆死的房間。\n",
                          sizeof(badpath)) );
}

void remove_maze()
{
        object room;
        /*
        string fname = base_name(this_object());
        int x,y;

        if( handle_id )
                SCHEDULE_D->delete_event(handle_id);

        for( x=0;x<l;x++ )
                for( y=0;y<l;y++ )
                        if( objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))) )
                                destruct(room);
        if( room = find_object(sprintf("%s/entry",fname)) )
                destruct(room);
        if( room = find_object(sprintf("%s/exit",fname)) )
                destruct(room);
        */
        if( room = find_object(sprintf("%senter.c",base_dir(this_object()))) )
                destruct(room);
        if( room = find_object(sprintf("%sleave.c",base_dir(this_object()))) )
                destruct(room);

        destruct(this_object());
}

// 設置迷宮銷燬時間
void set_remove_time(int t)
{
        remove_time = time() + t;
        handle_id = SCHEDULE_D->set_event(t, 0, this_object(), "remove_maze");
}

protected void link_to_west(int x, int y)        // The west room is (x-1,y)
{
        class coordinate temp;

        // 已經到達了迷宮出口
        if( x == leave->x && y == leave->y ) {
                line[x*2+1][y*2+1] =  HBRED "  " NOR;
                line2[x*2+1][y*2+1] = HBRED "  " NOR;
                return;
        }

        temp = new(class coordinate);
        temp->x = x-1;
        temp->y = y;

        // 西面的房間已經於 path 中,或者 已在待處理列表 newpath 中.
        if( all[temp->x][temp->y]&D )
                return;

        // 迷宮入口
        if( x == enter->x && y == enter->y ) {
                line[x*2+1][y*2+1] =  HBWHT "  " NOR;
                line2[x*2+1][y*2+1] = HBWHT "  " NOR;
        } else {
                // 標上路徑的顏色
                // 如果已經有顏色了，表示有寶箱或者陷阱，不再更改地圖
                if( line[x*2+1][y*2+1] == "  " ) {
                        line[x*2+1][y*2+1] = BGRN "  " NOR;
                }
        }

        all[x][y] |= W;
        all[x][y] |= R;
        all[temp->x][temp->y] |= E;
        all[temp->x][temp->y] |= D;
        newpath += ({ temp });
        roadpath += ({ temp }); // 路徑的房間

        line[x*2][y*2+1] = BGRN "  " NOR;
        line2[x*2][y*2+1] = "  ";
}

protected void link_to_east(int x,int y)        // The east room is (x+1,y)
{
        class coordinate temp;

        // 已經到達了迷宮出口
        if( x == leave->x && y == leave->y ) {
                line[x*2+1][y*2+1] =  HBRED "  " NOR;
                line2[x*2+1][y*2+1] = HBRED "  " NOR;
                return;
        }

        temp = new(class coordinate);
        temp->x = x+1;
        temp->y = y;

        // 東面的房間已經於 path 中,或者 已在待處理列表 newpath 中.
        if( all[temp->x][temp->y]&D )
                return;

        // 迷宮入口
        if( x == enter->x && y == enter->y ) {
                line[x*2+1][y*2+1] =  HBWHT "  " NOR;
                line2[x*2+1][y*2+1] = HBWHT "  " NOR;
        } else {
                // 如果已經有顏色了，表示有寶箱或者陷阱，不再更改地圖
                if( line[x*2+1][y*2+1] == "  " ) {
                        line[x*2+1][y*2+1] = BGRN "  " NOR;
                }
        }

        all[x][y] |= E;
        all[x][y] |= R;
        all[temp->x][temp->y] |= W;
        all[temp->x][temp->y] |= D;
        newpath += ({ temp });
        roadpath += ({ temp });

        line[x*2+2][y*2+1] = BGRN "  " NOR;
        line2[x*2+2][y*2+1] = "  ";
}

protected void link_to_south(int x,int y)       // The south room is (x,y-1)
{
        class coordinate temp;

        // 已經到達了迷宮出口
        if( x == leave->x && y == leave->y ) {
                line[x*2+1][y*2+1] =  HBRED "  " NOR;
                line2[x*2+1][y*2+1] = HBRED "  " NOR;
                return;
        }

        temp = new(class coordinate);
        temp->x = x;
        temp->y = y-1;

        // 南端的房間已經於 path 中,或者 已在待處理列表 newpath 中.
        if( all[temp->x][temp->y]&D )
                return;

        // 迷宮入口
        if( x == enter->x && y == enter->y ) {
                line[x*2+1][y*2+1] =  HBWHT "  " NOR;
                line2[x*2+1][y*2+1] = HBWHT "  " NOR;
        } else {
                // 如果已經有顏色了，表示有寶箱或者陷阱，不再更改地圖
                if( line[x*2+1][y*2+1] == "  " ) {
                        line[x*2+1][y*2+1] = BGRN "  " NOR;
                }
        }

        all[x][y] |= S;
        all[x][y] |= R;
        all[temp->x][temp->y] |= N;
        all[temp->x][temp->y] |= D;
        newpath += ({ temp });
        roadpath += ({ temp });

        line[x*2+1][y*2] = BGRN "  " NOR;
        line2[x*2+1][y*2] = "  ";
}

protected void link_to_north(int x,int y)       // The north room is (x,y+1)
{
        class coordinate temp;

        // 已經到達了迷宮出口
        if( x == leave->x && y == leave->y ) {
                line[x*2+1][y*2+1] =  HBRED "  " NOR;
                line2[x*2+1][y*2+1] = HBRED "  " NOR;
                return;
        }

        temp = new(class coordinate);
        temp->x = x;
        temp->y = y+1;

        // 北端的房間已經於 path 中,或者 已在待處理列表 newpath 中.
        if( all[temp->x][temp->y]&D )
                return;

        // 迷宮入口
        if( x == enter->x && y == enter->y ) {
                line[x*2+1][y*2+1] =  HBWHT "  " NOR;
                line2[x*2+1][y*2+1] = HBWHT "  " NOR;
        } else {
                // 如果已經有顏色了，表示有寶箱或者陷阱，不再更改地圖
                if( line[x*2+1][y*2+1] == "  " ) {
                        line[x*2+1][y*2+1] = BGRN "  " NOR;
                }
        }

        all[x][y] |= N;
        all[x][y] |= R;
        all[temp->x][temp->y] |= S;
        all[temp->x][temp->y] |= D;
        newpath += ({ temp });
        roadpath += ({ temp });

        line[x*2+1][y*2+2] = BGRN "  " NOR;
        line2[x*2+1][y*2+2] = "  ";
}

protected void init_to_west(int x,int y)        // The west room is (x-1,y)
{
        class coordinate temp;

        temp = new(class coordinate);
        temp->x = x-1;
        temp->y = y;

        all[x][y] |= W;
        all[temp->x][temp->y] |= E;
        all[temp->x][temp->y] |= D;
        roadpath += ({ temp });

        // 處理路徑地圖
        line[x*2][y*2+1] =  "  ";
        line2[x*2][y*2+1] = "  ";
}

protected void init_to_east(int x,int y)        // The east room is (x+1,y)
{
        class coordinate temp;

        temp = new(class coordinate);
        temp->x = x+1;
        temp->y = y;

        all[x][y] |= E;
        all[temp->x][temp->y] |= W;
        all[temp->x][temp->y] |= D;
        roadpath += ({ temp });

        line[x*2+2][y*2+1] =  "  ";
        line2[x*2+2][y*2+1] = "  ";
}

protected void init_to_south(int x,int y)       // The south room is (x,y-1)
{
        class coordinate temp;

        temp = new(class coordinate);
        temp->x = x;
        temp->y = y-1;

        all[x][y] |= S;
        all[temp->x][temp->y] |= N;
        all[temp->x][temp->y] |= D;
        roadpath += ({ temp });

        line[x*2+1][y*2] =  "  ";
        line2[x*2+1][y*2] = "  ";
}

protected void init_to_north(int x,int y)       // The north room is (x,y+1)
{
        class coordinate temp;

        temp = new(class coordinate);
        temp->x = x;
        temp->y = y+1;

        all[x][y] |= N;
        all[temp->x][temp->y] |= S;
        all[temp->x][temp->y] |= D;
        roadpath += ({ temp });

        line[x*2+1][y*2+2] =  "  ";
        line2[x*2+1][y*2+2] = "  ";
}

protected mixed init_to_link(int x,int y)
{
        int *outs = ({});
        int dir, retn = 0;
        class coordinate temp;
        mixed result = ({});

        all[x][y] |= T;

        if( ((x-1) >= 0)
        && !(all[x][y]&W) ) {
                if( !(all[x-1][y]&T)
                && !(all[x-1][y]&B) )
                        outs += ({ W });
        }

        if( ((x+1) < l)
        && !(all[x][y]&E) ) {
                if( !(all[x+1][y]&T)
                && !(all[x+1][y]&B) )
                        outs += ({ E });
        }

        if( ((y+1) < l)
        && !(all[x][y]&N) ) {
                if( !(all[x][y+1]&T)
                && !(all[x][y+1]&B) )
                        outs += ({ N });
        }

        if( ((y-1) >= 0)
        && !(all[x][y]&S) ) {
                if( !(all[x][y-1]&T)
                && !(all[x][y-1]&B) )
                        outs += ({ S });
        }

        if( sizeof(outs) < 1 ) {
                all[x][y] ^= T;
                if( !(all[x][y]&D) ) {
                        all[x][y] |= B;
                        all[x][y] |= D;
                        temp = new(class coordinate);
                        temp->x = x;
                        temp->y = y;
                        result = ({ temp });
                        badpath += ({ temp });
                }
                return result;
        }

        dir = outs[random(sizeof(outs))];
        retn |= dir;

        if( retn&N ) {
                temp = new(class coordinate);
                temp->x = x;
                temp->y = y+1;

                all[x][y] |= N;
                all[temp->x][temp->y] |= S;

                line[x*2+1][y*2+2] =  "  ";
                line2[x*2+1][y*2+2] = "  ";
        } else
        if( retn&S ) {
                temp = new(class coordinate);
                temp->x = x;
                temp->y = y-1;

                all[x][y] |= S;
                all[temp->x][temp->y] |= N;

                line[x*2+1][y*2] =  "  ";
                line2[x*2+1][y*2] = "  ";
        } else
        if( retn&W ) {
                temp = new(class coordinate);
                temp->x = x-1;
                temp->y = y;

                all[x][y] |= W;
                all[temp->x][temp->y] |= E;

                line[x*2][y*2+1] =  "  ";
                line2[x*2][y*2+1] = "  ";
        } else
        if( retn&E ) {
                temp = new(class coordinate);
                temp->x = x+1;
                temp->y = y;

                all[x][y] |= E;
                all[temp->x][temp->y] |= W;

                line[x*2+2][y*2+1] =  "  ";
                line2[x*2+2][y*2+1] = "  ";
        }

        if( !(all[temp->x][temp->y]&D) )
                result = init_to_link(temp->x, temp->y);

        all[x][y] ^= T;
        all[x][y] |= D;
        if( sizeof(result) > 0 ) {
                all[x][y] |= B;
                temp = new(class coordinate);
                temp->x = x;
                temp->y = y;
                badpath += ({ temp });
                result +=  ({ temp });
        }

        return result;
}

// 初始化地圖的處理
void init_line()
{
        int i, x, y, flag;

        line = allocate(l*2+1);  // 顯示詳細地圖
        line2 = allocate(l*2+1); // 顯示普通地圖
        for( i=0;i<sizeof(line);i++ ) {
                line[i] = allocate(l*2+1);
                line2[i] = allocate(l*2+1);
        } // 建立數組

        for( y=sizeof(line)-1;y>=0;y-- ) {
                for( x=0;x<sizeof(line[y]);x++ ) {
                        if( y%2 == 1 ) {
                                if( x%2 == 1 ) {
                                        if( all[x/2][y/2]&MAP ) {         // 有地圖寶箱
                                                line[x][y] = BYEL "  " NOR;
                                                line2[x][y] = "  ";
                                        } else if( all[x/2][y/2]&BOX ) {  // 寶箱
                                                line[x][y] = BYEL "  " NOR;
                                                line2[x][y] = "  ";
                                        } else if( all[x/2][y/2]&TRAP ) { // 陷阱
                                                line[x][y] = BMAG "  " NOR;
                                                line2[x][y] = "  ";
                                        } else if( all[x/2][y/2]&CENTER ) {  // 特殊房間
                                                line[x][y] = BCYN "  " NOR;
                                                line2[x][y] = "  ";
                                        } else if( all[x/2][y/2]&SPECIAL ) { // 特殊房間
                                                line[x][y] = BCYN "  " NOR;
                                                line2[x][y] = "  ";
                                        } else
                                                line[x][y] = line2[x][y] = "  ";
                                } else
                                        line[x][y] = line2[x][y] = HIG "│" NOR;
                        } else {
                                if( x%2 == 1 )
                                        line[x][y] = line2[x][y] = HIG "─" NOR;
                                else {
                                        if( y == 0 ) {
                                                if( x == 0 )
                                                        line[x][y] = line2[x][y] = HIG "└" NOR;
                                                else if( x == l*2 )
                                                        line[x][y] = line2[x][y] = HIG "┘" NOR;
                                                else
                                                        line[x][y] = line2[x][y] = HIG "┴" NOR;
                                        } else if ( y == l*2 ) {
                                                if( x == 0 )
                                                        line[x][y] = line2[x][y] = HIG "┌" NOR;
                                                else if( x == l*2 )
                                                        line[x][y] = line2[x][y] = HIG "┐" NOR;
                                                else
                                                        line[x][y] = line2[x][y] = HIG "┬" NOR;
                                        } else {
                                                if( x == 0 )
                                                        line[x][y] = line2[x][y] = HIG "├" NOR;
                                                else if( x == l*2 )
                                                        line[x][y] = line2[x][y] = HIG "┤" NOR;
                                                else
                                                        line[x][y] = line2[x][y] = HIG "┼" NOR;
                                        }
                                }
                        }
                }
        }
}

public string display_deep_map(object room)
{
        string map = "\n迷宮地圖：\n" WHT "白色方塊" NOR "表示迷宮入口；"
                                      RED "紅色方塊" NOR "表示迷宮出口；"
                                      HIB "藍色五角星" NOR "表示你當前的位置。\n"
                                      CYN "青色方塊" NOR "表示特殊房間；"
                                      YEL "黃色方塊" NOR "表示有寶箱；"
                                      MAG "紫色方塊" NOR "表示有陷阱。\n";
        int i, j;
        int x, y;

        if( !line )
                return "迷宮地圖不存在。\n";

        if( objectp(room) ) {
                x=query("maze/x", room);
                y=query("maze/y", room);
        } else {
                x = -10;
                y = -10;
        }

        for( j=sizeof(line)-1;j>=0;j-- ) {
                for( i=0;i<sizeof(line[j]);i++ ) {
                        if( i == x*2+1 && j == y*2+1 )
                                map += replace_string(line[i][j], "  ", HIB "★" NOR);
                        else
                                map += line[i][j];
                }
                map += "\n";
        }
        return map;
}

public string display_common_map(object room)
{
        string map = "\n迷宮地圖：\n" WHT "白色方塊" NOR "表示迷宮入口；"
                                      RED "紅色方塊" NOR "表示迷宮出口；"
                                      HIB "藍色五角星" NOR "表示你當前的位置。\n";
        int i, j;
        int x, y;

        if( map_status == MAP_NONE )
                return  "迷宮地圖失效。\n";

        if( map_status == MAP_DEEP )
                return display_deep_map(room);

        if( !line2 )
                return "迷宮地圖不存在。\n";

        if( objectp(room) ) {
                x=query("maze/x", room);
                y=query("maze/y", room);
        } else {
                x = -10;
                y = -10;
        }

        for( j=sizeof(line2)-1;j>=0;j-- ) {
                for( i=0;i<sizeof(line2[j]);i++ ) {
                        if( display_coordinate && i == x*2+1 && j == y*2+1 )
                                map += replace_string(line2[i][j], "  ", HIB "★" NOR);
                        else
                                map += line2[i][j];
                }
                map += "\n";
        }
        return map;
}

void init_special()
{
        int x, y, unique_num;
        class coordinate temp, *mazes = ({});

        unique_num = sizeof(unique_rooms);
        for( x=0;x<l;x++ ) {
                for( y=0;y<l;y++ ) {
                        if( x == l/2 && y == l/2 ) {
                                if( stringp(center_room) ) {
                                        all[x][y] |= CENTER;
                                        continue;
                                }
                                if( sizeof(unique_rooms) == 4 )
                                        continue;
                        }
                        if( unique_num > 0 && ((x == 0 && y == 0)
                        ||      (x == 0 && y == l-1)
                        ||      (x == l/2 && y == l/2)
                        ||      (x == l-1 && y == 0)
                        ||      (x == l-1 && y == l-1)) ) {
                                all[x][y] |= SPECIAL;
                                unique_num --;
                                continue;
                        }
                        if( (x == enter->x && y == enter->y) ||
                            (x == leave->x && y == leave->y) )
                                continue;

                        temp = new(class coordinate);
                        temp->x = x;
                        temp->y = y;
                        mazes += ({ temp });
                }
        }

        // 分佈帶地圖寶箱
        //temp = new(class coordinate);
        temp = mazes[random(sizeof(mazes))];
        x = temp->x;
        y = temp->y;
        all[x][y] |= MAP;
        mazes -= ({ temp });

        // 分佈其他的寶箱
        while( box_num > 0 ) {
                if( sizeof(mazes) < 1 )
                        break;
                //temp = new(class coordinate);
                temp = mazes[random(sizeof(mazes))];
                x = temp->x;
                y = temp->y;
                all[x][y] |= BOX;
                mazes -= ({ temp });
                box_num --;
        }

        // 分佈陷阱
        while( trap_num > 0 ) {
                if( sizeof(mazes) < 1 )
                        break;
                //temp = new(class coordinate);
                temp = mazes[random(sizeof(mazes))];
                x = temp->x;
                y = temp->y;
                all[x][y] |= TRAP;
                mazes -=  ({ temp });
                trap_num --;
        }
        return;
}

// 摔跤到隨機房間
public object trip_maze(object room)
{
        int x, y;
        object next;
        string fname;

        if( !objectp(room) ) return 0;

        fname = base_name(this_object());

        while( 1 ) {
                x = random(l);
                y = random(l);
                if( (x == enter->x && y == enter->y) ||
                    (x == leave->x && y == leave->y) )
                        continue;

                if( x == query("maze/x", room) &&
                    y == query("maze/y", room) )
                        continue;         // 不能是該房間本身

                if( all[x][y]&TRAP )
                        continue;

                next = load_object(sprintf("%s/%d/%d",fname,x,y));
                if( objectp(next) ) break;
        }
        return next;
}

// 拆除指定房間的陷阱
public void remove_trap(object room)
{
        int x, y;

        if( !line ) return;

        x=query("maze/x", room);
        y=query("maze/y", room);
        if( all[x][y]&R )
                line[x*2+1][y*2+1] = BGRN "  " NOR;
        else
                line[x*2+1][y*2+1] = "  ";

        return;
}

nomask int clean_up()
{
        string fname;
        int x,y;
        object room;

        if( !maze_built ) {
                destruct(this_object());
                return 0;
        }

        // 暫時取消
        return 1;

        fname = base_name(this_object());

        if( objectp(room = find_object(sprintf("%s/entry",fname))) ) {
                room->clean_up();
                if( objectp(room) )
                        return 1;
        }

        if( objectp(room = find_object(sprintf("%s/exit",fname))) ) {
                room->clean_up();
                if( objectp(room) )
                        return 1;
        }

        for( x=0;x<l;x++ )
                for( y=0;y<l;y++ )
                        if( objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))) ) {
                                //maze_objs += ({find_object(sprintf("%s/%d/%d",fname,x,y))});
                                room->clean_up();
                                if( objectp(room) )
                                        return 1;
                        }
        /*
        maze_objs->clean_up();
        maze_objs -= ({0});

        if(sizeof(maze_objs))
                return 1;
        else
        {
        */
                destruct(this_object());
                return 0;
//      }
}

void remove(string euid)
{
        string fname = base_name(this_object());
        object room;
        int x,y;

        if( handle_id )
                SCHEDULE_D->delete_event(handle_id);

        for( x=0;x<l;x++ )
                for( y=0;y<l;y++ )
                        if( objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))) )
                                destruct(room);
        if( room = find_object(sprintf("%s/entry",fname)) )
                destruct(room);
        if( room = find_object(sprintf("%s/exit",fname)) )
                destruct(room);
}

// 檢查某個房間裏是否有玩家。
int is_player_in(object room)
{
        object *inv;
        inv = all_inventory(room);
        for (int i = 0;i < sizeof(inv) ; i++)
                if (userp(inv[i]))
                        return 1;
        return 0;
}

int have_player_in()
{
        string fname = base_name(this_object());
        object room;
        int x,y;
        for( x=0;x<l;x++ ) {
                for( y=0;y<l;y++ ) {
                        if(objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))))
                                if (is_player_in(room))
                                        return 1;
                }
        }

        if( objectp(room = find_object(sprintf("%s/entry",fname))) )
                if (is_player_in(room))
                        return 1;
        if( objectp(room = find_object(sprintf("%s/exit",fname))) )
                if ( is_player_in(room) )
                        return 1;

        return 0;
}

object *query_maze_players()
{
        string fname = base_name(this_object());
        object *inv, *ret;
        object room;
        int x,y;
        ret = ({});
        for( x=0;x<l;x++ ) {
                for( y=0;y<l;y++ ) {
                        if( objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))) ) {
                                        inv = all_inventory(room);
                                        for( int i=0;i<sizeof(inv);i++ )
                                                if( userp(inv[i]) )
                                                        ret += ({ inv[i] });
                        }
                }
        }

        if( objectp(room = find_object(sprintf("%s/entry",fname))) ) {
                inv = all_inventory(room);
                for( int i=0;i<sizeof(inv);i++ )
                        if( userp(inv[i]) )
                                ret += ({ inv[i] });
        }
        if( objectp(room = find_object(sprintf("%s/exit",fname))) ) {
                inv = all_inventory(room);
                for( int i=0;i<sizeof(inv);i++ )
                        if( userp(inv[i]) )
                                ret += ({ inv[i] });
        }

        return ret;
}

void refresh_maze()
{
        string fname = base_name(this_object());
        object room;
        int x,y;

        if (this_object()->have_player_in()) {
                SCHEDULE_D->set_event(10, 0, this_object(), "refresh_maze");
                return;
        }

        for( x=0;x<l;x++ )
                for( y=0;y<l;y++ )
                        if(objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))))
                                destruct(room);
        if( room = find_object(sprintf("%s/entry",fname)) )
                destruct(room);
        if( room = find_object(sprintf("%s/exit",fname)) )
                destruct(room);

        // 處理迷宮特殊房間
        special_rooms = copy(unique_rooms);

        return;
}

void clear_maze_item(object user)
{
        object *inv, obj;
        inv = all_inventory(user);
        if( inv && sizeof(inv)>0 )
                foreach( obj in inv ) {
                        if( obj && query("maze_item", obj) )
                                destruct(obj);
                }
}

//      把所有玩家從迷宮裏搬走。
varargs int remove_all_players(object exile_room,string remove_msg)
{
        string fname = base_name(this_object());
        object room,*inv;
        int x,y,num;

        for( x=0;x<l;x++ ) {
                for( y=0;y<l;y++ ) {
                        if( objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))) ) {
                                if( remove_msg ) tell_room(room,remove_msg);
                                inv=all_inventory(room);
                                num=sizeof(inv);
                                while( num-- ) {
                                        if( !userp(inv[num]) ) continue;
                                        clear_maze_item(inv[num]);
                                        if( exile_room )
                                                inv[num]->move(exile_room);
                                        else
                                                inv[num]->move(VOID_OB);
                                }
                        }
                }
        }

        if( objectp(room = find_object(sprintf("%s/entry",fname))) ) {
                if( remove_msg ) tell_room(room,remove_msg);
                inv=all_inventory(room);
                num=sizeof(inv);
                while( num-- ) {
                        if( !userp(inv[num]) ) continue;
                        clear_maze_item(inv[num]);
                        if( exile_room )
                                inv[num]->move(exile_room);
                        else
                                inv[num]->move(VOID_OB);
                }
        }

        if( objectp(room = find_object(sprintf("%s/exit",fname))) )     {
                if( remove_msg ) tell_room(room,remove_msg);
                inv=all_inventory(room);
                num=sizeof(inv);
                while( num-- ) {
                        if( !userp(inv[num]) ) continue;
                        clear_maze_item(inv[num]);
                        if( exile_room )
                                inv[num]->move(exile_room);
                        else
                                inv[num]->move(VOID_OB);
                }
        }
}

void set_display_coor(int flag)
{
        if( !intp(flag) ) flag = 0;
        display_coordinate = flag;
}

void set_display_map(int flag)
{
        if( intp(flag) && flag>=2 )
                map_status = MAP_DEEP;
        else if( intp(flag) && flag==1 )
                map_status = MAP_COMM;
        else
                map_status = MAP_NONE;
}

void set_maze_boss(object ob)
{
        if( objectp(ob) )
                maze_boss = ob;
}

void set_boss_weakly()
{
        int i, level;
        mapping skills;
        string *ks;
        if( !objectp(maze_boss) ) return;
        if( mapp(skills = maze_boss->query_skills()) ) {
                ks = keys(skills);
                for( i=0;i<sizeof(ks);i++ ) {
                        level = skills[ks[i]]+2;
                        maze_boss->set_skill(ks[i], level/2);
                }
        }
        return;
}

/**** 以下是預設迷宮參數的接口函數 ****/
// 迷宮的單邊長
void set_maze_long(int mlong)
{
        if( !intp(mlong) )
                return;

        // 最小為 5，再小了沒什麼意義。
        if( (mlong < 5) || mlong > MAX_LONG )
                return;

        l = mlong;
}

// 迷宮可使用的房間文件名 (****)
void set_valid_rooms(mixed room_files)
{
        if( stringp(room_files) ) {
                // 檔案是否存在
                if( file_size(sprintf("%s.c",room_files)) > 0 ) {
                        object ob = find_object(room_files);

                        if( !ob )
                                ob = load_object(room_files);
                        if( ob && query("short", ob) && query("long", ob)){
                                valid_rooms = ({ room_files });
                                switch_flag = 1;
                        }
                }
                return;
        } else if( arrayp(room_files) ) {
                foreach( string f in room_files ) {
                        object ob;

                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                        if( !ob = find_object(f) )
                                ob = load_object(f);
                        if( !ob || !query("short", ob) || !query("long", ob) )
                                return;
                }
                valid_rooms = room_files;
                switch_flag = 1;
                return;
        }

}

// 迷宮房間所繼承的物件的檔案名稱。
void set_inherit_room( mixed rooms )
{
        if( stringp(rooms) ) {
                // 此檔案是否存在
                if( file_size(sprintf("%s.c",rooms)) > 0 )
                        inherit_rooms = ({ rooms });
                return;
        } else if( arrayp(rooms) ) {
                foreach( string f in rooms ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                inherit_rooms = rooms;
                return;
        }

        return;
}

// 入口方向(出口在對面)
void set_entry_dir(string dir)
{
        if( !stringp(dir) )
                return;

        // 入口方向的合法性檢查.
        if( member_array(dir,valid_dirs) == -1 )
                return;

        entry_dir = dir;
}

// 入口與區域的連接方向
void set_link_entry_dir(string dir)
{
        if( !stringp(dir) || dir == "" )
                return;

        link_entry_dir = dir;
}

// 迷宮入口所連接區域檔案的文件名
void set_link_entry_room(string lroom)
{
        if( !stringp(lroom) || lroom == "" )
                return;

        if( file_size(sprintf("%s.c",lroom)) <= 0 )
                return;

        link_entry_room = lroom;
}

// 迷宮入口房間的座標，我們無法用簡單的方法把迷宮座標安排在
// 進口/出口內（這個需要得到迷宮與區域的關係）
// 所以我們認為迷宮是進口區域延伸的一部分，當走出迷宮出口時，跳躍進入下一個區域。
// 缺點是，一個大迷宮的座標可能與真實區域重疊，這個就要設計者自己留意了，
// 比如説，不要把100x100的迷宮安排在 (1,1)和 (10,10)之間。。。。自己算一下吧
void set_link_entry_room_x(int x)
{
        if( !intp(x) ) link_entry_room_x=0;
        else    link_entry_room_x = x;
}
void set_link_entry_room_y(int y)
{

        if( !intp(y) ) link_entry_room_y=0;
        else    link_entry_room_y = y;
}
void set_link_entry_room_z(int z)
{
        if( !intp(z) ) link_entry_room_z=0;
        else    link_entry_room_z = z;
}

// 出口與區域的連接方向
void set_link_exit_dir(string dir)
{
        if( !stringp(dir) || dir == "" )
                return;

        link_exit_dir = dir;
}

// 迷宮出口所連接區域檔案的文件名
void set_link_exit_room(string lroom)
{
        if( !stringp(lroom) || lroom == "" )
                return;

        if( file_size(sprintf("%s.c",lroom)) <= 0 )
                return;

        link_exit_room = lroom;
}

// 迷宮入口的短描述
void set_entry_short(string desc)
{
        if( !stringp(desc) || desc == "" )
                return;

        entry_short = desc;
}

// 迷宮入口的長描述
void set_entry_desc(string desc)
{
        if( !stringp(desc) || desc == "" )
                return;

        entry_desc = desc;
}

// 迷宮出口的短描述
void set_exit_short(string desc)
{
        if( !stringp(desc) || desc == "" )
                return;

        exit_short = desc;
}

// 迷宮出口的長描述
void set_exit_desc(string desc)
{
        if( !stringp(desc) || desc == "" )
                return;

        exit_desc = desc;
}

// 迷宮房間的短描述
void set_maze_room_short(string desc)
{
        if( !stringp(desc) || desc == "" )
                return;

        maze_room_short = desc;
}

// 迷宮房間的描述，如果有多條描述，製造每個房
// 間的時候會從中隨機選擇一個。
void set_maze_room_desc(mixed desces)
{
        if( stringp(desces) ) {
                maze_room_desc = ({ desces });
                return;
        } else if(arrayp(desces)) {
                foreach( string desc in desces )
                        if( !stringp(desc) )
                                return;
                maze_room_desc = desces;
                return;
        }
}

// 迷宮房間是否為户外房間
void set_outdoors(int outd)
{
        if( !intp(outd) )
                return;

        if( outd )
                is_outdoors = 1;
}

// 迷宮中的怪物
void set_maze_npcs(mixed npc)
{
        if( stringp(npc) ) {
                // 此檔案是否存在
                if( file_size(sprintf("%s.c",npc)) > 0 )
                        maze_npcs = ({ npc });
                return;
        } else if( arrayp(npc) ) {
                foreach( string f in npc ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                maze_npcs = npc;
                return;
        } else if( mapp(npc) ) {
                string *ns;

                ns = keys(npc);
                foreach( string f in ns ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                maze_npcs = npc;
                return;
        }
        return;
}

// 迷宮入口的怪物
void set_entry_npcs(mixed npc)
{
        if( stringp(npc) ) {
                // 此檔案是否存在
                if( file_size(sprintf("%s.c",npc)) > 0 )
                        entry_npcs = ({ npc });
                return;
        } else if( arrayp(npc) ) {
                foreach( string f in npc ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                entry_npcs = npc;
                return;
        } else if( mapp(npc) ) {
                string *ks;

                ks = keys(npc);
                foreach( string f in ks ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                entry_npcs = npc;
                return;
        }
        return;
}

// 迷宮出口的怪物
void set_exit_npcs(mixed npc)
{
        if( stringp(npc) ) {
                // 此檔案是否存在
                if( file_size(sprintf("%s.c",npc)) > 0 )
                        exit_npcs = ({ npc });
                return;
        } else if( arrayp(npc) ) {
                foreach( string f in npc ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                exit_npcs = npc;
                return;
        } else if( mapp(npc) ) {
                string *ks;

                ks = keys(npc);
                foreach( string f in ks ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                exit_npcs = npc;
                return;
        }
        return;
}

void set_unique_room(mixed room)
{
        if( stringp(room) ) {
                // 此檔案是否存在
                if( file_size(sprintf("%s.c",room)) > 0 )
                        unique_rooms = ({ room });
        } else if( arrayp(room) ) {
                foreach( string f in room ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                unique_rooms = room;
        }
        special_rooms = copy(unique_rooms);
        return;
}

void set_center_room(string room)
{
        if( !stringp(room) || room == "" )
                return;
        if( file_size(sprintf("%s.c",room)) > 0 )
                center_room = room;
        return;
}

// 迷宮寶箱的數量
void set_maze_boxs(int number)
{
        if( intp(number) && number>=1 )
                box_num = number;
}

// 迷宮陷阱的數量
void set_maze_traps(int number)
{
        if( intp(number) && number>=1 )
                trap_num = number;
}

// 迷宮刷新
void set_maze_refresh(int refresh)
{
        if( intp(refresh) && refresh>=1 )
                refresh_delay = refresh;
}

// 迷宮設計非死亡房間
void set_maze_nodeath(int flag)
{
        if( intp(flag) && flag>=1 )
                is_nodeath = flag;
}

// 迷宮中的怪物出現可能性
void set_npcs_rate(int rate)
{
        if( !intp(rate) )
                return;

        random_rate = rate;
}

void set_normal_room(int flag)
{
        if( intp(flag) && flag >= 1 )
			    normal_room = flag;
}

void set_lonely_create(int flag)
{
        if( intp(flag) && flag>=1 )
                lonely_create = flag;
}
/**** 以上是預設迷宮參數的接口函數 ****/

// 創造迷宮房間，由 VIRTUAL_D 調用。
nomask object query_maze_room(string str)
{
        int idx,x,y,exits;
        int box_type,trap_type;
        object ob,obj;
        string f;
        int unique_flag;

        /*
        if( previous_object() && (geteuid(previous_object()) != ROOT_UID) )
                return 0;
        */

        if( !stringp(str) || str == "" )
                return 0;

        if( !maze_built ) // 迷宮未建立
                create_maze();
        if( !maze_built )
                return 0;

        if( !random_rate )
                random_rate = 50; // 房間內放置 npc 的可能性

        if( str == "entry" ) {     // 迷宮入口房間
                f = inherit_rooms[random(sizeof(inherit_rooms))];
                //ob = new(f);
                ob = load_object(f);
                if( !ob )
                        return 0;
                set("short", entry_short, ob);
                set("long", entry_desc, ob);
                set("maze", 1, ob);
                set("no_magic", 1, ob);
                set("virtual_room", 1, ob);
                if( is_outdoors )
                        set("outdoors", 1, ob);
                if( is_nodeath )
                        set("no_death", 1, ob);
                if( link_entry_room ) set(sprintf("exits/%s",link_entry_dir),link_entry_room,ob);
                set(sprintf("exits/%s",reverse_dir[entry_dir]),mroom_fname(enter->x,enter->y), ob);
                set("coor/x", link_entry_room_x, ob);
                set("coor/y", link_entry_room_y, ob);
                set("coor/z", link_entry_room_z, ob);
                set("mazeobj", base_name(this_object()), ob);
                set("maze/x", enter->x, ob);
                set("maze/y", enter->y, ob);
                if( arrayp(entry_npcs) && sizeof(entry_npcs) ) {
                        set("objects",([
                                entry_npcs[random(sizeof(entry_npcs))] : 1,
                        ]), ob);
                        ob->setup();
                } else if( mapp(entry_npcs) && sizeof(entry_npcs) ) {
                        set("objects", entry_npcs, ob);
                        ob->setup();
                }

                return ob;
        }

        if( str == "exit" ) {      // 迷宮出口房間
                f = inherit_rooms[random(sizeof(inherit_rooms))];
                //ob = new(f);
                ob = load_object(f);
                if( !ob )
                        return 0;

                set("short", exit_short, ob);
                set("long", exit_desc, ob);
                set("maze", 1, ob);
                set("no_magic", 1, ob);
                set("virtual_room", 1, ob);
                if( is_outdoors )
                        set("outdoors", 1, ob);
                if( is_nodeath )
                        set("no_death", 1, ob);
                if( link_exit_room ) set(sprintf("exits/%s",link_exit_dir),link_exit_room,ob);
                set(sprintf("exits/%s",entry_dir),mroom_fname(leave->x,leave->y),ob);
                set("mazeobj", base_name(this_object()), ob);
                set("maze/x", leave->x, ob);
                set("maze/y", leave->y, ob);
                if( arrayp(exit_npcs) && sizeof(exit_npcs) ) {
                        set("objects",([
                                exit_npcs[random(sizeof(exit_npcs))] : 1,
                        ]), ob);
                        ob->setup();
                } else if( mapp(exit_npcs) && sizeof(exit_npcs) ) {
                        set("objects", exit_npcs, ob);
                        ob->setup();
                }

                return ob;
        }

        idx = member_array('/', str);
        if( idx == -1 )
                return 0;

        if( !sscanf(str[0..idx-1],"%d",x) )
                return 0;
        if( !sscanf(str[idx+1..],"%d",y) )
                return 0;

        if( !exits = all[x][y] )
                return 0;

        // 處理unique rooms4個角落，和中心位置
        unique_flag = 0;
        if( exits&SPECIAL && sizeof(special_rooms) > 0 ) {
                unique_flag = 1;
                f = special_rooms[random(sizeof(special_rooms))];
                special_rooms -= ({ f });
        } else if( exits&CENTER ) {
                unique_flag = 1;
                f = center_room;
        } else if( exits&TRAP ) {
                f = TRAP_ROOM;
        } else {
                // 不同的創建方法
                if( switch_flag )
                        f = valid_rooms[random(sizeof(valid_rooms))];
                else
                        f = inherit_rooms[random(sizeof(inherit_rooms))];
        }

        //ob = new(f);
        ob = load_object(f);
        if( !ob )
                return 0;

        if( !switch_flag && !unique_flag ) {
                set("short", maze_room_short, ob);
                set("long", maze_room_desc[random(sizeof(maze_room_desc))], ob);
                set("maze", 1, ob);
                set("no_magic", 1, ob);
                set("virtual_room", 1, ob);
                if( is_outdoors )
                        set("outdoors", 1, ob);
                if( is_nodeath )
                        set("no_death", 1, ob);
        }

        if( exits&TRAP ) {
                trap_type = random(100);
                if( trap_type > 97 )
                        set("maze/trap", LOSTMAP, ob);//百分之一十
                else if( trap_type < 20 )
                        set("maze/trap", TRIP, ob);//百分之二十
                else if( trap_type < 40 )
                        set("maze/trap", CHANGEMAP, ob);//百分之四十
                else if (trap_type < 70)
                        set("maze/trap", WOUND, ob);//百分之七十
                else
                        set("maze/trap", BUSY, ob);
        }

        // 根據入口座標和迷宮大小來定義房間座標
        set("coor/x", x*10-l+link_entry_room_x, ob);
        set("coor/y", y*10-to_int(l/2)+link_entry_room_y, ob);
        set("coor/z", link_entry_room_z, ob);
        set("mazeobj", base_name(this_object()), ob);
        set("maze/x", x, ob);
        set("maze/y", y, ob);

        if( exits&W )
                set("exits/west", mroom_fname(x-1,y), ob);
        else if( !normal_room )
                set("exits/west", mroom_fname(x,y), ob);
        if( exits&E )
                set("exits/east", mroom_fname(x+1,y), ob);
        else if( !normal_room )
                set("exits/east", mroom_fname(x,y), ob);
        if( exits&N )
                set("exits/north", mroom_fname(x,y+1), ob);
        else if( !normal_room )
                set("exits/north", mroom_fname(x,y), ob);
        if( exits&S )
                set("exits/south", mroom_fname(x,y-1), ob);
        else if( !normal_room )
                set("exits/south", mroom_fname(x,y), ob);

        if( (x == enter->x) && (y == enter->y) )
                set(sprintf("exits/%s",entry_dir),
                        sprintf("%s/entry",base_name(this_object())), ob);
        if( (x == leave->x) && (y == leave->y) )
                set(sprintf("exits/%s",reverse_dir[entry_dir]),
                        sprintf("%s/exit",base_name(this_object())), ob);

        if( !switch_flag && !unique_flag ) {
                if( mapp(maze_npcs) && sizeof(maze_npcs) && (random(100) <= random_rate) ) {
                        set("objects", maze_npcs, ob);
                        ob->setup();
                } else if( arrayp(maze_npcs) && sizeof(maze_npcs) && (random(100) <= random_rate) ) {
                        set("objects",([
                                maze_npcs[random(sizeof(maze_npcs))] : 1,
                        ]), ob);
                        ob->setup();
                }
        }

        if( exits&MAP ) {
                obj = new(BOX_OB);
                set("maze/box", SPECIAL_MAP, obj);
                obj->move(ob);
        } else if( exits&BOX ) {
                obj = new(BOX_OB);
                box_type = random(100);
                if( box_type > 97 )
                        set("maze/box", SPECIAL_DAN, obj);//百分之二
                else if( box_type > 94 )
                        set("maze/box", JINKUAI, obj);//百分之三
                else if( box_type < 15 )
                        set("maze/box", GOLD, obj);//百分之十五
                else if( box_type < 65 )
                        set("maze/box", OBJ, obj);//百分之五十
                else if( box_type < 85 )
                        set("maze/box", SPECIAL_OBJ, obj);//百分之二十
                else {
                        if( objectp(maze_boss) )
                                set("maze/box", NPC_SKILL, obj);
                        else
                                set("maze/box", SPECIAL_OBJ, obj);//百分之十
                }

                obj->move(ob);
        }

        return ob;
}
