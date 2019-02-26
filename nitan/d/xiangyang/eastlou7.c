inherit ROOM;

void create()
{
        set("short", "城東箭樓");
        set("long", @LONG
這是東城頭的箭樓，裏面佈滿了一排的垛口，一排大宋的箭手們
正警惕地監視着城外的一舉一動，隨時準備給前來偷襲的蒙古兵以迎
頭痛擊。
LONG );
        set("indoors", "xiangyang");
        set("no_clean_up", 0);
        set("site", "east_out");
        set("no_fly",1);     
        set("exits", ([
                "east" : __DIR__"east_out1",
                "up" : __DIR__"eastlou8",  
                "down" : __DIR__"eastlou6",  
        ]));
        set("coor/x", -7780);
	set("coor/y", -770);
	set("coor/z", 70);
	setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "east" )
        return notify_fail("衝出去做什麼，送死啊？\n");
        return ::valid_leave(me,dir);
}