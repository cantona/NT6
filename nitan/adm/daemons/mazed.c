// This program is a part of NITAN MudLIB
// mazed.c 迷宮的守護進程

/***********************************************************************
 * 每個迷宮的數據包括：                                                *
 * boss:            迷宮中放置的NPC                                    *
 * roomlist:        迷宮的房間點陣                                     *
 * entry:           迷宮的入口                                         *
 * target:          迷宮的出口                                         *
 * direction:       迷宮的方向                                         *
 * deep_map:        迷宮帶路線的地圖                                   *
 * comm_map:        迷宮不帶路線的地圖                                 *
 * born_time:       迷宮創建的時間                                     *
 * map_status:      迷宮的地圖狀態                                     *
 ***********************************************************************/

#include <ansi.h>
#include <maze.h>

#pragma optimize
#pragma save_binary

inherit F_DBASE;

int clean_up() { return 1; }

/***********************************************************************/

nosave mapping mazelist;                                  // 所有迷宮列表
nosave int mazeindex = 0;                                 // 所有迷宮索引  
nosave int show_local_room = 1;                           // 是否顯示玩家所在的位置   
nosave mixed dead_room_list;                              // 在創建迷宮時記錄死胡同       
nosave object *all_dead_room;                             // 記錄所有在死胡同中的房間    
 
// 定義提供給外部調用的接口函數
public void check_maze(string mazename);                  // 檢查迷宮的狀態 
public void remove_maze(string mazename);                 // 拆除指定的迷宮 
public object create_maze(object npc);                    // 創建新的迷宮   
public void init_maze(string mazename);                   // 初始化迷宮地圖  
public string get_comm_map(string mazename, object room); // 獲取迷宮普通地圖 
public string get_deep_map(string mazename, object room); // 獲取迷宮詳細地圖
public object trip_maze(string mazename, object room);    // 摔跤到隨機房間   
public void lostmap_maze(string mazename);                // 迷宮地圖失效    
public void remove_xianjing(string mazename, object room);// 拆除指定房間的陷阱  
public void openmap_maze(string mazename);                // 開放迷宮詳細地圖 
public void del_npc_skill(string mazename);               // 降低NPC的武功    

// 專供管理調用的接口函數
public string* query_all_maze();                          // 返回迷宮名稱列表   
public mapping query_maze(string mazename);               // 返回指定迷宮的詳細信息  
public void set_locate_show(string mazename);             // 設置指定迷宮是否顯示玩家所在的位置  

void create()
{
        seteuid(getuid());
        set("channel_id", "迷宮精靈");
        CHANNEL_D->do_channel(this_object(), "sys", "迷宮系統已經啟動。");
        mazelist = ([ ]);
        collect_all_maze_information();
        set_heart_beat(HEART_TIME);
}

// 迷宮系統重新啟動的時候收集所有迷宮房間的消息
void collect_all_maze_information()
{
        // 將所有的迷宮房間全部清除
        int i, room_num;
        object *obs;
        
        obs = children(ROOM_FILE);
    
        room_num = sizeof(obs);
        if ( !room_num ) return;
    
        for ( i = 0; i < sizeof(obs); i++ )
                obs[i]->destruct_me();
    
        return;
}

private void heart_beat()
{
        int i, maze_num;
        array maze_key;
    
        // 清理超時的迷宮，清理NPC已經消失的迷宮
        if ( !mapp(mazelist) ) return;

        maze_key = keys(mazelist);
        if ( !arrayp(maze_key) ) return;

        maze_num = sizeof(maze_key);
        if ( !maze_num ) return;
        
        for ( i = 0; i < sizeof(maze_key); i++ )
                check_maze(maze_key[i]);
        
        return;
}

public void check_maze(string mazename)
{
        mapping maze;
        mixed roomlist;
        int w, l;
    
        if ( !stringp(mazename) ) return;
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) ) return;
             
        maze = mazelist[mazename];
        
        if ( !objectp(maze["boss"]) || 
             time() - maze["born_time"] > MAZE_LIFT_CYCLE )
        {
                if ( undefinedp(maze["roomlist"]) )
                {
                        map_delete(mazelist, mazename);
                        return;
                }
                
                roomlist = maze["roomlist"];
                for (w = 0; w < sizeof(roomlist); w++)
                        for (l = 0; l < sizeof(roomlist[w]); l++)
                                if ( objectp(roomlist[w][l]) )      
                                        roomlist[w][l]->destruct_me();
                                        
                map_delete(mazelist, mazename);
        }

        return;
}

public void remove_maze(string mazename)
{
        mapping maze;
        mixed roomlist;
        int w, l;
    
        if ( !stringp(mazename) ) return;
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) ) return;
    
        maze = mazelist[mazename];

        if ( undefinedp(maze["roomlist"]) )
        {
                map_delete(mazelist, mazename);
                return;
        }
    
        roomlist = maze["roomlist"];
        for (w = 0; w < sizeof(roomlist); w++)
                for (l = 0; l < sizeof(roomlist[w]); l++)
                        if ( objectp(roomlist[w][l]) )
                                roomlist[w][l]->destruct_me();
                                
        map_delete(mazelist, mazename);

        return;
}

public object create_maze(object npc)
{
        int i, j;
        string entry_name = "";
        string mazename;        /* 迷宮名字         */
        mapping tempmaze;       /* 迷宮實體         */
        mixed mazeroom;         /* 迷宮房間點陣     */
        int *entry;             /* 迷宮入口 */
        int *target;            /* 迷宮出口 */
        object temp_room;
    
        if ( !objectp(npc) || !npc->is_character() || !stringp(npc->name()) )
                return 0;
    
