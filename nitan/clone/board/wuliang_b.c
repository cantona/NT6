// /clone/board/wuliang_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("無量弟子留言板", ({ "board" }) );
        set("location", "/d/wuliang/road1");
        set("board_id", "wuliang_b");
        set("long", "這是一個供無量劍門下交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

