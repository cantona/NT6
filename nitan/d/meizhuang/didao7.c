// didao7.c
inherit ROOM;

void create()
{
        set("short", "梅莊密道");
        set("long", @LONG
這是一條昏暗潮濕的地道，地道很長，兩邊點著兩根不太明亮的
火把，地道兩旁的牆壁上畫著很多不知道出自何人之手的壁畫，而且
畫得相當難看。北面有一扇鐵門，但是走進了才發現原來是虛掩的，
並沒有上鎖。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "west" : __DIR__"didao6",
            "north" : __DIR__"laofang",
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}