        // 生成迷宮的名字（唯一值）
        mazename = sprintf("%s-%d", npc->name(), mazeindex);
        mazeindex ++;
    
        tempmaze = ([ ]);

        // 設置迷宮的創建時間
        tempmaze["born_time"] = time();
    
        // 迷宮地圖初始化為普通模式
        tempmaze["map_status"] = MAP_COMM;

        // 設置迷宮中放置的NPC
        tempmaze["boss"] = npc;

        // 設置迷宮的方向
        tempmaze["direction"] = random(4);  //隨機生成迷宮的方向

        // 設置迷宮的入口和出口
        entry = ({0,0});
        target = ({0,0});
    
        switch(tempmaze["direction"])
        {
        case TO_NORTH:
                entry[0] = HEIGHT - 1;
                entry[1] = random(LENGTH);
                target[0] = 0;
                target[1] = random(LENGTH);
                break;
        case TO_SOUTH:
                entry[0] = 0;
                entry[1] = random(LENGTH);
                target[0] = HEIGHT - 1;
                target[1] = random(LENGTH);
                break;
        case TO_WEST:
                entry[0] = random(HEIGHT);
                entry[1] = LENGTH - 1;
                target[0] = random(HEIGHT);
                target[1] = 0;
                break;
        default:
                entry[0] = random(HEIGHT);
                entry[1] = 0;
                target[0] = random(HEIGHT);
                target[1] = LENGTH - 1;
                break;
        }
        
        tempmaze["entry"] = entry;
        tempmaze["target"] = target;

        // 設置迷宮的房間點陣    
        mazeroom = allocate(HEIGHT);
        for ( i = 0; i < sizeof(mazeroom); i++ )
        {
                mazeroom[i] = allocate(LENGTH);
                for ( j = 0; j < sizeof(mazeroom[i]); j++ )
                {
                        temp_room = new(ROOM_FILE);
                        temp_room->set("maze/x", i);
                        temp_room->set("maze/y", j);
                        temp_room->delete("exits");
                        temp_room->set("maze/roomtype", NOT_DEFINED);
                        temp_room->set("maze/north", NOT_DEFINED);
                        temp_room->set("maze/south", NOT_DEFINED);
                        temp_room->set("maze/west", NOT_DEFINED);
                        temp_room->set("maze/east", NOT_DEFINED);
                        temp_room->set("maze/mazename", mazename);
            
                        // 給迷宮的入口房間打上標記
                        if ( i == entry[0] && j == entry[1] )
                        {
                                temp_room->set("short", "迷宮入口");
                                temp_room->set("maze/entry", 1);
                        }
                        // 給迷宮的出口房間打上標記
                        else if ( i == target[0] && j == target[1] )
                        {
                                temp_room->set("short", "迷宮出口");
                                temp_room->set("maze/target", 1);
                        }
                        
                        mazeroom[i][j] = temp_room;
                }
        }
        
        tempmaze["roomlist"] = mazeroom;
    
        // 給迷宮分布寶箱和陷阱
        init_special_room(tempmaze);

        // 將迷宮交給守護進程管理
        mazelist[mazename] = tempmaze;

        // 創建迷宮布局
        init_maze(mazename);
    
        // 返回迷宮的出口房間
        return tempmaze["roomlist"][target[0]][target[1]];
}

void init_line(mapping maze)
{
        mixed line;        /* 帶路線的迷宮地圖     */
        mixed line2;       /* 不帶路線的迷宮地圖   */
        int i, j;
        mixed roomlist;
        object room;
    
        if ( !mapp(maze) ) return;
        if ( undefinedp(maze["roomlist"]) ) return;

        roomlist = maze["roomlist"];
    
        line = allocate(HEIGHT*2+1);
        line2 = allocate(HEIGHT*2+1);

        for ( i = 0; i < sizeof(line); i++ )
        {
                line[i] = allocate(LENGTH*2+1);
                line2[i] = allocate(LENGTH*2+1);
                for ( j = 0; j < sizeof(line[i]); j++ )
                {
                        if ( i%2 == 1 )
                        {
                                if ( j%2 == 1 )
                                {
                                        room = roomlist[i/2][j/2];
                                        if ( objectp(room) && room->query("maze/xianjing") )
                                        {
                                                line[i][j] = BMAG "　" NOR;
                                                line2[i][j] = "　";
                                        }
                                        else if ( objectp(room) && room->query("maze/box") )
                                        {
                                                line[i][j] = BYEL "　" NOR;
                                                line2[i][j] = "　";
                                        }
                                        else
                                                line[i][j] = line2[i][j] = "　";
                                } 
                                else
                                        line[i][j] = line2[i][j] = HIG "│" NOR;
                        } 
                        else
                        {
                                if ( j%2 == 1 )
                                        line[i][j] = line2[i][j] = HIG "─" NOR;
                                else
                                {
                                        if ( i == 0 )
                                        {
                                                if ( j == 0 )
                                                        line[i][j] = line2[i][j] = HIG "┌" NOR; 
                                                else if ( j == LENGTH*2 )
                                                        line[i][j] = line2[i][j] = HIG "┐" NOR;
                                                else
                                                        line[i][j] = line2[i][j] = HIG "┬" NOR;
                                        } 
                                        else if ( i == HEIGHT * 2 )
                                        {
                                                if ( j == 0 )
                                                        line[i][j] = line2[i][j] = HIG "└" NOR;
                                                else if ( j == LENGTH*2 )
                                                        line[i][j] = line2[i][j] = HIG "┘" NOR;
                                                else
                                                        line[i][j] = line2[i][j] = HIG "┴" NOR;
                                        } 
                                        else
                                        {
                                                if ( j == 0 )
                                                        line[i][j] = line2[i][j] = HIG "├" NOR;
                                                else if ( j == LENGTH*2 )
                                                        line[i][j] = line2[i][j] = HIG "┤" NOR;
                                                else
                                                        line[i][j] = line2[i][j] = HIG "┼" NOR;
                                        }
                                }
                        }
                }
        }
    
        maze["deep_map"] = line;
        maze["comm_map"] = line2;
}

