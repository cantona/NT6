// /clone/board/meizhuang_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("日月神教梅莊記事板", ({ "board" }) );
        set("location", "/d/meizhuang/dating");
        set("board_id", "meizhuang_b");
        set("long", "這是一個專供日月神教教眾在梅莊使用的留言板。\n" );
        setup();
        set("capacity", 300);
        replace_program(BULLETIN_BOARD);
}

