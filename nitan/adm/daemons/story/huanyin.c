// story:huanyin 幻陰指法

#include <ansi.h>

nosave string char_id;
nosave string char_name;
nosave string family_name;

int give_gift();
object select_character();

nosave mixed *story = ({
        "謝遜：成昆！休走，今天我就和你做一了斷",
        "成昆：他奶奶的，今天遇到這瞎子，算我倒黴到家了。",
        "楊逍：成昆，你作惡多端，害死陽教主，今天還想跑麼？",
        "韋一笑：當年光明頂的事情還沒有了阿，你就這麼走了？",
        "張無忌哼了一聲，暗道：義父和這人是血海深仇，不能不報，我倒不必插手。",
        "成昆呵呵大笑：老夫豈能怕了你們，只不過你們倚多取勝，老夫就不能奉陪了。",
        "韋一笑笑道：成昆，你就呆着這裏，若能打贏獅王，就讓你走路，我們決不插手。",
        "成昆冷笑一聲，道：老夫活了幾十年，居然還在我面前玩這種小兒科？",
        "韋一笑陰陰道：那就別怪我...",
        "只見韋一笑身形倏的變快，直令人匪夷所思，雙腳踢得塵土飛揚，猶如一道利箭趕了上來...",
        "成昆暗道：吾命休矣！韋一笑倒也罷了，只是他纏上身來，我卻怎麼落得脱身？",
        "忽然路邊一人飄然而至，“嗯？這是為何？”",
        "韋一笑一掌探出，拍向那人，喝道：“讓開！”",
        "$N訝道：“怎的如此狠毒？想必也不是什麼善類。”隨即一掌輕輕揮出。",
        "兩掌相交，只震得韋一笑眼花繚亂，氣血翻湧，人平平的飛了出去，一跤摔倒在地。",
        "張無忌見狀大驚，連忙欺身近來，護住韋一笑。",
        "成昆哈哈大笑，道：張教主、楊左使、韋蝠王還有我得好徒兒，今天我可要失陪了。",
        "張無忌喝道：閣下何人？為何要插手此事？",
        "$N淡淡道：久聞明教無惡不作，今日一見，果不其然，我便是$N，如若不服，他日找上$F就是。",
        "張無忌：@@@@@@@",
        "......",
        "成昆：今天承蒙相救，老夫感激不盡，無以為贈，這路幻陰指法乃在下精研，閣下如果有意，也可參詳一番。",
        (: give_gift :),
});

void create()
{
        seteuid(getuid());

        if (! objectp(select_character()))
        {
                destruct(this_object());
                return;
        }
}

string prompt() { return HIG "【武林傳聞】" NOR; }

object select_character()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(),
                           (: ultrap($1) &&
                              living($1) &&
                              $1->query_skill("huanyin-zhi", 1) < 1 &&
                              query("family/family_name", $1) && 
                              ! wizardp($1) &&
                              !query("story/huanyin", $1):));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        char_id=query("id", ob);
        char_name = ob->name(1);
        family_name=query("family/family_name", ob);
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
                msg = replace_string(msg, "$F", family_name);
                msg = replace_string(msg, "$ID", char_id);
        }
        return msg;
}

int give_gift()
{
        object ob;

        ob = find_player(char_id);
        if (! ob) return 1;

        if (ob->query_skill("huanyin-zhi", 1) < 10)
                ob->set_skill("huanyin-zhi", 10);

        set("story/huanyin", 1, ob);
        tell_object(ob, HIC "你從成昆那裏學習到了幻陰指法。\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "聽説" + ob->name(1) +
                              "從成昆那裏學習到了幻陰指法。");
        STORY_D->remove_story("huanyin");
        return 1;
}
