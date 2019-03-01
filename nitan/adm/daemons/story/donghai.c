// story:donghai 東海龍傳說

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "哪吒：我洗澡去了。",
        "李天王：去就去，可少給我惹事。",
        "......",
        "哪吒：洗洗頭！",
        "哪吒：沖沖腳！",
        "哪吒：待我搓搓背！恩？我的小布條呢...",
        "唏～哩～嘩～啦～～～",
        "東海龍王：我的天，怎麼晃得這麼厲害？",
        "蝦兵蟹將：呼嚕呼嚕，不得了了！",
        "龍子龍孫：喔喔，老爸救命啊！",
        "三太子：豈有此理！一定是有人搞破壞，待我去查個明白！",
        "龍妹妹：哇，好帥呀！",
        "......",
        "三太子：兀那小子，東海龍宮豈是你折騰的地方？",
        "哪吒：什麼人，打擾我洗澡？賞你一鐵圈！",
        "啪！",
        "噢呦！",
        (: give_gift, "donghai" :),
        "聽說三太子(prince of dragon)和哪吒發生沖突，被打落凡間。",
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
