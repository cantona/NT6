// Room: /d/quanzhou/chenghuangmiao.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "城隍廟");
        set("long", @LONG
這是一間年代久遠的小廟，裏面供放着觀音菩薩和土地爺，是泉州
鄉間求卜問卦的場所，據説這裏的籤卦特靈。旁邊有扇小門。
LONG );
        set("objects", ([
                __DIR__"npc/miaozhu" : 1,
        ]));
        set("exits", ([
                "southeast" : __DIR__"chenghuangxiang",
                "southwest" : __DIR__"houshanmen",
        ]));
	set("coor/x", -920);
	set("coor/y", -7630);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}