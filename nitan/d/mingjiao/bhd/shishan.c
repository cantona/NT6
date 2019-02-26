// shishan.c 石山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIW"石山"NOR);
        set("long", @LONG
這是一座山石，山石周圍到處是奇花異樹，異樹叢中傳來陣陣的
奇香，皆由不知名之花朵傳出。山腳下露出一個石洞(dong)，西面是
通住火山之路，東邊半里處有一小石山，北邊是一片片深不見底的大
叢林。
LONG );
	set("outdoors","冰火島");
	set("exits",([
		"west"  :  __DIR__"ysroad1",
		"east"  :  __DIR__"shishan1",
                "south" :  __DIR__"pingyan2",
                "north" :  __DIR__"cling",
	]));

        set("item_desc", ([
                "dong" : "這是一個很大的熊洞，裏面不知道有些什麼古怪。\n",
        ]));
	setup();
}

void init()
{
        if(!this_player()->query_condition("cold_wind") && !wizardp(this_player()))
        this_player()->apply_condition("cold_wind", 1);
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object me;
        me = this_player();
        if( arg=="dong" ) {
            message("vision",me->name()+"一彎腰往洞裏走了進去。\n",environment(me),({me}));
            me->move(__DIR__"xiongdong");
            message("vision",me->name()+"從洞外走了進來。\n",environment(me), ({me}));
            return 1;
        }
}       
