// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "山道");
        set("long", @LONG
你正漫步在一條蜿蜒的山道上，兩邊繁茂的樹木散發出淡淡的宜
人的氣息，溪流在溝谷中流淌，水聲潺潺如幻。花香滿徑，山光樹色，
綠影葱蘢，輝映成畫。
LONG );
        set("outdoors", "xihu");
        set("exits", ([
                "north" : "/d/hangzhou/shandao2",
                "west"  : "/d/hangzhou/wenxin-quan",
                "south" : "/d/hangzhou/quanbian-xiaojing",
        ]));

//        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -1990);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}