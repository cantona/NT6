// Room: westroad3.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "西大街");
        set("long", @LONG
你不知不覺地就來到了成都西北角，從這裡往北望，顯得格外冷
清。青石大道上只有零零落落的幾個人，在慢悠悠閒逛。往南是西大
街，東北方向是另一條大街，西北角有個好大的藥店，賣一些武林中
人常用的藥，唐門弟子常來此配藥。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "south"      : __DIR__"westroad2",
            "northeast"  : __DIR__"northroad1",
            "northwest"  : __DIR__"yaodian",
        ]));
        set("objects", ([
            "/d/huashan/npc/haoke": 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15240);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}