inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "洞穴");
        set("long", @LONG
這裡是洞壁高處的一個洞穴，地方小得只能容納一個人存身。這
裡黑洞洞的什麼也看不見，只有洞旁的一株奇異的小草，葉面閃爍著
點點的磷光，顯得鬼魅異常。
LONG );

        set("objects", ([
                  __DIR__"obj/duanchang": 1,
        ]));
    

        setup();
}

void init ()
{
        add_action("do_use", "use");
        add_action("do_fire","fire");
        add_action("do_fire","dian");
        add_action("do_insert","insert");
        add_action("do_climb","climb");
}

int do_use(string arg)
{
        object me;
        me = this_player();

        if ( !arg || arg == "" ) return 0;
        if ( !present("fire", me)) return 0;
        if ( arg == "fire" )
        {
                write( HIY "你點燃了火折，可是洞穴裡實在太黑了，一支火折遠不"
                       "夠，看來要找支火把才行。\n\n" NOR);
                return 1;
        }
}

int do_fire (string arg)
{
        object me = this_player();

        if ( !arg || arg != "huo ba" )
                return notify_fail ("你想點燃什麼？\n");

        if ( !present(arg, me))
                 return notify_fail("你身上沒有這樣東西。\n");

        message_vision (HIR "$N" HIR "“嚓”的一聲點亮一支火把！\n\n" NOR, me);
        message_vision (HIY "剎那間四周被照得清清楚楚！\n" NOR, me);
        this_object()->recreate();
        set_temp("fire_huoba", 1, me);
        remove_call_out ("precreate");
        call_out ("precreate",20,this_object());
        destruct(present(arg,me));
        return 1;
}

void precreate (object me)
{
        tell_room (me, WHT "光線忽的一暗，火把熄滅了，四周又變得一片漆黑！\n\n" NOR);
        delete_temp("fire_huoba", me);
        me->create();
}

int do_insert (string arg)
{
        object ob;
        object me = this_player();

        if( query_temp("fire_huoba", me)<1 )
             return notify_fail("四周黑漆漆的，什麼也看不見啊？\n");

        if ( !arg || arg != "tong pai")
             return notify_fail("你要插入什麼？\n");

        if ( !present(arg, me))
             return notify_fail("你身上沒有這樣東西啊！\n");

        if( query_temp("fire_huoba", me)<1 )
             return notify_fail("四周黑漆漆的，什麼也看不見啊？\n");

        message_vision (HIY "$N" HIY "試著將銅牌插入石壁上的小孔中！\n\n" NOR,me);
        message_vision (HIC "忽然一陣隆隆的劇烈震動，$N" HIC "只覺得一陣天旋地轉！\n\n" NOR, me);
        destruct(present(arg,me));

        ob = load_object(__DIR__"mishi");
        ob = find_object(__DIR__"mishi");

        message("vision",HIR+query("name", me)+HIR"忽然從室頂縫隙中滑了進來。\n"NOR,ob);
        message_vision (HIR "$N" HIR "忽然覺得腳下一空，竟掉了下去！\n\n" NOR,me);
        delete_temp("fire_huoba", me);
        me->move(__DIR__"mishi");
        return 1;

}
int do_climb(string arg)
{
       
        object me = this_player();
        object ob;

        if( (!arg) ||!((arg == "巖壁") || (arg == "wall")))
             return notify_fail("你要爬什麼？\n");
        message_vision(HIC "$N" HIC "小心翼翼的攀著巖壁上突出的石筍爬了下去。\n\n" NOR,me);

        ob = load_object(__DIR__"wandu3");
        ob = find_object(__DIR__"wandu3");

        message("vision",HIC+query("name", me)+HIC"從巖壁上爬了下來。\n"NOR,ob);
        me->move(__DIR__"wandu3");
        return 1;
}

void recreate ()
{
        set ("short", "洞穴");
        set ("long", @LONG
這是一個狹窄的洞穴，四周石壁濕漉漉的，長滿了青苔。你仔細
觀察一下四周的情況，發現洞內深處有一塊石壁非常平整，象是有人
力的痕跡，正中間有一個扁扁的小孔，好象可以插入(insert)什麼東
西試試。
LONG);

        setup();
}