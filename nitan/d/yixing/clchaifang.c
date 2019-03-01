// /d/yixing/clchaifang.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "柴房");
        set("long", @LONG
一間簡單的柴房，普通的幫眾可以在這裡幹點雜活。劈好的木柴
凌亂地堆在牆角，旁邊是砍柴刀（chaidao）和笤帚（tiaozhou）。門
後還有個水缸，卻已經空了。時而也有幫眾過來打個盹。
LONG );
        set("exits", ([
                "east" : __DIR__"clzoulang1",
        ]));
        set("item_desc",([
                "chaidao"  : "一把鋒利的砍柴刀。\n",
                "tiaozhou" : "一把用來掃地的笤帚。\n",
        ]));

        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_steal", 1);

        set("coor/x", 269);
	set("coor/y", -1001);
	set("coor/z", -1);
	setup();
}

void init()
{
        add_action("do_get", "get");
}

int do_get(string arg)
{
        object obj;

        if( arg && objectp(obj = present(arg, environment(this_player()))) &&
                obj->is_character() )
        {
                write("你不能搬動玩家的身體。\n");
                return 1;
        }
        else
                return 0;
} 