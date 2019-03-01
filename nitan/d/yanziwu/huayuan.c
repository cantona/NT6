//room: huayuan.c
inherit ROOM;

void create()
{
        set("short","花園");
        set("long", @LONG
這個花園雖然不大，但整理的井井有條，看的出主人下了一番功
夫，丫環常來這裡嬉戲。沿著彎彎曲曲的花徑，可以同向各處。
LONG );
        set("outdoors", "yanziwu");
        set("exits",([
            "north" : __DIR__"changlang",
            "south" : __DIR__"jiashan",
            "west"  : __DIR__"dannuo",
            "east"  : __DIR__"biheqiao",
        ]));
        set("objects",([
            __DIR__"npc/yahuan" : 2,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
