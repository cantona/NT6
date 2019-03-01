// gushan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "孤山");
        set("long", @LONG
通過林蔭道向前，迎面石壁上刻有“孤山”兩個丹紅大字。朝南
拾級登山便是平台。東北邊便是放鶴亭。東南邊則是平湖秋月。西北
邊通往西泠橋。
LONG);
        set("exits", ([
            "westup"    : "/d/meizhuang/shijie",
            "east"      : __DIR__"pinghuqiuyue",
            "southup"   : __DIR__"gushanpingtai",
            "northwest" : __DIR__"xilingqiao",
            "northeast" : __DIR__"fangheting",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 810);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}