// /clone/board/guiyun_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("歸雲莊記事板", ({ "board" }) );
        set("location", "/d/guiyun/dayuan");
        set("board_id", "guiyun_b");
        set("long", "這是一個專供桃花島弟子在島外使用的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

