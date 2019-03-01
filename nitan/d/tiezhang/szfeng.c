#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIR "食指峰" NOR);
        set("long", @LONG
你終于爬上了峰頂，已經累得氣喘吁吁了。這裡只有丈許方圓的一小塊
地方，寸草不生，到處都是光禿禿的巖石。一陣狂風呼嘯而過，吹得你一個
趔趄，差點摔倒，看來還是趕快離開這裡的好。
LONG );

        set("exits", ([
                "southdown" : __DIR__"juebi-1",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "tiezhang");
        setup();
}