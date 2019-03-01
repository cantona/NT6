// Room: /d/yanziwu/huafang.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "五湖舫");
        set("long", @LONG
堤岸邊緊靠著一艘三丈長許的漢白玉畫舫。前桅上高掛著一盞紅燈
籠。舫中雕欄琉瓦，透著江南水鄉的靈氣。每個窗洞中桌台上擺放著紅
燭，想來靜夜紅燭，定有十分情調。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "westup" : __DIR__"hongxia1",
        ]));
        set("coor/x", 1260);
        set("coor/y", -1250);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}