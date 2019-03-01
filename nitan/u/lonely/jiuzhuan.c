// story:niulang 牛郎織女 ->改為偷九轉

#include <ansi.h>

nosave string char_id;
nosave string char_name;
nosave string family_name;

int give_gift();
object select_character();

string prompt() { return HIY "【故事傳聞】" NOR; }

nosave mixed *story = ({
        "太上老君的煉丹房。",
        "清風和明月正在打盹。",
        "ZZZ~~~~~",
        "$N翻箱倒櫃正找著什麼。",
        "門外傳來敲門聲：清風、明月，該起來尿尿啦！",
        "$N嚇得屁滾尿流，這不是太上老君的聲音嗎！",
        "太上老君：$N，你在這裡幹啥，莫非是學那猴頭來盜我仙丹？",
        "說罷手中浮塵一揮，$N便飛將出去。",
        "$N眼前一黑，從手中掉落一物。",
                (: give_gift :),
        "太上老君大叫：哎呀！不好，我的仙丹！",                
});
object select_character()
{
        object *obs;
        object ob;
        
        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 environment($1) &&
                                                 query("outdoors", environment($1)) && 
                                                 !query("doing", $1):));
        if (! sizeof(obs))
                return 0;
        
        ob = obs[random(sizeof(obs))];
        char_id=query("id", ob);
        char_name = ob->name(1);
        family_name=query("family/family_name", ob);
        return ob;
}
void create()
{
        seteuid(getuid());
                if (! objectp(select_character()))
        {
                        destruct(this_object());
                        return;
        }
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
        }
    return msg;
}

int give_gift()
{
        STORY_D->give_gift("/clone/gift/jiuzhuan", 1,
                HIM "\n“啪”的一聲一顆閃閃發光的仙丹掉到你面前。\n\n" NOR);
        return 1;
}
