// This program is a part of NT MudLIB

#include <ansi.h>

inherit BOSS;

void check_weapon();
int is_stay_in_room();

void create()
{
        set_name(HIY "獨孤求敗" NOR, ({ "dugu qiubai", "dugu", "qiubai" }) );
        set("title", HIR "劍魔" NOR);
        set("long", HIR "這便是傳説中的劍魔獨孤大俠，據説天下間竟無一敵手。\n"
                        "獨孤求敗曾感慨：嗚呼，生平求一敵手而不可得，誠寂寥難堪也！\n" NOR);

        set("gender", "男性");
        set("age", 59);

        set("str", 500);
        set("int", 500);
        set("con", 500);
        set("dex", 500);

        set("shen", 8000000);

        set_temp("apply/attack", 1000000);
        set_temp("apply/unarmed_damage", 100000);
        set_temp("apply/damage", 100000);
        set_temp("apply/armor", 60000);

        set("reborn/times", 2);

        set("max_qi", 6000000000);
        set("eff_qi", 6000000000);
        set("qi", 6000000000);

        set("max_jing", 3000000000);
        set("jing", 3000000000);
        set("eff_jing", 3000000000);
        set("max_jingli", 4000000000);
        set("jingli", 4000000000);

        set("neili", 500000000);
        set("max_neili", 500000000);
        set("jiali", 50000);
        set("combat_exp", 10000000000);
        set("level", 200);

        set_skill("unarmed", 4500);
        set_skill("finger", 4000);
        set_skill("claw", 4000);
        set_skill("strike", 4000);
        set_skill("hand", 4000);
        set_skill("cuff", 4000);
        set_skill("parry", 4000);
        set_skill("dodge", 4000);
        set_skill("force", 4000);
        set_skill("sword", 4500);
        set_skill("blade", 4000);
        set_skill("zuoyou-hubo", 2500);

        set_skill("lonely-sword", 4000);
        set_skill("jiuyang-shengong", 4000);
        set_skill("yinyang-shiertian", 4500);
        set_skill("qiankun-danuoyi", 4000);
        set_skill("martial-cognize", 5000);
        set_skill("lingbo-weibu", 4000);
        set_skill("literate", 4000);
        set_skill("huajia-su", 800);

        set_skill("jingluo-xue", 4000);

        set("no_nuoyi", 1); // 不被挪移影響
        set("lonely-sword/nothing", 1); //無招
        set("yinyang-shiertian/shier", 12);
        set("yinyang-shiertian/yinyang", 12);
        set("yinyang-shiertian/qiankun", 12);

        map_skill("parry", "lonely-sword");
        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "lingbo-weibu");
        map_skill("unarmed", "yinyang-shiertian");
        map_skill("finger", "yinyang-shiertian");
        map_skill("strike", "yinyang-shiertian");
        map_skill("hand", "yinyang-shiertian");
        map_skill("cuff", "yinyang-shiertian");
        map_skill("claw", "yinyang-shiertian");
        map_skill("sword", "lonely-sword");

        prepare_skill("finger", "yinyang-shiertian");
        prepare_skill("unarmed", "yinyang-shiertian");

        // yun perform
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
              // 獨孤九劍
              (: command("perform sword.jian") :),
              (: command("perform sword.po twice") :),
              (: command("perform sword.qi and sword.yi") :),
              (: command("perform sword.po and finger.tian") :),
              (: command("perform sword.po and sword.yi") :),
               (: command("perform finger.tian twice") :),
              // 陰陽12t
              (: command("perform finger.tian twice") :),
              (: command("perform finger.zhen and finger.jiu") :),

              (: exert_function, "powerup" :),
              (: exert_function, "shield" :),
              //(: exert_function, "roar" :),
              (: exert_function, "recover" :),
              (: exert_function, "recover" :),
              (: exert_function, "dispel" :),
              (: check_weapon :),

        }));

        set("my_life", 1); // 當氣血低於10%的時候補滿一次，設置該參數為0

        //set("auto_perform", 1);
        set("end_time", 1800);  // 必須戰鬥不少於1800秒後死亡
        set("rewards", ([
                "exp"   : 60000,
                "pot"   : 20000,
                "mar"   : 2000,
                "weiwang" : 1000,
                "score" : 1000,
                "gold"  : 100,
        ]));

        set("drops", ([
                "FI&/clone/fam/super/dugu/bldan"       : 100,
                "FI&/clone/fam/super/dugu/bhxdan"      : 50,
                "FI&/clone/fam/super/dugu/bjxcao"      : 50,
                "FI&/clone/fam/super/dugu/hlzhi"       : 50,
                "FI&/clone/fam/super/dugu/jzdan"       : 50,
                "FI&/clone/fam/super/dugu/qhcao"       : 50,
                "FI&/clone/fam/super/dugu/qhdan"       : 50,
                "FI&/clone/fam/super/dugu/sxguo"       : 50,
                "FI&/clone/fam/super/dugu/tldan"       : 50,
                "FI&/clone/fam/super/dugu/xhcao"       : 50,
                "FI&/clone/fam/super/dugu/xmgu"        : 50,
                "FI&/clone/fam/super/dugu/qlndan"      : 50,
                "FI&/clone/armor/dugu/jianmo-zhiyu"       : 25,
                "FI&/clone/armor/dugu/jianmo-zhiyu2"      : 25,
                "FI&/clone/armor/dugu/jianmo-zhiyu3"      : 25,
                "FI&/clone/armor/dugu/jianmo-zhiyu4"      : 25,
                "FI&/clone/armor/dugu/jianmo-zhiyu5"      : 25,
                "FI&/clone/armor/dugu/jianmo-zhiyu6"      : 25,
                "FI&/clone/tessera/rune29"      : 10,
                "FI&/clone/tessera/rune30"      : 5,
                "FI&/clone/tongren/tongren"+(1+random(2)) : 50,
        ]));

        set_temp("apply/reduce_damage", 80);
        set_temp("apply/reduce_busy", 36);
        set_temp("apply/add_busy", 15);
        set_temp("apply/add_poison", 80);

        setup();

        carry_object("/clone/cloth/bupao")->wear();
        carry_object("/clone/weapon/xuantie-jian")->wield();

        // 設置地點劍冢
        set("startroom", "/d/jianzhong/maigu");
}

