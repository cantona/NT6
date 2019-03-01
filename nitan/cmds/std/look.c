// This program is a part of NITAN MudLIB
// look.c

#pragma optimize
#pragma save_binary

#include <room.h>
#include <ansi.h>
#include <combat.h>
#include <armor.h>

// flag of func:look_all_inventroy_of_room/ret_str
#define SHOW_IMMEDIATELY        0
#define RETURN_RESULT           1

inherit F_CLEAN_UP;

#include <locate.h>
int look_room(object me, object env, int brief);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);
string look_equiped(object me, object obj, string pro);
string look_all_inventory_of_room(object me, object env, int ret_str);
string gettof(object me, object obj);
string getdam(object me, object obj);

mapping df_bkpic=([
        "foshan":"xiaozheng",
        "village":"xiaozheng",
        "hangzhou":"hangzhou",
        "heimuya":"heimuya",
        "huashan":"huashan",
        "guanwai":"guanwai",
        "lingjiu":"lingjiu",
        "motianya":"motianya",
        "register":"yanluodian",
        "shenlong":"shenlong",
        "taohua":"taohua",
        "wudang":"wudang",
        "wanjiegu":"wanjiegu",
        "xiakedao":"xiakedao",
        "quanzhen":"quanzhen",
        "beijing":"beijing",
        "changan":"changan",
        "city":"city",
        "city3":"city3",
        "dali":"dali",
        "emei":"emei",
]);

mapping rf_bkpic=([
        "_d_beijing_dangpu":"dangpu",
        "_d_changan_dangpu":"dangpu",
        "_d_city_dangpu":"dangpu",
        "_d_foshan_dangpu":"dangpu",
        "_d_xiangyang_dangpu":"dangpu",
        "_d_suzhou_dangpu":"dangpu",
        "_d_city_shuyuan":"shuyuan",
        "_d_city_shuyuan2":"shuyuan",
        "_d_suzhou_shuyuan":"shuyuan",
        "_d_songshan_shuyuan":"shuyuan",
        "_d_hangzhou_shuyuan":"shuyuan",
        "_d_changan_zahuopu":"zahuopu",
        "_d_fuzhou_zahuopu":"zahuopu",
        "_d_beijing_huichuntang":"yaopu",
        "_d_changan_yaopu":"yaopu",
        "_d_xiangyang_yaopu":"yaopu",
        "_d_suzhou_yaopu":"yaopu",
        "_d_dali_yaoshop":"yaopu",
        "_d_city_zuixianlou":"jiulou",
        "_d_city_shuyuan":"shuyuan",
        "_d_city_shuyuan2":"shuyuan",
        "_d_suzhou_shuyuan":"shuyuan",
        "_d_songshan_shuyuan":"shuyuan",
        "_d_hangzhou_shuyuan":"shuyuan",
        "_d_changan_zahuopu":"zahuopu",
        "_d_fuzhou_zahuopu":"zahuopu",
        "_d_beijing_huichuntang":"yaopu",
        "_d_changan_yaopu":"yaopu",
        "_d_xiangyang_yaopu":"yaopu",
        "_d_suzhou_yaopu":"yaopu",
        "_d_dali_yaoshop":"yaopu",
        "_d_city_zuixianlou":"jiulou",
        "_d_dali_huanggs":"huanggs",
        "_d_emei_jinding":"jingding",
        "_d_death_gate":"guimenguan",
        "_d_changan_bank":"qiangzhuang",
        "_d_beijing_qianzhuang":"qianzhuang",
        "_d_city_qianzhuang":"qianzhuang",
        "_d_changan_bank":"qiangzhuang",
        "_d_beijing_qianzhuang":"qianzhuang",
        "_d_city_qianzhuang":"qianzhuang",
        "_d_emei_jinding":"jingding",
        "_d_dali_huanggs":"huanggs",
        "_d_beijing_dangpu":"dangpu",
        "_d_changan_dangpu":"dangpu",
        "_d_city_dangpu":"dangpu",
        "_d_foshan_dangpu":"dangpu",
        "_d_xiangyang_dangpu":"dangpu",
        "_d_suzhou_dangpu":"dangpu",
]);

string *power_level_desc = ({
        BLU "不堪一擊" NOR,
        BLU "毫不足慮" NOR,
        BLU "不足掛齒" NOR,
        BLU "初學乍練" NOR,
        BLU "勉勉強強" NOR,
        HIB "初窺門徑" NOR,
        HIB "初出茅廬" NOR,
        HIB "略知一二" NOR,
        HIB "普普通通" NOR,
        HIB "平平淡淡" NOR,
        CYN "平淡無奇" NOR,
        CYN "粗通皮毛" NOR,
        CYN "半生不熟" NOR,
        CYN "馬馬虎虎" NOR,
        CYN "略有小成" NOR,
        HIC "已有小成" NOR,
        HIC "鶴立雞群" NOR,
        HIC "駕輕就熟" NOR,
        HIC "青出于藍" NOR,
        HIC "融會貫通" NOR,
        HIG "心領神會" NOR,
        HIG "爐火純青" NOR,
        HIG "了然于胸" NOR,
        HIG "略有大成" NOR,
        HIG "已有大成" NOR,
        YEL "豁然貫通" NOR,
        YEL "出類拔萃" NOR,
        YEL "無可匹敵" NOR,
        YEL "技冠群雄" NOR,
        YEL "神乎其技" NOR,
        HIY "出神入化" NOR,
        HIY "非同凡響" NOR,
        HIY "傲視群雄" NOR,
        HIY "登峰造極" NOR,
        HIY "無與倫比" NOR,
        RED "所向披靡" NOR,
        RED "一代宗師" NOR,
        RED "精深奧妙" NOR,
        RED "神功蓋世" NOR,
        RED "舉世無雙" NOR,
        WHT "驚世駭俗" NOR,
        WHT "撼天動地" NOR,
        WHT "震古鑠今" NOR,
        WHT "超凡入聖" NOR,
        WHT "威鎮寰宇" NOR,
        HIW "空前絕後" NOR,
        HIW "天人合一" NOR,
        MAG "深藏不露" NOR,
        HIM "深不可測" NOR,
        HIR "返璞歸真" NOR
});
string *heavy_level_desc= ({
        "極輕",
        "很輕",
        "不重",
        "不輕",
        "很重",
        "極重"
});

