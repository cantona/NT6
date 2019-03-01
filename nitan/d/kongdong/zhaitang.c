//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","齋堂");
	set("long",@LONG
這裡就是齋堂，是崆峒弟子和進香客用膳的地方，內有一口煉丹時用的長生
井，井深丈許，寬約二尺，井水長年不枯，據傳飲此水可以長生，因此要用一兩
黃金才能在這裡打一次水，齋堂的一角立著數口大灶，幾個小道士在燒火，忙著
做齋飯，另一角放了許多素菜，是崆峒弟子在山上自己種的。
LONG);
	set("exits",
	([
          "east" : __DIR__"zhaohe_tang",
          	]));
//        set("outdoors","kongdong");
set("need_clean", "崆峒派");
	set("objects",([
		__DIR__"npc/kdizi5" : 1,
                __DIR__"npc/kdizi3" : 2,
		]) );
        setup();
        //place_program(ROOM);
}
