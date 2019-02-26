// Room: /wuliang/huayuan.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "花園");
        set("long", @LONG
這是一個園子，庭院清幽，茶花爭放，山石古拙，蒼松翠竹，景
致煞是宜人。東面通往一間小屋，西邊是一條長長的甬道通向正廳。
LONG );
        set("outdoors", "wuliang");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"xiaowu",
                "west"  : __DIR__"road2",
        ]));
        set("objects", ([
                "/clone/medicine/nostrum/mangguzhuha": random(2),
        ]));
        set("coor/x", -70980);
        set("coor/y", -79890);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}