public string get_comm_map(string mazename, object room)
{
        string map = "\n迷宮地圖：\n" WHT "白色方塊" NOR "表示迷宮入口；" 
                                      RED "紅色方塊" NOR "表示迷宮出口；" 
                                      HIB "藍色五角星" NOR "表示你當前的位置。\n";
        mapping maze;
        mixed line;
        int i,j;
        int w, l;
    
        if ( undefinedp(mazelist[mazename]) )
                return "迷宮實體不存在。\n";
    
        maze = mazelist[mazename];
    
        if ( maze["map_status"] == MAP_NONE )
                return 0;
    
        if ( maze["map_status"] == MAP_DEEP )
                return get_deep_map(mazename, room);
    
        if ( undefinedp(maze["comm_map"]) )
                return "迷宮地圖不存在。\n";
    
        if ( objectp(room) )
        {
                w = room->query("maze/x");
                l = room->query("maze/y");
        } 
        else
        {
                w = -10;
                l = -10;
        }

        line = maze["comm_map"];
    
        for ( i = 0; i < sizeof(line); i++ )
        {
                for ( j = 0; j < sizeof(line[i]); j++ )
                {
                        if ( show_local_room && i == w*2+1 && j == l*2+1 )
                                map += replace_string(line[i][j], "　", HIB "★" NOR);
                        else
                                map += line[i][j];
                }
                map += "\n";
        }
    
        return map;
}

public string get_deep_map(string mazename, object room)
{
        string map = "\n迷宮地圖：\n" WHT "白色方塊" NOR "表示迷宮入口；" 
                                      RED "紅色方塊" NOR "表示迷宮出口；" 
                                      HIB "藍色五角星" NOR "表示你當前的位置。\n" 
                                      YEL "黃色方塊" NOR "表示有寶箱；" 
                                      MAG "紫色方塊" NOR "表示有陷阱。\n";
        mapping maze;
        mixed line;
        int i, j;
        int w, l;
    
        if ( undefinedp(mazelist[mazename]) )
                return "迷宮實體不存在。\n";
    
        maze = mazelist[mazename];
    
        if ( undefinedp(maze["deep_map"]) )
                return "迷宮地圖不存在。\n";

        if ( objectp(room) )
        {
                w = room->query("maze/x");
                l = room->query("maze/y");
        } 
        else
        {
                w = -10;
                l = -10;
        }
    
        line = maze["deep_map"];
    
        for ( i = 0; i < sizeof(line); i++ )
        {
                for ( j = 0; j < sizeof(line[i]); j++ )
                {
                        if ( i == w*2+1 && j == l*2+1 )
                                map += replace_string(line[i][j], "　", HIB "★" NOR);
                        else
                                map += line[i][j];
                }
                map += "\n";
        }
    
        return map;
}

