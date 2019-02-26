// group_quest:family 羣組任務——門派入侵

#include <ansi.h>
#include "family.h"

void create()
{
        seteuid(getuid());

        if (!select_quest())
        {
                // destruct(this_object());
                return;
        }
}

//string prompt() { return HIR "【門派入侵】" NOR; }
string prompt() { return HIR "【門派】" NOR; }

int select_quest()
{
        int i;
        object *all_user;
        object ob,the_user;
        string p,*kp;
        mapping fam_map = ([]);

        // 遍歷再現所有玩家，取得每個門派的在線玩家數，存入變量fam_map  family -> player_number
        foreach (object user in users())
        {
                if (! wizardp(user))
                {
                    p=query("family/family_name", user);
                    if (! stringp(p)) continue;
                    if (undefinedp(fam_map[p]))
                        fam_map[p] = ({ user });
                    else
                        fam_map[p] += ({ user });
                }
        }

        // MUD中沒有屬於任何一個門派的玩家
        if (!sizeof(fam_map))
            return 0;

        // 取得有玩家在線的門派名單
        kp = keys(fam_map);
        kp -= ({ "古村", "絕情谷", "雲龍門", "華山劍宗" });
        if( !sizeof(kp) ) return 0;

        // 隨即挑選一個門派
        p = kp[random(sizeof(kp))];

        // 根據這個門派在線的玩家數決定任務敵人數
        all = sizeof(fam_map[p]);
        if (all < 5) all = 5;
        if (all > 20) all = 30 - random(10);

        the_family = p;

        // 從這個門派中隨機抽取三個玩家的名單，
        // 這裏有一個問題，如果這個門派在線的玩家數少於3人怎麼辦？
        // 而且我也沒有發現哪裏使用到了name1, name2, name3，很奇怪
        // 我現在把他們放到一個name數組裏面
        i = 3;
        while (i--)
        {
            if (sizeof(fam_map[p]))
            {
                name[i]=(query("name", fam_map[p][random(sizeof(fam_map[p]))]));
            }
            else
                name[i] = p + "弟子";
        }

        // 設置國家
        the_nation = "中國";
        the_enemy = GROUP_QUEST_D->get_enemy(); 

        // 選取一個故事
        story = all_story[random(sizeof(all_story))];

        return 1;
}

string create_tiaoxin()
{
        object ob;
        int i,lvl;
        string title;

        title = HIY + the_family + NOR + HIW + "仇家" + NOR + " " + HIY +
                        the_enemy + NOR;

        for (i = 0;i < all;i ++)
        {
                lvl = random(15) + 1;
                ob = GROUP_QUEST_D->create_npc(the_nation,lvl);
                GROUP_QUEST_D->place_npc(ob,"門派",the_family,lvl);
                set("title", title, ob);
                ob->random_move();
                ob->random_move();
                ob->random_move();
                ob->random_move();
        }
        GROUP_QUEST_D->set_enemy(all);
        return "大小嘍羅高呼：『" + HIY + "【" + the_family + "】" + NOR + WHT + "的人快給我滾出來，大爺們今天要你們的好看！！』";
}

mixed query_quest_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (stringp(msg))
        {
                msg = replace_string(msg,"name1",name[0]);
                msg = replace_string(msg,"name2",name[1]);
                msg = replace_string(msg,"name3",name[2]);
                msg = replace_string(msg,"the_enemy",HIY + the_enemy + NOR + WHT);
                msg = replace_string(msg,"the_family",HIY + "【" + the_family + "】" + NOR + WHT);
        }
        return msg;
}
