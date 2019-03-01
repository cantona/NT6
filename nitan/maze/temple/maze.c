// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit VRM_SERVER;

void create() 
{ 
        //迷宮房間所繼承的物件的檔案名稱。 
        set_inherit_room( ROOM );  
                        
        //唯一房間
        set_unique_room( ({
                "/maze/temple/unique_room/zombie_room",
        }) ); 

        //迷宮房間裡的怪物。 
        set_maze_npcs( ([
                "/maze/temple/npc/zombie": 3,  
                "/maze/temple/npc/zombie_lord": !random(5),
        ]) );
        
        set_lonely_create(1);
        
        //set_maze_boxs(6); 
        
        //set_maze_traps(6); 

        //迷宮的單邊長 
        set_maze_long(10); 
                        
        //入口方向(出口在對面) 
        set_entry_dir("north"); 
                        
        //入口與區域的連接方向 
        set_link_entry_dir("north"); 
                        
        //入口與區域的連接檔案名 
        set_link_entry_room("/d/city/wumiao"); 
                        
        //出口與區域的連接方向 
        set_link_exit_dir("south"); 
                        
        //出口與區域的連接檔案名 
        set_link_exit_room("/d/city/wumiao"); 
                        
                        
        //普通房間描述
        set_maze_room_short(RED "失落神廟" NOR);
                        
        set_maze_room_desc(@LONG
神廟很大，柱子上雕刻著千奇百怪的動物，有的人身上卻
長著一顆狼頭，人身上生出一雙翅膀，怪異的怪首的雕刻讓人
嘆為觀止，廟頂成八角，屋脊曲線柔美,泥塑,剪黏,木雕,彩繪
皆為上品。
LONG); 
                        
        //入口房間短描述 
        set_entry_short(HIR "失落神廟入口" NOR); 
                        
        //入口房間描述 
        set_entry_desc(@LONG
神廟很大，柱子上雕刻著千奇百怪的動物，有的人身上卻
長著一顆狼頭，人身上生出一雙翅膀，怪異的怪首的雕刻讓人
嘆為觀止，廟頂成八角，屋脊曲線柔美,泥塑,剪黏,木雕,彩繪
皆為上品。
LONG); 
                        
        //出口房間短描述 
        set_exit_short(HIW "失落神廟出口" NOR); 
                        
        //出口房間描述 
        set_exit_desc(@LONG
神廟很大，柱子上雕刻著千奇百怪的動物，有的人身上卻
長著一顆狼頭，人身上生出一雙翅膀，怪異的怪首的雕刻讓人
嘆為觀止，廟頂成八角，屋脊曲線柔美,泥塑,剪黏,木雕,彩繪
皆為上品。
LONG); 
                                              
} 

