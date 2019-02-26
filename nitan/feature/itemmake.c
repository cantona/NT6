// itemmake.c 自制道具

#include <ansi.h>
#include <name.h>
#include <move.h>
#include <command.h>

inherit F_OBSAVE;
inherit F_NOCLONE;

int is_item_make() { return 1; }

#define LEVEL1          5
#define LEVEL2          10
#define LEVEL3          30
#define LEVEL4          100
#define LEVEL5          300
#define LEVEL6          1000
#define LEVEL7          3000
#define LEVEL8          10000
#define LEVEL9          25000
#define MAX_LEVEL       LEVEL9
#define ULTRA_LEVEL     (LEVEL9 + 1)

nosave int *levels = ({ LEVEL1, LEVEL2, LEVEL3, LEVEL4,
                        LEVEL5, LEVEL6, LEVEL7, LEVEL8,
                        LEVEL9 });

nosave int performing  = 0;
nosave int attack_lvl  = 0;
nosave int defense_lvl = 0;
nosave string *qianghua_level = ({
        HBRED"☆"NOR,
        HBRED"★"NOR,
        HBRED"★★"NOR,
        HBRED"★★★"NOR,
        HBRED"★★★★"NOR,
        HBRED"★★★★★"NOR,
        HBRED"★★★★★★"NOR,
        HBRED"★★★★★★★"NOR, 
        HBRED"★★★★★★★★"NOR, 
        HBRED"★★★★★★★★★"NOR, 
}); 

int is_stay_in_room() { return attack_lvl >= ULTRA_LEVEL; }
int is_ultimate()
{
        return attack_lvl >= ULTRA_LEVEL || query("ultimate/69") || 
               query("ultimate/87") || query("ultimate/105") || query("ultimate/121");
}

string chinese_s(mixed arg)
{
      if( !stringp(arg) )  return HIW "無";
      if( arg == "metal" ) return HIY "金";
      if( arg == "wood" )  return HIM "木";
      if( arg == "water" ) return HIB "水";
      if( arg == "fire" )  return HIR "火";
      if( arg == "earth" ) return HIG "土";
      if (arg == "cold")   return HIW "冰";
      if (arg == "fire")   return HIR "火";
      if (arg == "magic")  return HIY "魔";
      if (arg == "lighting")return HIM "電";
}

// 武器的主人ID - 通過文件的名字來判斷
string item_owner()
{
        string owner;
        if( sscanf(base_name(this_object()), ITEM_DIR "%*s/%s-%*s", owner) )
                return owner;

        return 0;
}

// 判斷該武器是否被當前某人所持有
int is_not_belong_me(object me)
{
        string user;

        user = query("user");
        if( !user || !sscanf(user, "%*s(" + query("id", me) + ")") )
                return 1;

        return 0;
}

// 武器裝備的等級
int weapon_level()
{
        mapping o;
        string *ks;
        mixed lvl;
        int i;

        lvl = 0;
        o = query("owner");
        if( mapp(o) ) {
                ks = keys(o);
                for (i = 0; i < sizeof(ks); i++)
                        lvl += o[ks[i]];
        }

        lvl /= 100;
        lvl = atoi(lvl);
        if( lvl > MAX_LEVEL ) lvl = MAX_LEVEL;

        if( lvl == MAX_LEVEL && query("magic/power") )
                // 具有魔法屬性
                lvl = ULTRA_LEVEL;
        return lvl;
}

// 防禦裝備的等級
int armor_level()
{
        // More to be added
        // 鍛造增加等級?
        return 0;
}

