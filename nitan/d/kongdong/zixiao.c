//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","紫霄崖");
	set("long",@LONG
在「齊雲廣志」裏面曾稱紫霄崖“壁立五百餘仞，勢欲壓。過之者足未涉而
氣已奪”，在紫霄崖的壁上有“天下奇觀”等石刻，崖前一大石酷似駱駝，是以
也有人將紫霄崖稱為“紫駝峯”，懸崖高處有一個小洞龕，中有三尊神像，周圍
環境清幽，實是道家品茗説道，打坐修仙的絕佳之所。
LONG);
	set("exits",
	([
          "east" : __DIR__"qipan_ling",
          	]));
        set("outdoors","kongdong");
        setup();
        //place_program(ROOM);
}
