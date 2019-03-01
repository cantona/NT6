// story:mengzi.c

#include <ansi.h>

nosave string char_id;
nosave string char_name;

object select_character();
int    give_gift();

nosave mixed *story = ({
        "大旱，民饑。",
        "流民如潮。",
        "$N架起大鍋，在路邊舍粥。",
        "天色漸晚，眼見鍋中粥將罄。",
        "只見路邊搖搖晃晃走過來一人。",
        "$N勺起最後一碗粥，就道：“嗟...”",
        "猛然間發現那人頭戴綸巾，雖然破舊，卻是整整齊齊。",
        "$N心中暗道：可不要是一個書呆子，讓我這最後一碗粥送不出去。",
        "想到這裡，便將那個嗟字暗自吞下肚子，客氣道：“這位先生，可能賞臉飲碗粥。”",
        "那人看了看$N，感激道：“一路上我為了這骨氣忍饑挨餓，想不到終于遇到這位賢人。”",
        "$N暗道：果然是個書呆子，還好，還好。",
        "...",
        "那人喝完粥，掏出一本破破爛爛的書，遞給$N。",
        "$N：...",
        "那人道：“承蒙賜粥，無以相贈，這本孟子送送給先生吧。”",
        "......",
        "眼見那人蹣跚而去，$N翻了翻手中的書，苦笑不止。",
        "“我大字不識一個，要這破書作甚？”想到這裡，$N把書隨手一丟，收起鍋走路。",
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

object select_character()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 living($1) &&
                                                 $1->query_skill("literate", 1) < 1 &&
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
        STORY_D->remove_story("mengzi");
        STORY_D->give_gift("/clone/book/mengzi", 1,
                           HIM "\n“啪”的一聲一本書掉到你面前。\n\n" NOR);
        return 1;
}
