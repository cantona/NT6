// /clone/board/player_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("江湖恩怨留言板", ({ "board" }) );
        set("location", "/d/city/chaguan");
        set("board_id", "player_b");
        set("long", "這是一個供玩家發泄江湖恩怨的留言板。謝絕人身攻擊。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