string power_level(int power)
{
        int lvl;
        int rawlvl;
        int grade = 1;

        if (power < 0) power = 0;

        rawlvl = (int) pow( (float) 1.0 * power, 0.3);
        lvl = to_int(rawlvl/grade);
        if (lvl >= sizeof(power_level_desc))
                lvl = sizeof(power_level_desc)-1;
        else if (lvl >= sizeof(power_level_desc) - 1)
                lvl = sizeof(power_level_desc) - 2;
        return power_level_desc[((int)lvl)];
}

string gettof(object me, object ob)
{
        object weapon;
        string skill_type;
        mixed attack_points;
        mapping prepare;

        if( objectp(weapon=query_temp("weapon", ob)) )
        {
                skill_type=query("skill_type", weapon);
                attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
        } else
        {
                string *sk;

                prepare = me->query_skill_prepare();
                if (! prepare) prepare = ([]);
                sk = keys(prepare);

                if (sizeof(sk) == 0) skill_type = "unarmed";
                else skill_type = sk[0];
                attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
                if (sizeof(prepare) == 2)
                {
                        mixed temp;
                        temp = COMBAT_D->skill_power(ob, sk[1], SKILL_USAGE_ATTACK);

                        if (attack_points < temp)
                                attack_points = temp;
                 }
        }
        return power_level(attack_points/10000);
}

string getdam(object me, object obj)
{
        int level;

        if (objectp(query_temp("weapon", obj)))
                level=query_temp("apply/damage", obj);
        else
                level=query_temp("apply/unarmed_damage", obj);

        level+=query("jiali", obj);
        level = level / 200;
        if( level >= sizeof(heavy_level_desc) )
                level = sizeof(heavy_level_desc)-1;
        if( level < 0 ) level = 0;
        return heavy_level_desc[((int)level)];
}

//add by JackyBoy@XAJH 2001/5/6
string get_bkpic(object env)
{
        string rf, df;

        rf = replace_string(base_name(env),"/","_");
        df = domain_file(rf);
        if (! undefinedp(rf_bkpic[rf]))
                return rf_bkpic[rf];
        if (! undefinedp(df_bkpic[df]))
                return df_bkpic[df];
        return "";
}

int info(object me, object env)
{
        string *dirs;
        string df;
        mapping exits;

        if( mapp(exits=query("exits", env)) )
                dirs = keys(exits);

        if (sizeof(dirs) == 1 && sizeof(dirs) != 0)
                write(TMI("bnway "+dirs[0]+";"));
        else if (sizeof(dirs) != 0)
                write(TMI( sprintf("bnway "+"%s;",implode(dirs[0..sizeof(dirs)], ";")) ));
        df = get_bkpic(env);
        if (df == "") return 1;
        if( df != query_temp("bkpic", me) )
        {
                set_temp("bkpic", df, me);
                write(TMI("bkpic "+df));
        }
        return 1;
}

string locate(string file)
{
        string domain_file;
        string *all_place;
        string the_place;

        if (sscanf(file, "/f/%*s"))
                return "副本";

        domain_file = domain_file(file);

        if (! undefinedp(place[domain_file]))
        {
                all_place = place[domain_file][1];
                the_place = place[domain_file][0];
                if (member_array(file, all_place) != -1)
                        return the_place;
        }

        if (! undefinedp(region_names[domain_file]))
                return region_names[domain_file];

        return "未知區域";
}

mapping dict = ([
        "axe"           :"斧",
        "bow"           :"弓",
        "sword"         :"劍",
        "blade"         :"刀",
        "club"          :"棍",
        "dagger"        :"匕首",
        "fork"          :"叉",
        "hammer"        :"錘",
        "staff"         :"杖",
        "throwing"      :"暗器",
        "whip"          :"鞭",
        "xsword"        :"簫",
        "head"          :"頭盔",
        "neck"          :"項鏈",
        "cloth"         :"衣服",
        "charm"         :"護身符",
        "rings"         :"戒指",
        "armor"         :"護甲",
        "surcoat"       :"披風",
        "waist"         :"腰帶",
        "wrists"        :"護腕",
        "shield"        :"盾甲",
        "hands"         :"鐵掌",
        "boots"         :"靴子",
        "finger"        :"指套",
        //"0"             :"粗制",
        "0"             :HIC"普通",
        "1"             :HIC"普通",
        "2"             :HIC"優良",
        "3"             :HIM"珍稀",
        "4"             :HIM"史詩",
        "5"             :HIY"傳說",
        "6"             :HIY"神器",
]);

string status_chinese(int status)
{
        if( status == 0 ) return HIK "劣質的";
        else if( status == 1 ) return HIK "劣質的";
        else if( status == 2 ) return HIB "普通的";
        else if( status == 3 ) return HIR "精致的";
        else if( status == 4 ) return HIM "卓越的";
        else if( status == 5 ) return HIY "無暇的";
        else if( status == 6 ) return HIY "完美的";
        else return HIY "神話的";
}

string to_chinese(string str)
{
        if (! undefinedp(dict[str]))
                return dict[str];
        else
                return str;
}

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj;
        object env;
        int result;
        string objid, where;

        if (! arg) result = look_room(me, environment(me), 0);
        else
        {
                if (sscanf(arg, "%s of %s", objid, where) == 2)
                {
                        if (where == "here")
                                obj = present(objid, environment(me));
                        else
                        if (where == "me")
                                obj = present(objid, me);
                        else
                        {
                                env = present(where, environment(me));
                                if (! objectp(env))
                                        return notify_fail("你要看哪裡的東西？\n");
                                obj = present(objid, env);
                                if (env->is_character() && env != me)
                                {
                                        if (! objectp(obj) ||
                                            !query("equipped", obj) &&
                                            query_temp("handing", env) != obj )
                                                return notify_fail("這人好像並沒有漏出來你想看的東西啊。\n");
                                        if( query("env/invisible_item", env) )
                                                return notify_fail("這人警惕性很高，好像並不想讓你看任何東西的屬性。\n");
                                        message("vision", me->name() + "盯著你的" + obj->name() +
                                                "看了一會兒，不知道在打什麼主意。\n", env);
                                        message("vision", me->name() + "盯著" + env->name() + "的" +
                                                obj->name() + "看了一會兒，不知道在打什麼主意。\n",
                                                environment(me), ({ me, env }));
                                }
                        }

                        if (! obj)
                                return notify_fail("那裡沒有這樣東西。\n");
                }

                if( obj || (obj = present(arg, environment(me))) || (obj = present(arg, me)) )
                {
                        if( obj->is_character() && ! obj->is_corpse()) result = look_living(me, obj);
                        else result = look_item(me, obj);
                } else result = look_room_item(me, arg);
        }

        return result;
}

