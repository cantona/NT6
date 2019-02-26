// Written by Lonely@IsMUD.net (05/21/2009)

#include <ansi.h>
inherit BOSS;

void sp_attack();
void create()
{
        set_name(HIB "秦始皇殭屍" NOR, ({ "qin shihuang", "king", "qin" }));
        set("long", HIB "這曾是一位統一六國的王者，現在只是殭屍一個。\n" NOR);
        set("title", HIY "皇帝" NOR);
        set("attitude", "aggressive");
        set("str", 120);
        set("con", 120);
        set("dex", 120);
        set("int", 120);

        set("max_qi", 800000000);
        set("max_jing", 400000000);
        set("neili", 2500000000);
        set("max_neili", 2500000000);
        set("max_jingli", 500000000);
        set("jingli", 50000000);
        set("jiali", 400000);
        set("level", 200);
        set("combat_exp", 20000000000);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: sp_attack :),
        }));

        set("reborn/times", 3);
        set("death_msg", HIY "\n$N散落成一堆碎骨頭。\n\n" NOR);

        set_skill("force", 6500);
        set_skill("zixia-shengong", 6500);
        set_skill("huashan-neigong", 6480);
        set_skill("dodge", 6500);
        set_skill("feiyan-huixiang", 6500);
        set_skill("huashan-shenfa", 6500);
        set_skill("parry", 6520);
        set_skill("sword", 6520);
        set_skill("lonely-sword", 6520);
        set_skill("blade", 6500);
        set_skill("fanliangyi-dao", 6500);
        set_skill("strike", 6480);
        set_skill("hunyuan-zhang", 6480);
        set_skill("cuff", 6480);
        set_skill("poyu-quan", 6480);
        set_skill("literate", 6480);
        set_skill("martial-cognize", 6420);

        map_skill("cuff", "poyu-quan");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "lonely-sword");
        map_skill("blade", "fanliangyi-dao");
        map_skill("sword", "lonely-sword");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        set("clear_fuben", 1);
        set("rewards", ([
                "exp" : 15000,
                "pot" : 4500,
                "mar" : 450,
        ]));
        set("drops", ([
                "RA&LEGEND60" : 100, 
                "RA&LEGEND60" : 100, 
                "RA&LEGEND60" : 100, 
                "RA&LEGEND70" : 50, 
                "RA&LEGEND70" : 50, 
                "RA&LEGEND70" : 50, 
                "FI&/clone/goods/resolve-scroll"   : 50,
                "FI&/clone/tessera/rune27"   : 30,
                "FI&/clone/tessera/rune28"   : 20,
                "FI&/clone/tessera/rune29"   : 10,
                "FI&/clone/tessera/rune30"   : 5,
                "FI&/clone/goods/wangzhe-zhixin"   : 2,
/*
                "FI&/clone/unique/xuanyuan_sword"   : 1,
                "FI&/clone/unique/ganjiang_sword"   : 1,
                "FI&/clone/unique/moye_sword"   : 1,
                "FI&/clone/unique/chengying_sword"   : 1,
                "FI&/clone/unique/chixiao_sword"   : 1,
                "FI&/clone/unique/chunjun_sword"   : 1,
                "FI&/clone/unique/qixing_sword"   : 1,
                "FI&/clone/unique/taie_sword"   : 1,
                "FI&/clone/unique/yuchang_sword"   : 1,
                "FI&/clone/unique/zhanlu_sword"   : 1,
*/
        ]));
        set_temp("apply/attack", 50000+random(30000));
        set_temp("apply/damage",50000+random(30000));
        set_temp("apply/unarmed_damage",50000+random(30000));
        set_temp("apply/armor", 50000+random(30000));
        set_temp("apply/add_weak", 90);
        set_temp("apply/reduce_damage", 90);
        set_temp("apply/reduce_busy", 36);
        set_temp("apply/add_busy", 50);

        setup();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        object me;

        ::init();
        if (! interactive(me = this_player()) ||
            this_object()->is_fighting())
                return;

        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}