public void init_maze(string mazename)
{
        int i,j,w,l,room_ok;
        object *roomlist, temp_room;
        mixed mazeroom;
        mapping maze;
        object *dead_room;
        int dead_num;
    
        if ( undefinedp(mazelist[mazename]) )
                return;
    
        maze = mazelist[mazename];    

        if ( undefinedp(maze["roomlist"]) )
                return;
    
        mazeroom = maze["roomlist"];

        // 初始化迷宮地圖
        init_line(maze);

        for ( i = 0; i < sizeof(mazeroom); i++ )
        {
                for ( j = 0; j < sizeof(mazeroom[i]); j++ )
                {
                        temp_room = mazeroom[i][j];
                        temp_room->delete("exits");
                        temp_room->set("maze/roomtype", NOT_DEFINED);
                        temp_room->set("maze/north", NOT_DEFINED);
                        temp_room->set("maze/south", NOT_DEFINED);
                        temp_room->set("maze/west", NOT_DEFINED);
                        temp_room->set("maze/east", NOT_DEFINED);
                        temp_room->delete("maze/dead_room");
                }
        }

        // 初始化迷宮路線
        init_road(mazeroom[maze["entry"][0]][maze["entry"][1]], maze);
    
        // 給路線上的房間制造岔路
        roomlist = ({ });
        for ( i = 0; i < sizeof(mazeroom); i++ )
        {
                for ( j = 0; j < sizeof(mazeroom[i]); j++ )
                {
                        if ( mazeroom[i][j]->query("maze/roomtype") == IS_ROAD )
                                roomlist += ({ mazeroom[i][j] });
                }
        }
    
        for ( i = 0; i < sizeof(roomlist); i++ )
                init_wall(roomlist[i], maze);
    
        // 將呆死的房間全部打通
        dead_room_list = ({ });
        all_dead_room = ({ });
        for ( i = 0; i < sizeof(mazeroom); i++ )
        {
                for ( j = 0; j < sizeof(mazeroom[i]); j++ )
                {
                        if ( mazeroom[i][j]->query("maze/roomtype") == NOT_DEFINED )
                        {
                                dead_room = finish_room(mazeroom[i][j], maze);
                                if ( arrayp(dead_room) ) dead_room_list += ({ dead_room });
                        }
                }
        }
    
        dead_num = sizeof(dead_room_list);
        if ( dead_num )
        {
                for ( i = 0; i < sizeof(dead_room_list); i++ )
                {
                        room_ok = 0;
                        // 遍歷迷宮的每個房間，看是否可以和其它地方連通起來
                        for ( j = 0; j < sizeof(dead_room_list[i]); j++ )
                        {
                                temp_room = dead_room_list[i][j];
                                w = temp_room->query("maze/x");
                                l = temp_room->query("maze/y");
                                if ( temp_room->query("maze/north") != CAN_WALK && w > 0 &&
                                     member_array(mazeroom[w-1][l], all_dead_room) == -1 )
                                {
                                        temp_room->set("maze/north", CAN_WALK);
                                        mazeroom[w-1][l]->set("maze/south", CAN_WALK);
                                        maze["deep_map"][w*2][l*2+1] = "　";
                                        maze["comm_map"][w*2][l*2+1] = "　";
                                        room_ok = 1;
                                } else 
                                if ( temp_room->query("maze/south") != CAN_WALK && w < HEIGHT - 1 &&
                                     member_array(mazeroom[w+1][l], all_dead_room) == -1)
                                {
                                        temp_room->set("maze/south", CAN_WALK);
                                        mazeroom[w+1][l]->set("maze/north", CAN_WALK);
                                        maze["deep_map"][w*2+2][l*2+1] = "　";
                                        maze["comm_map"][w*2+2][l*2+1] = "　";
                                        room_ok = 1;
                                } else 
                                if ( temp_room->query("maze/west") != CAN_WALK && l > 0 &&
                                     member_array(mazeroom[w][l-1], all_dead_room) == -1)
                                {
                                        temp_room->set("maze/west", CAN_WALK);
                                        mazeroom[w][l-1]->set("maze/east", CAN_WALK);
                                        maze["deep_map"][w*2+1][l*2] = "　";
                                        maze["comm_map"][w*2+1][l*2] = "　";
                                        room_ok = 1;
                                } else
                                if ( temp_room->query("maze/east") != CAN_WALK && l < LENGTH - 1 &&
                                     member_array(mazeroom[w][l+1], all_dead_room) == -1)
                                {
                                        temp_room->set("maze/east", CAN_WALK);
                                        mazeroom[w][l+1]->set("maze/west", CAN_WALK);
                                        maze["deep_map"][w*2+1][l*2+2] = "　";
                                        maze["comm_map"][w*2+1][l*2+2] = "　";
                                        room_ok = 1;
                                }
                                
                                if ( room_ok )    // 迷宮已經打通
                                {
                                        // 將本迷宮中的所有房間從all_dead_room中去掉
                                        for ( room_ok = 0; room_ok < sizeof(dead_room_list[i]); room_ok++ )
                                        {
                                                dead_room_list[i][room_ok]->delete("maze/dead_room");
                                                all_dead_room -= ({ dead_room_list[i][room_ok] });
                                        }
                                        break;
                                }
                        }
                }
        }
        
        if ( sizeof(all_dead_room) )
                log_file("static/maze", sprintf("有%d個呆死的房間。\n", sizeof(all_dead_room)) );

        dead_room_list = 0;
        all_dead_room = 0;
    
        // 將房間的出口刷新
        init_room_exits(maze);

        return;
}

void init_road(object room, mapping maze)
{
        int w, next_w;
        int l, next_l;
        object next_room;
        int *dirs;
        int temp_dir;
        mixed line;
        mixed line2;
        mixed mazeroom;
    
        room->set("maze/roomtype", IS_ROAD);
        line = maze["deep_map"];
        line2 = maze["comm_map"];
        mazeroom = maze["roomlist"];
    
        w = room->query("maze/x");
        l = room->query("maze/y");
    
        // 已經到達了迷宮出口
        if ( w == maze["target"][0] && l == maze["target"][1] )
        {
                line[w*2+1][l*2+1] =  HBRED "　" NOR;
                line2[w*2+1][l*2+1] = HBRED "　" NOR;
                return;
        }        
    
        if ( w == maze["entry"][0] && l == maze["entry"][1] ) // 這是迷宮入口
        {
                line[w*2+1][l*2+1] =  HBWHT "　" NOR;
                line2[w*2+1][l*2+1] = HBWHT "　" NOR;
        } 
        else
        {
                // 如果已經有顏色了，表示有寶箱或者陷阱，不再更改地圖
                if ( line[w*2+1][l*2+1] == "　" )
                        line[w*2+1][l*2+1] = BGRN "　" NOR;
        
                // line2[w*2+1][l*2+1] = "　";
        }
    
        dirs = ({ });
        if ( maze["direction"] != TO_EAST && l > 0 &&
             room->query("maze/west") == NOT_DEFINED &&
             (w != maze["target"][0] || l > maze["target"][1]) )
                dirs += ({ WEST });

        if ( maze["direction"] != TO_WEST && l < LENGTH - 1 &&
             room->query("maze/east") == NOT_DEFINED &&
             (w != maze["target"][0] || l < maze["target"][1]) )
                dirs += ({ EAST });

        if (maze["direction"] != TO_SOUTH && w > 0 &&
            room->query("maze/north") == NOT_DEFINED && 
            (l != maze["target"][1] || w > maze["target"][0]) )
                dirs += ({ NORTH });

        if ( maze["direction"] != TO_NORTH && w < HEIGHT - 1 && 
             room->query("maze/south") == NOT_DEFINED && 
             (l != maze["target"][1] || w < maze["target"][0]) )
                dirs += ({ SOUTH });
    
        if ( sizeof(dirs) < 1 ) return;
        
        temp_dir = dirs[random(sizeof(dirs))];
    
        switch(temp_dir)
        {
        case WEST:
                room->set("maze/west", CAN_WALK);
                next_w = w;
                next_l = l - 1;
                next_room = mazeroom[next_w][next_l];
                next_room->set("maze/east", CAN_WALK);
                line[w*2+1][l*2] = BGRN "　" NOR;
                line2[w*2+1][l*2] = "　";
                break;
        case EAST:
                room->set("maze/east", CAN_WALK);
                next_w = w;
                next_l = l + 1;
                next_room = mazeroom[next_w][next_l];
                next_room->set("maze/west", CAN_WALK);
                line[w*2+1][l*2+2] = BGRN "　" NOR;
                line2[w*2+1][l*2+2] = "　";
                break;
        case SOUTH:
                room->set("maze/south", CAN_WALK);
                next_w = w + 1;
                next_l = l;
                next_room = mazeroom[next_w][next_l];
                next_room->set("maze/north", CAN_WALK);
                line[w*2+2][l*2+1] = BGRN "　" NOR;
                line2[w*2+2][l*2+1] = "　";
                break;
        default:
                room->set("maze/north", CAN_WALK);
                next_w = w - 1;
                next_l = l;
                next_room = mazeroom[next_w][next_l];
                next_room->set("maze/south", CAN_WALK);
                line[w*2][l*2+1] = BGRN "　" NOR;
                line2[w*2][l*2+1] = "　";
                break;
        }
    
        init_road(next_room, maze);
    
        return;
}

