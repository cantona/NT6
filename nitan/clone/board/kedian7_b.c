// /clone/board/kedian7_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("客店留言板", ({ "board" }) );
        set("location", "/d/hangzhou/kedian");
        set("board_id", "kedian7_b");
        set("long", "有有用的話就往這裡說，亂灌水殺無赦。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
