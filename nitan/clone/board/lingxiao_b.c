// /clone/board/lingxiao_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("凌霄城弟子留言板", ({ "board" }) );
        set("location", "/d/lingxiao/dadian");
        set("board_id", "lingxiao_b");
        set("long", "這是一個供凌霄城弟子交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
