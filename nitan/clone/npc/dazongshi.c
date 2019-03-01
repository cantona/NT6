// dazongshi.c 大宗師

#include <ansi.h>;
inherit NPC;
string ask_me();

void create()
{
        set_name("大宗師", ({ "da zongshi", "zongshi" }));
        set("long","他就是江湖的大宗師。你只有先向他挑戰，才能獲得江湖對你實力和地位的承認。\n");
        set("gender", "男性");
        set("age", 40);
        set("class", "taoist");
        set("attitude", "friendly");
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("no_get",1);

        set("max_qi", 6000);
        set("max_jing", 3000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jingli", 100);
        set("max_jingli", 100);
        set("tili", 100);
        set("jiali", 100);
        set("food", 400);
        set("water", 400);
        set("combat_exp", 5000000);
        set("score", 500000);
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "sword.sui" :),
                (: perform_action, "parry.ren" :),
                (: exert_function, "powerup" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "recover" :),
        }) );
        set_skill("force", 300);
        set_skill("taiji-shengong", 300);
        set_skill("dodge", 300);
        set_skill("tiyunzong", 300);
        set_skill("unarmed", 300);
        set_skill("taiji-quan", 300);
        set_skill("parry", 300);
        set_skill("sword", 300);
        set_skill("taiji-jian", 300);
        set_skill("liangyi-jian", 300);
        set_skill("wudang-jian", 300);
        set_skill("wudang-quan", 300);
        set_skill("taoism", 150);
        set_skill("literate", 100);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "liangyi-jian");
        map_skill("sword", "taiji-jian");
        set("inquiry", ([
                "秒殺" : (: ask_me :),
                "出手" : (: ask_me :),
                "殺手" : (: ask_me :),
                "挑戰" : (: ask_me :),
                "品評" : (: ask_me :),
                "武功" : (: ask_me :),
        ]));
        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"dao-cloth")->wear();
        carry_object(CLOTH_DIR"dao-shoe")->wear();
}
string ask_me()
{
        object me = this_player(), ob = this_object();

        if( query("combat_exp", me)<500000 )
                return "等你的經驗湊夠了五十萬，再來找我吧。";
        set("killer/id",query("id",  me), ob);
        set("killer/time", time(), ob);
        set("eff_qi", 6000);
        set("eff_jing", 3000);
        set("qi", 6000);
        set("jing", 3000);
        set("food", 400);
        set("water", 400);
        set("neili", 5000);
        set("jiali", 100);
        command("yun powerup");
        set("neili", 5000);
        set("jiali", 100);
        return "好吧，那就來吧。";
}
void die()
{
        object *me, ob = this_object(); //,mm = this_player();
        int i, sc, new_killer;

//        sc = mm->query("score");
        me = all_inventory(environment(ob));
        for (i = 0; i < sizeof(me); i ++)
                if( query("id", me[i]) == query("killer/id", ob) )
                {
                        sc=query("score", me[i]);
                        new_killer=12345/(time()-query("killer/time", ob));
                        if( query("KILLER", me[i]) >= new_killer )
                        {
                                tell_object(me[i],HIR"\n大宗師臨死前告訴你：“沒有進步，白來一趟。”\n"NOR);
                                if( me[i]->quert("zongshi_winner")<3)addn("score", -5000, me[i]);
                        }
                        else
                        {
                                tell_object(me[i],HIR"\n大宗師臨死前告訴你：“好，好！好！沒有白來這一趟。”\n"NOR);
                                message("channel:chat",HIM"【閒聊】某人："+query("name", me[i])+chinese_number(time()-query("killer/time", ob))+"秒中刺殺大宗師成功。\n"NOR,users());
                                set("KILLER", new_killer, me[i]);
                                addn("zongshi_winner", 1, me[i]);
                                if( me[i]->quert("zongshi_winner")<3)addn("score", 10000, me[i]);
                        }
                }
        ::die();
}
