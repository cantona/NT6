// /clone/board/bonze_b.c

#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
    set_name(HIC "古村留言版" NOR, ({ "board" }) );
    set("location", "/d/newbie/shijiezhishu");
        set("board_id", "newbie_b");
        set("long", "這是新手村的留言版，可以輸入 post <標題> 留言。\n" );
        setup();
        set("capacity", 500);
        replace_program(BULLETIN_BOARD);
}

