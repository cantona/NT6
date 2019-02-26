// Room: /d/songshan/duzuntan.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "獨尊壇");
        set("long", @LONG
這裏是獨尊壇。向來五嶽以泰山號稱“獨尊”，但自從十來年前嵩
山派奪得五嶽盟主一席後，江湖上五嶽獨尊的地位就是嵩山的了。這裏
陳列華貴，雕樑畫棟，也着實花了不少心力。
LONG );
        set("exits", ([
                "south" : __DIR__"houting",
        ]));
        set("objects", ([
                __DIR__"npc/deng": 1,
        ]));
        set("coor/x", -20);
        set("coor/y", 940);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}