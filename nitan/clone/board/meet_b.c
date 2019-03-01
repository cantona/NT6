#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
        set_name("會議記錄簿", ({ "board" }));
        set("location", "/d/wizard/meeting_room");
        set("board_id", "meet_b");
        set("long", HIY "這堵牆上刻滿了希奇古怪的咒文，也不知道記載了些什麼。\n" NOR);
        setup();
        set("capacity", 1000);
        replace_program(BULLETIN_BOARD);
}

