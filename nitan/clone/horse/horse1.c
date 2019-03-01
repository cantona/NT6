
inherit ITEM;

#include <ansi.h>

#define MEMBER_D "/adm/daemons/memberd"

mapping trans = ([
"beijing"   : "/d/beijing/majiu",
"luoyang"   : "/d/luoyang/majiu",
"yangzhou"  : "/d/city/majiu",
"dali"      : "/d/dali/majiu", 
"foshan"    : "/d/foshan/majiu", 
"fuzhou"    : "/d/fuzhou/majiu", 
"guanwai"   : "/d/guanwai/majiu", 
"hangzhou"  : "/d/hangzhou/majiu", 
"lanzhou"   : "/d/lanzhou/majiu", 
"lingzhou"  : "/d/lingzhou/majiu", 
"yongdeng"  : "/d/huanghe/majiu", 
"suzhou"    : "/d/suzhou/majiu",
"xiangyang" : "/d/xiangyang/majiu", 
"yili"      : "/d/xingxiu/majiu", 
"chengdu"   : "/d/city3/majiu", 
"emei"      : "/d/emei/majiu1", 
"emei2"     : "/d/emei/majiu2", 
"quanzhou"  : "/d/quanzhou/majiu1", 
"jiaxing"   : "/d/quanzhou/majiu2", 
"jingzhou"  : "/d/jingzhou/majiu", 
"nanyang"   : "/d/shaolin/majiu1", 
"changan"   : "/d/changan/majiu", 
"wugong"    : "/d/quanzhen/majiu", 
"hengyang"  : "/d/henshan/majiu", 
"kaifeng"   : "/d/kaifeng/majiu", 
"kunming"   : "/d/kunming/majiu", 
"zhongzhou" : "/d/zhongzhou/majiu",
]);

mapping show_trans = ([
"beijing"   : "北京",
"luoyang"   : "洛陽",
"yangzhou"  : "揚州",
"dali"      : "大理", 
"foshan"    : "佛山", 
"fuzhou"    : "福州", 
"guanwai"   : "關外", 
"hangzhou"  : "杭州", 
"lanzhou"   : "蘭州", 
"lingzhou"  : "靈州", 
"yongdeng"  : "永登", 
"suzhou"    : "蘇州",
"xiangyang" : "襄陽", 
"yili"      : "伊犁", 
"chengdu"   : "成都", 
"emei"      : "峨嵋山", 
"emei2"     : "峨嵋半山", 
"quanzhou"  : "泉州", 
"jiaxing"   : "嘉興", 
"jingzhou"  : "荊州", 
"nanyang"   : "南陽", 
"changan"   : "長安", 
"wugong"    : "武功鎮", 
"hengyang"  : "衡陽", 
"kaifeng"   : "開封", 
"kunming"   : "昆明", 
"zhongzhou" : "中州",
]);

string get_trans_path(string s)
{
        return trans[s];
}

string get_trans_name(string s)
{
        return show_trans[s];
}

int is_horse()
{
        return 1;
}

void setup()
{
        set("ridable", 1);
        set("no_give", 1);        
        set("unit", "匹");
        set("base_unit", "匹");
        set_weight(1);

        remove_call_out("start_heart_beat");
        call_out("start_heart_beat", 2);

        ::setup();
}

int show_trans(object me)
{
        int i;
        string* places;
        mapping self_flag;

        write(HIY "你可以騎馬到以下地方：\n" NOR);

        places = keys(show_trans); 
        for (i = 0; i < sizeof(places); i ++)
                write(sprintf("%-20s%-20s\n", places[i], show_trans[places[i]]));

        // 自己記錄的地點
        self_flag = me->query("horse/flags");

        if (mapp(self_flag) && MEMBER_D->is_valib_member(me->query("id")))
        {
                if (sizeof(self_flag))
                {
                        places = ({});
                        places = keys(self_flag);
                        for (i = 0; i < sizeof(places); i ++)
                                write(sprintf(HIG "%-20s%-20s\n" NOR, places[i], "用戶記錄地點"));
                }
        }

        write(HIY "\n請使用 rideto <地名> 騎馬到指定地方。\n" NOR);

        return 1;

}

