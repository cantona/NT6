// didao6.c

inherit ROOM;

void create()
{
        set("short", "梅莊密道");
        set("long", @LONG
這是一條昏暗潮濕的地道，地道很長，兩邊點着兩根不太明亮的
火把，地道兩旁的牆壁上畫着很多不知道出自何人之手的壁畫，而且
畫得相當難看，你加快腳步，想知道地道的盡頭是什麼地方。 
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "south" : __DIR__"didao7",
                "east"  : __DIR__"didao6",
                "north" : __DIR__"didao5",
                "west"  : __DIR__"didao4",
        ]));

        setup();
        replace_program(ROOM);
}
