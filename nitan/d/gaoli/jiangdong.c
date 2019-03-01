// /d/gaoli/xuanwumen
#include <ansi.h>


inherit ROOM;


void create()
{
        set("short", "鴨綠江東岸");
        set("long", @LONG
面前是一條波濤翻滾的大江(river)。 濁流滾滾，萬舟競發。兩岸
渡船來來往往，江邊一長溜擺滿了魚攤，漁家就將船泊在岸邊，幾個破
蘿上面支一塊木板，板上擺滿了活蹦亂跳的鯉魚。不少過江客都在這裡
等待渡船擺渡。
LONG
        );

        set("exits", ([
                "east" : __DIR__"dadao2",
                "west" : __DIR__"jiangkou",

        ]));



        set("outdoors", "/d/gaoli/edao2");
        setup();
}

