// xizhaoshan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit BUNCH_ROOM;
void create()
{
        set("short", "夕照山");
        set("long", @LONG
夕照山上遍植棲樹和紅楓。每逢深秋，層林盡染，分外壯觀。山
頂有一座塔，雷峰塔。神話“白蛇傳”中的白娘娘就是被法海禁錮在
這座塔裡。每當夕陽西下，彩雲繚繞，塔影幢幢，這就是西湖十景之一
的“雷峰夕照”。
LONG);
        set("exits", ([
            "southdown"   : __DIR__"road16",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 800);
	set("coor/y", -2080);
	set("coor/z", 10);
	setup();
}
