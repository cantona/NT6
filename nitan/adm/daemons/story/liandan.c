// story:liandan 煉丹

#include <ansi.h>

int give_gift();

nosave mixed *story = ({
        "兩個童子拼命的煽火，只見煉丹爐中的火癒來癒旺。",
        "太上老君口中念念有詞：疾！",
        "兩個童子連忙開爐，一顆亮晶晶的仙丹騰空而起。",
        "太上老君金剛琢一抖，將仙丹圈下。",
        "太上老君舉著仙丹看了半天，嘆道：不知道這仙丹能不能發揮作用。",
        "太上老君：清風！來，你要不要試試這顆仙丹？",
        "清風忙不迭的搖頭：師傅！我就算了吧。",
        "太上老君：明月？",
        "明月慌忙道：我，我，我已經吃錯藥了！",
        "太上老君長嘆一聲，道：還是丟下去給凡人試試吧。",
        (: give_gift :),
});

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int give_gift()
{
        STORY_D->give_gift("/clone/gift/unknowdan", 1,
                           HIM "\n“啪”的一聲一顆仙丹掉到你面前。\n\n" NOR);
        return 1;
}
