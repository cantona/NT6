// story:hushan 火燄山傳說

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "白骨精：牛哥！",
        "牛魔王：幹啥？",
        "白骨精：牛哥，你可得給我做主啊！",
        "牛魔王：誰欺負你了？",
        "白骨精：還，還不是你那個義弟...",
        "牛魔王：義弟？哪個義弟？",
        "牛魔王暗想：我好象有好幾百個義弟吧，這說的是那一個啊？",
        "白骨精嗚嚥道：就是那個孫猴子啊。",
        "牛魔王大怒：你說的是那猴子？哼！他先坑害我兒子，後又欺負你嫂子...",
        "牛魔王想了想又道：騙走我的芭蕉扇，我已經把他開除了！",
        "白骨精大喜道：那你可要替我報仇啊，我剛被他欺負！",
        "牛魔王道：不忙，我這就找上幾個弟兄，去替你報仇！",
        "......",
        (: give_gift, "niutou" :),
        "聽說牛魔王派出牛頭怪(niutou guai)，下了火燄山。",
});

string prompt() { return HIM "【神話】" NOR; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int give_gift(string name)
{
        object ob;

        ob = new(CLASS_D("misc/") + name);
        if (! objectp(ob))
                return 0;

        NPC_D->place_npc(ob);
        if (! objectp(environment(ob)))
        {
                destruct(ob);
                return 0;
        }

        CHANNEL_D->do_channel(find_object(STORY_D), "sys",
                              ob->name() + "出現在" + environment(ob)->short() +
                              "(" + base_name(environment(ob)) + ")。");
        return 1;
}