void init_wall(object room, mapping maze)
{
        int w, next_w;
        int l, next_l;
        object next_room;
    
        w = room->query("maze/x");
        l = room->query("maze/y");
    
        // 向NORTH方向制造岔路
        if ( w > 0 && room->query("maze/north") == NOT_DEFINED )
        {
                next_w = w - 1;
                next_l = l;
                next_room = maze["roomlist"][next_w][next_l];
                if ( next_room->query("maze/roomtype") == NOT_DEFINED )
                {
                        // 路和牆各有一半的概率
                        if ( random(2) == 1 )
                        {
                                room->set("maze/north", CAN_WALK);
                                next_room->set("maze/south", CAN_WALK);
                                next_room->set("maze/roomtype", IS_ROOM);
                                maze["deep_map"][w*2][l*2+1] = "　";
                                maze["comm_map"][w*2][l*2+1] = "　";
                                init_wall(next_room, maze);
                        }
                        else
                        {
                                room->set("maze/north", IS_WALL);
                                next_room->set("maze/south", IS_WALL);
                        }
                }
        }
    
        // 向SOUTH方向制造岔路
        if ( w < HEIGHT - 1 && room->query("maze/south") == NOT_DEFINED )
        {
                next_w = w + 1;
                next_l = l;
                next_room = maze["roomlist"][next_w][next_l];
                if ( next_room->query("maze/roomtype") == NOT_DEFINED )
                {
                        // 路和牆各有一半的概率
                        if ( random(2) == 1 )
                        {
                                room->set("maze/south", CAN_WALK);
                                next_room->set("maze/north", CAN_WALK);
                                next_room->set("maze/roomtype", IS_ROOM);
                                maze["deep_map"][w*2+2][l*2+1] = "　";
                                maze["comm_map"][w*2+2][l*2+1] = "　";
                                init_wall(next_room, maze);
                        }
                        else
                        {
                                room->set("maze/south", IS_WALL);
                                next_room->set("maze/north", IS_WALL);
                        }
                }
        }

        // 向EAST方向制造岔路
        if ( l < LENGTH - 1 && room->query("maze/east") == NOT_DEFINED )
        {
                next_w = w;
                next_l = l + 1;
                next_room = maze["roomlist"][next_w][next_l];
                if ( next_room->query("maze/roomtype") == NOT_DEFINED )
                {
                        // 路和牆各有一半的概率
                        if ( random(2) == 1 )
                        {
                                room->set("maze/east", CAN_WALK);
                                next_room->set("maze/west", CAN_WALK);
                                next_room->set("maze/roomtype", IS_ROOM);
                                maze["deep_map"][w*2+1][l*2+2] = "　";
                                maze["comm_map"][w*2+1][l*2+2] = "　";
                                init_wall(next_room, maze);
                        }
                        else
                        {
                                room->set("maze/east", IS_WALL);
                                next_room->set("maze/west", IS_WALL);
                        }
                }
        }

        // 向WEST方向制造岔路
        if ( l > 0 && room->query("maze/west") == NOT_DEFINED )
        {
                next_w = w;
                next_l = l - 1;
                next_room = maze["roomlist"][next_w][next_l];
                if ( next_room->query("maze/roomtype") == NOT_DEFINED )
                {
                        // 路和牆各有一半的概率
                        if ( random(2) == 1 )
                        {
                                room->set("maze/west", CAN_WALK);
                                next_room->set("maze/east", CAN_WALK);
                                next_room->set("maze/roomtype", IS_ROOM);
                                maze["deep_map"][w*2+1][l*2] = "　";
                                maze["comm_map"][w*2+1][l*2] = "　";
                                init_wall(next_room, maze);
                        }
                        else
                        {
                                room->set("maze/west", IS_WALL);
                                next_room->set("maze/east", IS_WALL);
                        }
                }
        }
    
        return;
}

object *finish_room(object room, mapping maze)
{
        int *dirs;
        int temp_dir;
        int w, next_w;
        int l, next_l;
        object next_room;
        object *result = 0;
        object *dead_room;
    
