// /clone/board/kunlun_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("昆侖弟子留言板", ({ "board" }) );
        set("location", "/d/kunlun/qianting");
        set("board_id", "kunlun_b");
        set("long", "這是一個供昆侖門下交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

