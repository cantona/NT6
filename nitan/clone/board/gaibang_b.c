// /clone/board/gaibang_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("丐幫弟子留言板", ({ "board" }) );
        set("location", "/d/yueyang/gaibangtang");
        set("board_id", "gaibang_b");
        set("long", "這是一個供丐幫弟子交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