int look_room(object me, object env, int brief)
{
        int i;
        object room;
        mapping exits;
        string str, ext, *dirs;

        if( !env ) {
                tell_object(me, "你的四周灰蒙蒙地一片，什麼也沒有。\n");
                return 1;
        }

        if( !brief )
        {
                str = sprintf( HIC + "%s" + NOR + "%s\n    %s%s" + NOR,
                        env->short(),
                        wizardp(me)?"-"+file_name(env)+sprintf("-(%d,%d,%d)",query("coor/x", env),
                        query("coor/y", env),query("coor/z", env)):
                                     " - (你目前在" + HIY + locate(base_name(env)) + NOR + ")",
                        env->long(),
                        query("outdoors", env)?NATURE_D->outdoor_room_description():"");
        } else
        {
                str = sprintf( HIC + "%s" + NOR + "%s\n" + NOR,
                        env->short(),
                        wizardp(me)?"-"+file_name(env)+sprintf("-(%d,%d,%d)",query("coor/x", env),
                        query("coor/y", env),query("coor/z", env)):"");
        }

        ext = "";
        if( mapp(exits=query("exits", env)) )
        {
                dirs = keys(exits);
                for(i=0; i<sizeof(dirs); i++)
                        if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
                                dirs[i] = 0;
                dirs -= ({ 0 });
                if (sizeof(dirs) == 0)
                        ext = "    這裡沒有任何明顯的出路。\n";
                else if (sizeof(dirs) == 1)
                        ext = "    這裡唯一的出口是 " + HIY +
                              dirs[0] + NOR + "。\n";
                else
                        ext = sprintf("    這裡明顯的出口是 " + HIY "%s" + NOR + " 和 " + HIY + "%s" + NOR + "。\n",
                              implode(dirs[0..sizeof(dirs)-2], NOR+"、"+HIY), dirs[sizeof(dirs)-1]);
        }

        if (! brief || (intp(brief) && brief > 2 && brief < 4))
                str += ext;

        if( !query_temp("tomud", me))//byLonely
                str += look_all_inventory_of_room(me, env, RETURN_RESULT);
        else
        {
                info(me, env); //By JackyBoy@XAJH 2001/5/6
                str +=CLEAN0+ look_all_inventory_of_room(me, env, RETURN_RESULT);
        }

        if (intp(brief) && brief >= 4)
                str += ext;

        tell_object(me, str);

        // 以下部分為顯示地圖
        if( query("env/show_map", me) && !me->is_fighting() )
        {
                if( mapp(exits=query("exits", env)) )
                {
                        dirs = keys(exits);
                        for(i=0; i<sizeof(dirs); i++)
                                if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED)
                                        dirs[i] = 0;
                        dirs -= ({ 0 });
                        if (sizeof(dirs) != 0)
                        {
                        if( query("env/show_map", me) == 2 )
                        write(FRELINE(8, 40));
                        else write(ESC+"[r"+TOBOT(50));
                        write(SAVEC);

                        write(SETDISPLAY(7, 0) + DELLINE);
                        write(SETDISPLAY(1, 0) + DELLINE);
                        write(SETDISPLAY(2, 0) + DELLINE);
                        write(SETDISPLAY(3, 0) + DELLINE);
                        write(SETDISPLAY(4, 0) + DELLINE);
                        write(SETDISPLAY(5, 0) + DELLINE);
                        write(SETDISPLAY(6, 0) + DELLINE);

                        write(SETDISPLAY(4, 70) + HIR + filter_color(query("short", env)) + NOR);
                        for (i=0; i<sizeof(dirs); i++)
                        switch(dirs[i])
                        {
                        case "north":
                                write(SETDISPLAY(3, 72) + "│");
                                room = load_object(exits["north"]);
                                write(SETDISPLAY(2, 70) + filter_color(query("short", room)));
                                break;
                        case "up":
                                write(SETDISPLAY(3, 72) + "│");
                                room = load_object(exits["up"]);
                                write(SETDISPLAY(2, 70) + filter_color(query("short", room)));
                                break;
                        case "down":
                                write(SETDISPLAY(5, 72) + "│");
                                room = load_object(exits["down"]);
                                write(SETDISPLAY(6, 70) + filter_color(query("short", room)));
                                break;
                        case "south":
                                write(SETDISPLAY(5, 72) + "│");
                                room = load_object(exits["south"]);
                                write(SETDISPLAY(6, 70) + filter_color(query("short", room)));
                                break;
                        case "east":
                                room = load_object(exits["east"]);
                                write(SETDISPLAY(4, 80) + filter_color(query("short", room)));
                                write(SETDISPLAY(4, 78) + "─");
                                break;
                        case "west":
                                room = load_object(exits["west"]);
                                write(SETDISPLAY(4, 60) + filter_color(query("short", room)));
                                write(SETDISPLAY(4, 68) + "─");
                                break;
                        case "westup":
                                room = load_object(exits["westup"]);
                                write(SETDISPLAY(4, 60) + filter_color(query("short", room)));
                                write(SETDISPLAY(4, 68) + "←");
                                break;
                        case "eastup":
                                room = load_object(exits["eastup"]);
                                write(SETDISPLAY(4, 80) + filter_color(query("short", room)));
                                write(SETDISPLAY(4, 78) + "→");
                                break;
                        case "northup":
                                write(SETDISPLAY(3, 72) + "↑");
                                room = load_object(exits["northup"]);
                                write(SETDISPLAY(2, 70) + filter_color(query("short", room)));
                                break;
                        case "southup":
                                write(SETDISPLAY(5, 72) + "↓");
                                room = load_object(exits["southup"]);
                                write(SETDISPLAY(6, 70) + filter_color(query("short", room)));
                                break;
                         case "southdown":
                                write(SETDISPLAY(5, 72) + " ↑ ");
                                room = load_object(exits["southdown"]);
                                write(SETDISPLAY(6, 70) + filter_color(query("short", room)));
                                break;
                        case "northdown":
                                write(SETDISPLAY(3, 72) + " ↓ ");
                                room = load_object(exits["northdown"]);
                                write(SETDISPLAY(2, 70) + filter_color(query("short", room)));
                                break;
                        case "eastdown":
                                room = load_object(exits["eastdown"]);
                                write(SETDISPLAY(4, 80) + filter_color(query("short", room)));
                                write(SETDISPLAY(4, 78) + "←");
                                break;
                        case "westdown":
                                room = load_object(exits["westdown"]);
                                write(SETDISPLAY(4, 60) + filter_color(query("short", room)));
                                write(SETDISPLAY(4, 68) + "→");
                                break;
                        case "northwest":
                                write(SETDISPLAY(3, 68) + "＼");
                                room = load_object(exits["northwest"]);
                                write(SETDISPLAY(2, 60) + filter_color(query("short", room)));
                                break;
                        case "southwest":
                                write(SETDISPLAY(5, 68) + "／");
                                room = load_object(exits["southwest"]);
                                write(SETDISPLAY(6, 60) + filter_color(query("short", room)));
                                break;
                        case "northeast":
                                write(SETDISPLAY(3, 76) + "／");
                                room = load_object(exits["northeast"]);
                                write(SETDISPLAY(2, 80) + filter_color(query("short", room)));
                                break;
                        case "southeast":
                                write(SETDISPLAY(5, 76) + "＼");
                                room = load_object(exits["southeast"]);
                                write(SETDISPLAY(6, 80) + filter_color(query("short", room)));
                                break;
                        }

                        write(SETDISPLAY(1, 58) + "□□□□□□□□□□□□□□□□");
                        write(SETDISPLAY(2, 58) + "□");
                        write(SETDISPLAY(3, 58) + "□");
                        write(SETDISPLAY(4, 58) + "□");
                        write(SETDISPLAY(5, 58) + "□");
                        write(SETDISPLAY(6, 58) + "□");
                        write(SETDISPLAY(7, 58) + "□□□□□□□□□□□□□□□□");
                        write(SETDISPLAY(2, 88) + "□");
                        write(SETDISPLAY(3, 88) + "□");
                        write(SETDISPLAY(4, 88) + "□");
                        write(SETDISPLAY(5, 88) + "□");
                        write(SETDISPLAY(6, 88) + "□");

                        write(REST);
                        }
                write(TOBOT(50));
                }
        }

        //MYGIFT_D->check_mygift(me, "newbie_mygift/look");   
        return 1;
}

