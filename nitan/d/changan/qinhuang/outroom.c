// This is a room made by wsl.

inherit ROOM;
int do_climb(string arg);
void create()
{
    set("short", "兵馬俑");
        set("long", @LONG
來到這裏似乎已經無路可走了，左面有個石台，不知是做什麼用
的，石台的上方可以看到許多植物的根，盤根錯節，有些已經長到了
石台上了。
LONG );
        set("exits", ([
          "south" : __DIR__"shidao5",
]));
    setup();
}
void init()
{
        add_action("do_climb", "climb");
        add_action("do_jump", "jump");
        add_action("do_pa", "爬");
}
int do_climb(string arg)
{
        object me = this_player();
        if( !arg || arg == "" ) return 0;
        if( query_temp("pa", me))return notify_fail("你已經在石台上了，還爬什麼呀！\n");
        if( arg == "石台" ) {
                message_vision("$N想都不想，就爬上了去。\n",me);
        set_temp("pa", 1, me);
        return 1;
        }
}
int do_jump(string arg)
{
        object me = this_player();
        if( !query_temp("pa", me))return 0;
        if( !arg || arg == "") return notify_fail("你要跳到什麼地方去呀？\n");
        if( query_temp("jump", me))return notify_fail("你已經跳下來了。\n");
        if( arg == "down" ) {
                message_vision("$N提了提氣，又跳了下去。\n",me);
        set_temp("jump", 1, me);
        delete_temp("pa", me);
        return 1;
        }
}
int do_pa(string arg)
{
        object me = this_player();
        if( !query_temp("pa", me))return 0;
        if(!arg || arg == "") return notify_fail("你要往那爬？\n");
        if( arg == "根" ) {
                message_vision("$N顫悠悠地爬上了盤在石台上的樹根......\n",me);
        delete_temp("pa", me);
        delete_temp("jump", me);
        call_out("go_up", 10 , me );
        return 1;
        }
}
void go_up(object me)
{
        if(!me) return;
        tell_object(me, "你順着樹根爬呀...爬呀......\n你爬了很久，終於你又見到了陽光。\n");
        me->move("/d/changan/caodi.c");
}       