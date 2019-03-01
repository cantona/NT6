inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "大草原");
        set("long", @LONG
這裡就是蒙古大草原了，蒙古軍營就在不遠初了，你似乎可以聽
到蒙古軍隊的馬蹄聲，你不禁放慢了腳步，盡量隱蔽大軍的行蹤，試
圖偷偷接近蒙古軍的軍營。
LONG );
        set("outdoors", "xiangyang");
        set("no_magic",1);

        set("exits", ([
                    "west"  : __DIR__"caoyuan",
                    "east"  : __DIR__"caoyuan2", 
        ]));

        setup();
} 
