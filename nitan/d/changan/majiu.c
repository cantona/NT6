#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short", "馬廄");
        set("long", @LONG
這裡是長安城的馬廄，常年供應新鮮草料。長安民眾富裕來往商
賈甚多，因此馬夫們對馬好生照看，將它們喂飽飲足再洗刷得幹乾凈
凈，一直伺候到客人上路。馬廄雨檐下的爛木柱上釘著塊破木牌 (pa
izi)。馬廄中堆放著幾堆草料。
LONG );
        set("outdoors", "changan");
        set("no_fight", 1);
        set("no_beg", 1);
        set("no_clean_up", 0);
        set("resource/water", 1);        

        set("objects", ([
                "/clone/horse/zaohongma" : 1,
                "/clone/horse/huangbiaoma" : 1,
                "/clone/horse/ziliuma" : 1,
                "/clone/npc/mafu" : 1,
        ]));

        set("exits",([
                "south" : __DIR__"huarui1",
                "up"    : "/clone/shop/changan_shop",
               "north" : __DIR__"business",
        ]));
        set("coor/x", -10750);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}