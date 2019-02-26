// story:nanhai 南海傳説

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "譁～～～譁～～～轟隆！",
        "漁民：不好啦～～海嘯啦～～～快逃啊～～～",
        "譁～～～譁～～～轟隆！",
        "眼見海水不住的蔓延，昔日淺灘，盡成汪洋。",
        "恩？",
        "南海神尼驀然睜開雙眼，暗道：何方妖物？",
        "譁～～譁～～",
        "神尼喝道：“原來是你這個孽障！又在興風作浪，休要猖狂，吃我一掌！”",
        "啪！",
        "南海惡蛟：嘿嘿嘿嘿，什麼人這麼不識好歹？",
        "神尼直震得眼花繚亂，氣血翻湧，暗道：枉空我修煉百年，居然如此不濟。",
        "不及多想，神尼趕緊捲鋪蓋，自念道：趕緊上華山找獨孤求敗那老頭，難怪他躲在山上，有道理！",
        (: give_gift, "nanhai" :),
        "聽説南海惡蛟(monster dragon)重出大海，到人間興風作浪。",
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
