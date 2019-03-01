inherit BULLETIN_BOARD;

void create()
{
        set_name("主頁維護室留言版", ({ "board" }) );
        set("location", "/u/viremploy/webmaster");
        set("board_id", "webmaster_b");
        set("long", "請認真記錄。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

