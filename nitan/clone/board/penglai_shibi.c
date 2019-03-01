inherit BULLETIN_BOARD;

void create()
{
        set_name("蓬萊石壁", ({ "stone" }) );
        set("location", "/d/penglai/haitan");
        set("board_id", "penglai_shibi");
        set("long", "這是塊石壁，可以在上面刻字留言(post)。\n" );
        setup();
        set("capacity", 300);
        replace_program(BULLETIN_BOARD);
}

