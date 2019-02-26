inherit ROOM;

void create()
{
        set("short", "汴梁南街");
        set("long", @LONG
這裏是南大街了，西邊是一家店鋪，牆上寫着一個大大的『當』
字，仔細傾聽，可以聽到壓低的討價還價的聲音，東邊是一家錢莊，
不時傳來錢兩銀錠的叮噹聲。
LONG );
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "north" : __DIR__"nandajie2",
                "south" : __DIR__"chengmen",
        ]));  
        set("objects", ([
//                "/d/shaolin/npc/tiao-fu" : 1,
//                "/maze/battle3/npc/xiaofan" : 1,
        ]));

        setup();
  }
