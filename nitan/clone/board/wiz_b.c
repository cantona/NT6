// /clone/board/wiz_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("巫師留言簿", ({ "board" }) );
        set("location", "/d/wizard/wizard_room");
        set("board_id", "wiz_b");
        set("long", "這是一個專供巫師使用的留言板。\n" );
        set("poster_level", 1);
        set("wizard_only", 1);
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

