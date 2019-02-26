// Roo: /d/guu/yaofang.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"藥房"NOR);
        set("long", @LONG
這裏是一間石室，周圍的火把將石室照的燈火通明，石室裏面擺滿
了很多瓶瓶罐罐，上面都貼好了標籤，一瓶瓶玉蜂漿被古墓弟子製成後
放在此處。你能看見幾個古墓弟子正在忙碌的幹活。
LONG        );
        set("exits", ([
                "north" : __DIR__"mudao10",
        ]));
        set("objects", ([
                __DIR__"obj/yaolu" : 1,
                __DIR__"npc/baiyi_yaofang" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3220);
        set("coor/y", -30);
        set("coor/z", 90);
        setup();
}

//void init()
//{
//        add_action("do_make","make");
//        add_action("do_make","huo");
//}

int do_make(string arg)
{
        object ob, name1, me = this_player();
        int exp,pot,score;

        ob= present("feng mi", me);
        name1=query("id", me);
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着呢。\n");
        if ( arg =="jiang")
        {
                if( !query_temp("gm_job1", me) )
                        return notify_fail("你還沒去採蜜呢，怎麼來制玉蜂漿？\n");
                if (!objectp(present("feng mi", me)))
                        return notify_fail("你用什麼來製成玉蜂漿？\n");
                if( query_temp("gm/make", ob) != name1 )
                        return notify_fail("這蜂蜜好像不是你採來的吧？\n");
                message_vision(HIY"$N仔細地將蜂蜜調和均勻，製成玉蜂漿，放在架上。\n"NOR,me);
                delete_temp("gm_job1", me);
                exp=40+random(20);
                addn("combat_exp", exp, me);
                pot= 10+random(10);
                addn("potential", pot, me);
                score=2+random(5);
                addn("score", score, me);
                call_out("destroying", 1, ob);
                tell_object(me,HIW"因為勞作，你增長了：" + chinese_number(exp) + "點實戰經驗" + chinese_number(pot) + "點潛能" + chinese_number(score) + "點江湖閲歷。\n"NOR);
                return 1;
        }
        return notify_fail("你想把蜂蜜製成什麼啊？\n");
}

void destroying(object ob)
{
        destruct(ob);
        return;
}
