// Room: /d/yanziwu/chixia.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "赤霞莊");
        set("long", @LONG
這裏是赤霞莊。莊上是慕容世家藏兵之所。慕容家自失國以來，三
十世以降，皆不忘復國。這裏的兵器足應一時之需。
    莊外湖面正繫着一尾小舟(zhou)。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
                "south"  : __DIR__"bingqi",
        ]));
        set("item_desc", ([
                "zhou" : "這是赤霞莊和外界聯繫的小舟。舟上一個綠衫少女。島上的客人只要\n登舟(enter)就可以離開了。\n",
        ]));
        set("coor/x", 820);
        set("coor/y", -1850);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_enter", "enter");
}
int do_enter(string arg)
{
        object ob ;
        string dir;
        if( !arg || arg !="zhou" ) 
        {
                tell_object(this_player() , "你要投水？\n");
                 return 1 ;
        }
        ob = this_player();
message_vision("船上一個秀美温柔的江南少女看到$N登舟，竹篙輕點，舟已
離岸，赤霞莊漸漸在視野裏遠去。\n", ob);
        ob ->move(__DIR__"taihu") ;
        tell_object(ob, HIG "你在湖上飄流，四周看不盡的江南美景。\n" NOR ) ;
        call_out("home", 10 , ob );
        return 1 ;
}
void home( object ob )
{
        tell_object(ob , "小舟終於戀戀不捨地靠岸了。你走下小舟來。少女揮手依依道別。\n" ) ;
        ob->move (__DIR__"muti") ;
}