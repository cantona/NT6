
inherit BULLETIN_BOARD;

void create()
{
        set_name("工作筆記", ({ "board" }) );
        set("location", "/u/wuji/workroom");
        set("board_id", "wuji_b");
        set("long", "這是一個專供wuji使用的工作筆記。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

