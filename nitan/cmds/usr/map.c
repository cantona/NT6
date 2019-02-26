// map.c

#include <ansi.h>

inherit F_CLEAN_UP;

int map_view(object me, string arg);
int map_rumor(object me, string arg);

void create()
{
        seteuid(getuid());
}

int main(object me, string arg)
{
        string here, name;
        object env;
        string *mapped;
        int lvl;
        int exp, pot, score;
        int pot_limit;
        string msg;
        mixed prompt;
        string map;

        if (! arg)
        {
                MYGIFT_D->check_mygift(me, "newbie_mygift/map");  

                me->start_more(color_filter(MAP_D->show_map(environment(me)))); 
                return 1;
                return notify_fail("格式：map here | rumor | view | all | <地點> | <珍聞>。\n");
        }

        if (arg == "rumor")
                return map_rumor(me, arg);

        if (arg != "here")
                return map_view(me, arg);

        if( !query("out_family", me) )
        {
                write("你現在還沒有從師傅那裏領到地圖冊。\n");
                return 1;
        }

        // 查閲當前的環境
        env = environment(me);
        name = env->short();
        if( !stringp(here=query("outdoors", env)) )
        {
                write("只有在户外才有必要繪製地圖。\n");
                return 1;
        }

        if (! stringp(name) || clonep(env))
        {
                write("這裏是一處神祕的地方，你無法判斷它的方位。\n");
                return 1;
        }

        if( query("map_all", me) )
        {
                write("你已經獲得了地圖全集，沒有必要再繪製地圖了。\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("你現在正忙，沒有時間繪製地圖。\n");
                return 1;
        }

        // 查閲已經繪製過的地圖
        mapped=query("map/"+here, me);
        if (! arrayp(mapped)) mapped = ({ });
        if (member_array(name, mapped) != -1)
        {
                write("你已經繪製過這附近的地圖了，沒有必要"
                      "再重複了。\n");
                return 1;
        }

        if (! MAP_D->been_known(here))
        {
                write("你覺得這裏沒什麼好畫的。\n");
                return 1;
        }

        if( prompt=query("no_map", env) )
        {
                // no draw here
                if (stringp(prompt))
                        write(prompt);
                else
                        write("你看了半天，也沒有弄清楚附近的地形。\n");
                return 1;
        }

        if( query("jing", me)<50 )
        {
                write("你的精神不佳，無法集中全神貫注的繪製地圖。\n");
                return 1;
        }

        // 消耗精
        me->receive_damage("jing", 20 + random(30));

        if ((lvl = me->query_skill("drawing", 1)) < 30)
        {
                write("你在紙上塗抹了一會兒，連自己都看不出是什麼東西。\n");
                return 1;
        }

        message("vision", me->name() + "抬頭看了看四周，埋頭"
                "仔仔細細的繪製着什麼。\n", environment(me), ({ me }));
        tell_object(me, "你精心的繪製了" + name + "附近的地形。\n");

        mapped += ({ name });
        set("map/"+here, mapped, me);

        me->start_busy(1 + random(3));

        // 計算獎勵
        if (lvl > 200)
                lvl = (lvl - 200) / 4 + 150;
        else
        if (lvl > 100)
                lvl = (lvl - 100) / 2 + 100;

        exp = 20 + random(20);
        pot = 5 + random((lvl - 20) / 3);
        score = random(2);
        pot_limit=me->query_potential_limit()-query("potential", me);
        if (pot_limit < 0)
                pot_limit = 0;
        if (pot >= pot_limit)
                pot = pot_limit;

        msg = "你獲得了" + chinese_number(exp) + "點經驗";
        if (pot > 0)
                msg += "和" + chinese_number(pot) + "點潛能";

        if (score)
                msg += "，通過體驗，你累積了" + chinese_number(score) +
                       "點江湖閲歷";

        // 獎勵生效
        write(HIC + msg + "。\n" NOR);
        addn("combat_exp", exp, me);
        addn("potential", pot, me);
        addn("score", score, me);

        return 1;
}

// 查看已經繪製部分的地圖
int map_view(object me, string arg)
{
        mapping mapped;
        mapping rumor;
        string outdoors;
        string *shorts;
        string result;
        string key;
        string map;


        if (file_size("/doc/map/" + arg) > 0 &&
            stringp(map = read_file("/doc/map/" + arg)))
        {
                map = MAP_D->make_color(map);
                me->start_more(color_filter(map));
                return 1;
        }

        if( !query("out_family", me) )
        {
                write("你還沒有出門歷練，開始繪製地圖呢。\n");
                return 1;
        }

        mapped=query("map", me);
        if( !query("map_all", me) && !mapp(mapped) )
        {
                write("你還沒有繪製任何一個地方的地圖。\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("你現在正忙，沒法查看地圖。\n");
                return 1;
        }

        message_vision("$N拿出一本東西，嘩啦嘩啦的"
                       "翻開看了起來。\n", me);
        me->start_busy(1);

        // 察看是否閲讀記載
        if( mapp(rumor=query("rumor", me)) && 
            member_array(arg, keys(rumor)) != -1)
        {
                write("你翻到地圖冊的後面，仔細閲讀有關『" + arg +
                      "』的記載。\n" WHT + rumor[arg]->query_detail(arg) + NOR);
                return 1;
        }

        // 是否是察看本地地圖？
        if( arg == "view" || query("map_all", me) )
        {
                write(MAP_D->marked_map(environment(me)));
                me->start_busy(2);
                return 1;
        }

        // 判斷是否是中文地圖名字
        foreach (key in keys(mapped))
                if (MAP_D->query_map_short(key) == arg)
                {
                        // 是中文名字，轉換成英文ID
                        arg = key;
                        break;
                }

        // 查找這方面的地圖
        if (arrayp(shorts = mapped[arg]))
        {
                result = MAP_D->query_maps(arg);
                foreach (key in shorts)
                {
                        reset_eval_cost();
                        if (! stringp(key))
                                continue;
                        result = MAP_D->mark_map(result, key);
                }
                result = replace_string(result, "@R", WHT);
                result = replace_string(result, "@N", NOR);
                me->start_more(MAP_D->query_map_short(arg) + "的地圖信息：\n" + result);
                me->start_busy(2);
                return 1;
        }

        if (arg != "all")
        {
                write("你的地圖冊中並沒有有關 " + arg + " 的信息啊！\n");
                return 1;
        }

        outdoors=query("outdoors", environment(me));
        if (stringp(outdoors))
                result = "你現在身處" + MAP_D->query_map_short(outdoors) + "境內。\n";

        result = "目前你已經繪製了以下這些地方的地圖：\n";
        foreach (key in keys(mapped))
                result += MAP_D->query_map_short(key) + "("
                          HIY + key + NOR ")\n";
        write(result);
        return 1;
}

int map_rumor(object me, string arg)
{
        mapping rumor;
        string msg;

        if( !mapp(rumor=query("rumor", me)) )
        {
                write("你現在並沒有記錄任何傳聞趣事。\n");
                return 1;
        }

        msg = "你目前記載了有關" + implode(keys(rumor), "、") + "的傳聞。\n";
        msg = sort_string(msg, 60);
        write(msg);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : map here | rumor | all | map | view | <地點> | <珍聞>

如果你身上有了地圖冊，就可以使用這條命令繪製附近的地圖。當然
你必須是在户外，並且具備有一定的繪畫技巧才可以。繪製地圖可以
增加你的經驗、潛能並積累江湖閲歷。

使用 map all 可以查看你現在已經繪製了哪些地方的地圖， 而如果
指名了具體的地方，則可以查看該地點的地圖繪製情況。

如果你在户外，則可以使用 map view 命令查看你所在的地點。

map rumor 可以查閲你目前記錄的各地珍聞，使用 map <珍聞> 則可
以查看具體內容。
HELP );
    return 1;
}