inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "大草原");
        set("long", @LONG
這裏就是蒙古大草原了，蒙古軍營就在不遠初了，你似乎可以聽
到蒙古軍隊的馬蹄聲，你不禁放慢了腳步，儘量隱蔽大軍的行蹤，試
圖偷偷接近蒙古軍的軍營。
LONG );
        set("outdoors", "xiangyang");
        set("no_magic",1);

        set("exits", ([
                   "south"  : __DIR__"caoyuan3",
                   "north"  : __DIR__"myuanmen1",
        ]));

        setup();
} 