// 武器裝備的長描述
string weapon_long()
{
        string  n;
        mapping need;
        mapping c;
        int type;
        int k;
        int lvl;
        string tessera_name;
        string result = "";

        c = query("combat");
        n = query("unit") + name();
        if( !c )
                return "這" + n + "顯然還沒有飲過人血，上面純潔無暇。\n";
        k = c["MKS"] + c["PKS"];

        if( c["WPK_GOOD"] < k / 2 &&
            c["WPK_BAD"]  < k / 2 )
                type = 0;
        else
        if( c["WPK_GOOD"] > c["WPK_BAD"] * 2 )
                type = -1;
        else
                type = 1;

        if( c["MKS"] + c["PKS"] < 10 )
                return "這" + n + "看來已經用過人血開祭，上面隱現血痕。\n";

        attack_lvl = weapon_level();
        lvl = sizeof(levels);
        while (--lvl)
                if( attack_lvl >= levels[lvl] )
                        break;
        lvl++;
        
        switch (type)
        {
        case 1:
                if( attack_lvl >= ULTRA_LEVEL )
                        result = HIY "它看上去平平常常，沒有半點特殊，只是"
                                 "隱隱的讓人感到那不凡的氣質。\n" NOR;
                else
                if( attack_lvl >= MAX_LEVEL )
                        result = HIY "它看上去讓人發自內心無限崇敬，一股"
                               "皓然正氣悠然長存，頗具帝王風範，君臨\n"
                               "天下，威鎮諸路凶神惡煞、難道這就是傳説中才"
                               "會出現的諸神之" + name() + HIY "？\n" NOR;
                else
                if( attack_lvl >= LEVEL8 )
                        result = HIC "一眼望去，你覺得有無數的兇靈在瘋狂"
                               "亂舞，哭天搶地，悽烈之極，似乎要重返\n"
                               "人間。你忍不住要長歎一聲，昔日兇魔，也難逃死劫。\n" NOR;
                else
                if( attack_lvl >= LEVEL7 )
                        result = HIC "它上面附着着不知多少兇魂，無數邪派"
                               "兇魔斃命於下，一股哀氣猶然不散，讓你\n"
                               "忍不住打了個冷戰。\n" NOR;
                else
                if( attack_lvl >= LEVEL6 )
                        result = HIR "它看上去令人驚心動魄，這就是名動江湖的" + name() + HIR
                               "，多少凶煞就此斃命，成就人間正義。\n" NOR;
                else
                if( attack_lvl >= LEVEL5 )
                        result = HIR "它上面隱隱然透出一股血光，多年以來，許多"
                               "江湖上聞名一時的兇魔都成了" + name() + HIR "下的遊魂。\n" NOR;
                else
                if( attack_lvl >= LEVEL4 )
                        result = HIW "這就是江湖上著名的神兵之一：" + name() + HIW
                               "，窮兇極惡之徒見此物無不心馳神搖。\n" NOR;
                else
                if( attack_lvl >= LEVEL3 )
                        result = HIW "這" + n + HIW "有一股正氣散發出來，看來它下面兇魂不少。\n" NOR;
                else
                if( attack_lvl >= LEVEL2 )
                        result = RED "這" + n + RED "隱然透出一股正氣，"
                               "看來它殺了不少兇惡之徒。\n" NOR;
                else
                if( attack_lvl >= LEVEL1 )
                        result = RED "細觀之下，刃口有一絲血痕，想必是它殺人不少"
                               "，殷血於此吧！\n" NOR;
                else
                        result = CYN "看得出這" + n + CYN "曾經殺過不少兇惡之徒。\n" NOR;
                break;

        case -1:
                if( attack_lvl >= ULTRA_LEVEL )
                        result = HIR "它看上去平平常常，沒有半點特殊，但是"
                                 "不知為何卻總是讓人感到有些不安。\n" NOR;
                else
                if( attack_lvl >= MAX_LEVEL )
                        result = HIR "它看上去讓人打心底泛出陣陣寒意，隱"
                               "隱然上面似乎附着着無數冤魂，但是全然\n被這" + n + HIR
                               "上面的殺氣所制，難道這就是傳説中才會出現的邪神之" + name() + HIR
                               "？\n" NOR;
                else
                if( attack_lvl >= LEVEL8 )
                        result = HIC "一眼望去，你覺得有無數的冤魂向你撲"
                               "來，哭天搶地，悽烈之極，你忍不住打了\n"
                               "個寒戰，不敢再看第二眼。\n" NOR;
                else
                if( attack_lvl >= LEVEL7 )
                        result = HIC "它上面附着着不知多少冤魂，無數高手"
                               "飲恨於下，一股怨氣直衝霄漢，讓你忍不\n"
                               "住打了個冷戰。\n" NOR;
                else
                if( attack_lvl >= LEVEL6 )
                        result = HIW "它看上去令人驚心動魄，這就是名動江湖的" + name() + HIW
                               "，不知多少英雄就此飲恨。\n" NOR;
                else
                if( attack_lvl >= LEVEL5 )
                        result = HIW "它上面隱隱然透出一股血光，多年以來，許多"
                               "江湖上聞名一時的高手都成了" + name() + HIW "下的遊魂。\n" NOR;
                else
                if( attack_lvl >= LEVEL4 )
                        result = HIG "這就是江湖上著名的兇器之一：" + name() + HIG
                               "，誰曾想那麼多仁人義士飲恨於下。\n" NOR;
                else
                if( attack_lvl >= LEVEL3 )
                        result = HIG "這" + n + HIG "有一股戾氣散發出來，看來它下面遊魂不少。\n" NOR;
                else
                if( attack_lvl >= LEVEL2 )
                        result = RED "這" + n + RED "隱然透出一股戾氣，看來它殺了不少人。\n" NOR;
                else
                if( attack_lvl >= LEVEL1 )
                        result = RED "細觀之下，刃口有一絲血痕，想必是它殺人不少"
                               "，殷血於此吧！\n" NOR;
                else
                        result = CYN "看得出這" + n + CYN "曾經殺過不少俠義之士。\n" NOR;
                break;

        default:
                if( attack_lvl >= ULTRA_LEVEL )
                        result = HIC "它看上去平平常常，沒有半點特殊，只是一件"
                                 "平凡之極的兵器而已。\n" NOR;
                else
                if( attack_lvl >= MAX_LEVEL )
                        result = HIC "它安然暢意，似乎就要騰空而去，跳出"
                               "三界，不入五行。世間萬物，彷彿俱在它\n"
                               "霸氣所及之處。冤魂不舞、羣邪辟易，無不被這" + n + HIC
                               "上古神兵的霸氣所制。\n" NOR;
                else
                if( attack_lvl >= LEVEL8 )
                        result = HIM "一眼望去，你覺得有無數的遊魂向你撲"
                               "來，哭天搶地，悽烈之極，你頓時覺得它\n"
                               "沉重無比，幾乎拿捏不住。\n" NOR;
                else
                if( attack_lvl >= LEVEL7 )
                        result = HIM "它上面附着着不知多少遊魂，無數正邪"
                               "高手喪命於下，一股怨氣哀愁油然不盡，\n"
                               "讓你忍不住打了個冷戰。\n" NOR;
                else
                if( attack_lvl >= LEVEL6 )
                        result = HIR "它看上去令人驚心動魄，這就是名動江湖的" + name() + HIR
                               "，多少正邪高手都難逃此劫，墮入輪迴。\n" NOR;
                else
                if( attack_lvl >= LEVEL5 )
                        result = HIR "它上面隱隱然透出一股血光，多年以來，許多"
                               "江湖上聞名一時的高手都成了這" + n + HIR "下的遊魂。\n" NOR;
                else
                if( attack_lvl >= LEVEL4 )
                        result = HIW "這就是江湖上著名的利器之一：" + name() + HIW
                               "，誰能想到那麼多高手飲恨於下。\n" NOR;
                else
                if( attack_lvl >= LEVEL3 )
                        result = HIW "這" + n + HIW "有一股殺氣散發出來，看來它下面遊魂不少。\n" NOR;

                else
                if( attack_lvl >= LEVEL2 )
                        result = RED "這" + n + RED "隱然透出一股殺氣，看來它殺了不少人。\n" NOR;

                else
                if( attack_lvl >= LEVEL1 )
                        result = RED "細觀之下，刃口有一絲血痕，想必是它殺人不少"
                               "，殷血於此吧！\n" NOR;
                else
                        result = CYN "看得出這" + n + CYN "曾經殺過不少人。\n" NOR;
                break;
        }
        /*
        if( attack_lvl == ULTRA_LEVEL ) {
                if( stringp(tessera_name = query("magic/tessera")) )
                        result += "它上面鑲嵌着" + tessera_name + "，閃爍着奇異的光芒。\n";
                if( query("ultimate/121") )
                        result += HIY + name() + HIY "的等級：太古神品  LV10\n" NOR;
                else
                if( query("ultimate/105") )
                        result += HIY + name() + HIY "的等級：遠古神品  LV10\n" NOR;
                else
                if( query("ultimate/87") )
                        result += HIY + name() + HIY "的等級：上古神品  LV10\n" NOR;
                else
                        result += HIY + name() + HIY "的等級：無上神品  LV10\n" NOR;
        } else if( lvl ) {
                result += HIY + name() + HIY "的等級：" + lvl + "/9\n" NOR;

                if( query("magic/imbue_ok") )
                        result += HIM + name() + HIM "已經充分的浸入了，需要"
                                  "鑲嵌以充分發揮威力。\n" NOR;
                else
                if( (n = query("magic/imbue")) > 0 )
                        result += HIM + name() + HIM "已經運用靈物浸入了" +
                                  chinese_number(n) + "次，正在激發它的潛能。\n" NOR;
        }
        */

        
        if( query_temp("bonus/success_points") ) 
                result += HIM "目前該裝備強化時可增" + HIY + sprintf("%d", query_temp("bonus/success_points")) + "%"HIM"的成功率（僅一次有效）。\n" NOR; 
        if( query_temp("bonus/avoid_reduce") ) 
                result += HIM "目前該裝備強化時失敗後不會損失強化等級（僅一次有效）！\n" NOR; 
                
        result += sprintf(NOR "%s\n" NOR, qianghua_level[query("qianghua/level")]);
        
        result += sprintf(HIW "魔力屬性 : %s\n" NOR, chinese_s(query("magic/type")));
        result += sprintf(HIW "魔 力 值 : %d\n" NOR, query("magic/power"));
        result += sprintf(HIW "融 合 度 : %d\n" NOR, query("magic/blood"));
        if( this_object()->is_unarmed_weapon() )
                result += sprintf(HIW "傷 害 力 : %d\n" NOR, query("armor_prop/unarmed_damage"));
        else
                result += sprintf(HIW "傷 害 力 : %d\n" NOR, query("weapon_prop/damage"));
        result += sprintf(HIW "殺    戮 : %d\n" NOR, query("combat/PKS"));
        result += sprintf(HIW "鑲嵌凹槽 : %d\n" NOR, (int)query("enchase/flute"));
        //result += sprintf(HIW "煉化次數 : %d\n" NOR, (int)query("enchase/wash"));
        if( query("mod_level") )
                result += sprintf(HIC "套裝等級 : %s\n" NOR, query("mod_level"));
        /*
        if( mapp(need = query("require")) && sizeof(need) )
                foreach (string key in keys(need))
                        result += sprintf(RED "裝備要求 : %s  %d\n" NOR,
                                       to_chinese(key), need[key]);
        // result += sprintf(HIW "下線丟失 : %s\n" NOR, "否");
        */
        return result;
}

