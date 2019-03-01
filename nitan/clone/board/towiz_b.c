// /clone/board/towiz_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("玩家意見留言板", ({ "board" }) );
        set("location", "/d/wizard/guest_room");
        set("board_id", "towiz_b");
        set("long", "這是一個供玩家和巫師交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

