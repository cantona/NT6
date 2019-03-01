inherit ROOM;

void create()
{
        set("short", "帕米爾草原");
        set("long", @LONG
這裡已是南疆。獨特的地勢和氣候，竟形成南疆難得一見
的小片草原。因天山擋住了北方寒風，這兒物產豐富，聚居了
不少哈薩克族人。波斯商人也常來此地販賣土產。
LONG);
        set("outdoors", "gaochang");

        set("exits", ([
                    "northup" : __DIR__"huijiang1",
                    "southdown" : __DIR__"huijiang3",
        ]));
        set("objects", ([
                __DIR__"npc/hasake"  : 1,
                "/clone/quarry/yang" : 3,
        ]));
        set("quarrys", ([
                "yang"  : 100000,
                "gou"   : 100000,
                "lang"  : 80000,
                "lang2" : 50000,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}