// Room: /d/guiyun/zoulang6.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short","走廊");
        set("long",@LONG
這是從中廳通向練武場的走廊。長長的走廊曲曲折折，雕欄畫柱，
彩繪鏤空，滿目綠意，兩旁種滿了花樹。
LONG );
        set("exits",([
                "north" : __DIR__"zoulang5",
                "south" : __DIR__"lianwuchang",
        ]) );
        set("outdoors", "guiyun");
        set("objects",([
                __DIR__"npc/zhuangding3" : 1,
        ]));  
        set("coor/x", 250);
        set("coor/y", -850);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "south" && query("family/family_name", me) != "桃花島" )
                if (present("zhuang ding", this_object()))
                        return notify_fail("一位莊丁攔住了你，恭恭敬敬地說：“這位貴客請留步，那面是本莊弟子的練武場。”\n");
/*
                else
                        return notify_fail("一位莊丁忽然從花叢裡鑽了出來，攔住了你，恭恭敬敬地說：“這位貴客請留步，那面是本莊弟子的練武場。”\n看你停步不動了，那位莊丁一拱手，又退回了隱身處。\n");
        
*/
        return ::valid_leave(me, dir);
}