// /clone/board/taohua_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("桃花島弟子留言板", ({ "board" }) );
        //set("location", "/d/taohua/dating");
        set("location", "/d/taohua/jingshe");
        set("board_id", "taohua_b");
        set("long", "這是一個專供桃花島弟子使用的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

