//room: mtdating.c
inherit ROOM;
void create()
{
        set("short","大廳");
        set("long",@LONG
這就是摩天崖了。上面光禿禿的，連一棵小樹也沒有，峯頂到
也十分開闊，但身周雲霧繚繞，當真是置身雲端之中，使人心驚肉
跳。東面有一個小木屋，門邊立着一塊青白色石碑(bei)。
LONG );
        set("outdoors", "motianya");
        set("exits",([
                "east" : __DIR__"mtxiaowu",
                "down" : __DIR__"mtyadi",
        ]));
        set("item_desc",([
                "bei" : "   『摩天崖』  \n無「玄鐵令」者禁入！\n",
        ]));
        set("objects",([
                __DIR__"npc/xieyan" : 1,
        ]));
        set("coor/x", -2100);
        set("coor/y", -1700);
        set("coor/z", 30);
        setup();
}

int valid_leave(object me, string dir)
{
        if (  (dir == "east")
                && (!present("xuan tie",me))
                && objectp(present("xie yanke", environment(me))) )
        return notify_fail
                ("謝煙客把手一攔：你沒有「玄鐵令」，不能進去！\n");
        return ::valid_leave(me, dir);
}