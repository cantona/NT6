// Code of JHSH
// baituo snake 白駝山蛇谷的蛇
// 注意：千萬不可用在蛇谷以外的房間！
// by maco
#include <ansi.h>

inherit SNAKE;
void set_kind(int);

void create()
{
        set("age", 4);
        set("attitude", "peaceful");

        set("msg_fail", "$n衝$N嘶地一吐舌頭");
        set("msg_succ", "$n嘶嘶做響，蛇頭隨着$N的手動了起來");
        set("msg_trained","$n悄無聲息地游到$N的腳下不動了");
        set("wildness", 9);

        set("str", 26);
        set("cor", 30);

        set("combat_exp", 1000);

        set_temp("apply/attack", 15);
        set_temp("apply/damage", 6);
        set_temp("apply/armor", 2);
        set_kind(random(8));
        setup();
}

void set_kind(int poison)
{
        int s;

        if(poison > 7) poison = 7;

        s = random(40);

        switch( poison )
        {
        case 0:
                set_name("毒蛇", ({ "snake", "she" }) );
                set("long", "一隻有着三角形腦袋的蛇，尾巴沙沙做響。\n");
                set("combat_exp", 1000);
                break;
        case 1:
                set_name("黑蛇", ({ "hei she", "snake" ,"she" }) );
                set("long", "這條黑蛇身子黑得發亮，身上白點也是閃閃發光，張開大口，露出四根獠牙。\n");
                break;
        case 2:
                set_name("竹葉青", ({ "zhuye qing", "snake" }) );
                set("long", "一隻身體碧綠的蛇，顯得特別細小。\n");
                break;
        case 3:
                set_name("百步蛇", ({ "baibu she", "she", "snake" }) );
                set("long", "一條青色長蛇，黃鱗覆體。據説被百步蛇咬了，走出一百步必死無疑。\n");
                break;
        case 4:
                set_name("青花蛇", ({ "qinghua she", "she", "snake" }) );
                set("long", "一條混身青黃相間的毒蛇，斑條鮮明，蛇頭奇扁，作三角之形，顯具劇毒。\n");
                break;
        case 5:
                set_name("蝮蛇", ({ "fu she", "she", "snake" }) );
                set("long", "一條細頸青身的蝮蛇。\n");
                break;
        case 6:
                set_name("赤練蛇", ({ "chilian she", "chilian", "she", "snake" }) );
                set("long", "一條尺許長的赤練蛇，青紅斑斕，甚是可怖。\n");
                break;
        case 7:
                set_name("金線蛇", ({ "jinxian she", "she", "snake" }) );
                set("long", "一條方頭小蛇，全身綠鱗覆體，一條金線由蛇腹而下。\n");
                break;
        }
        set_weight(poison*600 + 9000);
        set("str", 30 + poison );
        set("con", 30 + poison );
        set("int", 20);
        set("dex", 30 + poison );

        set("max_jing", 800 + poison*200);
        set("max_qi", 800 + poison*200);
        set("eff_jing", 800 + poison*200);
        set("eff_qi", 800 + poison*200);
        set("jing", 800 + poison*200);
        set("qi", 800 + poison*200);

        set("combat_exp", (poison + 1)*60000);

        set_temp("apply/attack", 30 + s + poison*10 );
        set_temp("apply/damage", 30 + s + poison*10 );
        set_temp("apply/armor", 30 + s + poison*10 );

        set("snake_poison", ([
                "level"  : 45,
                "perhit" : 25,
                "remain" : 45,
                "maximum": 45,
                "supply" : 2,
        ]));
        set("bt_snake", 1);
}

void init()
{
        object ob;
        ::init();
        add_action("convert","bian");
        if (interactive(ob = this_player()) &&
            query("family/family_name", ob) != "歐陽世家" && 
                random(ob->query_kar() + ob->query_per()) < 30) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob);
                return;
        }
}

void die()
{
        object ob;
        message_vision("$N全身扭曲，翻騰揮舞，全身軟軟地散了開來。\n", this_object());
        ob = new(DRUG_D("shedan"));
        ob->move(environment(this_object()));
        destruct(this_object());
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        mixed poison;
        poison=query("snake_poison", me);

        if( poison && !query("snake_poison", victim) )
        {
            poison = poison["perhit"];
            victim->affect_by("snake_poison",
                              ([ "level" : poison/5 + random(poison/5),
                                 "id":query("id", me),
                                 "duration" :  poison/20 ]));
        }
        return HIR "只聽$n痛呼了一聲，給毒蛇狠狠的咬了一口！\n" NOR;
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="she") return 0;
        if( query("family/family_name", me) != "歐陽世家" )
                return notify_fail("你不能化蛇為杖。\n");

        if( query("name", this_object()) != "毒蛇" )
                return notify_fail(this_object()->name()+"不適合化為蛇杖。\n");

        if (random(me->query_skill("training",1)) <20) {
                kill_ob(me);
                return 1;
        }
        message_vision("$N左手按住蛇頭，右手輕撫其七寸，口中唸唸有詞，片刻間將蛇化為一根蛇杖。\n",
                me,);
                ob = new("/d/xingxiu/obj/shezhang");
        ob->move(environment(this_object()));
        destruct(this_object());
        return 1;
}