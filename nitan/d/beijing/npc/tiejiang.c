// smith.c

#include <ansi.h>

inherit SMITH;

mixed  ask_back();

void create()
{
        set_name("鐵匠", ({ "tie jiang", "tie", "smith" }));
        set("title", "鐵匠舖老板");
        set("shen_type", 1);

        set("gender", "男性" );
        set("age", 33);
        set("long", "鐵匠正用鐵鉗夾住一塊紅熱的鐵塊放進爐中。\n");

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                "/clone/weapon/changjian",
                "/d/baituo/obj/tiezheng",
                "/clone/weapon/longbow",
                "/clone/weapon/wolfarrow",
                "/clone/weapon/zhujian",
                "/clone/weapon/hammer",
                "/clone/weapon/tudao",
                "/clone/weapon/dagger",
                "/clone/weapon/tiegun",
                "/clone/weapon/gangdao",
                "/clone/cloth/tiejia",
                "/clone/weapon/gangjian",
                "/clone/weapon/qimeigun",
                "/clone/weapon/dadao",
                "/clone/weapon/jiedao",
                "/clone/weapon/falun",
                "/clone/weapon/arrow",  
                "/clone/weapon/bow",  
                "/clone/weapon/bow1",
                "/clone/weapon/bow2",
                "/clone/weapon/bow3",
                "/clone/weapon/bow4",
                "/clone/weapon/bow5",
                "/clone/weapon/bow6",
                "/clone/weapon/bow7",
                "/clone/weapon/bow8",                                
                "/d/item/obj/jingtie",
        }));

        set("inquiry", ([
                "血海無邊" : (: ask_back :),
        ]));

        setup();

        carry_object("/d/beijing/npc/obj/hammer")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

/*
varargs int receive_damage(string type, int n, object who)
{
        if (! objectp(who) || ! interactive(who) || who == this_object())
                return 0;

        tell_object(who, HIR "你發現" + name() +
                    HIR "詭秘一笑，忽然覺得一陣心悸，神智一陣恍惚。\n" NOR);
        return who->receive_damage(type, n, this_object());
}

varargs int receive_wound(string type, int n, object who)
{
        if (! objectp(who) || ! interactive(who) || who == this_object())
                return 0;

        tell_object(who, RED "你忽見" + name() +
                    RED "桀桀怪笑，只覺得渾身都是一痛，直入骨髓深處。\n" NOR);
        return who->receive_wound(type, n, this_object());
}
*/

mixed ask_back()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "血刀門" )
        {
                message_vision("$N自顧自的幹活，好象沒有聽見$n在說什麼。\n",
                               this_object(), me);
                return -1;
        }

        message_vision("$N猛然抬起頭來，上上下下打量了一會"
                       "兒$n，眼角微微一動，\n放下手中的活"
                       "計，低聲道：快跟我來。\n說罷，$N領"
                       "著$n急急忙忙的朝後面走去。\n", this_object(), me);
        tell_object(me, "你跟著" + name() + "急急的走著，來到了"
                    "一處秘道，" + name() + "指著前面道：“一直走"
                    "就行了，去吧！”\n");
        tell_object(me, HIW "你走了很久，越來越冷，忽然眼前一亮，"
                    "你已經看到了陽光，只見附近的積雪映得眼花繚亂。\n" NOR);
        me->move("/d/xuedao/sroad8");
        return -1;
}

