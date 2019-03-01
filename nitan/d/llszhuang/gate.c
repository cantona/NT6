#include <ansi.h>
inherit ROOM;
void create()
{
         set("short", "柳綠山莊正門");
        set("long",
"柳綠山莊現在就聳立在你的面前，這山莊看起來已久久無人居住，大\n"
"雪堆積在檐上，瓦上，廊上，樑上，隱隱有一股殺氣透出來。莊牆外到處\n"
"是積雪，一支生鏽的鐵箭訂在牆上，兀自涔涔滴血。雪地上是觸目驚心的\n"
"血字：\n"+ 
        HIR"                      一 入 柳 綠 莊\n" 
       "                      此 生 不 還 鄉\n\n\n"NOR 
);

        set("exits", ([ /* sizeof() == 2 */
          "north" : __DIR__"yongdao1",
          "south" : __DIR__"xueyuan",
        ]));
        set("no_magic", "1");


        setup();
}
