// Room: /d/shaolin/qfdian.c
// Date: YZC 96/01/19

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "千佛殿");
        set("long", @LONG
這是千佛殿。大殿入口是硃紅格扇，七寶玲瓏。內裏供奉的西天
諸佛，計有八菩薩，四金剛，五百阿羅，三千揭諦，十一大曜，十八
伽藍，以及眾優婆塞，優婆夷等。直看得你眼花繚亂。邊上有道小木
門。
LONG );
        set("exits", ([
                "southdown" : __DIR__"guangchang5",
                "north" : __DIR__"bamboo1",                
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/qing-guan" : 1,
        ]));
        create_door("north","木門","south",DOOR_CLOSED);
//        set("no_clean_up", 0);
        setup();
}
