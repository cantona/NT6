// /clone/board/xueshan_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("雪山寺弟子留言板",({ "board" }) );
        set("location", "/d/xueshan/dadian");
        set("board_id", "xueshan_b");
        set("long","這是供雪山寺弟子傳遞信息用的留言板\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