// 騎馬到指定地點
int move_to(object me, string place)
{
        object running, horse, follower;
        string trans_path;
        int trans_times, sk_riding, horse_level, horse_tili, cost_tili, level;
        string temp;
        object trans_target;

        // 檢查是否騎馬
        if (! objectp(horse = me->query_temp("is_riding")))
        {
                write("你並沒有騎馬啊。\n" );
                return 1;
        }
        if (horse->query_temp("running"))
        {
                write(this_object()->name() + NOR "正在奔跑呢！\n" NOR);
                return 1;
        }
        if (me->query_temp("running"))
        {
                write("你正在奔跑中呢。\n");
                return 1;
        }
        if (me->is_busy() || me->is_fighting())
        {
                write("你正忙呢！\n");
                return 1;
        }
        sk_riding = me->query_skill("riding", 1);
        if (sk_riding < 30)
        {
                write("你騎術不夠，無法騎馬到指定地點。\n");
                return 1;
        }

        // 檢查是否有該地方可去
        if (! stringp(trans_path = get_trans_path(place)))
        {
                if (stringp(trans_path = me->query("horse/flags/" + place)))
                {
                        if (! find_object(trans_path) && ! load_object(trans_path))
                        {
                                write("你無法騎馬達到這個地方。\n");
                                return 1;
                        }
                                
                }
                if (! stringp(trans_path = me->query("horse/flags/" + place)))
                {
                        write("你無法騎馬達到這個地方。\n");
                        return 1;
                }
                /*
                else
                {
                        if (! MEMBER_D->is_valib_member(me->query("id")))
                        {
                                write("你無法騎馬達到這個地方。\n");
                                return 1;
                        }
                }
                */
        }

        // 某些地方無法騎馬到達
        trans_target = find_object(trans_path);
        if (! objectp(trans_target))trans_target = load_object(trans_path);

        if (! objectp(trans_target))
        {
                write("你無法騎馬達到這個地方。\n");
                return 1;
        }
        
        if (trans_target->query("no_flyto"))
        {
                write("你無法騎馬達到這個地方。\n");
                return 1;
        }

    // 在天界也無法到達
        if (sscanf(trans_path, "/kungfu/class/sky%s", temp) == 1)
        {
                write("你無法騎馬達到這個地方。\n");
                return 1;
        }

        // 根據馬的好壞及騎馬者的騎術來判斷達到目的地時間
        level = horse->query("level");
        if (sk_riding >= 300)sk_riding = 300;
        trans_times = 1 + random(1 + 300 / sk_riding) + random(21 - level*4);

        if (trans_times <= 0)
                log_file("horse_time", trans_times + "\n");

        // 判斷騎馬到指定地點馬所消耗的體力
        horse_tili = horse->query("tili");
        cost_tili = 10 + random(trans_times * 25);

        if (horse_tili <= cost_tili)
        {
                write(horse->name() + NOR "體力不足，還是讓它休息會兒吧。\n");
                return 1;
        }

        running = new("/clone/misc/running");

        if (objectp(follower = horse->query_temp("is_rided_follow")))
        {
                if (environment(follower) && interactive(follower))
                        follower->move(running);
        }
        me->move(running);
        horse->add("tili", -1 * cost_tili);
        horse->set_temp("running", 1);
        me->set_temp("running", 1);

        message("vision",  "\n" + this_object() ->name() + HIW "一聲長"
                  "嘶，箭一般地沖出 ……\n" NOR, environment(me), ({horse}));

        call_out("arrived_dest", trans_times, me, follower, running, horse, trans_path);

        return 1;
}

int arrived_dest(object me, mixed follower, object running, object horse, string trans_path)
{
        if (objectp(me))
        {
                me->move(trans_path);
                me->delete_temp("running");
                if (random(2))me->improve_skill("riding", 1);
        }
        if (objectp(follower))follower->move(trans_path);
        if (objectp(horse))horse->delete_temp("running");
        if(objectp(running))destruct(running);

        if (objectp(horse))
                message("vision",  "\n" + this_object()->name() + HIW "到了目的地，猛然長嘶，前"
                          "踢高揚，頓時塵土四散……\n" NOR, environment(horse), ({horse}));

        return 1;
}

// 強行上馬
int force_me_ride(object me)
{
        object owner;

        if (this_object()->query_temp("is_rided_follow"))
                return 0;

        owner = this_object()->query_temp("is_rided_by");

          this_object()->set_temp("is_rided_follow", me);
        me->set_temp("is_riding_follow", this_object());

        message_vision("$N躍上$n" NOR "，坐在" + owner->name() + "的身後。\n", me, this_object());

        return 1;
}

// 心跳
void start_heart_beat()
{
     int level;
     object follower;

     remove_call_out("start_heart_beat");
     call_out("start_heart_beat", 2);

     level = this_object()->query("level");

     if (! this_object()->query_temp("running"))
     {
            if (this_object()->query("tili") + 1 < this_object()->query("max_tili"))                
                           this_object()->add("tili", level + random(level));
                
            if (this_object()->query("tili") > this_object()->query("max_tili"))
                this_object()->set("tili", this_object()->query("max_tili"));
     }

     follower = this_object()->query_temp("is_rided_follow");
     if (! objectp(follower))return;

     if (! objectp(environment(follower)) || 
         (objectp(follower) && ! interactive(follower)) ||
          (objectp(follower) && environment(follower) != environment(this_object()->query_temp("is_rided_by"))))
     {
            this_object()->delete_temp("is_rided_follow");
     }

     return;
}

int query_autoload()
{
     return 1;
}