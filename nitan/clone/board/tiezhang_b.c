// tiezhang_b.c
// Last Modified by winder on Nov. 15 2000

inherit BULLETIN_BOARD;

void create()
{
        set_name("鐵掌幫弟子留言板", ({ "board" }) );
        set("location", "/d/tiezhang/guangchang");
        set("board_id", "tiezhang_b");
        set("long", "這是一個專供眾弟子交流使用的留言板。\n" );
        setup();
        set("capacity", 60);
        replace_program(BULLETIN_BOARD);
}

