#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "萬安寺寺門");
        set("long", @LONG
這裏便是萬安寺的大門所在，那萬安寺樓高四層，寺後的一座十三級寶塔更
老遠便可望見。大門內外不時有親兵在來回巡視察看，戒備很是森嚴。
LONG );

    set("exits", ([
        "enter" : "/d/tulong/yitian/was_dayuan",
        "south" : "/d/tulong/yitian/road3",
    ]));

    set("objects", ([
        "/d/tulong/yitian/npc/bing1" : 4,
        "/d/tulong/yitian/npc/bing2" : 1,
    ]));
    setup();
}

int valid_leave(object me,string dir)
{
        object ob;

        if ( dir == "enter" && ob = present("qianfu zhang"))
        {
                ob->command("tnnd"+query("id", me));
                message_vision(CYN "$N喝道：亂黨賊子，敢在這裏撒野？去死吧！\n" NOR,ob,me);
                ob->kill_ob(me);
                ob=present("guan bing 1");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("guan bing 2");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("guan bing 3");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("guan bing 4");
                if (objectp(ob)) ob->kill_ob(me);
                return notify_fail("大門被蒙古兵擋住了。\n");
        }
        return 1;
}
void init()
{
        object sword, me;
        me = this_player();
        if ((objectp(sword = present("yitian sword", me))))
        {
                remove_call_out("yixiao_rob");
                call_out("yixiao_rob", 1, me, sword);
        }
}

void yixiao_rob(object me, object sword)
{
        message_vision(HIC "\n只聽一聲詭異的長笑，一條青影向$N" HIC
                       "直撲而來，你定睛一看，原來是明教四大護"
                       "教法王之一的「" NOR+HIB 
                       "青\n翼蝠王" NOR+HIC
                       "」韋一笑。\n\n" NOR,  me);

        if ((int)me->query_skill("parry") < 400)
        {
                message_vision(HIW "$N" HIW "只見對方來勢洶湧，連忙抽身抵擋，"
                           "頓時只覺手中一輕，倚天劍已被韋一笑"
                           "奪了過去！\n\n" NOR, me);
                sword->move(environment(me));
                destruct(sword);
                shout(HIR "\n【倚天屠龍】" NOR+WHT "韋一笑：嘿嘿，多謝你將倚天劍取回，咱們後會有期。\n" NOR );
        }
        else {
                message_vision(HIW "$N" HIW "見對方來勢洶湧，當即縱身躍起，半"
                           "空中拔出倚天劍，劃出一道美麗的寒芒直貫韋一"
                           "笑，只聽韋\n一笑一聲慘嚎，" NOR+HIR 
                           "鮮血" NOR+HIW 
                           "飛濺。\n\n", me);
        }
        write(HIC "韋一笑長嘯一聲，施展絕世輕功，飛身飄然而起，揚起一路塵"
              "埃，已不見了蹤影......\n" NOR);
}
