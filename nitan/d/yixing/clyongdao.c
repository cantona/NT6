// /d/yixing/clbajiaoting.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "甬道");
        set("long", @LONG
長長的甬道通向一個石室，旁邊壁上每隔不遠便有一盞油燈，頭上
是高高的拱頂，顯得有些陰森可怖。幾名幫眾在這裡把守，閒雜人等不
能隨意前進。
LONG );
        set("exits", ([
                "east" : __DIR__"clshishi",
                "west" : __DIR__"clhuayuan",
        ]));
        set("objects",([
                __DIR__"npc/cl_bangzhong" : 1,
        ]));
        set("coor/x", 299);
	set("coor/y", -991);
	set("coor/z", -1);
	setup();
}

int valid_leave(object me, string dir)
{
        object ob;

        if( dir != "east" ) return ::valid_leave(me, dir);
        if( !(ob = present("changle bangzhong", environment(me))) )
                 return ::valid_leave(me, dir);
        if( !living(ob) ) return ::valid_leave(me, dir);
        return notify_fail(sprintf("%s攔在你面前，說道：裡面是關押本幫叛徒的地方，你請回吧。\n", ob->name()));
}