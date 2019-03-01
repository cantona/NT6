// Room: /d/wuxi/huishan.c
// Winder 2000/02/22 

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "惠山山頂");
        set("long", @LONG
登上惠山山頂，但見滿山青鬆綽約，綠樹蒼翠，寺院石塔，巍然
聳立。從此可遠眺無錫全城和浩渺太湖。此山原名錫山，山產錫礦，
到漢代採盡。又有人挖到一石碑，上書：有錫兵，天下爭。無錫寧，
天下清。遂命名此城無錫。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "southdown"  : __DIR__"road15",
        ]));
        set("coor/x", 990);
	set("coor/y", -700);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}