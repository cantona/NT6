#include <ansi.h>;
inherit ROOM;
//inherit F_DEALER;

void init();
int do_kan(string arg);

void create()
{
        set("name", "唐門酒樓二樓");
        set("short", "唐門酒樓二樓");
        set("long",
"這裏是雅座，非常的清靜，一般沒有人來在這裏的，來的都是一些唐\n"
"門中人，好像找唐肥有事的。所以這裏雖然是雅座，卻是沒有生意的。老\n"
"板唐肥正坐在一扇窗子(window)的邊上，好像向外在看什麼東東。牆上掛\n"
"着一些個沒見過的字畫。\n"
);
        set("item_desc", ([
                "window" : HIG"一眼看去,早春的點點綠綠，讓你只覺得心曠神怡。。\n"NOR,
        ]));
        set("exits", ([
                "down" : __DIR__"jiulou",
        ]));
        set("objects", ([
                CLASS_D("tangmen") + "/tangfei" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        
}

void init()
{
        add_action("do_kan","kan");
}

int do_kan(string arg)
{
        object me;
        
        me = this_player();
        
        if ( !arg || arg!= "zihua")
           return notify_fail(HIR"不要亂看啊！\n"NOR);
           
        if( query("combat_exp", me)<120000 )
        {
                tell_object(me,HIR"心中頓覺氣塞，神智不由得迷亂起來。\n"NOR);
                if( query("qi", me)<500 )
                {
                        me->unconcious();
                        return 1;
                }       
                addn("qi", -500, me);
                addn("jingli", -50, me);
                return 1;
        }       
        
        if( query_temp("thua", me) )
           return notify_fail("不要再看了，看多了對你不好的！\n");
            
        if ( (int)me->query_skill("tangmen-jueqi",1) < 120)
           return notify_fail("好一幅風景畫，從來都沒有看過，真是不枉此生。\n");
        
        if( query_temp("thua1", me) )
        {
                set_temp("thua2", 1, me);
                delete_temp("thua1", me);
           return notify_fail("一聲怒吼：貪心的人不會有好下場的！\n");   
        }  
        
        message_vision(HIR"唐花"NOR+HIC"，一朵如此美麗的花，你不由的痴了...... \n"NOR,me);
        set_temp("thua", 1, me);
        return 1;
}
