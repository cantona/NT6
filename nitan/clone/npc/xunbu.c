// xunbu.c

#include <ansi.h>

inherit NPC;

void do_chat();

void create()
{
        NPC_D->generate_cn_name(this_object());
        set("title", HIR "六扇門內巡捕" NOR);
        set("gender", "男性");
        set("age", 43);
        set("long", @LONG
這是一個巡捕，身體強壯，看上去武功不錯。
LONG );
        set("combat_exp", 600000);
        set("attitude", "heroism");
        set("max_neili", 3000);
        set("neili", 3000);
        set("max_jing", 1500);
        set("jing", 1500);
        set("max_qi", 2200);
        set("qi", 2200);

        set("str", 31);
        set("int", 19);
        set("con", 26);
        set("dex", 22);

        set_skill("unarmed", 150);
        set_skill("sword", 150);
        set_skill("parry", 150);
        set_skill("dodge", 150);
        set_skill("force", 150);
        set_skill("huashan-neigong", 150);
        set_skill("huashan-sword", 150);
        set_skill("huashan-quan", 150);
        set_skill("feiyan-huixiang", 150);
        map_skill("dodge", "feiyan-huixiang");
        map_skill("force", "huashan-neigong");
        map_skill("sword", "huashan-sword");
        map_skill("unarmed", "huashan-quan");
        map_skill("parry", "huashan-sword");

        set("chat_chance", 30);
        set("chat_msg", ({
                (: do_chat :),
        }));

        set_temp("born_time", time());

        setup();
        keep_heart_beat();

        set_max_encumbrance(100000000);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 50);
        set_temp("apply/armor", 100);

        carry_object("/d/beijing/npc/obj/sword4")->wield();
        carry_object("/d/beijing/npc/obj/guanfu5")->wear();
}

int do_halt()
{
        object me;

        if (this_player() == query_temp("catch_ob"))
        {
                write(CYN + name() + "罵道：“跑什麼跑？你跑到哪裏也跑不掉！”\n" NOR);
                return 1;
        }

        return 0;
}