string desc_of_objects(object *obs)
{
        int i;

        string  str;
        mapping count;
        mapping unit;
        string  short_name;
        string  *dk;

        if (obs && sizeof(obs) > 0)
        {
                str = "";
                count   = ([]);
                unit    = ([]);

                for (i = 0; i < sizeof(obs); i++)
                {
                        short_name = obs[i]->short();
                        if (undefinedp(count[short_name]))
                        {
                                count += ([ short_name : 1 ]);
                                unit += ([ short_name : query("unit", obs[i]) ]);
                        }
                        else
                                count[short_name] += 1;
                }

                dk = sort_array(keys(count), 1);
                for (i = 0; i < sizeof(dk); i++)
                {
                        str += "  ";
                        if (count[dk[i]] > 1)
                                str += chinese_number(count[dk[i]]) + unit[dk[i]];
                        str += dk[i] + "\n";
                }
                return str;
        }

        return "";
}

string look_all_inventory_of_room(object me, object env, int ret_str)
{
        object *inv;
        object *obs;
        object ob;
        string  str;

        if (! env || ! me) return "";

        str = "";

        inv = all_inventory(env);
        if (! sizeof(inv)) return str;

        if( query_temp("tomud", me) )
        {
                foreach(ob in inv)
                if (ob != me && me->visible(ob))
                        str += ADD0(ob); //By JackyBoy@XAJH 2001/5/6
        }

        if( !query("env/brief", me) || (intp(query("env/brief", me)) &&
            query("env/brief", me)>1) )
        {
                obs = filter_array(inv, (: $(me) != $1 && userp($1) && $(me)->visible($1) :));
                str += desc_of_objects(obs);

                obs = filter_array(inv, (: $(me) != $1 && ! userp($1) && $1->is_character() &&
                                           $(me)->visible($1) :));
                str += desc_of_objects(obs);

                obs = filter_array(inv, (: ! $1->is_character() :), me);
                str += desc_of_objects(obs);
        }
        if (! ret_str)
                tell_object(me, str);

        return str;
}

