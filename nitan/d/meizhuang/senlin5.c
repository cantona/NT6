// senlin5.c
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
        set("exits", ([ /* sizeof() == 8 */
            "southeast" : __DIR__"senlin4",
            "northeast" : __DIR__"senlin2",
            "west" : __DIR__"senlin2",
            "east" : __DIR__"senlin2",
            "north" : __DIR__"senlin3",
            "south" : __DIR__"senlin5",
            "northwest" : __DIR__"senlin4",
            "southwest" : __DIR__"senlin6",
        ]));
        set("outdoors", "meizhuang");
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
