//Room: /d/dali/wuyiminju3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","烏夷民居");
        set("long",@LONG
這是一所烏夷族的房屋。此間正處市鎮，四周無山勢可依，門口
正對巷陌。青石大房，裝修頗為不俗，大門是精心雕制的，刻有
日、月、虎豹等精美的圖案，看來這裡是烏撒部的祭祀大屋。
LONG);
        set("exits",([ /* sizeof() == 1 */
            "enter"  : __DIR__"jisidawu1",
            "east"   : __DIR__"zhenxiong",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19220);
	set("coor/y", -6860);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}