// wuliang.c 事件：無量山玉壁劍舞

#include <ansi.h>

void create() { seteuid(getuid()); }

// 開始創建事件
void create_event()
{
        // 每月15日凌晨
        EVENT_D->at_after(0, 1, -15, -23);
}

// 獎勵
private void do_bonus(object room)
{
        object *obs;
        object ob;
        string msg;
        int lvl;
        int r;

        obs = all_inventory(room);
        obs = filter_array(obs, (: playerp($1) && living($1) :));
        if (sizeof(obs) < 1)
                return;

        r = random(100);
        if (r == 0)
        {
                msg = HIW  "只見皎潔的月光下，兩個飄逸絕倫的身影倒映在對面山壁之上，持劍翩翩起\n"
                           "舞，劍光頓挫，仙影迴翔。你不由驚歎：寰宇之中，竟有如此絕奧之技，今\n"
                           "日有緣得見仙人之姿，實在是福分非淺。\n" NOR;

                message("vision", msg, obs);

                for( int i=0; i<sizeof(obs); i++ )
                {
                        addn("potential", 1000, obs[i]);
                        addn("combat_exp", 5000, obs[i]);
                }

                // 增加武學修養基本劍法及基本身法
                foreach (ob in obs)
                {
                        if( query("combat_exp", ob)>2000000 )
                        {
                                tell_object(ob, HIG "你心中暗自掂量，這二人當真是"
                                                "世上高手，不過自己似乎也可辦到。\n" NOR);
                                continue;
                        }

                        if ((lvl = ob->query_skill("sword", 1)) >= 80 &&
                            ob->can_improve_skill("sword"))
                                ob->improve_skill("sword", 90000);

                        if ((lvl = ob->query_skill("dodge", 1)) >= 80 &&
                            ob->can_improve_skill("dodge"))
                                ob->improve_skill("dodge", 90000);

                        if ((lvl = ob->query_skill("martial-cognize", 1)) >= 80 &&
                            ob->can_improve_skill("martial-cognize"))
                                ob->improve_skill("martial-cognize", 40000);

                        tell_object(ob, HIG "你對仙人的劍舞頗有所感，武學上頓時有了新的領悟。\n" NOR);
                }

                // 記錄事件
                MAP_D->record_rumor(obs, "無量山玉壁劍舞", this_object());

                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "聽説大理無量山又出仙人劍舞，仙影玄奇，令人匪夷所思。");
        } else
        if (r < 60)
        {
                switch (random(3))
                {
                case 0:
                        msg = HIY "只見對面無量山玉壁上仙影一閃即過，身形之敏捷，令你根本無法捕捉。\n" NOR;
                        break;
                case 1:
                        msg = HIY "只見無量山玉壁上閃過幾道仙影，似乎是施展一種奇妙無比的武功絕學。\n" NOR;
                        break;
                default:
                        msg = HIY "忽然間兩個飄逸絕倫的身影顯映在對面山上，但仙影轉瞬即逝，你根本無法看清。\n" NOR;
                        break;
                }
                msg += HIG "你受到了仙影的感悟，武學方面又有了一些體會。\n" NOR;
                obs->improve_experience(500 + random(500));

                message("vision", msg, obs);

                // 記錄事件
                MAP_D->record_rumor(obs, "無量山玉壁仙影", this_object());
        } else
        {
                switch (random(3))
                {
                case 0:
                        msg = WHT "眼見皎潔的月光升起，可是一團雲飄過，遮蓋了月光，你眼前頓時一片漆黑。\n" NOR;
                        break;
                case 1:
                        msg = WHT "你目不轉睛的注視着對面的玉壁，可剎那間雷聲轟鳴，山風捲雲，將月光遮了個嚴實。\n" NOR;
                        break;
                default:
                        msg = WHT "夜晚已至，可一團團濃厚的雲層卻籠罩着天空，你連對面的山頭都無法看清。\n" NOR;
                        break;
                }
                msg += HIG "你不禁歎息道：“怎奈緣分未至，無緣窺視仙影！”\n" NOR;

                message("vision", msg, obs);
        }
}

// 事件觸發
void trigger_event()
{
        object room;

        // 無量山玉壁劍舞
        //if (objectp(room = find_object("/d/wanjiegu/wlhoushan")))
        if (objectp(room = find_object("/d/xiaoyao/pubu")))
                do_bonus(room);

        create_event();
}

// 描述
string query_detail(string topic)
{
        switch (topic)
        {
        case "無量山玉壁劍舞":
                return "皎潔的月光下，無量山壁上有仙人偏偏起舞，神姿仙態"
                       "平生難得一見。\n";

        case "無量山玉壁仙影":
                return "皎潔的月光下，壁上能隱隱約約倒影出仙人之姿。實乃"
                       "世間僅有。\n";

        }
}
