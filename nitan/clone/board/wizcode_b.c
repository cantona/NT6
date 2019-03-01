// /clone/board/wizcode_b.c
inherit BULLETIN_BOARD;
void create()
{
        set_name("程序更新留言簿", ({ "board" }) );
        set("location", "/d/wizard/meeting_room");
        set("board_id", "wizcode_b");
        set("long", "這是一個專供巫師記錄程序更新情況的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}