        w = room->query("maze/x");
        l = room->query("maze/y");
    
        // 給房間加上一個臨時標記，保証在遞歸過程中不會被重復調用
        room->set("maze/finish_room", 1);
    
        dirs = ({ });
        if ( l > 0 && room->query("maze/west") != CAN_WALK && 
            !maze["roomlist"][w][l-1]->query("maze/finish_room") && 
            !maze["roomlist"][w][l-1]->query("maze/dead_room") )
                dirs += ({ WEST });

        if ( l < LENGTH-1 && room->query("maze/east") != CAN_WALK && 
            !maze["roomlist"][w][l+1]->query("maze/finish_room") && 
            !maze["roomlist"][w][l+1]->query("maze/dead_room") )
                dirs += ({ EAST });

        if ( w > 0 && room->query("maze/north") != CAN_WALK && 
             !maze["roomlist"][w-1][l]->query("maze/finish_room") && 
             !maze["roomlist"][w-1][l]->query("maze/dead_room") )
                dirs += ({ NORTH });

        if ( w < HEIGHT-1 && room->query("maze/south") != CAN_WALK && 
            !maze["roomlist"][w+1][l]->query("maze/finish_room") && 
            !maze["roomlist"][w+1][l]->query("maze/dead_room") )
                dirs += ({ SOUTH });
    
        if ( sizeof(dirs) < 1 ) 
        {   
                room->delete("maze/finish_room");
                if ( room->query("maze/roomtype") == NOT_DEFINED )
                {
                        room->set("maze/dead_room", 1);
                        room->set("maze/roomtype", IS_ROOM);
                        dead_room = ({ room });
                        all_dead_room += ({ room });
                        return dead_room;
                }
                else
                {
                        return 0;
                }
        }
    
        temp_dir = dirs[random(sizeof(dirs))];
    
        switch(temp_dir)
        {   
        case NORTH:
                next_w = w - 1;
                next_l = l;
                next_room = maze["roomlist"][next_w][next_l];
                room->set("maze/north", CAN_WALK);
                next_room->set("maze/south", CAN_WALK);
                maze["deep_map"][w*2][l*2+1] = "　";
                maze["comm_map"][w*2][l*2+1] = "　";
                break;
        case SOUTH:
                next_w = w + 1;
                next_l = l;
                next_room = maze["roomlist"][next_w][next_l];
                room->set("maze/south", CAN_WALK);
                next_room->set("maze/north", CAN_WALK);
                maze["deep_map"][w*2+2][l*2+1] = "　";
                maze["comm_map"][w*2+2][l*2+1] = "　";
                break;
        case WEST:
                next_w = w;
                next_l = l - 1;
                next_room = maze["roomlist"][next_w][next_l];
                room->set("maze/west", CAN_WALK);
                next_room->set("maze/east", CAN_WALK);
                maze["deep_map"][w*2+1][l*2] = "　";
                maze["comm_map"][w*2+1][l*2] = "　";
                break;
        default:
                next_w = w;
                next_l = l + 1;
                next_room = maze["roomlist"][next_w][next_l];
                room->set("maze/east", CAN_WALK);
                next_room->set("maze/west", CAN_WALK);
                maze["deep_map"][w*2+1][l*2+2] = "　";
                maze["comm_map"][w*2+1][l*2+2] = "　";
                break;
        }
    
        if ( next_room->query("maze/roomtype") == NOT_DEFINED )
                result = finish_room(next_room, maze);
    
        room->set("maze/roomtype", IS_ROOM);
        room->delete("maze/finish_room");

        if ( arrayp(result) )
        {
                room->set("maze/dead_room", 1);
                result += ({ room });
                all_dead_room += ({ room });
        }    

        return result;
}

