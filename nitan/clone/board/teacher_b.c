inherit BULLETIN_BOARD;

void create()
{
        set_name("新手導師室留言版", ({ "board" }) );
        set("location", "/u/viremploy/teacher");
        set("board_id", "teacher_b");
        set("long", "請認真記錄。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

