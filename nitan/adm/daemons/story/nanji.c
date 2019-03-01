// story:nanji.c

#include <ansi.h>

string give_gift();

nosave mixed *story = ({
        "赤腳大仙：南極仙翁！您生日好。",
        "南極仙翁：呵呵，你好，你好。",
        "赤腳大仙：喏，這是我給你的禮物。",
        "南極仙翁：哈哈！還是你老兄聰明，就知道我喜歡喝酒。",
        "赤腳大仙：過獎過獎，對了，這是鬥戰勝佛讓我轉交的禮物。",
        "南極仙翁連忙接過。",
        "南極仙翁看了半天，道：什麼破玩藝，黑不溜秋的，看來他做了佛也改不了猴性。",
        "南極仙翁隨手把丹藥扔了出去。",
        (: give_gift :),
        "南極仙翁：啊？那我快去找找！",
        "赤腳大仙：唉！",
});

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

string give_gift()
{
        STORY_D->give_gift("/clone/gift/xisuidan", 1,
                           HIM "\n“啪”的一聲一枚黑不溜秋的丹藥掉到你面前。\n\n" NOR);
        return "赤腳大仙急道：唉！老兄，你誤會了！這是鬥戰勝佛蒙佛主所賜的洗髓丹，妙不可言。";
}
