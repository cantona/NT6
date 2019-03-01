inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這裡是少林寺的練武場。由無數塊巨大的花崗巖石板舖就。上千
年的踩踏已使得這些石板如同鏡子般平整光滑。練武場中間豎立著不
少草靶。十來個僧人正在練習武藝。西面有一長溜僧房。
LONG );
        set("exits", ([
                "south" : __DIR__"zoulang3",
                "west" : __DIR__"wuchang",
                "east" : __DIR__"luohan5",
                "north" : __DIR__"zoulang7",
        ]));
        set("outdoors", "shaolin");
        set("objects",([
                "/clone/npc/mu-ren" : 4
        ]));
        setup();
        replace_program(ROOM);
}
