inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","冰洞");
        set("long",@LONG
蛇！一條足有水桶粗的白蛇，正橫臥在冰洞正中，望見有人
進來，呼地一聲直立起來，吐出血紅的信子，徑直撲了過來。帶
過來一股腥臭的味道。旁邊一面冰壁很薄，隱約可見裡面有什麼
東西。
LONG);
        set("exits",([
                    "out"  : __DIR__"wave2", 
        ])); 
        set("objects", ([
                "/clone/beast/xuanmang" : 1, 
        ]));
        setup();
}

void init()
{
        add_action("do_break", "break");
}

int do_break(string arg)
{
            object me;
            me = this_player();

            message_vision(HIW "$N" HIW "走到冰壁前，運勁向冰壁轟去！\n" NOR, me);

            if( query("neili", me)<2000 )
            {
                       message_vision(HIR "結果只聽一聲悶哼，$N" HIR "被冰壁的"
                               "寒氣回侵經脈，眼前一黑……\n" NOR, me);
                       set("neili", 0, me);
                       me->unconcious();
                       return 1;
            }
            message_vision(HIY "$N" HIY "只聽一聲轟響，冰壁被轟穿了，露出一"
                       "個小洞來。\n" NOR, me);
            set("exits/enter", __DIR__"yudong");
            set("neili", 0, me);
            remove_call_out("close");
            call_out("close", 5, this_object());
            return 1;
}

void close_out()
{
            if (query("exits/enter")) delete("exits/enter");
}

void close(object room)
{
            message("vision", HIW "一股寒氣自洞中冒出，將洞口又凍了個嚴嚴實實。\n"
                          NOR, room);
            delete("exits/enter", room);
}

int valid_leave(object me)
{
        if (objectp(present("xuanbing chimang", environment(me))))
                   return notify_fail(HIY "你正欲離開此地，卻只見" NOR + HIW "玄冰" NOR +
                                   HIR "赤" NOR + HIW "蟒" NOR + HIY "一個盤旋，頓時將"
                                   "去路完全封鎖。\n" NOR);
        return ::valid_leave(me);
}
