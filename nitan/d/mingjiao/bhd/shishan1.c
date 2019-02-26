// shishan1.c 小石山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", YEL"小石山"NOR);
        set("long", @LONG
這是一座小山石，比之西面的石山要小多了。山石周圍到處都是
奇花異樹，異樹叢中傳來陣陣的奇香，皆由不知名之花朵傳出。山腳
下露出一個小小的石洞(dong)，西邊有一座石山。
LONG );
	set("outdoors","冰火島");
        set("resource/water", 1);
	set("exits",([
		"west"  :  __DIR__"shishan",
	]));
        set("item_desc", ([
                "dong" : "這是一個山洞，裏面不知道有些什麼古怪。\n",
        ]));
	setup();
}

void init()
{
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object me;
        me = this_player();
        if( arg=="dong") {
            message("vision",me->name()+"一彎腰往洞裏走了進去。\n",environment(me), ({me}) );
            me->move(__DIR__"xdong");
            message("vision",me->name()+"從洞外走了進來。\n",environment(me), ({me}) );
            return 1;
        }
}       
