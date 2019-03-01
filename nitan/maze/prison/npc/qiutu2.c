#include <ansi.h>
inherit NPC;

void set_from_me(object me);
mapping family_punishers = ([
        "武當派"   : ({ CLASS_D("misc") + "/chongxu" }),
        "少林派"   : ({ CLASS_D("misc") + "/fangsheng" }),
        "華山派"   : ({ CLASS_D("misc") + "/murenqing" }),
        "峨嵋派"   : ({ CLASS_D("misc") + "/guoxiang" }),
        "桃花島"   : ({ CLASS_D("misc") + "/taogu" }),
        "神龍教"   : ({ CLASS_D("misc") + "/zhong" }),
        "丐幫"     : ({ CLASS_D("misc") + "/wangjiantong" }),
        "古墓派"   : ({ CLASS_D("misc") + "/popo" }),
        "全真教"   : ({ CLASS_D("misc") + "/laodao" }),
        "星宿派"   : ({ CLASS_D("misc") + "/xiaoxian" }),
        "逍遙派"   : ({ CLASS_D("misc") + "/liqiushui" }),
        "大輪寺"   : ({ CLASS_D("misc") + "/laoseng" }),
        "血刀門"   : ({ CLASS_D("misc") + "/hongri" }),
        "靈鷲宮"   : ({ CLASS_D("misc") + "/tonglao" }),
        "慕容世家" : ({ CLASS_D("misc") + "/furen" }),
        "歐陽世家" : ({ CLASS_D("misc") + "/laonu" }),
        "關外胡家" : ({ CLASS_D("misc") + "/huyidao" }),
        "段氏皇族" : ({ CLASS_D("misc") + "/duansh" }),
        "明教"     : ({ CLASS_D("misc") + "/yangdingtian" }),
        "日月神教" : ({ CLASS_D("misc") + "/zhanglao" }),
]);

void create()
{
        set_name("兇惡的囚徒", ({ "qiu tu", "qiu", "tu" }));
        set("long", "一個兇惡的囚徒。\n");
        set("gender", "男性");
        set("age", 30);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        // the follow 5 setting has no use        
        set("max_qi", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 100);

        set("combat_exp", 3000000);
        set("attitude", "friendly");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set_temp("apply/armor", 50);
        set_temp("apply/damage", 50);

        set("killer_reward", 
                ([
                "RA&RANDOM70"                                    :       10000,  // 低級普通裝備
                "RA&RANDOM80"                                    :       300,    // 中級普通裝備
                "MO&A2000"       :       300,
                "MO&A2001"       :       300,
                "MO&A2002"       :       300,
                "MO&A2003"       :       300,
                "MO&A2004"       :       300,
                "MO&A2005"       :       300,
        ]));
        setup();
        add_money("gold", 10 + random(10));
}

void init()
{
        object me;

        ::init();
        if (! interactive(me = this_player()) || 
            this_object()->is_fighting())
                return;

        set_from_me(me);
        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}

void set_from_me(object me)
{
        mapping hp_status, skill_status, map_status, prepare_status;
        mapping my;
        object npc,weapon,punisher;
        array sname, mname, pname;
        int i, skl_lvl;

        npc = this_object();

        npc->set("family/family_name", keys(family_punishers)[random(sizeof(family_punishers))]);

        punisher = get_object(family_punishers[npc->query("family/family_name")][0]);
        
        skl_lvl = NPC_D->init_skill_level(me);
        if (skl_lvl < 200) skl_lvl = 200;

        if (mapp(skill_status = punisher->query_skills()))
        {
                sname = keys(skill_status);
                for (i = 0; i < sizeof(skill_status); i++)
                        // npc->set_skill(sname[i], skill_status[sname[i]]);
                        npc->set_skill(sname[i], skl_lvl);
        }
        
        if (mapp(map_status = punisher->query_skill_map()))
        {
                mname = keys(map_status);
                for(i = 0; i < sizeof(map_status); i++)
                        npc->map_skill(mname[i], map_status[mname[i]]);
        }

        if (mapp(prepare_status = punisher->query_skill_prepare()))
        {
                pname = keys(prepare_status);
                for(i = 0; i < sizeof(prepare_status); i++)
                        npc->prepare_skill(pname[i], prepare_status[pname[i]]);
        }

        if ( me->query_skill("qiankun-danuoyi",1) > 0)
        {
                npc->set_skill("qiankun-danuoyi",skl_lvl);
                npc->map_skill("parry","qiankun-danuoyi");
        }

        if ( me->query_skill("douzhuan-xingyi",1) > 0)
        {
                npc->set_skill("douzhuan-xingyi",skl_lvl);
                npc->map_skill("parry","douzhuan-xingyi");
        }

        if ( me->query_skill("lingbo-weibu",1) > 0)
        {
                npc->set_skill("lingbo-weibu",skl_lvl);
                npc->map_skill("dodge","lingbo-weibu");
        }
        
        destruct(punisher);

        hp_status = me->query_entire_dbase();
        my = npc->query_entire_dbase();

        my["str"] = hp_status["str"];
        my["int"] = hp_status["int"];
        my["con"] = hp_status["con"];
        my["dex"] = hp_status["dex"];

        my["qi"] = my["eff_qi"] = my["max_qi"] = hp_status["max_qi"];
        my["jing"] = my["eff_jing"] = my["max_jing"] = hp_status["max_jing"];
        my["jingli"] = my["eff_jingli"] = my["max_jingli"] = hp_status["max_jingli"];
        my["neili"] = my["max_neili"]  = hp_status["max_neili"];
        my["jiali"] = npc->query_skill("force") / 2;

        my["combat_exp"] = hp_status["combat_exp"];

        my["max_qi"]     *= 1.2;
        my["eff_qi"]     *= 1.2;
        my["qi"]         *= 1.2;
        my["max_jing"]   *= 1.4;
        my["eff_jing"]   *= 1.4;
        my["jing"]       *= 1.4;

        my["max_qi"]     += my["max_qi"]/10;
        my["eff_qi"]     += my["eff_qi"]/10;
        my["qi"]         += my["qi"]/10;
        my["max_jing"]   += my["max_jing"]/10;
        my["eff_jing"]   += my["eff_jing"]/10;
        my["jing"]       += my["jing"]/10;

        switch (npc->query("family/family_name"))
        {
                case "武當派":
                case "華山派":
                case "峨嵋派":
                case "桃花島":
                case "全真教":
                case "慕容世家":
                        weapon = new("/clone/weapon/changjian");
                        weapon->move(npc);
                        weapon->wield();
                        break;
                case "日月神教":
                        weapon = new("/d/fuzhou/obj/xiuhua");
                        weapon->move(npc);
                        weapon->wield();
                        break;
                case "大輪寺":
                        weapon = new("/clone/weapon/falun");
                        weapon->move(npc);
                        weapon->set_amount(4);
                        weapon->wield();
                        break;
                case "關外胡家":
                case "血刀門":
                        weapon = new("/clone/weapon/blade");
                        weapon->move(npc);
                        weapon->wield();
                        break;
                case "星宿派":
                case "神龍教":
                        weapon = new("/clone/weapon/gangzhang");
                        weapon->move(npc);
                        weapon->wield();
                        break;
                case "古墓派":
                        weapon = new("/clone/weapon/gangjian");
                        weapon->move(npc);
                        weapon->wield();
                        break;
                case "少林派":
                        weapon = new("/clone/weapon/changbian");
                        weapon->move(npc);
                        weapon->wield();
                        break;
        }

        npc->reset_action();

        return;
}

