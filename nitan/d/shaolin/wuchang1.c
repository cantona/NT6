inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這裡是少林寺的練武場。由無數塊巨大的花崗巖石板舖就。上千
年的踩踏已使得這些石板如同鏡子般平整光滑。練武場中間豎立著不
少木人。十來個僧人正在練習武藝。東面有一長溜僧房。
LONG );
        set("exits", ([
                "south" : __DIR__"zoulang2",
                "west" : __DIR__"banruo5",
                "east" : __DIR__"wuchang",
                "north" : __DIR__"zoulang6",
        ]));
        set("outdoors", "shaolin");
        set("objects",([
                "/clone/npc/mu-ren" : 4
        ]));
        setup();
        replace_program(ROOM);
}