// 防具裝備的長描述
string armor_long()
{
        mapping need;
        string result = "";

        if( query("ultimate/87") )
                result += HIY + name() + HIY "的等級：遠古神品\n" NOR;
        else
        if( query("ultimate/69") )
                result += HIY + name() + HIY "的等級：上古神品\n" NOR;
        else
        if( query("ultimate/37") || query("ultimate/39") )
                result += HIY + name() + HIY "的等級：無上神品\n" NOR;

        if( query_temp("bonus/success_points") ) 
                result += HIM "目前該裝備強化時可增" + HIY + sprintf("%d", query_temp("bonus/success_points")) + "%"HIM"的成功率（僅一次有效）。\n" NOR; 
        if( query_temp("bonus/avoid_reduce") ) 
                result += HIM "目前該裝備強化時失敗後不會損失強化等級（僅一次有效）！\n" NOR; 
                
        result += sprintf(NOR "%s\n" NOR, qianghua_level[query("qianghua/level")]);

        result += sprintf(HIW "魔力屬性 : %s\n" NOR, chinese_s(query("magic/type")));
        result += sprintf(HIW "防 護 力 : %d\n" NOR, query("armor_prop/armor"));
        result += sprintf(HIW "鑲嵌凹槽 : %d\n" NOR, (int)query("enchase/flute"));
        //result += sprintf(HIW "煉化次數 : %d\n" NOR, (int)query("enchase/wash"));
        if( query("mod_level") )
                result += sprintf(HIC "套裝等級 : %s\n" NOR, query("mod_level"));
        /*
        if( mapp(need = query("require")) && sizeof(need) )
                foreach (string key in keys(need))
                        result += sprintf(RED "裝備要求 : %s  %d\n" NOR,
                                       to_chinese(key), need[key]);
        // result += sprintf(HIW "下線丟失 : %s\n" NOR, "否");
        */

        return result;
}

