inherit ROOM;

void create()
{
        set("short", "中央廣場");
        set("long", @LONG
這裏是汴梁城中央廣場了了，北面就是皇宮正門了，一般的尋常
百姓都不敢到那裏去，不過在這裏還是相當的熱鬧，街頭賣藝的，唱
戲的都雲集於此，形成一大景光。
LONG );
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "north" : __DIR__"ydmen",
                "south" : __DIR__"nandajie2",
        ]));

        set("objects", ([
//                "/maze/battle3/npc/flowerg" :    1,   
        ]));

        setup();
        replace_program(ROOM);
}
