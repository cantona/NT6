// /d/gaoli/xuanwumen
#include <ansi.h>


inherit ROOM;


void create()
{
        set("short", "渾江口");
        set("long", @LONG
渾江口西岸也是相當熱鬧，自西岸渡口往西，一條筆直的土路直通
山海關。此地民風淳樸，路旁夾柳成陰，酒廝林立，且都有一面大大的
「酒」旗迎風飄揚，蔚為壯觀。也有不少小販沿路叫買，語多難辨，卻
也令人盛情難卻。
LONG
        );

        set("exits", ([
                "west" : __DIR__"dadao1",
                "southwest" : __DIR__"yucun",
                "east" : __DIR__"jiangdong",

        ]));

        set("outdoors", "/d/gaoli/hunjiangkou");
        setup();
}

