// /clone/board/kedian6_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("客店留言板", ({ "board" }) );
        set("location", "/d/xiangyang/kedian");
        set("board_id", "kedian6_b");
        set("long", "有有用的話就往這裡說，亂灌水殺無赦。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
