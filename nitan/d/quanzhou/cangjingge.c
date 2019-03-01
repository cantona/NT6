// Room: /d/quanzhou/cangjingge.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "藏經閣");
        set("long", @LONG
藏經閣是開元寺的最高處，建在一個小山坡上。閣分兩層，閣下有
一小門緊閉。登閣憑欄，看雙塔凌空，點壇俯地，饒富詩意。閣上藏經
近萬卷。
LONG );
        set("exits", ([
                "southdown" : __DIR__"jietang",
                "northdown" : __DIR__"houshanmen",
        ]));
        set("objects", ([
                __DIR__"npc/sengren" : 1,
        ]));
	set("coor/x", -920);
	set("coor/y", -7610);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}