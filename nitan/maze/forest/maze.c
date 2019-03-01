#include <ansi.h>
inherit VRM_SERVER;
 
#define ENTER_ROOM_X  0
#define ENTER_ROOM_Y  0
#define ENTER_ROOM_Z  0

string *unique_rooms = ({
        "/maze/forest/unique_room/snakehole",
        "/maze/forest/unique_room/bearlair",
        "/maze/forest/unique_room/wolfcave",
        "/maze/forest/unique_room/tigerhill",
        "/maze/forest/unique_room/dragonland",
});

void create() 
{ 
        //迷宮房間所繼承的物件的檔案名稱。 
        set_inherit_room( ROOM ); 
                        
        //唯一房間
        set_unique_room( unique_rooms ); 

        //迷宮房間裡的怪物。 
        set_maze_npcs( ([
                /*
                "/maze/forest/npc/toad": !random(5), 
                "/maze/forest/npc/rabbit": !random(5),  
                "/maze/forest/npc/wolf_baby": !random(5), 
                "/maze/forest/npc/wolf_big": !random(5), 
                "/maze/forest/npc/snake_baby": !random(5), 
                "/maze/forest/npc/snake_big": !random(5), 
                "/maze/forest/npc/tiger_baby": !random(5), 
                "/maze/forest/npc/tiger_big": !random(5), 
                "/maze/forest/npc/bear_baby": !random(5), 
                "/maze/forest/npc/bear_big": !random(5), 
                "/maze/forest/npc/dragon_baby": !random(10), 
                */
                "/maze/forest/npc/tiger_king": !random(5), 
                "/maze/forest/npc/wolf_king": !random(5), 
                "/maze/forest/npc/bear_king": 1, 
                "/maze/forest/npc/snake_king": !random(5), 
        ]) );                   

        set_lonely_create(1);

        //迷宮的單邊長 
        set_maze_long(8); 
        
        //入口方向(出口在對面) 
        set_entry_dir("east"); 
                        
        //入口與區域的連接方向 
        set_link_entry_dir("east"); 
                        
        //入口與區域的連接檔案名 
        set_link_entry_room(__DIR__"enter"); 
                        
        //出口與區域的連接方向 
        set_link_exit_dir("west"); 
                        
        //出口與區域的連接檔案名 
        set_link_exit_room(__DIR__"out"); 
                        
        //以下是入口坐標
        set_link_entry_room_x(ENTER_ROOM_X);
        set_link_entry_room_y(ENTER_ROOM_Y);
        set_link_entry_room_z(ENTER_ROOM_Z);
                        
        //普通房間描述
        set_maze_room_short(HIG"原始森林"NOR);
                        
        set_maze_room_desc(@LONG
原始森林樹葉蒼黑如蓋，遮天蔽日，林中彌漫著枯葉腐爛
和樹脂混合的味道，地上的苔鮮落葉踩上去軟綿綿的，上面還
布滿野獸的痕跡，四周濃密的山霧，讓人難以分辨方向。
LONG); 

        //入口房間短描述 
        set_entry_short(HIR"原始森林入口"NOR); 
                        
        //入口房間描述 
        set_entry_desc(@LONG
原始森林樹葉蒼黑如蓋，遮天蔽日，林中彌漫著枯葉腐爛
和樹脂混合的味道，地上的苔鮮落葉踩上去軟綿綿的，上面還
布滿野獸的痕跡，四周濃密的山霧，讓人難以分辨方向。
LONG);
                        
        //出口房間短描述 
        set_exit_short(HIY"原始森林出口"NOR); 
                        
        //出口房間描述 
        set_exit_desc(@LONG
原始森林樹葉蒼黑如蓋，遮天蔽日，林中彌漫著枯葉腐爛
和樹脂混合的味道，地上的苔鮮落葉踩上去軟綿綿的，上面還
布滿野獸的痕跡，四周濃密的山霧，讓人難以分辨方向。
LONG);

        // 迷宮房間是否為戶外房間？ 
        set_outdoors(1);                                                

        // 迷宮房間是否刷新且刷新時間設置
        //set_maze_refresh(180);
        
} 


