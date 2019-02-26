inherit BULLETIN_BOARD;

void create()
{
        set_name("匿名留言版", ({ "board" }) );
        set("location", "/d/wizard/noname_room");
        set("board_id", "noname_b");
        set("noname_board", 1);
        set("private_board", 1);
        set("long", "説吧，除了巫師沒人知道是你説的內容。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}


       
