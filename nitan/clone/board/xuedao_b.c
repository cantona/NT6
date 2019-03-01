// /clone/board/xuedao_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("血刀門弟子留言板",({ "board" }) );
        set("location", "/d/xuedao/shandong3");
        set("board_id", "xuedao_b");
        set("long","這是供血刀門弟子傳遞信息用的留言板\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
