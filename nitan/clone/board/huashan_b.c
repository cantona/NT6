// /clone/board/huashan_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("華山弟子留言板", ({ "board" }) );
        set("location", "/d/huashan/buwei3");
        set("board_id", "huashan_b");
        set("long", "這是一個供華山門下交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