void init_special_room(mapping maze)
{
        mixed roomlist;
        int box_num, xianjing_num;
        int w, l;
        object *allroom, room;
        int xianjing_type;
        int box_type;
        object baoxiang;
    
        if ( !mapp(maze) || undefinedp(maze["roomlist"]) ) return;
    
        roomlist = maze["roomlist"];
        allroom = ({ });
    
        for ( w = 0; w < sizeof(roomlist); w++ )
        {
                for (l = 0; l < sizeof(roomlist); l++ )
                {
                        if ( roomlist[w][l]->query("maze/entry") || 
                             roomlist[w][l]->query("maze/target") )
                                continue;
            
                        allroom += ({ roomlist[w][l] });
                }
        }
        
        // 分布寶箱
        box_num = 0;
        // 首先放置地圖，這是必須有的
        room = allroom[random(sizeof(allroom))];
        room->set("maze/box", SPECIAL_MAP);
        baoxiang = new(BAOXIANG_OB);
        if ( baoxiang )
        {
                baoxiang->set("maze/mazename", room->query("maze/mazename"));
                baoxiang->set("maze/box", SPECIAL_MAP);
                baoxiang->move(room);
        }
        
        allroom -= ({ room });
        box_num ++;    
    
        while ( box_num < BOX_NUM )
        {
                if ( sizeof(allroom) < 1 ) 
                        break;
                        
                room = allroom[random(sizeof(allroom))];
                baoxiang = new(BAOXIANG_OB);
                baoxiang->set("maze/mazename", room->query("maze/mazename"));
                baoxiang->move(room);

                box_type = random(100);
                if ( box_type > 97 )
                {
                        room->set("maze/box", SPECIAL_DAN);     //百分之二
                        baoxiang->set("maze/box", SPECIAL_DAN);
                }
                else if ( box_type > 94 )
                {
                        room->set("maze/box", JINKUAI);         //百分之三
                        baoxiang->set("maze/box", JINKUAI);
                }
                else if ( box_type < 15 )
                {
                        room->set("maze/box", GOLD);            //百分之十五
                        baoxiang->set("maze/box", GOLD);
                }
                else if ( box_type < 65 )
                {
                        room->set("maze/box", OBJ);             //百分之五十
                        baoxiang->set("maze/box", OBJ);
                }
                else if ( box_type < 85 )
                {
                        room->set("maze/box", SPECIAL_OBJ);     //百分之二十
                        baoxiang->set("maze/box", SPECIAL_OBJ);
                }
                else
                {
                        if ( base_name(maze["boss"]) == CLASS_D("generate") + "/player_npc" )
                        {
                                room->set("maze/box", NPC_SKILL);
                                baoxiang->set("maze/box", NPC_SKILL);
                        }
                        else
                        {
                                room->set("maze/box", SPECIAL_OBJ); //百分之十
                                baoxiang->set("maze/box", SPECIAL_OBJ);
                        }
                }
                
                allroom -= ({ room });
                box_num ++;        
        }

        // 分布陷阱
        xianjing_num = 0;
    
        while ( xianjing_num < XIANJING_NUM )
        {
                if ( sizeof(allroom) < 1 ) 
                        break;
                        
                room = allroom[random(sizeof(allroom))];
                xianjing_type = random(100);
                if ( xianjing_type > 99 )
                        room->set("maze/xianjing", LOSTMAP);    //暫時關閉
                else if ( xianjing_type < 20 )     
                        room->set("maze/xianjing", TRIP);       //百分之二十
                else if ( xianjing_type < 40 )
                        room->set("maze/xianjing", CHANGEMAP);  //百分之二十
                else if ( xianjing_type < 70 )
                        room->set("maze/xianjing", WOUND);      //百分之三十
                else
                        room->set("maze/xianjing", BUSY);       //百分之三十
                        
                allroom -= ({ room });
                xianjing_num ++;        
        }
 
        return;   
}

void init_room_exits(mapping maze)
{
        int i, j;
        mixed mazeroom;
        object room;
    
        if ( undefinedp(maze["roomlist"]) )
                return;
    
        mazeroom = maze["roomlist"];
        for ( i = 0; i < sizeof(mazeroom); i++ )
        {
                for ( j = 0; j < sizeof(mazeroom[i]); j++)
                {
                        room = mazeroom[i][j];
                        if ( room->query("maze/north") == CAN_WALK )
                                room->set("exits/north", sprintf("/%O", mazeroom[i-1][j]) );
                        else
                                room->set("exits/north", sprintf("/%O", room) );
                                
                        if ( room->query("maze/south") == CAN_WALK )
                                room->set("exits/south", sprintf("/%O", mazeroom[i+1][j]) );
                        else
                                room->set("exits/south", sprintf("/%O", room) );

                        if ( room->query("maze/west") == CAN_WALK )
                                room->set("exits/west", sprintf("/%O", mazeroom[i][j-1]) );
                        else
                                room->set("exits/west", sprintf("/%O", room) );

                        if ( room->query("maze/east") == CAN_WALK )
                                room->set("exits/east", sprintf("/%O", mazeroom[i][j+1]) );
                        else
                                room->set("exits/east", sprintf("/%O", room) );
            
                        // 給迷宮的出口房間增加出口
                        if ( room->query("maze/target") )
                                room->set("exits/out", ROOM_EXIT_FILE);
                }
        }
    
        return;
}

public object trip_maze(string mazename, object room)
{
        mapping maze;
        mixed roomlist;
        int w, l;
        object next_room;
    
        if ( !stringp(mazename) || !objectp(room) )
                return 0;
    
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) )
                return 0;
    
        maze = mazelist[mazename];
    
        if ( undefinedp(maze["roomlist"]) )
                return 0;
    
        roomlist = maze["roomlist"];
    
        next_room = 0;
        while ( 1 )
        {
                w = random(HEIGHT);
                l = random(LENGTH);
       
                next_room = roomlist[w][l];
                if ( !objectp(next_room) ) break;
                if ( next_room->query("maze/target") ) continue;    // 不能是迷宮出口
                if ( next_room->query("maze/xianjing") ) continue;  // 不能是另一個陷阱
                if ( w == room->query("maze/x") && 
                     l == room->query("maze/y") ) continue;         // 不能是該房間本身

                break;
        }
   
        return next_room;
}

public void lostmap_maze(string mazename)
{
        mapping maze;
    
        if ( !stringp(mazename) )
                return 0;
    
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) )
                return 0;
    
        maze = mazelist[mazename];
    
        maze["map_status"] = MAP_NONE;
    
        return;
}

public void openmap_maze(string mazename)
{
        mapping maze;
    
        if ( !stringp(mazename) )
                return 0;
    
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) )
                return 0;
    
        maze = mazelist[mazename];
    
        maze["map_status"] = MAP_DEEP;
    
        return;
}

public void del_npc_skill(string mazename)
{
        mapping maze;
        object npc;
        mapping skill_status;
        array sname;
        int i, temp, now_lvl;
    
        if ( !stringp(mazename) )
                return 0;
    
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) )
                return 0;
    
        maze = mazelist[mazename];
        npc = maze["boss"];
    
        if ( !npc ) return;
        
        if ( mapp(skill_status = npc->query_skills()) )
        {
                skill_status = npc->query_skills();
                sname = keys(skill_status);

                temp = sizeof(skill_status);
                for ( i = 0; i < temp; i++ )
                {
                        now_lvl = skill_status[sname[i]] + 2;
                        npc->set_skill(sname[i], now_lvl/2);
                }
        }
    
        return;
}

