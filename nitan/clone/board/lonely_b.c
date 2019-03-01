// /clone/board/lonely_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("工作筆記", ({ "board" }) );
        set("location", "/u/lonely/workroom");
        set("board_id", "lonely_b");
        set("long", "這是一個專供Lonely使用的工作筆記。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

