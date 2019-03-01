// story:laojun

#include <ansi.h>

string give_gift();

nosave mixed *story = ({
        "玉皇大帝：老君，你那兒有沒有治笨病的藥？",
        "太上老君：有，有，我這兒新研制了一種仙丹，可以使人變聰明。",
        "玉皇大帝大喜道：好，快給我兩顆。",
        "太上老君疑惑道：莫非......",
        "玉皇大帝長嘆一聲：不是不是，我們家那口子是越來越不行了，蟠桃園虧慘了！還不及弼馬溫管呢。", 
        "太上老君掏出一葫蘆：喏，這兒。",
        "玉皇大帝：" HIC "哎呀！" NOR,
        "太上老君：不好，怎麼掉了，馬上派人去找找。",
        "玉皇大帝：算了算了，不就一仙丹嘛，再給我一顆就是了。",
        (: give_gift :)
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
        STORY_D->give_gift("/clone/gift/xiandan", 1,
                           HIM "\n“啪”的一聲一枚仙丹掉到你面前。\n\n" NOR);
        return HIM "聽說天庭遺落了一枚仙丹。" NOR;
}