void heart_beat()
{
        // 解除不能perform yun的限制
        if (random(3) == 1)
        {
                delete_temp("no_perform");
                delete_temp("no_exert");
        }

        if (random(5) == 1)check_weapon();

        return ::heart_beat();
}

// 檢查武器
void check_weapon()
{
        object me, ob;

        me = this_object();

        // 同時補充內力
        set("neili", query("max_neili"));

        if (me->is_busy()) me->interrupt_busy(me, 1000);

        if (me->is_busy()) me->interrupt_me(me);

        if (! query_temp("weapon"))
        {
                if( !objectp(ob = present("xuantie jian", environment(me))) )
                ob = new("/clone/weapon/xuantie-jian");
                ob->move(me);
                "/cmds/std/wield"->main(me, "xuantie jian");
        }

        if (random(5) == 1)
        {
                delete_temp("no_perform");
                delete_temp("no_exert");

                addn_temp("apply/damage", 50000);
                if (random(10) == 1)
                        command("perform sword.tian twice");
                else
                        command("perform sword.po and finger.tian");
                addn_temp("apply/damage", -50000);

                if (random(2))
                {
                        delete_temp("eff/jiuyin-shengong/xin");
                }
        }

        if (random(10) == 1)
        {
                me->clear_condition();
        }

        // 很小几率恢復氣血
        if (random(1000) == 1)
        {
                if (query("eff_qi") < query("max_qi") / 3) addn("eff_qi", query("max_qi") / 5);
                if (query("qi") < query("max_qi") / 3) addn("qi", query("max_qi") / 5);
        }

        if (me->is_busy()) me->interrupt_busy(me);

        if (! me->is_fighting() || random(5) == 1)
        {
                command("yun powerup");
        }

        return;
}

int accept_hit(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_kill(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

void new_life()
{
        full_self(); // 補滿氣血

        delete_temp("no_perform");
        delete_temp("no_exert");

        set_temp("apply/attack", 1200000);
        set_temp("apply/unarmed_damage", 150000);
        set_temp("apply/damage", 150000);
        set_temp("apply/armor", 100000);

        delete("my_life");

        message_vision(HIG "\n$N" HIG "大喝一聲，目光頓時充滿殺意！\n\n" NOR, this_object());

        return;
}

int receive_damage(string type, int damage, object who)
{
        object *ppl;

        if( !who ) who = this_object()->query_last_damage_from();
        if( !who ) return;
        ppl = query_temp("damage_from");
        if( !arrayp(ppl) || !sizeof(ppl) ) ppl = ({});
        if( userp(who) && member_array(who, ppl) == -1 )
        {
                ppl += ({ who });
                set_temp("damage_from", ppl);
        }

        if (query("my_life") && query("qi") < query("max_qi") / 10)
        {
                new_life(); // 重生一次
                return 0;
        }

        return ::receive_damage(type, damage, who);
}

void die(object killer)
{
        string prop, name;
        mapping data;
        object ob, where;
        string *apply = ({ "reduce_busy", "avoid_busy", "def_damage", "avoid_weak",
                "add_locked", "reduce_damage", "add_busy", "add_weak", "avoid_locked",
                "add_damage", "add_skill" });

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
                return;
        }

        if( !objectp(killer) ) killer = this_object()->query_last_damage_from();
        if( !objectp(killer) ) killer = query_temp("last_damage_from");

        // 如果還未重生，則重生一次
        if (query("my_life"))
        {
                new_life();
                return;
        }

        if( time() < query_temp("end_time") ) // 時間沒有到，死亡不了
        {
                addn("jing", query("max_jing") / 10);
                if( query("jing") > query("max_jing") ) set("jing", query("max_jing"));
                addn("eff_jing", query("max_jing") / 10);
                if( query("eff_jing") > query("max_jing") ) set("eff_jing", query("max_jing"));
                addn("qi", query("max_qi") / 10);
                if( query("qi") > query("max_qi") ) set("qi", query("max_qi"));
                addn("eff_qi", query("max_qi") / 10);
                if( query("eff_qi") > query("max_qi") ) set("eff_qi", query("max_qi"));
                message_vision(HIR "\n$N" HIR "大喝一聲，運用祕法，氣血有所回升！\n\n" NOR, this_object());
                return;
        }

        where = environment();

        prop = apply[random(sizeof(apply))];
        name = EQUIPMENT_D->chinese(prop)+"元素";

        data = ([]);
        data["element"] = prop;
        data["name"] = name;
        ob = TEMPLATE_D->create_object("/inherit/template/element/element", prop, data);
        ob->set_name(name, ({prop, "element"}));
        set("who_get/id", query("id", killer), ob);
        set("who_get/time", time() + 10, ob);
        ob->move(where);
        message_vision(HIC "叮~~一聲，從$N" HIC "身上掉出" + ob->name() + NOR + HIC "，落在地上。\n" NOR, this_object());

        message("vision", HIR +this_object()->name(1) + HIR "仰天長嘯：哈哈哈，老夫今日終於如願以償 ……\n" NOR, all_interactive());

        return ::die(killer);
}

varargs void unconcious(object defeater)
{
        object ob;

        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
        die(defeater);
        return;
}

// 不會被busy
/*
varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        return;
}
*/
