//RJQLWCH.C

inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
走進了銳金旗的練武場，發現這裡有些奇怪。練武的教眾們並不
是在相互切磋，而是穿戴著特制的護具，同一架奇怪的裝置打鬥。裝
置從不移開原地，只是它似乎具備用不完的各種兵器，進攻起來絲毫
不弱于江湖好手。
LONG );
        set("exits", ([
                "north" : __DIR__"rjqyuan",
                "south" : __DIR__"jinlianchang",
        ]));
        set("objects",([
                __DIR__"npc/wujincao" : 1,
        ]));

        set("no_clean_up", 0);
//        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}