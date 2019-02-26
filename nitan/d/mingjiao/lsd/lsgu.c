// /u/qingyun/lsd/lsgu.c
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIY"靈蛇谷"NOR);
        set("long", @LONG
這裏是島裏的一個山谷。山谷長着許多奇花異草，到處花香鳥語，
分外美麗，這裏遠離凡塵，你到了此處不禁疑為仙境。此島雖然到處
有毒蛇出沒但唯有此處不見毒物之蹤影，也許此間主人長在此間修行
之果。
LONG );
	set("exits", ([ 
  		"southup" : __DIR__"shanguang",
                "north" : __DIR__"sfjiao",
	]));
	set("objects",([
             CLASS_D("mingjiao") + "/dai" : 1,
	]));
	set("outdoors","靈蛇島");
	setup();
}
