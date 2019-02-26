// story:baihu 白虎

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "天庭。",
        "太白金星：今日太乙真人廣邀羣仙赴宴，不知他又要搞什麼名堂。",
        "童子：師父，太上老君來了。",
        "太白金星：哦？來得正好！",
        "太上老君：金星啊，時候也差不多了，這就走吧，不然遲到了太乙真人又要發標了。",
        "太白金星面露怯色，好像害怕什麼。",
        "太白金星：走啦，童兒，快去牽我的坐騎來。",
        "童子：是！説罷飛奔而出 ……",
        "太上老君：太白金星啊，你那個坐騎跑得太慢，不如坐我這隻仙鶴，免得遲到。",
        "太白金星恍然大悟道：正是，正是！還是坐你的仙鶴快！免得那老不死的又要發標。",
        "太上老君和太白金星乘仙鶴飛去 ……",
        "童子：師父，我來了。你的坐騎在這裏~~",
        "童子：？？？師父不見了？正好這個時候出去玩玩。",
        "童子：小虎，小虎，我出去玩你就呆在這別到處亂跑哦！",
        "小虎：盎~！哄~！",
        "童子：好吧，我走了！説罷童子飛奔而出 ……",
        "小虎跟着跑了出去 ……",       
        (: give_gift, "baihu" :),
        "聽説白虎(white tiger)一陣亂躥，到了凡間。",
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
