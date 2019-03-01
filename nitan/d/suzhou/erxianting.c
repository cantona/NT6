// Room: /d/suzhou/erxianting.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "二仙亭");
        set("long", @LONG
二仙亭在千人石東側，建于北宋。亭壁嵌兩方石碑，分別刻著五代
宋初陳摶與唐代呂洞賓二仙像。亭柱上有兩幅石刻楹聯：“夢中說夢原
非夢，元裡求元便是元”；“昔日岳陽曾顯跡，今朝虎阜再留蹤”。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"qianrenshi",
                "north" : __DIR__"bailianchi",
        ]));
	set("coor/x", 1110);
	set("coor/y", -1040);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}