// 是普通武器裝備
int is_weapon()
{
        return stringp(query("skill_type"));
}

// 是空手武器裝備
int is_unarmed_weapon()
{
        return query("armor_type") == "hands" ||
               query("armor_type") == "finger";
}

// 道具的長描述
string item_long()
{
        if( is_weapon() || is_unarmed_weapon() )
                return weapon_long();

        return armor_long();
}

// 武器裝備的傷害值
int apply_damage()
{
        int d;
        int p;
        int r;
        int s;
        mixed q;

/*
        attack_lvl = weapon_level();
        p = query("point");
        //d = attack_lvl * p / MAX_LEVEL + query("bless") * 10; // 乾坤聖水聖化一次增加十點攻擊
        d = attack_lvl * p / MAX_LEVEL + query("require/level") * 10;
        return d + p;
*/
        p = query("quality_level");
        d = query("require/level");
        r = query("status");
        s = (d + r * 15) * p * 10;
        q = ITEM_D->qianghua_effect(this_object(), "weapon"); 
        s += s * q;
        return s;
}

// 防禦裝備的有效值
int apply_armor()
{
        int d;
        int p;
        int r;
        int s;
        mixed q;

/*
        defense_lvl = armor_level();
        p = query("point");
        //if( d > p * 3 / 2) d = p * 3 / 2 + query("bless") * 10;// 乾坤聖水聖化一次增加10點防禦
        //d = p * 3 / 2 + query("bless") * 2;// 乾坤聖水聖化一次增加2點防禦
        d = p * 3 / 2 + query("require/level") * 2;
        return d + p;
*/
        p = query("quality_level");
        d = query("require/level");
        r = query("status");
        s = (d + r * 15) * p * 2;
        q = ITEM_D->qianghua_effect(this_object(), "armor"); 
        s += s * q;
        return s;
}

