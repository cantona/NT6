inherit ROOM;

void create()
{
        set("short", "英豪酒樓");
        set("long", @LONG
這是中州城最大的酒樓，南來北往的過客都要在此歇歇腳
喝壺好酒。説不準還會交到一兩個朋友。大廳挺寬敞，兩根大
柱子上有幾個斗大的字。要和朋友小聚，樓上還有雅座。據説
樓上還有休息室，專門為了那些有點貪杯的人準備的。
LONG);

        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
         set("exits", ([
                "west" : __DIR__"wendingbei1",
                "east" : __DIR__"majiu",
                "up"   : __DIR__"yinghaoup",
        ]));

        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));

        set("coor/x", -9030);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
}