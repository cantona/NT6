// Room: /d/xingxiu/xxroad5.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
山勢在這裡漸漸變得平緩，你已經可以聽見西邊山澗底的水聲。東
面有一個山洞。
LONG );
        set("exits", ([
                "south" : __DIR__"xxroad4",
                "enter" : __DIR__"cangku",
                "north" : __DIR__"xxroad6",
        ]));
        set("objects", ([
                CLASS_D("xingxiu")+"/chuchen" : 1,
        ]) );
//        set("no_clean_up", 0);
        set("outdoors", "xingxiu");
        set("coor/x", -51000);
        set("coor/y", 20120);
        set("coor/z", 30);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((!myfam || myfam["family_name"] != "星宿派") &&
                dir != "south" && (present("chuchen zi", environment(me))))
        {
                say("出塵子一言不發，閃身攔在"+me->name()+"面前。\n");
                return notify_fail("出塵子一言不發，閃身攔在你面前。\n");
        }
        return ::valid_leave(me, dir);
}