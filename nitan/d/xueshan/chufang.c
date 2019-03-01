inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
 這裡是雪山寺的廚房，新來的僧人可以在此打雜。房中醒目的位
置有一塊牌子，但已經破舊不堪，字跡模糊了,依稀看的出：恭喜發財到此一遊？！？@
LONG );
        set("exits", ([
                "south" : __DIR__"xiaoyuan",
        ]));

        set("objects", ([
                __DIR__"obj/cha" : 2 + random(2),
                __DIR__"obj/nailao" : 2 + random(2),
        ]));

        set("resource/water", 1);

        set_temp("times" , 5);
        setup();
}