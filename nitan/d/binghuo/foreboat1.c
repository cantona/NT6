// Room: /binghuo/foreboat1.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "東海海面");
        set("long", @LONG
東海海面波平如鏡，大船在海鷗遊魚中穿行，風帶風帆，你也不
知道船往哪裡去。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "binghuo");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
