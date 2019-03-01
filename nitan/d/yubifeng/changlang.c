// /yubifeng/changlang.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
這是一條長長的走廊，四處透著濃濃的寒氣。出去就是玉筆山莊的
大門，沿這裡走過去可以直達大廳，周圍一塵不染，非常安靜。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
                "north" : __DIR__"dating",
                "out"   : __DIR__"damen"
        ]));
        set("objects", ([ /* sizeof() == 4 */
                __DIR__"npc/xuanmingzi" : 1,
                __DIR__"npc/lingqing" : 1,
                __DIR__"npc/jiang" : 1,
        ]));

        set("coor/x", 6120);
        set("coor/y", 5170);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}