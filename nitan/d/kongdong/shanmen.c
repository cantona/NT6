//1997-3-10 by qyz
#include <room.h>

inherit ROOM;



void create()
{
        set("short","崆峒山門");
        set("long",@LONG
一片蒼松古柏之間，掩映着崆峒山門，此地環境清幽靜謐，入口處，一棟高
大的門樓，古色古香，頂上書“崆峒勝境”三個燙金大字，門柱上是一副筆走龍
蛇，字體遒勁的石刻楹聯：“洞天福地，名山寶剎”，往裏進去是一條平坦的青
石大道，一直引向裏面的庭院。
LONG);
        set("exits",
        ([
          "southdown" : __DIR__"juxian_qiao",
          "west" : __DIR__"qipan_ling",
          "north" : __DIR__"tingyuan",
        ]));
        create_door("north","紅漆木門","south",DOOR_CLOSED );
        setup();
}
