// /clone/board/wudang_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("武當弟子留言板", ({ "board" }) );
        set("location", "/d/wudang/sanqingdian");
        set("board_id", "wudang_b");
        set("long", "這是一個供武當門下交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

