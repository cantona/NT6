// caoebei.c
// By Jpei

inherit ROOM;

void create()
{
        set("short", "曹娥碑");
        set("long",@long
相傳曹娥死後葬于此，上虞令命邯鄲淳作文鐫碑(gravestone)以記
其事。時邯鄲淳年方十三，文不加點，一揮而就，立于墓側。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "north" : __DIR__"jiangbian",
                "east"  : __DIR__"nongshe",
        ]));
        set("no_clean_up", 0);
        set("item_desc", ([
                "gravestone" : "經過多年的風吹雨淋，碑上文字幾不可考，倒是背面有“黃絹幼婦外孫齏臼”這麼幾個字。\n",
                "bei" : "經過多年的風吹雨淋，碑上文字幾不可考，倒是背面有“黃絹幼婦外孫齏臼”這麼幾個字。\n",
        ]) );
	set("coor/x", 1030);
	set("coor/y", -1100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}