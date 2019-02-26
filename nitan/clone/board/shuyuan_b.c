// /clone/board/shuyuan_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("先賢的傳説", ({ "board" }) );
        set("location", "/d/city/shuyuan2");
        set("board_id", "shuyuan_b");
        set("long", "先賢的江湖風雨，傳説故事。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