// 進行保存數據的接口函數
mixed save_dbase_data()
{
        mapping data;
        object  user;

        data = ([ "combat" : query("combat"),
                  "owner"  : query("owner"),
                  "magic"  : query("magic"),
                  "quality_level" : query("quality_level"),
                  "status" : query("status"),
                  "require"   : query("require"),
                  //"makeinfo"  : query("makeinfo"),
                  "mod_name"   : query("mod_name"),
                  "mod_mark"   : query("mod_mark"),
                  "mod_level"  : query("mod_level"),
                  "mod_prop"   : query("mod_prop"),
                  //"modfile"  : query("modfile"),
                  //"color"   : query("color"),
                  //"colorname"   : query("colorname"),
                  "enchase"     : query("enchase"),
                  "insert"      : query("insert"),
                  "reform"      : query("reform"),
                  "qianghua"    : query("qianghua"),
                  "ultimate"    : query("ultimate"),
                  "consistence" : query("consistence"),
                  "bless"       : query("bless"),
                  "stable"      : query("stable")]);

        if( !(user = environment()) )
                data += ([ "user" : query("user") ]);
        else
        if( playerp(user) )
                data += ([ "user" : user->name(1) + "(" + query("id", user) + ")" ]);

        return data;
}

// 接受存盤數據的接口函數
int receive_dbase_data(mixed data)
{
        if( !mapp(data) )
                return 0;

        if( mapp(data["combat"]) )
                set("combat", data["combat"]);

        if( mapp(data["owner"]) )
                set("owner", data["owner"]);

        if( mapp(data["magic"]) )
                set("magic", data["magic"]);

        if( intp(data["quality_level"]) )
                set("quality_level", data["quality_level"]);

        if( intp(data["status"]) )
                set("status", data["status"]);
                
        if( mapp(data["require"]) )
                set("require", data["require"]);

        //if( stringp(data["makeinfo"]) )
        //        set("makeinfo", data["makeinfo"]);

        if( stringp(data["mod_name"]) )
                set("mod_name", data["mod_name"]);

        if( stringp(data["mod_mark"]) )
                set("mod_mark", data["mod_mark"]);

        if( stringp(data["mod_level"]) )
                set("mod_level", data["mod_level"]);
   
        if( mapp(data["mod_prop"]) )
                set("mod_prop", data["mod_prop"]);
                            
        //if( stringp(data["color"]) )
        //        set("color", data["color"]);

        //if( stringp(data["colorname"]) )
        //        set("colorname", data["colorname"]);

        if( mapp(data["enchase"]) )
                set("enchase", data["enchase"]);

        if( mapp(data["insert"]) )
                set("insert", data["insert"]);

        if( mapp(data["reform"]) )
                set("reform", data["reform"]);
                        
        if( mapp(data["qianghua"]) )
                set("qianghua", data["qianghua"]);
                      
        if( mapp(data["ultimate"]) )
                set("ultimate", data["ultimate"]);

        if( stringp(data["user"]) )
                set("user", data["user"]);

        if( !undefinedp(data["consistence"]) )
                set("consistence", data["consistence"]);

        if( intp(data["bless"]) )
                set("bless", data["bless"]);

        if( intp(data["stable"]) )
                set("stable", data["stable"]);

        return 1;
}

