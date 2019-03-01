inherit ROOM;
void create()
{
        set("short", "城外空地");
        set("long", @LONG
這是城外的空地，一些蒙古兵的姦細和箭手常在這帶遊弋，以尋
找他們感興趣的獵物，不時有幾枚冷箭從頭頂嗖地飛過，令人防不勝
防。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);
        set("step",9);
        set("no_fly",1);     
        set("exits", ([
               "east" : __DIR__"east_out1",
               "west" : __DIR__"east_out8", 
        ]));
        set("coor/x", -7770);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
}