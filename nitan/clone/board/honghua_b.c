// /clone/board/honghua_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("紅花會留言板", ({ "board" }) );
        set("location", "/d/huijiang/zongduo");
        set("board_id", "honghua_b");
        set("long", "這是一個供紅花會眾交流的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

