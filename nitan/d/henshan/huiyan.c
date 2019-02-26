inherit ROOM;

void create()
{
        set("short", "回雁樓");
        set("long", @LONG
這裏是衡陽回雁樓，是本地最大的酒樓。往日這時已經十分忙碌
的酒樓今天卻有點異樣。一個年近四十的白衣漢子，正端坐自飲，桌
面橫放着一把快刀，旁邊卻坐着一個小尼姑，滿臉憂急愁苦之色，容
貌卻十分秀麗。
LONG );
        set("exits", ([
               "down" : __DIR__"shop",
        ]));
        set("objects", ([
                __DIR__"npc/tian"   : 1,
                __DIR__"npc/yilin"  : 1,
        ]));

        set("no_clean_up", 0);

	set("coor/x", -6900);
	set("coor/y", -5710);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}