// /clone/board/xiake_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("俠客島留言板", ({ "board" }) );
        set("location", "/d/xiakedao/dating");
        set("board_id", "xiake_b");
        set("long", "這是一個供來到俠客島的貴賓交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

