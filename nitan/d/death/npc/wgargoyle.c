// gargoyle.c

#include <ansi.h>
#include <command.h>
#include <login.h>

inherit NPC;

string *death_msg = ({
        HIW "白無常說道：喂！新來的，你叫什麼名字？\n\n" NOR,
        HIW "白無常用奇異的眼光盯著你，好像要看穿你的一切似的。\n\n" NOR,
        HIW "白無常「哼」的一聲，從袖中掏出一本像帳冊的東西翻看著。\n\n" NOR,
        HIW "白無常翻了半天，有些困惑。\n\n" NOR,
        HIW "白無常仔細看了看你，沒有說什麼。\n\n" NOR,
        HIW "白無常又翻了一會兒帳冊，考慮了半天。\n\n" NOR,
        HIW "白無常打量了一會兒你，皺了皺眉頭。\n\n" NOR,
        HIW "白無常嘆了一口氣。\n\n" NOR,
        HIW "白無常合上冊子，想了一會兒。\n\n" NOR,
        HIW "白無常說道：你陽壽未盡？有些奇怪。\n\n" NOR,
        HIW "白無常接著說道：讓你留在陰間不合時宜，讓我想想。\n\n" NOR,
        HIW "白無常搔了搔頭，嘆道：罷了罷了，你走吧。\n\n"
            "一股陰冷的濃霧突然出現，很快地包圍了你。\n\n" NOR,
});

void create()
{
        set_name("白無常", ({ "white gargoyle", "gargoyle" }));
        set("title", "冥府地藏王殿前");
        set("long",
                "白無常瞪著你，死白的臉上看不出任何喜怒哀樂。\n");
        set("attitude", "peaceful");
        set("chat_chance", 1);
        set("chat_msg", ({
                "白無常無聊的打了個哈欠。\n",
                "白無常嘿嘿姦笑兩聲。\n",
        }));
        set("age", 217);
        set("combat_exp", 20000);
        set("max_jing", 900);
        set("max_qi", 900);
        set_skill("dodge", 40);
        set_skill("unarmed", 40);
        setup();
}

void init()
{
        ::init();
        if (! previous_object() ||
            ! userp(previous_object()) ||
            ! previous_object()->is_ghost() ||
            wizardp(previous_object())) return;
        call_out("death_stage", 30, previous_object(), 0);
}

void death_stage(object ob, int stage)
{
        int i;
        object *inv, mailbox;
        if (! ob || ! present(ob)) return;

        tell_object(ob, death_msg[stage]);
        if (++stage < sizeof(death_msg))
        {
                call_out("death_stage", 10, ob, stage);
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
        message("vision",
                "你忽然發現前面多了一個人影，不過那人影又好像已經在那裡\n"
                "很久了，只是你一直沒發覺。\n", environment(ob), ob);
}