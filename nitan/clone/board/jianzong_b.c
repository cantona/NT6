// /clone/board/jianzong_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("華山劍宗弟子留言板", ({ "board" }) );
        set("location", "/d/huashan/xiaowu");
        set("board_id", "jianzong_b");
        set("long", "這是一個供華山劍宗門下交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

