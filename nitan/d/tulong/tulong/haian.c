#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "蔚藍海邊");
        set("long", @LONG
無邊無際的大海就在眼前了。海風拂面，一洗過往旅客的一路勞頓。海風清
涼，略有點鹹味，海面微微泛着波浪。碧藍的的海水上面湧動的潔白的浪花，海
面飄着輕輕的薄霧。茫茫的大海上沒有一點帆影，極目遠眺，海天交界處濛濛一
片，分不出哪裏是海，哪裏是天。
LONG );

        set("exits", ([
                "south" : "/d/beijing/haigang",
                "east" :  "/d/tulong/tulong/shatan",
        ]));

        set("objects", ([
                "/d/tulong/yitian/npc/huiyue" : 1,
                "/d/tulong/yitian/npc/miaofeng" : 1,
        ]));

        set("no_clean_up", 0);
        set("outdoors", "tulong");
        setup();
}
