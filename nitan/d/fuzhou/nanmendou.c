// Room: /d/fuzhou/nanmendou.c
// Date: may.12 1998 Java
inherit ROOM;

void create()
{
        set("short", "南門兜");
        set("long", @LONG
南門兜中央有一株巨大古榕，根繁葉茂，濃蔭遮蓋樹畝，將整個街
口遮閉嚴實不漏日光。大榕樹下有一小洞(dong)，深藏根下。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "north"  : __DIR__"nandajie",
            "south"  : __DIR__"nanmen",
            "west"   : __DIR__"shiqiao",
            "east"   : __DIR__"xiaochang",
        ]));
        set("objects", ([
                __DIR__"npc/wu" : 1,
        ]));
        set("item_desc", ([
            "dong"   : "一個深邃幽暗的洞穴。\n",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -80);
	set("coor/y", -6200);
	set("coor/z", 0);
	setup();
}
void init()
{
        add_action("do_enter", "enter");
        add_action("do_enter", "zuan");
}

int do_enter(string arg)
{
        object me;
        mapping fam;

        me = this_player();
        if( !arg || arg=="" ) return 0;
        if( arg=="dong" )
        {
           if( (fam=query("family", me)) && fam["family_name"] == "丐幫" )
           {
               message("vision",
                        me->name() + "運起丐幫縮骨功，一彎腰往洞裡鑽了進去。\n",
                        environment(me), ({me}) );
               me->move("/d/gaibang/underfz");
               message("vision",
                        me->name() + "從洞裡走了進來。\n",
                        environment(me), ({me}) );
                        return 1;
           }
           else  return notify_fail("這麼小的洞，你鑽得進去嗎？\n");
       }
}