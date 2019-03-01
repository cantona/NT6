// story:master 宗師聚會

#include <ansi.h>

nosave string *char_id;
nosave string *char_name;
nosave string winner_name;
nosave string winner_id;
nosave string ann_name;
nosave string ann_id;

int   get_winner();
mixed give_gift();
int   rob_gift();
int   select_characters();

nosave mixed *story = ({
        "$1[$I1]：好，今日我們五人齊聚華山，不必寒暄，可快入正題。",
        "$2[$I2]：嗯，來龍去脈也不必多說了，此次乃是為了江湖上近日出現的"
        HIM "玄黃紫清丹" NOR WHT "一事。",
        "$3[$I3]：聽說此丹千年一遇，服用以後妙用無窮，平增十年功力。",
        "$4[$I4]：嘿嘿，只是每次出現弄得江湖腥風血雨，不得安寧。",
        "$5[$I5]：所以在下召集諸位，以武會友，定下這神丹名分。",
        "$2[$I2]：也是，這等神物，若是給江湖宵小拿去，真可謂明珠暗投！",
        "$5[$I5]：近來江湖你爭我奪，在下實在是看不過去，這才親自出手取了來。",
        "$1[$I1]：甚好甚好，理當如此。",
        "$5[$I5]：只是此神物我也不敢貿然自居，故請得諸位來華山論劍，以決此物歸屬。",
        "$3[$I3]：廢話不必多說，如何比法？",
        "$4[$I4]：我們各顯絕藝，誰能壓倒對方，便是得主，如何？",
        "$2[$I2]：好吧，$4所言極是。",
        "...",
        "天黑了...",
        "天又亮了...",
        "天又黑了...",
        "天又亮了...",
        "...",
        (: get_winner :),
        "$a嘆服道：三天以來，看來還是$w武功高強，更勝一籌啊！",
        "$w謙道：哪裡哪裡，各位身手不凡，在下亦是眼界大開，方知天外有天。",
        "$a[$Ia]：不必謙讓，此物理應歸$w所有，此乃天意啊。",
        (: give_gift :),
        "$w[$Iw]：休走！接招！",
        "那黑影驀然回身，和$w對了一掌，只震得$w眼花繚亂，氣血翻湧。",
        "黑影哈哈長笑，飄然下山而去。",
        "$w調息良久，緩緩的吐出一口氣，道：此人內力當真深厚，我看好像是$6。",
        (: rob_gift :),
});

void create()
{
        seteuid(getuid());

        if (uptime() < 86400)
        {
                destruct(this_object());
                return;
        }

        ann_id = 0;
        ann_name = 0;
        winner_id = 0;
        winner_name = 0;
        if (! select_characters())
        {
                STORY_D->remove_story("master");
                destruct(this_object());
                return;
        }
}

string prompt() { return HIG "【華山論劍】" NOR; }

int select_characters()
{
        object *obs;
        object ob;
        int i;

        obs = filter_array(all_interactive(),
                           (: ! wizardp($1) && ultrap($1) && living($1):));
        if (sizeof(obs) < 6)
                return 0;

        char_id = allocate(6);
        char_name = allocate(6);
        for (i = 0; i < 6; i++)
        {
                ob = obs[random(sizeof(obs))];
                char_id[i]=query("id", ob);
                char_name[i] = ob->name(1);
                obs -= ({ ob });
        }

        return 1;
}

mixed query_story_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (functionp(msg)) msg = evaluate(msg);
        if (stringp(msg))
        {
                msg = replace_string(msg, "$1", char_name[0]);
                msg = replace_string(msg, "$I1", char_id[0]);
                msg = replace_string(msg, "$2", char_name[1]);
                msg = replace_string(msg, "$I2", char_id[1]);
                msg = replace_string(msg, "$3", char_name[2]);
                msg = replace_string(msg, "$I3", char_id[2]);
                msg = replace_string(msg, "$4", char_name[3]);
                msg = replace_string(msg, "$I4", char_id[3]);
                msg = replace_string(msg, "$5", char_name[4]);
                msg = replace_string(msg, "$I5", char_id[4]);
                msg = replace_string(msg, "$6", char_name[5]);
                msg = replace_string(msg, "$I6", char_id[5]);
                if (ann_name && ann_id)
                {
                        msg = replace_string(msg, "$a", ann_name);
                        msg = replace_string(msg, "$Ia", ann_id);
                }
                if (winner_name && winner_id)
                {
                        msg = replace_string(msg, "$w", winner_name);
                        msg = replace_string(msg, "$Iw", winner_id);
                }
        }
        return msg;
}

int get_winner()
{
        int i;

        i = random(5);
        winner_name = char_name[i];
        winner_id = char_id[i];
        do
        {
                i = random(5);
                ann_id = char_id[i];
                ann_name = char_name[i];
        } while (ann_id == winner_id);

        return 1;
}

mixed give_gift()
{
        object gob;
        object gift;

        gob = find_player(winner_id);
        if (random(2))
        {
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "聽說五大宗師在華山聚會，將" +
                                      "玄黃紫清丹交給" + winner_name + "。");
                STORY_D->remove_story("master");
                if (gob)
                {
                        gift = new("/clone/ultra/xuanhuang");
                        if (gift) gift->move(gob, 1);
                }
                return 0;
        }

        return "一道黑影掠過，一掌重重的擊在$a的背心，$a大叫一聲，吐出一口鮮血。";
}

int rob_gift()
{
        object rob;
        object gift;

        rob = find_player(char_id[5]);
        CHANNEL_D->do_channel(this_object(), "rumor",
                              "聽說" + char_name[5] + "從五大宗師手中奪走了"
                              "玄黃紫清丹。");
        STORY_D->remove_story("master");
        if (rob)
        {
                gift = new("/clone/ultra/xuanhuang");
                if (gift) gift->move(rob, 1);
        }
        return 0;
}
