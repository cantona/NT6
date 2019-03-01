// Room: /d/songshan/westwuchang.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;
void create()
{
        set("short", "西武場");
        set("long", @LONG
這裡是嵩山派的練武場。地面是用黃泥土拌雜砂石砸實的，看起來
很結實的樣子。練武場中間安著些器械，看來是練功用的。一些嵩山弟
子正滿頭臭汗地刻苦練功。
LONG );
        set("outdoors", "songshan");
        set("exits", ([
                "east"  : __DIR__"westpath3",
                "south" : __DIR__"westpath2",
        ]));
        set("objects", ([
                "/d/shaolin/npc/mu-ren" : 5,
        ]));
        set("coor/x", -40);
        set("coor/y", 920);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}