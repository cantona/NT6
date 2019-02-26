// story:pangtong.c

#include <ansi.h>

nosave string char_id;
nosave string char_name;

object select_character();
int give_gift();

nosave mixed *story = ({
        "三軍蜿蜒而行。",
        "“嗯？那寫了什麼？”",
        "小兵：報告軍師，上面寫着“落雞坡”三個字。",
        "龐統：嗯... 不好！我的外號是小雞，這裏大大的不吉利，火速撤退！",
        "“轟！隆隆！”",
        "張任：嘿嘿！龐統，哪兒跑？以為我們四川這兒想來就來，想走就走？",
        "龐統：魏延將軍呢？",
        "小兵：報告軍師，魏延將軍在前頭，已經出谷了。",
        "龐統：黃忠將軍呢？",
        "小兵：報告軍師，黃老將軍在後頭，還沒有入谷。",
        "龐統：他奶奶的，就我一個不緊不慢，恰好趕在中間！",
        "張任：放箭！",
        "箭如雨下",
        "龐統翻翻白眼，倒在地上，口中吐出兩口鮮血，死了。",
        "......",
        "一年過去了...",
        "十年過去了...",
        "一百年過去了...",
        "一千年過去了...",
        "$N漫步在山間... 咦？這是什麼？",
        "亂堆從中一堆枯骨，中間好像有本書？",
        "$N翻了出來，發現這本書似乎不是一般的材料書寫的。",
        "“好像很值錢呀”，讓我看看....",
        "“嗯？鬼穀神算？”",
        (: give_gift :),
});

void create()
{
        seteuid(getuid());
        if (! objectp(select_character()))
        {
                STORY_D->remove_story("pangtong");
                destruct(this_object());
                return;
        }
}

string prompt() { return HIW "【傳奇】" NOR; }

object select_character()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 living($1) &&
                                                 $1->query_skill("literate", 1) > 50 &&
                                                 !query("doing", $1):));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        char_id=query("id", ob);
        char_name = ob->name(1);
        return ob;
}

mixed query_story_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (stringp(msg))
        {
                msg = replace_string(msg, "$N", char_name);
                msg = replace_string(msg, "$ID", char_id);
        }
        return msg;
}

int give_gift()
{
        object ob;
        object gob;

        ob = find_player(char_id);
        if (! ob) return 1;

        STORY_D->remove_story("pangtong");

        gob = new("/clone/book/guigu");
        gob->move(ob, 1);
        CHANNEL_D->do_channel(this_object(), "rumor", "聽説" + ob->name(1) +
                              "撿到了奇書《鬼穀神算》。");
        return 1;
}
