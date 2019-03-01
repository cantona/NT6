//1997-3-10 by qyz
#include <room.h>

inherit DOOR_ROOM;



void create()
{
        set("short","庭院");
        set("long",@LONG
這裡是一個庭院，院內香樟成林，古木參天，濃蔭鬱綠，中間一條石甬道，
古樸典雅，甬道中有一古井，名為靈泉井，傳說是前輩先師白玉蟾奉天師法旨所
開。大院西牆下立著一塊石碑，由于年代已久，上面的字跡已經看不清楚了，院
裡還栽了一棵九裡香，虯枝勁幹，葉茂花盛，不時發出一陣陣淡淡的清香。
LONG);
        set("exits",
        ([
          "south" : __DIR__"shanmen",
          "north" : __DIR__"zhaohe_tang",
        ]));
        set("need_clean", "崆峒派");
        set("outdoors","kongdong");
        create_door("south","紅漆木門","north",DOOR_CLOSED);
        set("objects",([
                __DIR__"npc/ke" : 2,
                ]) );
        setup();
 
}
