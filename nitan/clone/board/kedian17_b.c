// Last Modified by winder on Feb. 28 2001
// /clone/board/kedian17_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("客店留言板", ({ "board" }) );
        set("location", "/d/hanzhong/kedian1");
        set("board_id", "kedian17_b");
        set("long", "有有用的話就往這裏説，亂灌水殺無赦。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

