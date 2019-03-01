// zoulang2.c
inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是一條長長的走廊，走廊兩邊是四位莊主中的其他三位平時休
息和練功的地方，這裏的左邊是棋室，右邊則是梅莊弟子感覺勞頓的
時候休息的地方，二莊主黑白子不分晝夜都在棋室裏研究他那些不知
道哪兒找來的古棋譜。 
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "west" : __DIR__"qishi",
            "east" : __DIR__"xiuxishi",
            "north" : __DIR__"zoulang3",
            "south" : __DIR__"zoulang1",
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
