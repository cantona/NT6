inherit ROOM;

void create()
{
          set("short", "失足巖");
        set("long", @LONG
這是通向靈鷲宮的必經之路，山道被一塊如鷹喙突出的巨巖截斷，
巨巖光可鑒人，只有中間鑿出了一條窄窄的石階通向山道的那一頭。
你小心翼翼地試著踏了上去。失足巖的右側是一塊大平台，依稀看去
好象有不少人在那裡聚會。
LONG );
        set("outdoors", "lingjiu");
        set("exits",([
                "northup"  : __DIR__"jian",
                "eastdown" : __DIR__"ya",
                "east" : __DIR__"shandao",
        ]));
        set("objects",([
                CLASS_D("lingjiu") + "/zhuo" : 1,
                "/clone/npc/walker" : 1,
        ]));

        setup();
        replace_program(ROOM);
}