public void remove_xianjing(string mazename, object room)
{
        mapping maze;
        mixed line;
        int w, l;
        object next_room;
    
        if ( !stringp(mazename) || !objectp(room) )
                return 0;
    
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) )
                return 0;
    
        maze = mazelist[mazename];
    
        if ( undefinedp(maze["deep_map"]) )
                return 0;
    
        line = maze["deep_map"];
    
        w = room->query("maze/x");
        l = room->query("maze/y");
    
        if ( room->query("maze/roomtype") == IS_ROAD )
                line[w*2+1][l*2+1] = BGRN "　" NOR;
        else
                line[w*2+1][l*2+1] = "　";
    
        return;
}

public void set_local_show(int arg)
{
        if ( !intp(arg) ) arg = 0;
        show_local_room = arg;
}

public string* query_all_maze()
{
        array mazes;
        mazes = ({ });

        if ( !mapp(mazelist) ) return mazes;
    
        mazes = keys(mazelist);
        return mazes;
}

public mapping query_maze(string mazename)
{
        mapping result;
        mapping maze;

        result = ([]);
        if ( !stringp(mazename) ) return 0;
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) ) return 0;

        maze = mazelist[mazename];
        result["boss"] = maze["boss"];
        result["player"] = maze["boss"]?maze["boss"]->query_temp("quester"):0;
        result["born_time"] = maze["born_time"];
        result["direction"] = maze["direction"];
        result["entry"] = maze["roomlist"][maze["entry"][0]][maze["entry"][1]];
        result["target"] = maze["roomlist"][maze["target"][0]][maze["target"][1]];
        result["map_status"] = maze["map_status"];
        result["deep_map"] = maze["deep_map"];
        
        return result;    
}

/*************************副本-虛擬迷宮********************************/
#define MAZE                    "maze.c"
#define ENTRY                   "enter.c"
#define EXIT                    "out.c"
#define MAZE_DIR                "/data/maze/"  

public string query_maze_file(string x, string y)
{
        return sprintf(MAZE_DIR + "%s/%s/", x, y);
}

protected mixed create_maze_file(object me, string maze)
{
        string src, dst;
        string filename;
        string dir1, dir2;
        
        dir1 = "/d/maze/" + maze + "/";
        dir2 = query_maze_file(me->query("id"), maze);
                
        src = dir1 + MAZE;
        dst = dir2 + MAZE;
        assure_file(dst);
        cp(src, dst);
        
        src = dir1 + ENTRY;
        dst = dir2 + ENTRY;
        filename = dst;
        cp(src, dst);
        
        src = dir1 + EXIT;
        dst = dir2 + EXIT;
        cp(src, dst);
        
        return filename;
}

public int enter_virtual_maze(object me, string arg) 
{
        string enter_file, maze_file;
        object *member, room;
        object *inv, maze;
        string id, dir;
        int min, max;
        
        if ( me->query_condition("killer") )
        {
                tell_object(me, "殺人通緝犯是不能進入副本的。\n");
                return 0;
        }

        inv = deep_inventory(me);
        if ( inv && sizeof(inv) > 0 )
        {
                foreach ( object ob1 in inv ) 
                        if( ob1 && ob1->is_character() ) 
                        {
                                tell_object(me, "你不可以將其他玩家或者NPC(包括寵物)背進副本內。\n");
                                return 0;
                        }
        }
                
        member = me->query_team_member(); 
        if ( !member || !sizeof(member) )
                id = me->query("id");
        else        
                id = me->query_team_leader()->query("id");  
                    
        dir = query_maze_file(id, arg);        
        enter_file = dir + ENTRY;
        
        // 已經創建過
        if ( file_size(enter_file) > 0 )
        {
                // 沒有被載入
                room = find_object(enter_file);
                if ( !room  )
                {                        
                        if ( sizeof(member) && !me->is_team_leader() )
                        { 
                                tell_object(me, "必須由隊長來創建副本任務的。\n");
                                return 0;
                        }    
                                                                                 
                        room = load_object(enter_file);
                }
                // 已經載入過濾
        } else  // 沒有創建過  
        {      
                dir = query_maze_file(me->query("id"), arg);                       
                enter_file = create_maze_file(me, arg);  
                if ( !enter_file )
                {
                        tell_object(me, "創建副本失敗。\n");
                        return 0;
                }              
                             
                room = load_object(enter_file);
        }
        
        maze_file = dir + MAZE; 
        maze = find_object(maze_file);
        if (! maze) maze = load_object(maze_file);
        
        min = maze->query_enter_minlevel();
        max = maze->query_enter_maxlevel();
        
        if (me->query("level") < min || (max && me->query("level") > max))
        {
                tell_object(me, HIW "副本要求最低等級為 " + min + " ，" + 
                                (max ? "最高等級為 " + max + " ，" : "") + 
                                "你無法進入副本。\n" NOR);
                return 0;
        }                
               
        tell_object(me, HIR "祝你好運氣！\n" NOR);
        me->move(room); 
        return 1;
}

public mixed query_maze_dir(object ob) 
{
        object env;
        string user, maze, dir;
        
        env = environment(ob);
        if( !env ) return 0;

        if( sscanf(base_name(env), MAZE_DIR + "%s/%s/%*s", user, maze) != 3 )
                return 0;
                
        dir = query_maze_file(user, maze);      
        return dir;
}

public object query_maze_mainobj(object ob) 
{
        string file;
        
        file = query_maze_dir(ob) + MAZE;      
        return get_object(file);
}
