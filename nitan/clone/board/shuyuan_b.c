// /clone/board/shuyuan_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("先賢的傳說", ({ "board" }) );
        set("location", "/d/city/shuyuan2");
        set("board_id", "shuyuan_b");
        set("long", "先賢的江湖風雨，傳說故事。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
