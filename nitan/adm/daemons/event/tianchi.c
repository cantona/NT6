// emei.c 事件：長白山天池夜隕

#include <ansi.h>

void create() { seteuid(getuid()); }

// 開始創建事件
void create_event()
{
        // 每凌晨12點
        EVENT_D->at_after(0, 0, 1, -1);
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

        r = random(365);
        if (r == 0)
        {
                msg = HIR "只聽天空驟然傳來一陣刺耳的摩擦聲，你仰望上蒼，發現穹蒼裡已豁然出現\n"
                          "無數顆流星。夜隕如雨飛墜，鋒芒劃空，爾落入天池之中，又再激起萬股七\n"
                          "色浪濤，漆黑夜穹竟猶如白晝一般。你不禁感嘆，大自然之威，當真神鬼莫\n"
                          "測。\n" NOR;

                msg += HIC "你仔細的觀察了流星雨的全過程，發現其中竟有很多奧秘可以融于武學。\n" NOR;

                for( int i=0; i<sizeof(obs); i++ )
                {
                        addn("potential", 300, obs[i]);
                        addn("combat_exp", 500, obs[i]);
                }

                message("vision", msg, obs);

                // 增加基本身法、暗器。胡家弟子可以同時增加內功及刀法。
                foreach (ob in obs)
                {
                        if ((lvl = ob->query_skill("dodge", 1)) >= 80 &&
                            ob->can_improve_skill("dodge"))
                                ob->improve_skill("dodge", 160000);

                        if ((lvl = ob->query_skill("throwing", 1)) >= 80 &&
                            ob->can_improve_skill("throwing"))
                                ob->improve_skill("throwing", 160000);

                        /*
                        if( query("born_family", ob) != "關外胡家" )
                                continue;
                        */

                        if (ob->query_skill("mantian-xing", 1) >= 80 &&
                            !query("can_perform/mantian-xing/xing", ob) )
                        {
                                tell_object(ob, HIM "你心中一動，登時有所感悟，領悟了滿天星中穹外飛星這一絕技！\n" NOR);
                                set("can_perform/mantian-xing/xing", 1, ob);
                        }
                }

                // 記錄事件
                MAP_D->record_rumor(obs, "天池流星雨", this_object());

                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "聽說長白山天池上夜空竟現流星雨，五彩繽紛，煞為壯觀。");
        } else
        if (r < 40)
        {
                msg = RED "只聽遠處一陣刺耳的摩擦聲，舉目望去，發現竟有流星從天邊劃過，怎奈距\n"
                          "隔委實太遠，根本無法看清。\n" NOR;

                msg += HIC "你觀罷流星，隱隱的對暗器功夫有了一絲體會。\n" NOR;

                obs->improve_skill("throwing", 300);
                message("vision", msg, obs);

                // 記錄事件
                MAP_D->record_rumor(obs, "夜空流星", this_object());
        } else
        {
                switch (random(2))
                {
                case 0:
                        msg = WHT "眼見天邊一片明亮，知是流星雨將至，可怎奈間隔遙且雲層厚，卻無緣得見。\n" NOR;
                        break;
                default:
                        msg = WHT "眼見天邊一片明亮，但是水氣，霧氣和雲層交雜，讓你什麼都看不清楚。\n" NOR;
                        break;
                }
                msg += HIG "你心中連嘆：“太可惜了！”\n" NOR;

                message("vision", msg, obs);
        }
}

// 事件觸發
void trigger_event()
{
        object room;

        // 長白山天池夜隕
        if (objectp(room = find_object("/d/guanwai/tianchi1")))
                do_bonus(room);

        create_event();
}

// 描述
string query_detail(string topic)
{
        switch (topic)
        {
        case "天池流星雨":
                return "長白山天池夜空能見流星雨，煞為壯觀。\n";

        case "夜空流星":
                return "夜空常有流星隕落，頗為美麗。\n";
        }
}
