//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","峯口");
	set("long",@LONG
崆峒山一名空同山，乃唐時杜光庭《洞天福地嶽瀆名山記》所列七十二福地
之一，眼前便是崆峒山主峯--馬鬃山，峯高千仞，三面臨淵，鬆遮雲繞，向峯頂
望去，隱約可見一排排精緻奇巧的古建築，上接雲天，下臨深谷，紅樓碧瓦，猶
如天宮一般。傳説崆峒最早為道家所崇奉的仙人廣成子修煉得道之所，被道教奉
為遠祖的噌登崆峒問道於廣成子，故此山有“道家第一名山”之稱。
LONG);
	set("exits",
	([
	"south" : "/d/map/xibei/kongdong_shan",
          "northup" : __DIR__"shijie1",
	]));
	if( random(10) > 7 )
	    set("objects", ([
		MISC_DIR "killer" : 1,
		]));
        set("outdoors","kongdong");
        setup();
        //place_program(ROOM);
}
