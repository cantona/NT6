// /clone/board/hengshan_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("恆山弟子留言板", ({ "board" }) );
        set("location", "/d/hengshan/baiyunan");
        set("board_id", "hengshan_b");
        set("long", "這是一個供恆山門下交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

