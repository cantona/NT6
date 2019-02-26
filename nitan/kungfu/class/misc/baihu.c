// nanhai.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIW "白虎" NOR, ({ "white tiger", "white", "tiger" }) );
        set("title", HIC "神獸" NOR);
        set("gender", "男性");
        set("age", 5);
        set("long", @LONG
這是一隻巨大的白虎，雄壯無比。乃為太白金星的坐騎。
LONG );
        set("combat_exp", 10000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 220000);
        set("neili", 220000);
        set("max_jing", 180000);
        set("jing", 180000);
        set("max_qi", 340000);
        set("qi", 340000);
        set("jingli", 120000);
        set("max_jingli", 120000);

        set("str", 160);
        set("int", 30);
        set("con", 80);
        set("dex", 80);

        set_skill("unarmed", 1800);
        set_skill("sword", 1800);
        set_skill("parry", 1800);
        set_skill("dodge", 1800);
        set_skill("force", 1800);

        set("jiali", 300);

        set_temp("apply/attack", 400);
        set_temp("apply/unarmed_damage", 600);
        set_temp("apply/armor", 1000);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set("born_time", time());
                keep_heart_beat();
        }

        setup();
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        message_vision(HIW "$N一聲長嘯，張牙舞爪，面目猙獰。\n" NOR, this_object(), ob);

        ::fight_ob(ob);
        if( !is_killing(query("id", ob)) )
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision(HIW "$N" HIW "一聲長嘯，撲向$n" HIW "上來。\n" NOR,
                       this_object(), ob);
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->receive_wound("qi", 200 + random(200), me);
        set("neili",query("max_neili",  me), me);
        return HIW "$N" HIW "周圍雲霧繚繞，面目猙獰，登時令$n"
               HIW "迷惑不已，難以自拔。\n" NOR;
}

void unconcious()
{
        die();
}

varargs void die(object killer)
{
        object ob;
        string str;
        string* prize = ({
             "/clone/fam/etc/hugu",
             "/clone/fam/etc/hujin",
             "/clone/fam/etc/hupi",
        });

        str = prize[random(sizeof(prize))];
        ob = new(str);
        command("chat 盎~！盎~~！！");
        CHANNEL_D->do_channel(this_object(), "rumor", HIW "畜生，快快跟我回去吧！" NOR);
        command("chat 盎~！盎~~！！");
        CHANNEL_D->do_channel(this_object(), "rumor", HIM "聽説白虎被太白金星抓回天庭！\n" NOR);
        message_sort(HIR "$N" HIR "身子一扭，消失在雲氣中，"
                     "只聽叮玲玲的一聲，從$N" HIR "身上掉下了一" +
                     query("unit", ob)+ob->name()+
                     HIR "。\n" NOR, this_object());

        if (objectp(killer)) set("who_get", ([ "id"    : query("id", killer),
                                               "time"  : time() + 60]), ob); // 60秒內只允許殺死我的ID揀
        ob->move(environment());

        // 帝王符圖
        // 編號31
        if (random(10) == 1)
        {
                int n_tt;
                object ob_tt;
                n_tt = 31;
                ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                if (ob_tt)
                {
                        write(HIG "叮~~一張帝王符圖碎片落在地上。\n" NOR);
                        ob_tt->move(environment());
                }
        }

        // 1/800機率掉出無名銅人
        if (random(800) < 1)
        {
                object ob_tongren;
                ob_tongren = new("/clone/tongren/tongren" + (1 + random(2)));
                message_vision(HIR "當~~一聲，從$N" HIR "身上掉出" + ob_tongren->name() + HIR "，落在地上。\n" NOR, this_object());
                set("who_get/id", "NONE", ob_tongren);
                set("who_get/time", time() + 30, ob_tongren); // 30秒內都不能撿取
                ob_tongren->move(environment(this_object()));
        }
        destruct(this_object());
}

void random_move()
{
        if (time() - query("born_time") > 1800)
        {
                message_vision("$N急急忙忙的走了。\n", this_object());
                CHANNEL_D->channel_broadcast("rumor",
                        "聽説" + name() + HIM "逍遙世間，後來終於被太白金星抓回天庭。" NOR);
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}
