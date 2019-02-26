// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit VRM_SERVER;

void create() 
{ 
        // 迷宮房間所繼承的物件的檔案名稱。 
        set_inherit_room( ROOM );  
                        
        // 唯一房間
        set_unique_room("/d/reborn/unique_room/xinmo_room"); 

        // 迷宮房間裏的怪物。 
        set_maze_npcs( ([
                "/d/reborn/npc/shadow": random(2),  
        ]) );   
        
        // 迷宮的單邊長 
        set_maze_long(10); 
                        
        // 入口方向(出口在對面) 
        set_entry_dir("north"); 
                        
        // 入口與區域的連接方向 
        set_link_entry_dir("north"); 
                        
        // 入口與區域的連接檔案名 
        set_link_entry_room("/d/reborn/jitan1"); 
                        
        // 出口與區域的連接方向 
        set_link_exit_dir("south"); 
                        
        // 出口與區域的連接檔案名 
        set_link_exit_room("/d/reborn/jitan1");                        
                        
        // 普通房間描述
        set_maze_room_short(RED "幻境" NOR);
                        
        set_maze_room_desc(@LONG
幻境裏到處是迷霧瀰漫，周邊的景物似有似無，虛無縹緲。
LONG); 
                        
        // 入口房間短描述 
        set_entry_short(HIR "幻境入口" NOR); 
                        
        // 入口房間描述 
        set_entry_desc(@LONG
幻境裏到處是迷霧瀰漫，周邊的景物似有似無，虛無縹緲。
LONG); 
                        
        // 出口房間短描述 
        set_exit_short(HIW "幻境出口" NOR); 
                        
        // 出口房間描述 
        set_exit_desc(@LONG
幻境裏到處是迷霧瀰漫，周邊的景物似有似無，虛無縹緲。
LONG); 

        // 迷宮房間是否為户外房間？ 
        set_outdoors(1); 
        
        set_remove_time(420);
} 

string query_my_map(){  return read_file(__DIR__"maze.map");}

