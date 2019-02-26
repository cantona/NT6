#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", HIC"失落神廟"NOR);
        set("long", @LONG
神廟很大，柱子上雕刻着千奇百怪的動物，有的人身上卻
長着一顆狼頭，人身上生出一雙翅膀，怪異的怪首的雕刻讓人
歎為觀止，廟頂成八角，屋脊曲線柔美,泥塑,剪黏,木雕,彩繪
皆為上品。
LONG);
        
        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room", 1);
        set("no_clean_up", 1);       
        set("objects",([
                "/maze/temple/npc/zombie": 10,  
                "/maze/temple/npc/zombie_lord": 3,
                "/maze/temple/npc/zombie_king": 1,
        ]));
        setup();
}

