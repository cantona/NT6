// Room: /d/yanping/ximen.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "西門");
        set("long", @LONG
西門外便是羣山了。極目西望，大溪東來，羣峯蒼茫。西門是通往
贛南湘南的要道，青磚城牆上掛着一些告示和海捕文書。延平府向來清
明，蓋歷任知府多為理學門生故也。
LONG );
        set("exits", ([
                "east"      : __DIR__"road3",
                "north"     : __DIR__"sixianci",
                "southwest" : __DIR__"gudao4",
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 1,
        ]));
        set("outdoors", "yanping");
        setup();
        replace_program(ROOM);
}