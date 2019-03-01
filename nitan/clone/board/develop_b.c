inherit BULLETIN_BOARD;

void create()
{
        set_name("開發意見留言版", ({ "board" }) );
        set("location", "/d/wizard/develop_room");
        set("board_id", "develop_b");
        set("long", "請您注意您的留言主題和內容。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
