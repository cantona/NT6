// dbshan.c 冰山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"冰山"NOR);
        set("long", @LONG
大冰山在日光的照射下發出刺眼的光芒，顯得十分奇麗，這裡到
處都是冰雪，冰山頗大，如陸地上之山丘，一眼望去，橫百余丈，縱
長幾十丈，冰山上滑不留步。海中不時有幾塊小浮基正在向北飄流。
LONG );
        set("outdoors", "極北");
        set("exits", ([  
              "west" : __DIR__"dbshan",
        ]));

        setup();
}
