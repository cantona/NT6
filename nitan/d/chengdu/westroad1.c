// Room: westroad1.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "西大街");
        set("long", @LONG
你正走在成都府的西大街上，這是一條寬敞開闊的大路，往北面
一直延伸。路上行人來來往往，好不熱鬧。小商小販常在這裡做些小
買賣，常常可見有人騎著高頭大馬穿行其間。    西南邊卻顯得特別
清靜，好象是個清幽所在，東南方向通往南大街。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "southwest"  : __DIR__"qingyanggong",
            "southeast"  : __DIR__"southroad3",
            "north"      : __DIR__"westroad2",
            "west"       : __DIR__"ruin1",
        ]));
        set("objects", ([
            "/d/village/npc/seller": 1,
            "/d/city/npc/liumang"  : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15240);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}