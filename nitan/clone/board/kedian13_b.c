// /clone/board/kedian13_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("客店留言板", ({ "board" }) );
        set("location", "/d/tiezhang/kedian");
        set("board_id", "kedian13_b");
        set("long", "有有用的話就往這裏説，亂灌水殺無赦。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

