//htqdating.c
inherit ROOM;

void create()
{
        set("short", "厚土旗大廳");
        set("long", @LONG
這裡是厚土旗的大廳，廳中刀槍如林，黃旗招展，教眾穿著鐵甲
鋼盔，腰間別著鍬鏟錘鑽，一個個精神抖擻。正中端坐著個矮墩漢子，
就是厚土旗掌旗使顏垣。
LONG );
        set("exits", ([
                "out" : __DIR__"htqmen",
        ]));
        set("objects", ([
                __DIR__"npc/yanyuan": 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}