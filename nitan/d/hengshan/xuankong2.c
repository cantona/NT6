// Room: /d/hengshan/xuankong2.c
// Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
        set("short", "懸空寺南樓");
        set("long", @LONG
這裡是懸空寺的南門樓，也是南碑亭。懸空寺于陡崖上鑿石穴插懸
樑為基，樓宇間棧橋相連。全寺面東座西，南北危樓對望，斷崖分斷，
很是艱險。
LONG
        );
        set("exits", ([
                "north"   : __DIR__"zhanqiao",
                "southup" : __DIR__"zhandao",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 3160);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}
