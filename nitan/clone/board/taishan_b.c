// /clone/board/taishan_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("泰山弟子留言板", ({ "board" }) );
        set("location", "/d/taishan/riguan");
        set("board_id", "taishan_b");
        set("long", "這是一個供泰山門下交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

