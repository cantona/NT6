inherit ROOM;

void create()
{
        set("short", "黃員外府邸");
        set("long", @LONG
這裏是中州富豪黃員外府邸的前院，一面大大的牆門上畫
了個大的倒的富字。繞過牆門可以到黃員外的前廳。不過據説
黃員外是中州出了名的惡霸。沒什麼事的話還是不要進去為妙。
LONG);
        set("objects",([
                "/clone/quarry/gou2" : 2,
                __DIR__"npc/guanjia" : 1,
                __DIR__"npc/jiading" : 2,
        ]));
        set("exits", ([
                  "south" : __DIR__"yanlingdong1",
        ]));
        set("outdoors", "zhongzhou");

        set("coor/x", -9020);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}