int look_item(object me, object obj)
{
        object hob;
        mixed *inv;
        mapping count;
        mapping equiped;
        mapping unit;
        mapping insert;
        string ins;
        string short_name;

        string str, desc;
        string *dk;
        mapping enchase_prop, applied_prop = ([]);
        mapping in_data;
        string in_desc = "";
        string *ikey;
        string *apply, *apply1, *apply2, *apply3;
        int i, f;
        int n, t;

        count   = ([]);
        unit    = ([]);
        equiped = ([]);
        enchase_prop = ([]);
        applied_prop = ([]);
        apply = ({});
        apply1 = ({});
        apply2 = ({});
        apply3 = ({});

        str = obj->long();
        str += "\n";
        if( query("no_identify", obj) )
        {
                str += HIW "----------------------------------------\n" NOR;
                str += HIK "此物品未鑒定\n" NOR;
                str += HIW "----------------------------------------\n" NOR;
        } else
        if (mapp(query("weapon_prop", obj)) ||
            mapp(query("armor_prop", obj)) )
        {
                if( query("skill_type", obj) ) {
                        applied_prop = copy(query("weapon_prop", obj));
                        str += HIW "裝備類型 : 武器 - " + to_chinese(query("skill_type", obj)) +"\n" NOR;
                }
                else if( query("armor_type", obj) ) {
                        applied_prop = copy(query("armor_prop", obj));
                        if( query("armor_type", obj) == "rings" || query("armor_type", obj) == "neck" ||
                            query("armor_type", obj) == "charm" )
                                str += HIW "裝備類型 : 飾品 - " + to_chinese(query("armor_type", obj)) +"\n" NOR;
                        else if( query("armor_type", obj) == "hands" || query("armor_type", obj) == "finger" )
                                str += HIW "裝備類型 : 空手武器 - " + to_chinese(query("armor_type", obj)) +"\n" NOR;
                        else
                                str += HIW "裝備類型 : 防具 - " + to_chinese(query("armor_type", obj)) +"\n" NOR;
                }
                
                str += HIW "裝備品級 : " + status_chinese(query("status", obj)) +"\n" NOR;
                //str += HIW "稀 有 度 : " + to_chinese(to_string(query("quality_level", obj))) +"\n" NOR;
                str += HIW "綁定類型 : ";
                if( intp(t=query("bindable", obj))){
                        if( t == 1 )      str += "裝備後綁定";
                        else if( t == 2 ) str += "拾取後幫定";
                        else if( t == 3 ) str += "直接掉落綁定";
                        else              str += "無綁定類型";
                }
                if( query("bind_owner", obj) )
                        str += HIM "（已綁定）\n" NOR;
                else
                        str += HIK "（無綁定）\n" NOR;

                if( query("require/level", obj) ) str += HIW "裝備要求 : 等級 Lv." + query("require/level", obj) + "\n" NOR;
                if( query("require/int", obj) ) str += HIW "裝備要求 : 靈性 " + query("require/int", obj) + "\n" NOR;
                if( query("require/str", obj) ) str += HIW "裝備要求 : 臂力 " + query("require/str", obj) + "\n" NOR;
                if( query("require/con", obj) ) str += HIW "裝備要求 : 根骨 " + query("require/con", obj) + "\n" NOR;
                if( query("require/dex", obj) ) str += HIW "裝備要求 : 敏捷 " + query("require/dex", obj) + "\n" NOR;

                t = query("max_consistence", obj);
                if( !t ) t = 100;
                str += HIW "耐 久 值 : " + query("consistence", obj)+"/"+ t + "\n" NOR;
                str += "\n";
                insert=query("insert", obj);
                if( mapp(insert) && sizeof(insert) )
                {
                        ikey = keys(insert);
                        n = sizeof(ikey);
                        str += sprintf(HIW "鑲嵌寶石 : %d/%d\n" NOR, (int)query("enchase/used", obj), (int)query("enchase/flute", obj));
                        for( i = 0; i < n; i++ )
                        {
                                ins = ikey[i];
                                if( !obj->is_item_make() )
                                {
                                        in_data = copy(insert[ins]["apply_prop"]);
                                        in_desc = "";
                                        foreach( string key in keys(in_data) )
                                                in_desc += HIK + filter_color(EQUIPMENT_D->chinese(key, in_data[key]),1) + NOR+",";

                                        in_desc = in_desc[0..<2];
                                }
                                str += sprintf(HIK "⊙" NOR "%s(%s)<%s>\n" NOR,
                                        insert[ins]["name"], insert[ins]["id"], obj->is_item_make() ? "":in_desc);
                        }
                        str += "\n";
                }
                /*
                if (mapp(query("enchase/apply_prop", obj))) {
                        enchase_prop = copy(query("enchase/apply_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                if (! sizeof(applied_prop) || undefinedp(applied_prop[apply3[i]]))
                                        applied_prop[apply3[i]] = enchase_prop[apply3[i]];
                                else
                                        applied_prop[apply3[i]] += enchase_prop[apply3[i]];
                        }
                }
                if (mapp(query("reform/apply_prop", obj))) {
                        enchase_prop = copy(query("reform/apply_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                if (! sizeof(applied_prop) || undefinedp(applied_prop[apply3[i]]))
                                        applied_prop[apply3[i]] = enchase_prop[apply3[i]];
                                else
                                        applied_prop[apply3[i]] += enchase_prop[apply3[i]];
                        }
                }
                */
                if (mapp(applied_prop) && sizeof(applied_prop) > 0) {
                        apply = keys(applied_prop);
                        for (i = 0; i<sizeof(apply); i++)
                        {
                                f = applied_prop[apply[i]];
                                if( !f ) continue;
                                str += HBCYN "裝備效果" NOR " : ";
                                desc = EQUIPMENT_D->chinese(apply[i], f);
                                desc = HIC + desc + NOR;
                                str += desc + "\n";
                        }
                }
                if (mapp(query("enchase/apply_prop", obj))) {
                        enchase_prop = copy(query("enchase/apply_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                f = enchase_prop[apply3[i]];
                                if( !f ) continue;
                                str += HBBLU "裝備效果" NOR " : ";
                                desc = EQUIPMENT_D->chinese(apply3[i], f);
                                desc = HIB + desc + NOR;
                                str += desc + "\n";

                        }
                }
                if (mapp(query("reform/apply_prop", obj))) {
                        enchase_prop = copy(query("reform/apply_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                f = enchase_prop[apply3[i]];
                                if( !f ) continue;
                                str += HBMAG "裝備效果" NOR " : ";
                                desc = EQUIPMENT_D->chinese(apply3[i], f);
                                desc = HIM + desc + NOR;
                                str += desc + "\n";

                        }
                }
                if (mapp(query("enchase/rune_prop", obj))) { // 符文物語
                        enchase_prop = copy(query("enchase/rune_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                f = enchase_prop[apply3[i]];
                                if( !f ) continue;
                                str += HBRED "裝備效果" NOR " : ";
                                desc = EQUIPMENT_D->chinese(apply3[i], f);
                                desc = HIR + desc + NOR;
                                str += desc + "\n";

                        }
                }
                if (mapp(query("qianghua/apply_prop", obj))) {
                        enchase_prop = copy(query("qianghua/apply_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                f = enchase_prop[apply3[i]];
                                if( !f ) continue;
                                str += HBYEL "裝備效果" NOR " : ";
                                desc = EQUIPMENT_D->chinese(apply3[i], f);
                                desc = HIY + desc + NOR;
                                str += desc + "\n";

                        }
                }
                if (mapp(query("enchase/mod_prop", obj))) {
                        enchase_prop = copy(query("enchase/mod_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                f = enchase_prop[apply3[i]];
                                if( !f ) continue;
                                str += HBGRN "套裝效果" NOR " : ";
                                desc = EQUIPMENT_D->chinese(apply3[i], f);
                                desc = (query_temp("mod_active", obj) ? HIG : HIK) + desc + NOR;
                                str += desc + "\n";

                        }
                }
                str += "\n";
                if (stringp(query("mod_level", obj)))
                        // str = column_string(filter_color(str, 1), MODULE_D->module_stats(obj, me), 64);
                        str = column_string(sort_string(str, 56, 0), MODULE_D->module_stats(obj, me), 60);
        }

        while (mapp(query_temp("daub", obj)))
        {
                if( !query_temp("daub/poison/remain", obj) )
                        // no poison remain now
                        break;

                if( query_temp("daub/poison/id", obj) == query("id", me) )
                {
                        str += HIG "你發現這上面還有你煉制的" +
                               query_temp("daub/poison/name", obj)+
                               HIG "呢。\n" NOR;
                        break;
                }

                if( query_temp("daub/who_id", obj) == query("id", me) )
                {
                        str += HIG "這上面還有你親手布下的" +
                               query_temp("daub/poison/name", obj)+
                               HIG "呢。\n" NOR;
                        break;
                }

                if (random(4) && random((int)me->query_skill("poison", 1)) < 30)
                        // nothing was worked out
                        break;

                str += HIG "忽然間你發現上面似乎泛著一些奇異熒光";
                if (me->query_skill("poison", 1) >= 120)
                {
                        str+="，可能是"+query_temp("daub/poison/name", obj);
                }

                str += "。\n" NOR;
                break;
        }

        /*if (query("consistence", obj))
                str += sprintf("耐久值：" WHT "%d\n" NOR, query("consistence", obj));*/

        inv = all_inventory(obj);
        if (! sizeof(inv))
        {
                message("vision", str, me);
                return 1;
        }

        if (obj->is_corpse())
        {
                if( objectp(hob=query_temp("handing", obj)) )
                {
                        if (hob->query_amount())
                                str += "手中還死死握著一" + query("base_unit", hob) +
                                       hob->name() + "，";
                        else
                                str += "手中還死死握著一" + query("unit", hob) +
                                       hob->name() + "，";
                        inv -= ({ hob });
                        if (! sizeof(inv))
                                str += "沒有什麼其他遺物了。\n";
                        else
                                str += "裡面的遺物有：\n";
                } else
                        str += "裡面的遺物有：\n";
        } else
                str += "裡面有：\n";

        for (i = 0; i < sizeof(inv); i++)
        {
                short_name = inv[i]->short();
                if (undefinedp(count[short_name]))
                {
                        count += ([ short_name : 1 ]);
                        unit += ([ short_name : query("unit", inv[i]) ]);
                }
                else
                        count[short_name] += 1;

                if( query("equipped", inv[i]) )
                        equiped[short_name] = 1;
        }

        dk = keys(count);
        dk = sort_array(dk, 1);
        for (i = 0; i < sizeof(dk); i++)
        {
                if (equiped[dk[i]])
                {
                        if( dk[i] == query_temp("secondary_weapon", obj) )
                                str += HIM "  □" NOR;
                        else
                                str += HIC "  □" NOR;
                }
                else
                        str += "    ";

                if (count[dk[i]] > 1)
                        str += chinese_number(count[dk[i]]) + unit[dk[i]];
                str += dk[i] + "\n";
        }

        if (strlen(str) > 4096)
                me->start_more(str);
        else
                message("vision", str, me);
        return 1;
}

string look_equiped(object me, object obj, string pro)
{
        mixed *inv;
        string str;
        string subs;
        object hob;
        int i;
        int n;

        inv = all_inventory(obj);
        n = 0;

        str = "";
        subs = "";
        for (i = 0; i < sizeof(inv); i++)
        {
                switch(query("equipped", inv[i]) )
                {
                case "wielded":
                        n++;
                        if( inv[i] == query_temp("secondary_weapon", obj) )
                                subs = HIM "  □" NOR + inv[i]->short() + "\n" + subs;
                        else
                                subs = HIC "  □" NOR + inv[i]->short() + "\n" + subs;
                        break;

                case "worn":
                        n++;
                        subs += HIC "  □" NOR + inv[i]->short() + "\n";
                        break;

                default:
                        break;
                }
        }

        if (n)
                str += pro + "裝備著：\n" + subs;

        if( objectp(hob=query_temp("handing", obj)) &&
            (me == obj || obj->query_weight() > 200))
        {
                int mad;

                // dress nothing but handing a cloth !
                mad = (! objectp(query_temp("armor/cloth", obj)) &&
                       query("armor_type", hob) == "cloth");

                str = pro + "手中" + (mad ? "卻" : "" ) + "握著一" +
                      (hob->query_amount() ? query("base_unit", hob)
                                           : query("unit", hob)) +
                      hob->name() +
                      (mad ? "，瘋了，一定是瘋了！\n" : "。\n") + str;
        }

        if (playerp(obj) &&
            ! objectp(query_temp("armor/cloth", obj)))
        {
                str = pro + "身上沒有穿衣服啊！\n" + str;
        }

        return str;
}

string description(object obj)
{
        if (playerp(obj))
        {
            int per;
            int age;
            per = obj->query_per();
            age=query("age", obj);
            if( query("special_skill/youth", obj) ) age = 14;
            if ((string)query("gender", obj) == "男性" || (string)query("gender", obj) == "無性")
            {
                    if (per >= 30) return "長得宛如玉樹臨風，風流倜儻，顧盼之間，神採飛揚。真正是人中龍鳳！\n";
                    if (per >= 26) return "英俊瀟洒，氣宇軒昂，風度翩翩，面目俊朗，貌似潘安。\n";
                    if (per >= 22) return "相貌英俊，儀表堂堂。骨格清奇，豐姿非俗。\n";
                    if (per >= 18) return "五官端正。\n";
                    if (per >= 15) return "相貌平平。沒什麼好看的。\n";
                                   return "長得... 有點對不住別人。\n";
            } else
            {
                    if (per >= 30) return "有傾國傾城之貌，容色麗鬱，嬌艷絕倫，堪稱人間仙子！\n長發如雲，肌膚勝雪，風華絕代，不知傾倒了多少英雄豪傑。\n";
                    if (per >= 28) return "清麗絕俗，風姿動人。有沉魚落雁之容，避月羞花之貌！\n俏臉生春，妙目含情，顧盼神飛，輕輕一笑，不覺讓人怦然心動。\n";
                    if (per >= 26) return "膚如凝脂，眉目如畫，風情萬種，楚楚動人。當真是我見猶憐！\n";
                    if (per >= 24) return "容色秀麗，面帶暈紅，眼含秋波。舉手投足之間，確有一番風韻。\n";
                    if (per >= 21) return "氣質高雅，面目姣好，雖算不上絕世佳人，也頗有幾份姿色。\n";
                    if (per >= 18) return "相貌平平，還看得過去。\n";
                    if (per >= 15) return "的相貌嘛... 馬馬虎虎吧。\n";
                                   return "長得和無鹽有點相似耶。\n";
            }
        } else
        if( !query("can_speak", obj) && living(obj) )
        {
                if( !query_temp("owner", obj) )
                        return "是一只未被馴服的畜生，眼光裡滿是戒心和敵意。\n";
                else
                        return "是一只被"+query_temp("owner_name", obj)+
                               "馴服的畜生，一副很溫馴的樣子。\n";
        }

        return "";
}

int look_living(object me, object obj)
{
        int per;
        int age;
        string str="", pro, desc,icon;
        mapping my_fam, fam;
        int me_shen, obj_shen;
        mixed tmp;

        if( (tmp=query("icon", obj)) )
        {
                if( intp(tmp) )
                {
                        icon = sprintf("%d",tmp);
                        str=L_ICON(icon);
                }
                else if( stringp(tmp) )
                {
                        icon = tmp;
                        str=L_ICON(icon);
                }
        }
        obj_shen=query("shen", obj);
        per = obj->query_per();
        age=query("age", obj);
        pro = (obj==me) ? gender_self(query("gender", obj)) : gender_pronoun(query("gender", obj));

        me_shen=query("shen", me);
        if (me != obj)
        {
                message("vision", me->name() + "正盯著你看，不知道在打什麼主意。\n", obj);
                message("vision", me->name() + "盯著" + obj->name() +
                        "看了一會兒，不知道在打什麼主意。\n",
                        environment(me), ({ me, obj }));
        }

        str += obj->long();
        if (me != obj && objectp(query_temp("is_riding", obj)))
                str += sprintf("%s正騎在%s上，低頭看著你。\n", pro, query_temp("is_riding", obj)->name());

        // if (me != obj && objectp(query_temp("is_changing", obj)))
        if (objectp(query_temp("is_changing", obj)))
        {
                if( query_temp("armor/beast", obj) )
                        str += sprintf("%s全身被鎧化的魔幻獸(%s)細胞組織保護著，象全身戴著金色盔甲似的。\n", pro,
                                query_temp("is_changing", obj)->name());
                else
                        str += sprintf("%s的右手臂上留有魔幻獸(%s)依附的痕跡。\n", pro,
                                query_temp("is_changing", obj)->name());
        }

        if (obj->is_character() &&
            query("can_speak", obj) )
        {
                int charlevel;
                charlevel=query("level", obj)?query("level", obj):1;
                str += pro + "是一位" + chinese_number(charlevel) + "級的" + query("gender", obj) + "人士。\n";
                // 是人物角色
                if (age >= 25 && query("special_skill/youth", obj))
                        str += pro + "看不出年紀的大小，好像只有二十多歲。\n";
                else
                {
                        if (age >= 200)
                                str += pro + "看起來年紀很大了，難以估計。\n";
                        else
                        if (age < 10)
                                str += pro + "看起來年紀尚幼。\n";
                        else
                                str += pro + "看起來有" + chinese_number(age / 10 * 10) +
                                       "多歲。\n";
                }
                str += sprintf("%s的武功看來", pro);
                str += gettof(me, obj);
                str += sprintf("，");
                str += sprintf("出手似乎");
                str += getdam(me, obj);
                str += sprintf("。\n");
        }

        desc = description(obj);
        if (desc && desc != "")
                str += pro + desc;

        //check about wife and husband
        if( query("id", obj) == query("couple/id", me) )
        {
                // 夫妻關系
                if( query("gender", me) == "女性" )
                        str += sprintf("%s就是你的夫君。\n", pro);
                else
                        str += sprintf("%s就是你的妻子。\n", pro);
        } else
        if (obj->is_brother(me))
        {
                // 兄弟
                if( query("gender", obj) == "女性" )
                {
                        if( query("mud_age", obj) > query("mud_age", me) )
                                str += sprintf("%s是你的義姐。\n", pro);
                        else
                                str += sprintf("%s是你的結義妹子。\n", pro);
                } else
                {
                        if (query("mud_age", obj) > query("mud_age", me))
                                str += sprintf("%s是你的結義兄長。\n", pro);
                        else
                                str += sprintf("%s是你的義弟。\n", pro);
                }
        } else
        if (obj != me && query("league", obj) &&
            query("league/league_name", obj) == query("league/league_name", me) )
        {
                str += sprintf("%s和你均是%s的同盟義士。\n", pro,
                               query("league/league_name", obj));
        }

        if (obj != me && query("bunch", obj) && stringp(query("bunch/bunch_name", obj)) &&
            query("bunch/bunch_name", obj) == query("bunch/bunch_name", me) )
        {
                str += sprintf("%s和你均是%s的幫友，%s在幫中的職位為%s，", pro,
                               query("bunch/bunch_name", obj),pro,
                               stringp(query("bunch/title", obj)) ? query("bunch/title", obj) : "幫眾");
                if( query("bunch/level", obj)>query("bunch/level", me) )
                        str += "地位比你高。\n";
                else
                if( query("bunch/level", obj) == query("bunch/level", me) )
                        str += "地位和你相當。\n";
                else
                        str += "地位比你低。\n";
        } else
        if (obj != me && query("bunch", obj) && stringp(query("bunch/bunch_name", obj)) &&
            query("bunch/bunch_name", obj) != query("bunch/bunch_name", me) )
        {
                str += sprintf("%s是江湖上%s的%s。\n", pro,
                               query("bunch/bunch_name", obj),
                               stringp(query("bunch/title", obj)) ? query("bunch/title", obj) : "幫眾");
        }

        // If we both has family, check if we have any relations.
        if (obj != me &&
            mapp(fam=query("family", obj)) &&
            mapp(my_fam=query("family", me)) &&
            fam["family_name"] == my_fam["family_name"])
        {

                if (fam["generation"] == my_fam["generation"])
                {

                        if( query("gender", obj) == "男性" ||
                                query("gender", obj) == "無性" )
                                str += sprintf( pro + "是你的%s%s。\n",
                                        my_fam["master_id"] == fam["master_id"]? "": "同門",
                                        my_fam["enter_time"] > fam["enter_time"] ? "師兄": "師弟");
                        else
                                str += sprintf( pro + "是你的%s%s。\n",
                                        my_fam["master_id"] == fam["master_id"]? "": "同門",
                                        my_fam["enter_time"] > fam["enter_time"] ? "師姐": "師妹");
                } else
                if (fam["generation"] < my_fam["generation"])
                {
                        if( my_fam["master_id"] == query("id", obj) )
                                str += pro + "是你的師父。\n";
                        else
                        if (my_fam["generation"] - fam["generation"] > 1)
                                str += pro + "是你的同門長輩。\n";
                        else
                        if (fam["enter_time"] < my_fam["enter_time"])
                                str += pro + "是你的師伯。\n";
                        else
                                str += pro + "是你的師叔。\n";
                } else
                {
                        if (fam["generation"] - my_fam["generation"] > 1)
                                str += pro + "是你的同門晚輩。\n";
                        else
                        if( fam["master_id"] == query("id", me) )
                                str += pro + "是你的弟子。\n";
                        else
                                str += pro + "是你的師侄。\n";
                }
        }

        if (obj->is_chatter())
        {
                message("vision", str, me);
                return 1;
        }

        if (stringp(query_temp("eff_status_msg", obj)))
        {
                str+=query_temp("eff_status_msg", obj)+"\n";
        } else
        if( query("max_qi", obj) )
                str += pro + COMBAT_D->eff_status_msg((int)query("eff_qi", obj)* 100 / (int)query("max_qi", obj)) + "\n";

        if( query_temp("daub/poison/remain", obj) &&
            (me == obj || random((int)me->query_skill("poison", 1)) > 80))
        {
                str += pro + HIG "身上現在" + (me == obj ? "" : "似乎") +
                       "淬了" + (me == obj ? query_temp("daub/poison/name", obj) : "毒") +
                       NOR "。\n";
        }

        str += look_equiped(me, obj, pro);
        message("vision", str, me);

        if (obj != me && living(obj) &&
            ! me->is_brother(obj) &&
            query("couple/id", me) != query("id", obj) &&
            (((me_shen < 0) && (obj_shen > 0)) ||
             ((me_shen > 0) && (obj_shen < 0))) &&
            (((me_shen-obj_shen)>(query("max_neili", obj)*20)) ||
             ((obj_shen-me_shen)>(query("max_neili", obj)*20))) )
        {
                tell_object(me, obj->name() + "突然轉過頭來瞪你一眼。\n");
                /*
                if( query("age", obj)>15 && query("age", me)>15 )
                   if (! wizardp(obj) && ! wizardp(me))
                        COMBAT_D->auto_fight(obj, me, "berserk");
                */
        }

        return 1;
}

int look_room_item(object me, string arg)
{
        object env;
        mapping item, exits;

        if (! objectp(env = environment(me)))
                return notify_fail("這裡只有灰蒙蒙地一片，什麼也沒有。\n");
        if( mapp(item=query("item_desc", env)) && !undefinedp(item[arg]) )
        {
                if (stringp(item[arg]))
                        tell_object(me, item[arg]);
                else
                if(functionp(item[arg]))
                        tell_object(me, (string)(*item[arg])(me));

                return 1;
        }
        if( mapp(exits=query("exits", env)) && !undefinedp(exits[arg]) )
        {
                if (objectp(env = find_object(exits[arg])))
                        look_room(me, env, 0);
                else
                {
                        call_other(exits[arg], "???");
                        if( !find_object(exits[arg]) ) return notify_fail("那邊是空間裂縫，無法進入或觀察。\n");
                        look_room(me, find_object(exits[arg]), 0);
                }
                return 1;
        }
        return notify_fail("你要看什麼？\n");
}

int help(object me)
{
        write(@HELP
指令格式: look [<物品>|<生物>|<方向>]

這個指令讓你查看你所在的環境、某件物品、生物、或是方向。如果
在look指令後面有參數，將先察看身上是否有該物品，如果沒有則察
看你所在的環境中是否有該物品或人物。如果你身上的物品和你所在
的環境有ID相同的物品，你可以指明look ??? of me/here 以指明你
想要察看自己身上的物品還是附近環境中的物品。同時，如果使用命
令 look ??? of <id> 可以看他人的裝備或是亮出來的物品。

HELP
);
        return 1;
}
