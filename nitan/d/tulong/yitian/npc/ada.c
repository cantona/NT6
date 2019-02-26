#include <ansi.h>

inherit NPC;

void create()
{
        set_name("阿大", ({ "a da", "a", "da" }));
        set("long", "八臂神劍方東白是丐幫四大長老之首，劍術\n"
                    "之精，名動江湖，只因他出劍奇快，有如生\n"
                    "了七八條手臂一般，因此上得了這個外號。\n"
                    "十多年前聽説他身染重病身亡，當時人人都\n"
                    "感惋惜，不覺他竟尚在人世。\n");
        set("title", "丐幫四大長老之首");
        set("nickname", HIW "八臂神劍" NOR);
        set("gender", "男性");
        set("age", 68);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("per", 20);
        set("str", 45);
        set("int", 45);
        set("con", 45);
        set("dex", 45);
        
        set("max_qi", 5500);
        set("max_jing", 2000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 2000000);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.kuang" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        set_skill("literate", 180);
        set_skill("begging", 200);
        set_skill("checking", 200);
        set_skill("force", 270);
        set_skill("dodge", 270);
        set_skill("unarmed", 270);
        set_skill("parry", 270);
        set_skill("strike", 270);
        set_skill("sword", 270);
        set_skill("feiyan-zoubi", 270);
        set_skill("huntian-qigong", 270);
        set_skill("kuangfeng-jian", 270);
        set_skill("dragon-strike", 270);

        map_skill("dodge", "feiyan-zoubi");
        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("parry", "kuangfeng-jian");
        map_skill("sword", "kuangfeng-jian");

        prepare_skill("strike", "dragon-strike");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        add_action("begin","bi");
}

int accept_fight(object who)
{
        command("say 沒郡主的吩咐我不會出手。");
        return 0;
}

int accept_hit(object who)
{
        command("say 沒郡主的吩咐我不會出手。");
        return 0;
}

int accept_kill(object who)
{
        command("say 沒郡主的吩咐我不會出手，殺了我也一樣。");
        return notify_fail("剎那間你只覺得下不了手。\n");
}

int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是隻見樓上人影晃動，根本看不清楚。\n");
}

int begin()
{
        object weapon, env, shelf, sword;
        object me=this_player();
        object obj=this_object();
        env = environment(this_object());
        shelf = present("shelf", env);
        sword = present("yitian sword", shelf);


        if (objectp(present("a er", environment())))
        return 0;

        if( !query_temp("win_aer", me) )
        {
                command("heng");
                command("say 閣下是誰？為何剛才不出戰，現在來趁機揀便宜。");
                return notify_fail("看起來阿大並不想跟你較量。\n");
        }

        if( !objectp(weapon=query_temp("weapon", me)) )
        {
                command("say 我只和你比兵器功夫！");
                return notify_fail("看起來阿大並不想跟你較量。\n");
        }

        if (sword)
        {
                command("nod");
                command("bow");

                message_vision(CYN "突然趙敏喝道：“慢着！拿着倚天劍和$n" CYN
                                   "鬥！”\n" NOR,
                                   obj, this_player());

                message_vision(CYN "阿大微微點了點頭，道：“遵命！”\n\n" NOR,
                                   obj, this_player());

                message_vision(CYN "阿大躬身上前，輕輕在" NOR+RED 
                                   "紅木劍架" NOR+CYN
                                   "上一拍，那號稱天下第一神兵的" NOR+WHT
                                   "倚天劍" NOR+CYN
                                   "頓時凌空躍起，飛如阿大手中。\n\n" NOR,
                                   obj, this_player());

                message_vision(HIW "只聽“嗖”的一聲破空聲響，號稱天下第一神兵的倚天劍已被阿大握在手中。\n\n" NOR,
                                   this_object(),this_player());

                sword->move(this_object());
                sword->wield();

                command("say 進招了。");

                message_vision(HIR "阿大仰天一聲清嘯，手中倚天劍寒芒頓時爆漲數倍，“刷刷刷刷”連續數劍，向$n" HIR 
                                   "各處要害連續刺去！\n身法之快，劍法之高明，的確世所罕見。\n\n" NOR,
                                   this_object(),this_player());
        }

        call_out("do_unwield",3);
        set_temp("bi", 1, me);
        set("anti",me);
        obj->kill_ob(this_player());
        this_player()->kill_ob(obj);
        return 1;
}

void unconcious()
{
        object ob;
        object me = this_player();

        if (objectp(query("anti")))
        {
                message_vision(HIR "\n$n" HIR 
                                   "暗自摸索阿大劍招中的破綻，手中兵器揮灑，將阿大手中的倚天劍牢牢圈住，"
                                   "阿大頓感不妙，剛要撤劍回\n防，只覺胸口一陣冰涼，$n" HIR 
                                   "的劍身已經貫胸而入。\n\n" NOR,
                                   this_object(),query("anti"));

                message_vision(HIR "$n" HIR
                                   "得勢不饒人，緊接着連攻出數劍，將阿大全身各處筋脈盡數削斷。\n\n" NOR,
                                   this_object(),query("anti"));

                message_vision(CYN "\n趙敏一張俏臉頓時慘白，歎了口氣，説道：“很好，這倚天劍你就拿去吧！”\n" NOR,
                                   this_object());

                message_vision(CYN "趙敏對着$n" CYN 
                                   "嫣然一笑，隨即輕輕伸了伸腰，輕聲説道：“鹿先生，鶴先生，我累了。”\n" NOR,
                                   this_object(), query("anti"));

                message_vision(HIR "只見趙敏身後閃出兩個人影，相互使了個眼神，二話不説，對着$n" HIR 
                                   "直撲過來。”\n" NOR,
                                   this_object(), query("anti"));

                delete_temp("bi", query("anti"));
                delete_temp("win_he", query("anti"));
                delete_temp("win_asan", query("anti"));
                delete_temp("win_aer", query("anti"));

                ob = new("/d/tulong/yitian/npc/hebiweng");
                ob->move("/d/tulong/yitian/was_lou4");
                if (objectp(ob)) ob->kill_ob(me);

                ob = new("/d/tulong/yitian/npc/luzhangke");
                ob->move("/d/tulong/yitian/was_lou4");
                if (objectp(ob)) ob->kill_ob(me);

                ob = present("zhao min");
                if (objectp(ob)) destruct(ob);

        }
        ::die();
}
