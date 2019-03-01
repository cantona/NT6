// /clone/board/taindihui_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("天地會弟子留言板", ({ "board" }) );
        set("location", "/d/beijing/qingmu_dating");
        set("board_id", "tiandi_b");
        set("long", "這是一個供天地會弟子交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
