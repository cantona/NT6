inherit ROOM;

void create()
{
        set("short", "中央廣場");
        set("long", @LONG
這裡是汴樑城中央廣場了了，北面就是皇宮正門了，一般的尋常
百姓都不敢到那裡去，不過在這裡還是相當的熱鬧，街頭賣藝的，唱
戲的都雲集于此，形成一大景光。
LONG );
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "north" : __DIR__"ydmen",
                "south" : __DIR__"nandajie2",
        ]));

        set("objects", ([
//                "/d/city2/npc/flowerg" :    1,   
        ]));

        setup();
        replace_program(ROOM);
}
