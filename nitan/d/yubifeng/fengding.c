// /yubifeng/fengding.c
// Last modified by winder 2003.9.2

int do_enter(string arg);

inherit ROOM;

void create()
{
        set("short", "玉筆峯");
        set("long", @long
只見山峯旁好大三個絞盤，互以竹索牽連，三盤互絞，升降竹籃，
需要上下的人等，只能在竹籃(basket)中上下。
long );
        set("exits", ([
                "east" : __DIR__"damen",
        ]));
        set("item_desc", ([
                "basket" : "那是一個竹籃，好像是裝人下山的。\n",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yubifeng");
        set("coor/x", 6110);
        set("coor/y", 5170);
        set("coor/z", 100);
        setup();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_enter", "zuan");
        add_action("do_enter", "jin");
}

int do_enter(string arg)
{
        object me = this_player();

        if( arg != "basket")
                return notify_fail("你要往那裏鑽？\n");
        message_vision("$N哈腰鑽進竹籃，只聽“嗖”地一聲，絞盤轉動，竹籃被急速放了下去。\n\n....\n\n只見眼前白雪耀眼，白雲飛動\n\n....\n\n", me);
        me->move(__DIR__"fengdi");
        return 1;
}