int accept_fight(object ob)
{
        object me;
        me = this_object();
        set_from_me(ob);
        command("say 你給我去死吧！");
        command("yun powerup");
        command("yun shield");
        switch (me->query_skill_mapped("force"))
        {
                case "linji-zhuang":
                        command("yun tiandi");
                        command("yun daxiao");
                        me->set("qi",me->query("max_qi"));
                        me->set("jing",me->query("max_jing"));
                        break;
                case "huagong-dafa":
                        command("yun hua");
                        break;
                case "zixia-shengong":
                        command("yun ziqi");
                        break;
                case "huntian-qigong":
                        command("yun haixiao");
                        command("yun shengang");
                        break;
                case "bibo-shengong":
                        command("yun wuzhuan");
                        break;
                case "yunv-xinfa":
                        command("yun wang");
                        break;
                case "nuhai-kuangtao":
                        command("yun haixiao");
                        break;
                case "xiantian-gong":
                        command("yun chunyang");
                        break;
                case "longxiang":
                        command("yun longxiang");
                        command("yun panlong");
                        command("yun tunxiang");
                        break;
                case "hamagong":
                        command("yun reserve");
                        break;
                case "lengyue-shengong":
                        command("yun freeze");
                        break;
                case "kurong-xinfa":
                        command("yun kurong");
                        break;
        }
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        object me;
        me = this_object();
        set_from_me(ob);
        command("say 你給我去死吧！");
        command("yun powerup");
        command("yun shield");
        switch (me->query_skill_mapped("force"))
        {
                case "linji-zhuang":
                        command("yun tiandi");
                        command("yun daxiao");
                        me->set("qi",me->query("max_qi"));
                        me->set("jing",me->query("max_jing"));
                        break;
                case "huagong-dafa":
                        command("yun hua");
                        break;
                case "zixia-shengong":
                        command("yun ziqi");
                        break;
                case "huntian-qigong":
                        command("yun haixiao");
                        command("yun shengang");
                        break;
                case "bibo-shengong":
                        command("yun wuzhuan");
                        break;
                case "yunv-xinfa":
                        command("yun wang");
                        break;
                case "nuhai-kuangtao":
                        command("yun haixiao");
                        break;
                case "xiantian-gong":
                        command("yun chunyang");
                        break;
                case "longxiang":
                        command("yun longxiang");
                        command("yun panlong");
                        command("yun tunxiang");
                        break;
                case "hamagong":
                        command("yun reserve");
                        break;
                case "lengyue-shengong":
                        command("yun freeze");
                        break;
                case "kurong-xinfa":
                        command("yun kurong");
                        break;
        }
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        object me;
        me = this_object();
        set_from_me(ob);
        command("say 你給我去死吧！");
        command("yun powerup");
        command("yun shield");
        switch (me->query_skill_mapped("force"))
        {
                case "linji-zhuang":
                        command("yun tiandi");
                        command("yun daxiao");
                        me->set("qi",me->query("max_qi"));
                        me->set("jing",me->query("max_jing"));
                        break;
                case "huagong-dafa":
                        command("yun hua");
                        break;
                case "zixia-shengong":
                        command("yun ziqi");
                        break;
                case "huntian-qigong":
                        command("yun haixiao");
                        command("yun shengang");
                        break;
                case "bibo-shengong":
                        command("yun wuzhuan");
                        break;
                case "yunv-xinfa":
                        command("yun wang");
                        break;
                case "nuhai-kuangtao":
                        command("yun haixiao");
                        break;
                case "xiantian-gong":
                        command("yun chunyang");
                        break;
                case "longxiang":
                        command("yun longxiang");
                        command("yun panlong");
                        command("yun tunxiang");
                        break;
                case "hamagong":
                        command("yun reserve");
                        break;
                case "lengyue-shengong":
                        command("yun freeze");
                        break;
                case "kurong-xinfa":
                        command("yun kurong");
                        break;
        }
        kill_ob(ob);
        return 1;
}
