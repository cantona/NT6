
inherit ROOM;

void create()
{
        set("short", "內屋");
        set("long", @LONG
這裏是回春堂專門出售藥王莊弟子精心炮製的成藥的地方。
藥王谷有許多技藝高超的弟子，他們有時會炮製一些成藥
就放在這裏出售，療效比一般的藥材效果更佳。
LONG );

        set("no_clean_up", 1);
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"nanting",
        ]));
        set("objects", ([
                __DIR__"npc/huoji2" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
