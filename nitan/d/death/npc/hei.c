#include <ansi.h>
#include <command.h>
#include <login.h>

inherit NPC;

string *death_msg = ({
        HIW "黑無常説道：喂！新來的，你叫什麼名字？\n\n" NOR,
        HIW "黑無常用奇異的眼光盯著你，好像要看穿你的一切似的。\n\n" NOR,
        HIW "黑無常「哼」的一聲，從袖中掏出一本像帳冊的東西翻看著。\n\n" NOR,
        HIW "黑無常合上冊子，説道：咦？陽壽未盡？怎麼可能？\n\n" NOR,
        HIW "黑無常搔了搔頭，歎道：罷了罷了，你走吧。\n\n"
                "一股陰冷的濃霧突然出現，很快地包圍了你。\n\n" NOR,
});

void create()
{
        set_name("黑無常", ({ "hei wuchang", "hei", "wuchang" }));
        set("title", HIR "冥府地藏王殿前" NOR);
        set("long", "\n黑無常瞪著你，焦黃的臉上看不出任何喜怒哀樂。\n");
        set("attitude", "peaceful");
        set("chat_chance", 15);
        set("chat_msg", ({
                CYN "黑無常嘿嘿乾笑數聲：你可終於落到我的手裏了……\n" NOR,
                CYN "黑無常東張西望，不知道在打什麼主意。\n" NOR,
        }) );
        set("age", 217);

        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 250);

        set("combat_exp", 50000000);

        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("blade", 500);
        set_skill("staff", 500);
        set_skill("hammer", 500);
        set_skill("club", 500);
        set_skill("whip", 500);
        set_skill("dagger", 500);
        set_skill("throwing", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("never-defeated", 1000);
        set_skill("magic", 1000);

        map_skill("sword", "never-defeated");
        map_skill("blade", "never-defeated");
        map_skill("staff", "never-defeated");
        map_skill("hammer", "never-defeated");
        map_skill("club", "never-defeated");
        map_skill("whip", "never-defeated");
        map_skill("dagger", "never-defeated");
        map_skill("parry", "never-defeated");
        map_skill("dodge", "never-defeated");
        map_skill("force", "never-defeated");

        setup();

        carry_object(__DIR__"obj/cloth1")->wear();
        carry_object(__DIR__"obj/suolian")->wield();
        set_temp("handing", carry_object(__DIR__"obj/bi"));
}

void init()
{
        ::init();
        if (! previous_object() ||
            ! userp(previous_object()) ||
            ! previous_object()->is_ghost() ||
            wizardp(previous_object())) return;
        call_out("death_stage", 5, previous_object(), 0);
}

void death_stage(object ob, int stage)
{
        int i;
        object *inv, mailbox;
        if (! ob || ! present(ob)) return;

        tell_object(ob, death_msg[stage]);
        if (++stage < sizeof(death_msg))
        {
                call_out( "death_stage", 5, ob, stage );
                return;
        } else
                ob->reincarnate();

        if (! wizardp(ob))
        {
                    inv = all_inventory(ob);
                    for (i = 0; i < sizeof(inv); i++)
                            DROP_CMD->do_drop(ob, inv[i]);
        }
        
        ob->move(REVIVE_ROOM);
        set("startroom", REVIVE_ROOM, ob);
        message("vision", HIW "你忽然發現前面多了一個人影，不過那人影又好像已經在那裏\n"
                          "很久了，只是你一直沒發覺。\n" NOR, environment(ob), ob);
}