// /clone/board/riyue_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("日月神教教眾記事板", ({ "board" }) );
        set("location", "/d/heimuya/chengdedian");
        set("board_id", "riyue_b");
        set("long", "這是一個專供日月神教教眾在使用的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

