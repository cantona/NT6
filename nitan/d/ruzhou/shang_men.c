inherit ROOM;

void create()
{
        set("short", "商家堡大門");
        set("long", @LONG
一座巨大的宅院映入你的眼簾，正對著你的是一扇朱漆銅釘
的大門，四周是近丈高的圍牆。大門的上方橫著一塊匾，匾上寫
著「商家堡」三個大字。
LONG);
        set("exits", ([
                "north"  : __DIR__"shang_qgc",
                "south"  : __DIR__"shang_road3",
        ]));
        set("objects", ([
                CLASS_D("shang") + "/zhen" : 1,
                __DIR__"npc/shang2" : 2,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -6750);
	set("coor/y", 1840);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        object zhen;

        if (dir != "north"
           || ! objectp(zhen = present("shang baozhen", this_object()))
            || (query("born_family", me) == "山東商家"
            && !query("family/family_name", me)) )
                return ::valid_leave(me, dir);

        return zhen->permit_pass(me, dir);
}