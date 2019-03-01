// Room: /d/lingzhou/piandian.c

inherit ROOM;

void create()
{
        set("short", "偏殿");
        set("long", @LONG
這裡是後宮邊上的偏殿，雖然不大卻很整齊，有幾把椅子和一張桌
子，是侍女們休息的地方。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
                "west" : __DIR__"garden",
                "east" : __DIR__"hougong",
        ]));
        set("objects", ([
                __DIR__"npc/gongnu" : 2,
        ]));
        set("coor/x", -6275);
        set("coor/y", 2995);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}