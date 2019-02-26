// story:zagang.c

#include <ansi.h>

int give_gift();

nosave mixed *story = ({
        "關羽：聽説三弟你在長板橋一下子嚇跑了幾十萬大軍，好厲害啊。",
        "張飛：那是自然，我吃了神力丸，功力是更勝往昔！",
        "關羽：嘖嘖，真不錯，三弟還有沒有？",
        "張飛塞給關羽一顆神力丸，道：我這還多着呢。",
        "關羽：嘿嘿！",
        "張飛：噢！二哥，有件事忘説了，據説吃完以後人的臉色會變。",
        "關羽：？怎麼變？",
        "張飛：像我，白臉變黑臉唄，往相反的方向變嘛。",
        "關羽：靠！那我不是要變成綠臉了？",
        "張飛：應該。",
        "關羽狠狠的把神力丸扔了出去。",
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
        STORY_D->give_gift("/clone/gift/shenliwan", 1,
                           HIM "\n“啪”的一聲一枚神力丸掉到你面前。\n\n" NOR);
        return 0;
}
