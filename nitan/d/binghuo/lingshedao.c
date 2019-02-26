// Room: /binghuo/lingshedao.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "靈蛇島海灘");
        set("long", @LONG
這是個樹木葱翠的大島，島上奇峯挺拔，聳立着好幾座高山。島
西端山石直降入海，並無淺灘，往來船隻近岸泊就。
LONG );
        set("outdoors", "lingshe");
        set("exits", ([
                "east"  : __DIR__"lingsheroad1",
        ]));
        set("objects", ([
                __DIR__"npc/yinli" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
