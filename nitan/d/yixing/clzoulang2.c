// /d/yixing/clzoulang2.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這裡往來的人少了些，西面不斷傳來陣陣吵鬧之聲，有時還夾雜著
怒罵和尖叫。空中彌漫著煙酒的氣味。地上顯得甚是骯臟，拋棄著一些
油膩的殘羹剩菜。
LONG );
        set("exits", ([
                "east"  : __DIR__"clhuayuan",
                "west"  : __DIR__"clxiaowu",
                "south" : __DIR__"clzoulang1",
                "north" : __DIR__"clxiaoting",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yixing");
        set("coor/x", 279);
	set("coor/y", -991);
	set("coor/z", -1);
	setup();

        replace_program(ROOM);
}