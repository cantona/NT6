inherit BULLETIN_BOARD;

void create()
{
        set_name("意見反饋板", ({ "board" }) );
        set("location", "/d/city/advice/advice");
        set("board_id", "game_advice");
        set("long", "有用的話就往這裏説，亂灌水殺無赦。\n" );
        setup();
        set("capacity", 100000);
        replace_program(BULLETIN_BOARD);
}



