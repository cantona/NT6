inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "玄嶽門");
        set("long", @LONG
你的面前是一座林木繁茂的高山，幾座山峯在雲霧中隱約可見，
一條石階向山上延伸，走着幾個進香客。一個四柱三間五樓式的石坊
跨山而建，正面鐫有「治世玄嶽」四個大字，原來這就是天下聞名的
武當山。武當山一名太和山，為七十二福地之一，有二十七峯、三十
六巖、二十四澗、五台、五井、三潭、三天門、三洞天和一福地，百
裏內密樹森羅，蔽日參天景物幽絕。
LONG );
        set("objects", ([
                CLASS_D("wudang") + "/zhike": 1,
                CLASS_D("wudang") + "/daotong": 2,
        ]));
        set("outdoors", "wudang");
        set("exits", ([
                "east"     : __DIR__"slxl3",
                "southup"  : __DIR__"shijie1",
        ]));
        set("coor/x", -370);
        set("coor/y", -180);
        set("coor/z", 20);
        setup();
}