void do_chat()
{
        string msg;

        switch (random(20))
        {
        case 0:
                msg = CYN "$N東看看，西瞅瞅，似乎在找什麼人。\n" NOR;
                break;
        case 1:
                msg = CYN "$N無聊得打了個哈欠，一副沒精打采的樣子。\n" NOR;
                break;
        case 2:
                msg = CYN "$N“嗯”了一聲，也不知道究竟聽到了什麼。\n" NOR;
                break;
        case 3:
                msg = CYN "$N“啊秋”一聲打了個噴嚏，好像是着涼了。\n" NOR;
                break;
        case 4:
                msg = CYN "$N看了看四周，道：“有沒有看到什麼可疑人物？”\n" NOR;
                break;
        case 5:
                msg = CYN "$N嘿嘿乾笑了幾聲，道：“犯了案馬上自首，否則罪加一等。”\n" NOR;
                break;
        case 6:
                msg = CYN "$N哼了一聲道：“知情不報，罪與犯同。”\n" NOR;
                break;
        default:
                random_move();
                return;
        }

        message("vision", replace_string(msg, "$N", name()),
                environment());
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        if (ob != query_temp("catch_ob"))
        {
                message_vision(CYN "$N對$n" CYN "怒喝道：“大膽！居然敢攻"
                               "擊官差？找死麼？”\n" NOR,
                               this_object(), ob);
        }

        ::fight_ob(ob);
        if( !is_killing(query("id", ob)) )
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision(CYN "$N搖搖頭，對$n" CYN "道：“我可沒興趣”。\n" NOR,
                       this_object(), ob);
        return 0;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

void init()
{
        object ob;

        add_action("do_halt", "halt");
        ob = this_player();

        if (is_busy() ||
            is_fighting() ||
            ! living(this_object()) ||
               query("no_fight", environment())) 
                return;

        if (ob == query_temp("catch_ob") ||
            ! query_temp("catch_ob") &&
            ob->query_condition("killer"))
        {
                remove_call_out("catch_killer");
                call_out("catch_killer", 1, ob);
        }
}

void catch_ob(object ob)
{
        remove_enemy(ob);
        message_vision(HIY "$N把鐵索往$n" HIY "頭上一套，然後拖起$n"
                       HIY "，冷笑道：“跟我走吧！”\n" NOR,
                       this_object(), ob);
        ob->move(this_object());
        if (is_fighting())
        {
                // Am I in fighting now ?
                message_vision(CYN "$N冷冷道：“我先要先回去交"
                               "差了，改日再收拾你們幾個！”\n" NOR,
                               this_object());
        }

        if (base_name(environment()) != "/d/changan/baihu1")
        {
                set_temp("old_position", base_name(environment()));
                message_vision(HIR "$N輕聲哼了一聲，拖着$n" HIR
                               "轉身離去。\n" NOR, this_object(), ob);
                move("/d/changan/baihu1");
                remove_call_out("return_back");
                call_out("return_back", 1);
        }

        message_vision(HIW "$N拖着$n" HIW "走了過來，幾個獄卒迎了上"
                       "來，把$n" HIW "押進大牢去了。\n" NOR, this_object(), ob);
        CHANNEL_D->do_channel(this_object(), "rumor", "聽説" +
                            ob->name(1) + HIM "被巡捕" + name() +
                            "緝拿歸案，押入大牢。");
        ob->get_into_prison(0, "/d/changan/prison", 360);
        ob->clear_condition("killer");
        ob->remove_killer(this_object());
        remove_killer(ob);
        delete_temp("catch_ob");
        return;
}

void catch_killer(object ob)
{
        if (! ob || environment(ob) != environment() ||
            ! living(this_object()))
                return;

        if (! living(ob))
        {
                catch_ob(ob);
                return;
        }

        if( is_killing(query("id", ob)) )
                return;

        if (ob->name() != ob->name(1) &&
            random((int)ob->query_skill("pretending")) > 50)
                return;

        message_vision(HIY "$N盯着$n" HIY "看了一會兒，突然喝道：“你不"
                       "就是在逃的" + ob->name(1) + HIY "嗎？今天撞到我"
                       "的手裏，不要想再跑了！”\n" NOR, this_object(), ob);
        set_temp("catch_ob", ob);
        kill_ob(ob);                       
}

void return_back()
{
        if (! living(this_object()))
                return;

        if (! stringp(query_temp("old_position")))
                return;

        message_vision(CYN "$N打了個哈欠，喃喃自語了幾聲後走開了。\n" NOR,
                       this_object());
        move(query_temp("old_position"));
        message_vision(CYN "$N懶洋洋的走了過來。\n" NOR, this_object());
        delete_temp("old_position");
}

int attack()
{
        object ob;

        if (objectp(ob = query_temp("catch_ob")) &&
            ! living(ob) &&
            environment(ob) == environment())
        {
                catch_ob(ob);
                return 1;
        } else
                return ::attack();
}

void scan()
{
        object ob;

        ::scan();

        if (! objectp(ob = query_temp("catch_ob")))
        {
                if (time() - query_temp("born_time") > 900 &&
                    ! is_fighting() && living(this_object()))
                {
                        message_vision(CYN "$N左顧右盼，悻悻的走了。\n" NOR,
                                       this_object());
                        destruct(this_object());
                }
                return;
        }
        
        if (environment(ob) != environment() ||
            query("no_fight", environment(ob)) )
        {
                message_vision(CYN "$N悻悻道：“哼，豈有此理。”\n" NOR,
                               this_object());
                delete_temp("catch_ob");
                return;
        }

        if (! living(ob))
        {
                catch_ob(ob);
                return;
        }

        if (! is_fighting(ob))
                fight_ob(ob);
}
