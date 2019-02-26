#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("何太沖", ({ "he taichong", "he", "taichong" }));
        set("long", "一個五十多歲的中年男子，眉頭緊鎖，原來\n"
                    "這就是崑崙派的掌門，人稱“鐵琴先生”的\n"
                    "何太沖，至六大門派圍攻光明頂之後，被趙\n"
                    "用計擒拿，關押在這裏。\n");
        set("title", "崑崙派第三代掌門");
        set("nickname", WHT "鐵琴先生" NOR);
        set("gender", "男性");
        set("age", 58);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("per", 30);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 3500);
        set("max_jing", 1200);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 100);
        set("combat_exp", 1400000);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.fanyin" :),
                (: exert_function, "recover" :),
        }) );

        set_skill("literate", 100);
        set_skill("tanqin-jifa", 250);
        set_skill("qingxin-pushan", 250);
        set_skill("force", 220);
        set_skill("dodge", 220);
        set_skill("unarmed", 220);
        set_skill("parry", 220);
        set_skill("strike", 220);
        set_skill("sword", 220);
        set_skill("lingxu-bu", 220);
        set_skill("songshan-xinfa", 220);
        set_skill("kunlun-jian", 220);
        set_skill("cuixin-zhang", 220);

        map_skill("dodge", "lingxu-bu");
        map_skill("force", "songshan-xinfa");
        map_skill("strike", "cuixin-zhang");
        map_skill("parry", "kunlun-jian");
        map_skill("sword", "kunlun-jian");
        map_skill("tanqin-jifa", "qingxin-pushan");

        prepare_skill("strike", "cuixin-zhang");

        create_family("崑崙派", 3, "掌門");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhujian")->wield(); 
}

void init()
{
        add_action("begin","bi");
}

int accept_fight(object who)
{
        command("say 哼，如我何太沖內力尚在，也由不得你猖狂。");
        return 0;
}

int accept_hit(object who)
{
        command("say 哼，如我何太沖內力尚在，也由不得你猖狂。");
        return 0;
}

int accept_kill(object who)
{
        command("heng");
        command("say 我何太沖被你們用詭計擒住，早就沒想過要繼續存活，要殺就動手吧。");
        return notify_fail("剎那間你只覺下不了手。\n");
}

int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是隻見樓上人影晃動，根本看不清楚。\n");
}

int begin()
{
        object weapon;
        object me=this_player();
        object obj=this_object();

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
        {
                command("say 我內力全失，現在只能和你比劍！");
                return notify_fail("看起來何太沖並不想跟你較量。\n");
        }

        command("heng");
        command("say 進招吧！");
        message_vision(HIY "$N話音未落，單手一抖，手中竹劍對準$n" HIY
                           "當胸斜斜刺出！正是崑崙嫡傳的兩儀劍法。\n" NOR,
                           obj, this_player());

        set_temp("bi", 1, me);
        set("anti",me);
        obj->kill_ob(this_player());
        this_player()->kill_ob(obj);
        return 1;
}

void die()
{
        if (objectp(query("anti")))
        {
                message_vision(CYN "\n趙敏皺了皺眉頭，低聲罵道：“廢物！”\n" NOR,
                                   this_object());

                set_temp("win_he", 1, query("anti"));
                delete_temp("bi", query("anti"));
        }
::die();
}
