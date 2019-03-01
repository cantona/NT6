inherit ROOM;

void create()
{
          set("short", "平台山道");
        set("long", @LONG
山道被一塊如鷹喙突出的巨巖截斷，巨巖光可鑒人，只有中間鑿
出了一條窄窄的石階通向山道的那一頭。你小心翼翼地試著踏了上去。
右側是一塊大平台，依稀看去好象有不少人在那裡聚會。
LONG );
        set("outdoors", "lingjiu");
        set("exits", ([
                "west" : __DIR__"yan",
                "east" : __DIR__"pingtai",
                "north" : __DIR__"shandao2",
                "south" : __DIR__"pingtai3",
        ]));
        set("objects",([
                CLASS_D("lingjiu") + "/duanmu" : 1,
        ]));

        setup();
        replace_program(ROOM);
}