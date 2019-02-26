// Room: /d/songshan/zhongmen.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;
void create()
{
        set("short", "中門");
        set("long", @LONG
這裏是峻極禪院通往後庭的中門，門厚三寸，紅松銅箍，門上兩幅
門神經多年風雨，多有剝落，現下顏色尚新，想來是嵩山派新近油漆了
的。外派人士到此就該回頭了。
LONG );
        set("outdoors", "songshan");
        set("exits", ([
                "south" : __DIR__"chanyuan",
                "north" : __DIR__"huimengtang",
        ]));
        set("objects", ([
                CLASS_D("songshan")+"/yao": 1,
        ]));
        set("coor/x", -20);
        set("coor/y", 880);
        set("coor/z", 90);
        setup();
}

/*
int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);
        if( query("combat_exp", me)<100000)return 1;
        if ( (!myfam || (myfam["family_name"] != "嵩山派")) &&
                (dir == "north") &&
                objectp(present("yao hou", environment(me))))
                return notify_fail("樂厚一抬手攔住了你：非嵩山弟子，到此止步吧。\n");
        else return 1;
}
*/
