// zoulang1.c
inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是一條長長的走廊，走廊兩邊是四位莊主中的其他三位平時休
息和練功的地方，這裏的左邊是書室，右邊是畫室，三莊主禿筆翁和
四莊主丹青生在閒來無事的時候，便到那裏面去揮毫，潑墨。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "west" : __DIR__"shushi",
            "east" : __DIR__"huashi",
            "north" : __DIR__"zoulang2",
            "south" : __DIR__"neiyuan",
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
