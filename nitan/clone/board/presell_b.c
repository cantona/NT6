inherit BULLETIN_BOARD;

void create()
{
        set_name("遊戲宣傳室留言版", ({ "board" }) );
        set("location", "/u/viremploy/presell");
        set("board_id", "presell_b");
        set("long", "請認真記錄。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

