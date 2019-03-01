// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "北樓");
        set ("long", @LONG
上得樓來，只見中間靠窗放著一張大書桌，放著筆墨紙硯與十來本
書，還有一件縫了一半的小孩衣衫。這是萬家公子萬圭住的地方。
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "down"  : __DIR__"wan_ketang",
        ]));
        set("objects", ([
                __DIR__"npc/wangui"    : 1,
                __DIR__"obj/lianpen"    : 1,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2010);
	set("coor/z", 10);
	setup();
}
void init()
{
        add_action("do_put","put");
        add_action("do_put","jin");
        add_action("do_put","fang");
}
int do_put(string arg)
{
        object ob, me = this_player();
        if (arg != "tangshi book")
                return notify_fail("你要把什麼浸到臉盆中去？\n");
        if (! objectp(ob = present("tangshi book", me)))
                return notify_fail("你沒有這本書。\n");
        message("vision", me->name()+"把唐詩選輯浸到臉盆中去，書上慢慢顯示出數字來。哇！唐詩劍法！\n", environment(me));
        destruct(ob);
        ob = new("/clone/book/tangshi_book");
        ob->move(me);
        return 1;
}