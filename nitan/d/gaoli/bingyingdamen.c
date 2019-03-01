

inherit ROOM;

void create()
{
        set("short", "兵營大門");
        set("long", @LONG
你正站在兵營的門口，面對著一排簡陋的營房，可以看到穿著制服
的官兵正在操練，不時地傳來吶喊聲。老百姓是不允許在此觀看的，你
最好還是趕快走開為妙。
LONG
        );

        set("exits", ([
                "north" : __DIR__"qinglong-1",
                "south" : __DIR__"bingying",
        ]));
           set("objects", ([
                "/d/gaoli/npc/bing" : 2,
        ]));
 setup();
        replace_program(ROOM);
}        
