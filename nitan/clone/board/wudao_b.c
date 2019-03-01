// /clone/board/wudao_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("比武大會成績版", ({ "board" }) );
        set("location", "/d/city/wudao4");
        set("board_id", "wudao_b");
        set("long", "這是一個專供公布每月比武大會成績的布告板，其他灌水殺無赦。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

