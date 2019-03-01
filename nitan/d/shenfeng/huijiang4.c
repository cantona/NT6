inherit ROOM;

void create()
{
        set("short", "收購店");
        set("long", @LONG
這是一個小收購店，房屋內舖著羊毛地毯。店老板為一波
斯人，專門收購當地物產。在一張大羊皮紙上，寫著需收購的
各類物產表。
LONG);
        set("exits", ([
                    "east" : __DIR__"huijiang3",
        ]));
        set("objects", ([
                __DIR__"npc/dealer": 1
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}