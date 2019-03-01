// Room: /binghuo/eastboat2.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "東海海面");
        set("long", @LONG
東海海面波平如鏡，大船在海鷗遊魚中穿行，風帶風帆，獵獵作
響。遠遠可見東邊海平線上，有個蔥蔥鬱鬱的小島，在萬千碧海中，
著實綠得可愛。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "wangpan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
