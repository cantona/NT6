// /clone/board/gaibang_r.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("揚州城人物偵測報告", ({ "report" }) );
        set("location", "/d/gaibang/pomiao");
        set("board_id", "gaibang_r");
        set("long", "這是一個供丐幫弟子交流信息的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