// 讀取存盤的數據
int restore()
{
        int r;

        if( base_name(this_object()) + ".c" == __FILE__ )
                return 0;

        r = ::restore();
        set("no_sell", 1);
        set("stable", query("stable"));
        set("bless", query("bless"));
        return r;
}

// 保存數據
int save()
{
        int res;

        if( base_name(this_object()) + ".c" == __FILE__ )
                return 0;

        return ::save();
}

// 9/10級兵器攻擊對手
mixed weapon_hit_ob(object me, object victim, int damage_bonus)
{
        int ap;
        int dp;
        int damage;

/*
        if( attack_lvl < MAX_LEVEL ||
            query("owner/" + query("id", me)) < MAX_LEVEL*80 )
                return;

        if( attack_lvl >= ULTRA_LEVEL &&
            mapp(query("magic")) ) {
                return ITEM_D->weapon10lv_hit_ob(me, victim, this_object(), damage_bonus);
        }
*/
        if( query("status") < 5 )
                return;

        if( query("status") >= 6 && query("magic/type") )
                return ITEM_D->weapon10lv_hit_ob(me, victim, this_object(), damage_bonus);

        return ITEM_D->weapon_hit_ob(me, victim, this_object(), damage_bonus);
}

// 以下的函數因為執行的頻度並不高，而且具有高度重複的性質，
// 所以都調用ITEM_D中的執行程序。

// 殺了人以後的獎勵
void killer_reward(object me, object victim)
{
        ITEM_D->killer_reward(me, victim, this_object());
}

// 呼喚物品
int receive_summon(object me)
{
        return ITEM_D->receive_summon(me, this_object());
}

// 隱藏物品
int hide_anywhere(object me)
{
        return ITEM_D->hide_anywhere(me, this_object());
}

// 追尋物品
int receive_miss(object me)
{
        if( !is_weapon() && !is_unarmed_weapon() ) {
                write("你無法追尋" + name() + "。\n");
                return 0;
        }

        if( attack_lvl < ULTRA_LEVEL ) {
                write(name() + "尚未通靈，你難以自如的感應。\n");
                return 0;
        }

        return ITEM_D->receive_miss(me, this_object());
}

// 插在地上
int do_stab(object me)
{
        return ITEM_D->do_stab(me, this_object());
}

// 特殊能力
int do_touch(object me)
{
        if( attack_lvl != ULTRA_LEVEL )
                return notify_fail("你摸了半天，好像沒什麼反應。\n");

        return ITEM_D->do_touch(me, this_object());
}

// 裝備聖化
int do_san(object me)
{
        if( (is_weapon() || is_unarmed_weapon()) &&
             attack_lvl < MAX_LEVEL )
                return notify_fail("你的武器等級不到，無法聖化。\n");

        return ITEM_D->do_san(me, this_object());
}

// 浸透物品
int do_imbue(object me, object imbue)
{
        return ITEM_D->do_imbue(me, this_object(), imbue);
}

// 鑲嵌物品
int do_enchase(object me, object tessera)
{
        return ITEM_D->do_enchase(me, this_object(), tessera);
}

// 裝備煉化
int do_wash(object me)
{
        return ITEM_D->do_wash(me, this_object());
}

// 裝備升級
int do_forging(object me, object ob)
{
        return ITEM_D->do_forging(me, this_object(), ob);
}

// 裝備要求
int do_require(object me, object ob)
{
        return ITEM_D->do_require(me, this_object(), ob);
}

mixed query_autoload() { return (query("equipped") ? query("equipped") : "kept"); }

void autoload(string parameter)
{
        switch (parameter)
        {
        case "worn":
                this_object()->wear();
                break;

        case "wielded":
                this_object()->wield();
                break;
        }
}