void sp_attack()
{
        object *enemies, enemy, ob;
        object *obs;
        string msg;
        int i;

        enemies = query_enemy();
        if( !enemies || sizeof(enemies) == 0 )
                return;
        enemy = enemies[random(sizeof(enemies))];
           obs=filter_array(all_inventory(environment(this_object())),(:query("id", $1) == "skeleton fighter":)); 
        if( sizeof(obs) < 7 && !random(5) ) {
                msg = HIY"$N展開手中的黑色幡布，頓時陰風呼號，慘霧瀰漫，召喚出數個骷髏武士，\n"
                         "這些骷髏生前是秦皇身邊的護衞，死後仍然受他驅策，慘嘯着向$n撲來！\n"NOR;
                message_vision(append_color(msg, HIY),this_object(),enemy);
                for( i=0;i<3;i++ ) {
                        ob = new(__DIR__"skeleton");
                        ob->set_from_me(enemy);
                        ob->move(environment(enemy));
                        ob->kill_ob(enemy);
                }
                return;
        }
        if( !enemy->is_busy() && sizeof(ob) > 3 && !random(5) ) {
                msg = HIY"$N祭起手中的五色石印，只見那石印飛到空中，射出一道濛濛青光，把$n籠罩在內。\n"
                         "$n只覺得身體彷彿被一座大山壓住，四肢動彈不得，就連呼吸都十分艱難，只能眼\n"
                         "睜睜地看着骷髏獰笑着一步步走近！\n" NOR;
                message_vision(append_color(msg, HIY),this_object(),enemy);
                enemy->start_busy(5);
                return;
        }
        /*
        秦皇殭屍久攻不下，感到十分不耐煩，於是把河圖虎符都仍在一旁，從身邊的劍鞘中
        拔出一把青光閃閃的寶劍，雖然在棺中歷經千年歲月，這把寶劍仍然光可鑑人，鋒利
        無匹。燭光跳動間你赫然看見，劍鞘上刻着兩個篆字：鹿盧。
        */
        switch( random(5) ){
                case 4: msg = HIY "$N"HIY"手一揮，一道金光化作一把利劍射從$n"HIY"穿體而過！\n"NOR; break;
                case 3: msg = HIW "$N"HIW"張開大口，一道道冰刀迅猛而至，$n"HIW"只覺自己氣血凝滯，頓受重創。\n"NOR; break;
                case 2: msg = HIR "$N"HIR"雙掌併力將一巨大的火球推向$n"HIR"，$n"HIR"被燒的體無完膚。\n"NOR; break;
                case 1: msg = MAG "$N"MAG"一聲嚎叫，口中吐出黃沙，狂風呼嘯，那尖利的嘯聲夾雜這黃沙如刀，如劍，越來越尖... 越來越急...\n"
                                  "$n"MAG"全身頓時千創百孔，鮮血直湧而出。\n"NOR;break;
                default: msg= HIG "$N"HIG"腳一跺地，只見$n"HIG"腳邊的地上快速生長出樹藤緊緊包裹這$n"HIG"，$n"HIG"頓時呼吸不暢，頭暈眼花。\n"NOR; break;
        }
        message_vision(msg,this_object(),enemy);
        if( !random(20) ) enemy->unconcious(); 
        enemy->receive_damage("qi",5000000+random(5000000),this_object());
        COMBAT_D->report_status(enemy);
        if( !enemy->is_busy() )
                enemy->start_busy(2);
        return;
}

varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        return;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        int damage;
        int reduce;

        damage = 10000 + random(10000);
        reduce=query_temp("apply/reduce_fire", ob);
        damage -= damage * reduce / 100;
        if( damage < 0 ) damage = 0;
        ob->receive_damage("qi", damage, me);
        ob->receive_wound("qi", damage, me);
        set("neili",query("max_neili",  me), me);
        return HIY "$N" HIY "全身閃出耀眼的金光，登時令$n"
               HIY "全身有若刀絞。\n" NOR;
}
