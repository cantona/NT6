// /clone/board/gumu_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("古墓派弟子留言板", ({ "board" }) );
        set("location", "/d/gumu/zhongting");
        set("board_id", "gumu_b");
        set("long", "這是一個供古墓派門下交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

