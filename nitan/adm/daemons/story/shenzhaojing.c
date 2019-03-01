#include <ansi.h> 

nosave string char_id; 
nosave string char_name;

object select_character();
int    give_gift(); 

nosave mixed *story = ({ 
        "很久，", 
        "很久，", 
        "很久，", 
        "以前。", 
        "某人碰到了一位女子，一見鐘情。", 
        "某人：凌霜華……為了愛你，就算讓我呆在牢裡，我也願意。。。。", 
        "□鐺！！！某人被關進了牢房。", 
        "某人：我死在這裡不要緊，但這武功以後無人知曉該怎麼辦？怎麼對的起梅念笙先生！", 
        "某人：哎……看看誰與我有緣吧。", 
        "“……靠，什麼破東西，居然敢砸到我的頭。”$N把書隨手一丟，大模大樣的走了。",
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
                                                 $1->query_skill("shenzhaojing", 1) < 1 && 
                                                 SKILL_D("shenzhaojing")->valid_learn($1) && 
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
        STORY_D->remove_story("shenzhaojing"); 
        STORY_D->give_gift("/clone/book/shenzhaojing", 1,
                           HIM "\n“啪”的一聲一本書掉到你面前。\n\n" NOR); 
        return 1;
} 
