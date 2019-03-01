// shuiledong.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "水樂洞");
        set("long", @LONG
水樂洞有兩個洞口，洞的左口有股山泉從石縫中湧出。泉水聲如
金石，和諧悅耳。旁有“天然琴聲”，“聽無弦琴”等石刻字句。洞
內兩壁有很多鐘乳石。往東是下山的路，西上便到了煙霞洞。
LONG);
        set("exits", ([
                "westup"    : __DIR__"yanxiadong",
                "eastdown"  : __DIR__"manjuelong",
        ]));
        set("resource/water", 1);
        set("no_clean_up", 0);
	set("coor/x", 790);
	set("coor/y", -2110);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}