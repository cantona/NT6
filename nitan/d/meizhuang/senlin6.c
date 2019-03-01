// senlin6.c
inherit ROOM;

void create()
{
        set("short", "百木園");
        set("long", @LONG
這裏是梅莊的百木園，你一走到這裏，就象走到了一個連綿無盡
的小森林一樣，這裏無數的松樹，柏樹，白楊，還有很多叫不出來名
字的異種苗木，你走在其中，只想把這片樹林盡情的欣賞一遍，永不
出去才好。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "south" : __DIR__"senlin7",
            "north" : __DIR__"senlin4",
            "west" : __DIR__"senlin3",
            "east" : __DIR__"senlin8",
        ]));
        set("objects", ([ /* sizeof() == 1 */
            __DIR__"npc/jiading.c" : 1,
        ]));
        set("outdoors", "meizhuang");
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
