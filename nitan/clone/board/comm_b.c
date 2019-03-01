
inherit BULLETIN_BOARD;
void create()
{
        set_name("玩家交流板", ({ "board" }) );
        set("location", "/d/city/tree");
        set("board_id", "comm_b");
        set("long", "這是一塊供玩家交流心得的留言板。\n");
        setup();

        set("capacity", 218);
        replace_program(BULLETIN_BOARD);
}

