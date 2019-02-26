// story:jiuyang 九陽神功

#include <ansi.h>

nosave string char_id;
nosave string char_name;

int give_gift();
object select_character();

nosave mixed *story = ({
        "一堆佛經。",
        "$N拿起一本細細的看了半天，卻不得要領，這分明就是一本佛經，沒有半點武功訣竅。",
        "$N沉思片刻，將書反了過來，逆句讀、跳字讀，還是沒有什麼奧妙。",
        "盛怒之下，$N用力將佛經扔了開去，又揀起一本，卻是《金剛經》。",
        "研讀片刻，還是一堆廢話。",
        "“豈有此理，少林寺的藏經閣就放了這些東西？”$N心中暗道：“莫非少林僧人其實都不會武功？”",
        "隨揀隨丟，須臾已經翻了幾十本經書，沒有找到半點頭緒。",
        "$N不由得暗暗叫苦，看了看地上躺着的慧真和道一二人，心想：這次闖進藏經閣，實在是幹冒奇險，居然...",
        "一時間$N不由得心頭大怒，將手中的經書撕了個粉碎，霎時紙片飛揚。",
        "忽然幾張碎紙片飄過$N的眼前，似乎寫着：力從人借，氣由脊發。胡能氣由脊發...",
        "$N見識不凡，看了這幾句心中登時一動，這分明是極上乘的武學訣竅！",
        "$N看了看手中剩下的半卷經書，赫然是一本：《楞伽經》，只見夾縫中密密麻麻的寫着一些文字。",
        "只是經書已經缺了一半，如何是好？$N連忙在地上慢慢尋找，把碎紙一片片尋回。",
        "待到碎片悉數裱好，已然過了兩個時辰，$N細細讀過，原來這《楞伽經》夾縫中居然錄有一份九陽真經。",
        "$N心下暗自琢磨：當年華山論劍，也不過是爭奪一本九陰真經而已，今天我得了此書，當真是奇遇。",
        "$N隨即將燭台拿近，慢慢揣摩真經要旨，只是真經博大精深，一時未能全然領悟。",
        "眼見天色漸晚，$N不敢久留，揣起經書，想了想，又把經文開頭一段扯下撕碎，這才收好。",
        "$N暗道，待我回去細細研讀這九陽真經，他日天下無敵，豈不美哉？",
        "想罷，$N躍出窗去，悄然飄失在夜幕中。",
        (: give_gift :),
});

void create()
{
        seteuid(getuid());

        if (! objectp(select_character()))
        {
                STORY_D->remove_story("jiuyang");
                destruct(this_object());
                return;
        }
}

string prompt() { return HIG "【武林奇遇】" NOR; }

object select_character()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(),
                           (: living($1) &&
                              $1->query_skill("jiuyang-shengong", 1) < 1 &&
/*
                              query("combat_exp", $1) >= 100000 && 
                              query("combat_exp", $1)<1500000 && 
*/
                              SKILL_D("jiuyang-shengong")->valid_learn($1) &&
                              ! wizardp($1) &&
                              !query("story/jiuyang", $1):));
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
        object book;

        ob = find_player(char_id);
        if (! ob) return 1;

        if (ob->query_skill("jiuyang-shengong", 1) < 50)
                ob->set_skill("jiuyang-shengong", 50);

        set("story/jiuyang", 1, ob);
        tell_object(ob, HIC "你學習到了九陽神功。\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "聽説少林寺"
                              "藏經閣失竊，遺失楞伽經一本。");
        book = new("/clone/book/jiuyang-book");
        book->move(ob, 1);
        STORY_D->remove_story("jiuyang");
        return 1;
}
