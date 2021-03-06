// hu.c 胡青牛
// shilling 97.2
#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

//void attempt_apprentice(object ob);
int ask_me();

void create()
{
        set_name("胡青牛", ({ "hu qingniu", "hu" }));
        set("long", 
                "他就是明教號稱見死不救的胡青牛，據説他精通醫理，可以起死回\n"
                "生。但他從不醫教外人士。\n");
        set("gender", "男性");
            set("title",HIG "明教" NOR "教眾");
        set("nickname","蝶谷醫仙");
        set("age", 50);
        set("class", "shaman");
        set("attitude", "peaceful");
        set("str", 25);
        set("int", 27);
        set("con", 25);
        set("dex", 25);
        set("inquiry", ([
                "療傷" : (:ask_me:),
        ]) );

        set("max_qi", 1500);
        set("max_jing", 600);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 60);
        set("combat_exp", 150000);
        set("score", 80000);

        set_skill("force", 90);
        set_skill("dodge", 90);
        set_skill("unarmed",90);
        set_skill("parry", 90);

        create_family("明教", 35, "弟子");
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

int ask_me()
{
        object ob;
        ob=this_player();

        if( query("family/family_name", ob) != "明教" )
                return notify_fail("你不是我明尊座下弟子，我不可以為你療傷。\n");
        if( query("eff_qi", ob) == query("max_qi", ob) )
        {
                command("?"+query("id", ob));
                command("say 你沒有受任何傷啊？\n");
                return 1;
        }
        else
        {
                message_vision("胡青牛喂$N服下一顆藥丸,然後盤膝坐下，雙掌貼着$N的背心。\n", ob);
                remove_call_out("recover");
                call_out("recover",2,ob);
                return 1;
        }
}


int recover(object ob)
{
        set("eff_qi",query("max_qi",  ob), ob);
        set("eff_jing",query("max_jing",  ob), ob);
        message_vision("大約過了一盅茶的時份，胡青牛慢慢地站了起來。\n",ob);
        command("say 你的傷勢已經全好了,可以走啦。\n");
        return 1;
}
