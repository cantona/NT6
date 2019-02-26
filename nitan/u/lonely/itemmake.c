// itemmake.c 自制道具

#include <dbase.h>
#include <ansi.h>
#include <name.h>
#include <move.h>
#include <command.h>

inherit F_OBSAVE;
inherit F_NOCLONE;

int is_item_make() { return 1; }

#define LEVEL1    5
#define LEVEL2    10
#define LEVEL3    30
#define LEVEL4    100
#define LEVEL5    300
#define LEVEL6    1000
#define LEVEL7    3000
#define LEVEL8    10000
#define LEVEL9    50000
#define MAX_LEVEL       LEVEL9
#define ULTRA_LEVEL     (LEVEL9 + 1)
#define MEMBER_D        "/adm/daemons/memberd"

#define TAOZHUANG_D     "/adm/daemons/taozhuangd"

nosave int *levels = ({ LEVEL1, LEVEL2, LEVEL3, LEVEL4,
                        LEVEL5, LEVEL6, LEVEL7, LEVEL8,
                        LEVEL9 });

nosave int performing  = 0;
nosave int attack_lvl  = 0;
nosave int defense_lvl = 0;
37      static mapping qianghua_level = ([ 
38              "1":       "★", 
39              "2":       "★★", 
40              "3":       "★★★", 
41              "4":       "★★★★", 
42              "5":       "★★★★★", 
43              "6":       "★★★★★★", 
44              "7":       "★★★★★★★", 
45              "8":       "★★★★★★★★", 
46              "9":       "★★★★★★★★★", 
47              "10":      "★★★★★★★★★★", 
48      ]); 

int is_stay_in_room() { return attack_lvl >= ULTRA_LEVEL; }

// n_type 0 為福緣 1 為氣運
int f_enchase_points(int n_type);

string chinese_s(mixed arg)
{
      if (! stringp(arg))return "無";
      if (arg == "cold")return HIW "冰";
      if (arg == "fire")return HIR "火";
      if (arg == "magic")return HIY "魔";
      if (arg == "lighting")return HIM "電";
}


// 武器的主人ID - 通過文件的名字來判斷
string item_owner()
{
        string owner;
        if (sscanf(base_name(this_object()), ITEM_DIR "%*s/%s-%*s", owner))
                return owner;

        return 0;
}

// 判斷該武器是否被當前某人所持有
int is_not_belong_me(object me)
{
        string user;

  user = query("user");
        if (! user || ! sscanf(user, "%*s(" + me->query("id") + ")"))
                return 1;

        return 0;
}

// 武器裝備的等級
int weapon_level()
{
        mapping o;
        string *ks;
        int lvl;
        int i;

        lvl = 0;
        o = query("owner");
        if (mapp(o))
        {
                ks = keys(o);
                for (i = 0; i < sizeof(ks); i++)
                        lvl += o[ks[i]];
        }

        lvl /= 100;
        if (lvl > MAX_LEVEL) lvl = MAX_LEVEL;

        if (lvl == MAX_LEVEL && query("magic/power"))
                // 具有魔法屬性
                lvl = ULTRA_LEVEL;
        return lvl;
}

// 防禦裝備的等級
int armor_level()
{
        // More to be added
        return 0;
}

// 武器裝備的長描述
string weapon_long()
{
        string  n;
        mapping c;
        int type;
        int k;
        int lvl;
        string tessera_name;
        string result;
        int enchase_number;
        mixed enchase_objects;
        string* key_objects;
        int i, enchase_points;

        c = query("combat");
        n = query("unit") + name();
        if (! c)
                return "這" + n + "顯然還沒有飲過人血，上面純潔無暇。\n";
        k = c["MKS"] + c["PKS"];

        if (c["WPK_GOOD"] < k / 2 &&
            c["WPK_BAD"]  < k / 2)
                type = 0;
        else
        if (c["WPK_GOOD"] > c["WPK_BAD"] * 2)
                type = -1;
        else
                type = 1;

        if (c["MKS"] + c["PKS"] < 10)
                return "這" + n + "看來已經用過人血開祭，上面隱現血痕。\n";

        attack_lvl = weapon_level();
        lvl = sizeof(levels);
        while (--lvl)
                if (attack_lvl >= levels[lvl])
                        break;
        lvl++;

        switch (type)
        {
        case 1:
                if (attack_lvl >= ULTRA_LEVEL)
                        result = HIY "它看上去平平常常，沒有半點特殊，只是"
                                 "隱隱的讓人感到那不凡的氣質。\n" NOR;
                else
                if (attack_lvl >= MAX_LEVEL)
                        result = HIY "它看上去讓人發自內心無限崇敬，一股"
                               "皓然正氣悠然長存，頗具帝王風範，君臨\n"
                               "天下，威鎮諸路凶神惡煞、難道這就是傳説中才"
                               "會出現的諸神之" + name() + HIY "？\n" NOR;
                else
                if (attack_lvl >= LEVEL8)
                        result = HIC "一眼望去，你覺得有無數的兇靈在瘋狂"
                               "亂舞，哭天搶地，悽烈之極，似乎要重返\n"
                               "人間。你忍不住要長歎一聲，昔日兇魔，也難逃死劫。\n" NOR;
                else
                if (attack_lvl >= LEVEL7)
                        result = HIC "它上面附着着不知多少兇魂，無數邪派"
                               "兇魔斃命於下，一股哀氣猶然不散，讓你\n"
                               "忍不住打了個冷戰。\n" NOR;
                else
                if (attack_lvl >= LEVEL6)
                        result = HIR "它看上去令人驚心動魄，這就是名動江湖的" + name() + HIR
                               "，多少凶煞就此斃命，成就人間正義。\n" NOR;
                else
                if (attack_lvl >= LEVEL5)
                        result = HIR "它上面隱隱然透出一股血光，多年以來，許多"
                               "江湖上聞名一時的兇魔都成了" + name() + HIR "下的遊魂。\n" NOR;
                else
                if (attack_lvl >= LEVEL4)
                        result = HIW "這就是江湖上著名的神兵之一：" + name() + HIW
                               "，窮兇極惡之徒見此物無不心馳神搖。\n" NOR;
                else
                if (attack_lvl >= LEVEL3)
                        result = HIW "這" + n + HIW "有一股正氣散發出來，看來它下面兇魂不少。\n" NOR;
                else
                if (attack_lvl >= LEVEL2)
                        result = RED "這" + n + RED "隱然透出一股正氣，"
                               "看來它殺了不少兇惡之徒。\n" NOR;
                else
                if (attack_lvl >= LEVEL1)
                        result = RED "細觀之下，刃口有一絲血痕，想必是它殺人不少"
                               "，殷血於此吧！\n" NOR;
                else
                        result = CYN "看得出這" + n + CYN "曾經殺過不少兇惡之徒。\n" NOR;
                break;

        case -1:
                if (attack_lvl >= ULTRA_LEVEL)
                        result = HIR "它看上去平平常常，沒有半點特殊，但是"
                                 "不知為何卻總是讓人感到有些不安。\n" NOR;
                else
                if (attack_lvl >= MAX_LEVEL)
                        result = HIR "它看上去讓人打心底泛出陣陣寒意，隱"
                               "隱然上面似乎附着着無數冤魂，但是全然\n被這" + n + HIR
                               "上面的殺氣所制，難道這就是傳説中才會出現的邪神之" + name() + HIR
                               "？\n" NOR;
                else
                if (attack_lvl >= LEVEL8)
                        result = HIC "一眼望去，你覺得有無數的冤魂向你撲"
                               "來，哭天搶地，悽烈之極，你忍不住打了\n"
                               "個寒戰，不敢再看第二眼。\n" NOR;
                else
                if (attack_lvl >= LEVEL7)
                        result = HIC "它上面附着着不知多少冤魂，無數高手"
                               "飲恨於下，一股怨氣直衝霄漢，讓你忍不\n"
                               "住打了個冷戰。\n" NOR;
                else
                if (attack_lvl >= LEVEL6)
                        result = HIW "它看上去令人驚心動魄，這就是名動江湖的" + name() + HIW
                               "，不知多少英雄就此飲恨。\n" NOR;
                else
                if (attack_lvl >= LEVEL5)
                        result = HIW "它上面隱隱然透出一股血光，多年以來，許多"
                               "江湖上聞名一時的高手都成了" + name() + HIW "下的遊魂。\n" NOR;
                else
                if (attack_lvl >= LEVEL4)
                        result = HIG "這就是江湖上著名的兇器之一：" + name() + HIG
                               "，誰曾想那麼多仁人義士飲恨於下。\n" NOR;
                else
                if (attack_lvl >= LEVEL3)
                        result = HIG "這" + n + HIG "有一股戾氣散發出來，看來它下面遊魂不少。\n" NOR;
                else
                if (attack_lvl >= LEVEL2)
                        result = RED "這" + n + RED "隱然透出一股戾氣，看來它殺了不少人。\n" NOR;
                else
                if (attack_lvl >= LEVEL1)
                        result = RED "細觀之下，刃口有一絲血痕，想必是它殺人不少"
                               "，殷血於此吧！\n" NOR;
                else
                        result = CYN "看得出這" + n + CYN "曾經殺過不少俠義之士。\n" NOR;
                break;

        default:
                if (attack_lvl >= ULTRA_LEVEL)
                        result = HIC "它看上去平平常常，沒有半點特殊，只是一件"
                                 "平凡之極的兵器而已。\n" NOR;
                else
                if (attack_lvl >= MAX_LEVEL)
                        result = HIC "它安然暢意，似乎就要騰空而去，跳出"
                               "三界，不入五行。世間萬物，彷彿俱在它\n"
                               "霸氣所及之處。冤魂不舞、羣邪辟易，無不被這" + n + HIC
                               "上古神兵的霸氣所制。\n" NOR;
                else
                if (attack_lvl >= LEVEL8)
                        result = HIM "一眼望去，你覺得有無數的遊魂向你撲"
                               "來，哭天搶地，悽烈之極，你頓時覺得它\n"
                               "沉重無比，幾乎拿捏不住。\n" NOR;
                else
                if (attack_lvl >= LEVEL7)
                        result = HIM "它上面附着着不知多少遊魂，無數正邪"
                               "高手喪命於下，一股怨氣哀愁油然不盡，\n"
                               "讓你忍不住打了個冷戰。\n" NOR;
                else
                if (attack_lvl >= LEVEL6)
                        result = HIR "它看上去令人驚心動魄，這就是名動江湖的" + name() + HIR
                               "，多少正邪高手都難逃此劫，墮入輪迴。\n" NOR;
                else
                if (attack_lvl >= LEVEL5)
                        result = HIR "它上面隱隱然透出一股血光，多年以來，許多"
                               "江湖上聞名一時的高手都成了這" + n + HIR "下的遊魂。\n" NOR;
                else
                if (attack_lvl >= LEVEL4)
                        result = HIW "這就是江湖上著名的利器之一：" + name() + HIW
                               "，誰能想到那麼多高手飲恨於下。\n" NOR;
                else
                if (attack_lvl >= LEVEL3)
                        result = HIW "這" + n + HIW "有一股殺氣散發出來，看來它下面遊魂不少。\n" NOR;

                else
                if (attack_lvl >= LEVEL2)
                        result = RED "這" + n + RED "隱然透出一股殺氣，看來它殺了不少人。\n" NOR;

                else
                if (attack_lvl >= LEVEL1)
                        result = RED "細觀之下，刃口有一絲血痕，想必是它殺人不少"
                               "，殷血於此吧！\n" NOR;
                else
                        result = CYN "看得出這" + n + CYN "曾經殺過不少人。\n" NOR;
                break;
        }

        if (attack_lvl == ULTRA_LEVEL)
        {
                if (stringp(tessera_name = query("magic/tessera")))
                        result += "它上面鑲嵌着" + tessera_name + "，閃爍着奇異的光芒。\n";
                result += HIY + name() + HIY "的等級：無上神品  LV10\n" NOR;
        } else
        if (lvl)
        {
                result += HIY + name() + HIY "的等級：" + lvl + "/9\n" NOR;

                if (query("magic/imbue_ok"))
                        result += HIM + name() + HIM "已經充分的浸入了，需要"
                                  "鑲嵌以充分發揮威力。\n" NOR;
                else
                if ((n = query("magic/imbue")) > 0)
                        result += HIM + name() + HIM "已經運用靈物浸入了" +
                                  chinese_number(n) + "次，正在激發它的潛能。\n" NOR;
        }

              // 擴展鑲嵌物品信息
              enchase_objects = query("enchase");
        enchase_points = 0;
              if (! enchase_objects || ! sizeof(enchase_objects))
        {
      enchase_points = 0;
        }
        else
        {
      key_objects = keys(enchase_objects);
                        enchase_number = sizeof(key_objects);
                        for (i = 0; i < enchase_number; i ++)
        enchase_points += enchase_objects[key_objects[i]]["point"];
              }
              // 套裝
              result += HIC "--------------套裝-------------------\n";
              result += HIC "套裝等級：" + TAOZHUANG_D->taozhuang_name(query("taozhuang")) + "\n" NOR;
              result += "-------------------------------------\n";

              result += HIW "堅固修正： " + query("bless") + "\t" NOR;
              result += HIW "攻·防修正：" + sprintf("%d", query("bless") * 2 + enchase_points) + "\n" NOR;
              result += HIW "聖化次數： " + query("bless") + "\t" NOR;
              result += HIW "魔力改善值：" + query("magic/power") + "\n" NOR;
              result += HIW "魔力屬性：" + chinese_s(query("magic/type"))  + "\t" NOR;
              result += HIW "人器融合度：" + query("magic/blood") + "\n" NOR;
355                   // 顯示強化等級 
356                   if (query("qh_level")) 
357                   { 
358                             result +=  HIY "強化等級：" + qianghua_level[sprintf("%d", query("qh_level"))] + "\n" NOR; 
359                             if (query("weapon_prop/" + item_owner()+ "_potlimit")) 
360                             { 
361                                     if (this_object()->query("armor_type") == "hands") 
362                                             weapon_type = "armor_prop"; 
363                                     else 
364                                             weapon_type = "weapon_prop"; 
365                                     result += sprintf(HIY "%-10s%-12s%-10s%-10s\n" NOR,  
366                                                       "潛能上限：",  
367                                                       sprintf("+%d", query(weapon_type + "/" + item_owner()+ "_potlimit")) + 
368                                                        "%", 
369                                                       "擴展加成：",  
370                                                       sprintf("+%d", 0) + "%"); 
371                             } 
372                   } 
37
        result += HIG "\n---------------鑲嵌擴展--------------\n" NOR;
        result += HIW "鑲嵌槽使用：  " + sprintf("%d", 1 + enchase_number) + "/" +
                        sprintf("%d", 1 + query("enchase_all")) + "\n";
              result += HIY "---------------鑲嵌寶物--------------\n" NOR;
              result += sprintf(HIW "%-16s%-20s%-16s\n\n" NOR,"名稱", "ID", "堅固");
        if (! stringp(tessera_name))
       tessera_name = HIR "十級兵器保留槽" NOR;
        result += sprintf(NOR + WHT"%-16s%-20s%-16s\n" NOR, filter_color(tessera_name), "----", "----");
        for (i = 0; i < enchase_number; i ++)
      result = result + sprintf(NOR + WHT "%-16s%-20s%-16d\n" NOR,
                                          enchase_objects[key_objects[i]]["name"],
                                          key_objects[i],
                                          enchase_objects[key_objects[i]]["cur_firm"]);
              result += "-------------------------------------\n";
388                   // 如果存在裝備強化效果成功率加成則顯示 
389                   if (this_object()->query("suc_points_add")) 
390                             result += HIG "目前該裝備強化時可增" + HIY +  
391                                       sprintf("%d", this_object()->query("suc_points_add")) +  
392                                       HIG "%的成功率（僅一次有效）。\n" NOR; 
393                   // 如果存在裝備強化效果失敗後不掉級則顯示 
394                    if (this_object()->query("no_reduce_level")) 
395                             result += HIR "目前該裝備強化時失敗後不會損失強化等級（僅一次有效）！\n" NOR; 

        return result;
}

string armor_long()
{

        mapping enchase_objects;
        int enchase_points, enchase_number, i;
        string* key_objects;
        string result;

        // 擴展鑲嵌物品信息
              enchase_objects = query("enchase");
        enchase_points = 0;
              if (! enchase_objects || ! sizeof(enchase_objects))
        {
      enchase_points = 0;
        }
        else
        {
      key_objects = keys(enchase_objects);
                        enchase_number = sizeof(key_objects);
                        for (i = 0; i < enchase_number; i ++)
        enchase_points += enchase_objects[key_objects[i]]["point"];
              }
              // 套裝
              result = "";
              result += HIC "--------------套裝-------------------\n";
              result += HIC "套裝等級：" + TAOZHUANG_D->taozhuang_name(query("taozhuang")) + "\n" NOR;
              result += "-------------------------------------\n";
              result += HIW "堅固修正： " + query("bless") + "\t" NOR;
              result += HIW "攻·防修正：" + sprintf("%d", query("bless") * 10 + enchase_points) + "\n" NOR;
              result += HIW "聖化次數： " + query("bless") + "\n" NOR;
430                   // 顯示強化等級 
431                   if (query("qh_level")) 
432                   { 
433                             result += HIY "強化等級：" + qianghua_level[sprintf("%d", query("qh_level"))] + "\n" NOR; 
434                             if (query("armor_prop/qh_exp")) 
435                             { 
436                                     result += sprintf(HIY "%-10s%-12s%-10s%-10s\n" NOR,  
437                                                       "經驗加成：", sprintf("%d", query("armor_prop/qh_exp")) + "%", 
438                                                       "潛能加成：", sprintf("%d", query("armor_prop/qh_pot")) + "%"); 
439                                     result += sprintf(HIY "%-10s%-12s%-10s%-10s\n" NOR,  
440                                                       "體會加成：", sprintf("%d", query("armor_prop/qh_mar")) + "%", 
441                                                       "擴展加成：", sprintf("%d", query("armor_prop/qh_nono")) + "%");                              
442                             } 
443                             if (query("armor_prop/" + item_owner()+ "_potlimit")) 
444                             { 
445                                     result += sprintf(HIY "%-10s%-12s%-10s%-10s\n" NOR,  
446                                                       "潛能上限：",  
447                                                       sprintf("+%d", query("armor_prop/" + item_owner()+ "_potlimit")) + 
448                                                        "%", 
449                                                       "擴展加成：",  
450                                                       sprintf("+%d", 0) + "%"); 
451                             } 
452                   } 

        result += HIG "\n---------------鑲嵌擴展--------------\n" NOR;
        result += HIW "鑲嵌槽使用：  " + sprintf("%d", enchase_number) + "/" +
                        sprintf("%d", query("enchase_all")) + "\n";
              result += HIY "---------------鑲嵌寶物--------------\n" NOR;
              result += sprintf(HIW "%-16s%-20s%-16s\n\n" NOR,"名稱", "ID", "堅固");

        for (i = 0; i < enchase_number; i ++)
      result = result + sprintf(NOR + WHT "%-16s%-20s%-16d\n" NOR,
                                          enchase_objects[key_objects[i]]["name"],
                                          key_objects[i],
                                          enchase_objects[key_objects[i]]["cur_firm"]);
              result += "-------------------------------------\n";

    if (this_object()->query("enchase_all") >= 8)
    {
      log_file("srb_bug", base_name(this_object()) + "\n");
    }
466                   // 如果存在裝備強化效果成功率加成則顯示 
467                   if (this_object()->query("suc_points_add")) 
468                             result += HIG "目前該裝備強化時可增" + HIY +  
469                                       sprintf("%d", this_object()->query("suc_points_add")) +  
470                                       HIG "%的成功率（僅一次有效）。\n" NOR; 
471                   // 如果存在裝備強化效果失敗後不掉級則顯示 
472                    if (this_object()->query("no_reduce_level")) 
473                             result += HIR "目前該裝備強化時失敗後不會損失強化等級（僅一次有效）！\n" NOR; 
474      
475                     if (this_object()->query("enchase_all") >= 11) 
476                     { 
477                             log_file("srb_bug", base_name(this_object()) + "\n"); 
478                     } 
479      

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
        return query("armor_type") == "hands";
}

// 道具的長描述
string item_long()
{
        if (is_weapon() || is_unarmed_weapon())
                return weapon_long();


        return armor_long();
}

// 武器裝備的傷害值
int apply_damage()
{
        int d;
        int p;
        int i, enchase_points, enchase_number, flag_9kong;
        mixed enchase_objects;
        string* key_objects;

        attack_lvl = weapon_level();
        p = query("point");
        d = query("bless") * 10; // 乾坤聖水聖化一次增加2點攻擊

        enchase_objects = query("enchase");
  enchase_points = 0;
  flag_9kong = 0;

        if (! enchase_objects || ! sizeof(enchase_objects))
  {
    enchase_points = 0;
  }
  else
  {
    key_objects = keys(enchase_objects);
              enchase_number = sizeof(key_objects);
              for (i = 0; i < enchase_number; i ++)
              {
            enchase_points += enchase_objects[key_objects[i]]["point"];
            // 如果有九孔寶石--海藍石則做標記
            if (enchase_objects[key_objects[i]]["name"] == "海藍石")flag_9kong = 1;
            }
        }

  // 鑲嵌寶石海藍石提高整體50%攻擊力
  if (flag_9kong)enchase_points = enchase_points + enchase_points / 2;

  if (this_object()->query("enchase_all") >= 11)
  {
    log_file("srb_bug", base_name(this_object()) + "\n");
  }
546      
547             // 在這裏添加強化後對鑲嵌物品提升的傷害加成 
548             // 強化等級1-10級，每級遞增x% 
549             enchase_points = ITEM_D->qianghua_enchase_points("weapon", enchase_points, query("qh_level")); 
550              
551             // 增加潛能加成 
552             if (query("qh_level")) 
553             { 
554                     this_object()->set("weapon_prop/" + item_owner()+ "_potlimit",  
555                                                enchase_number * query("qh_level") / 2); 
556                     this_object()->set("armor_prop/" + item_owner()+ "_potlimit",  
557                                                enchase_number * query("qh_level") / 2);                                        
558             } 
559              


        return d + p + enchase_points * 2;
}

// 防禦裝備的有效值
int apply_armor()
{
        int d;
        int p;
        int i, enchase_points, enchase_number;
        mixed enchase_objects;
        string* key_objects;

        defense_lvl = armor_level();
        p = query("point");
        d = query("bless") * 10;// 乾坤聖水聖化一次增加2點防禦

        enchase_objects = query("enchase");
  enchase_points = 0;
        if (! enchase_objects || ! sizeof(enchase_objects))
  {
    enchase_points = 0;
  }
  else
  {
    key_objects = keys(enchase_objects);
                enchase_number = sizeof(key_objects);
                for (i = 0; i < enchase_number; i ++)
                {
      enchase_points += enchase_objects[key_objects[i]]["point"];
    }
        }
  if (this_object()->query("enchase_all") > 11)
  {
    log_file("srb_bug", base_name(this_object()) + "\n");
  }
  // 10孔鑲嵌luhua zhijing 提高傷害40
597             // 披風護腕強化後提升傷害 
598             if (this_object()->query("armor_type") == "wrists"|| this_object()->query("armor_type") == "surcoat") 
599             { 
600                     this_object()->set("armor_prop/damage", 0); 
601                     if (enchase_number > 0) 
602                     { 
603                              
604                             for (i = 0; i < enchase_number; i ++ ) 
605                             { 
606                                     // 是否鑲嵌10孔寶石 
607                                     if (enchase_objects[key_objects[i]]["spe_data"]["luhua-zhijing"]) 
608                                     { 
609                                             // LHZJ基本+4000，再計算出強化後的效果 
610                                             this_object()->set("armor_prop/damage", 4000); 
611                                     } 
612                             } 
613                             // 計算披風的強化傷害 
614                             if (this_object()->query("armor_type") == "surcoat") 
615                             { 
616                                     this_object()->add("armor_prop/damage", 
617                                     ITEM_D->qianghua_enchase_points("surcoat", enchase_number, query("qh_level"))); 
618                                      
619                                     // 披風對潛能上限加成 公式：鑲嵌數*強化等級/2% 
620                                     if (query("qh_level")) 
621                                     { 
622                                             // 設置了數值，也保持了擁有者有效 
623                                             this_object()->set("armor_prop/" + item_owner()+ "_potlimit",  
624                                                                 enchase_number * query("qh_level") / 2); 
625                                     } 
626                                      
627                             } 
628                             // 計算護腕的傷害 
629                             if (this_object()->query("armor_type") == "wrists") 
630                             { 
631                                     this_object()->add("armor_prop/damage", 
632                                     ITEM_D->qianghua_enchase_points("wrists", enchase_number, query("qh_level"))); 
633      
634                                     /*護腕對經驗，潛能和體會的加成 
635                                       -- 經驗加成：每級強化等比增加10%的經驗加成， 10級強化可 
636                                      增加100%經驗加成。 
637                                     -- 潛能加成：前5級強化每級增加4%的潛能加成，6到10級強化 
638                                      每級增加16%的潛能加成。 
639                                      10級強化可增加100%的潛能加成。 
640                                     -- 體會加成：前5級強化每級增加2%的潛能加成，6到10級強化 
641                                     每級增加8%的潛能加成。10級強化可增加50%的潛能加成。 
642                                     */ 
643                                     if (query("qh_level")) 
644                                     { 
645                                             this_object()->set("armor_prop/qh_exp", query("qh_level")*3); 
646                                             if (query("qh_level") <= 5) 
647                                             { 
648                                                     this_object()->set("armor_prop/qh_pot", query("qh_level")*2); 
649                                                     this_object()->set("armor_prop/qh_mar", query("qh_level")*2); 
650                                                     // 設置擁有者 
651                                                     this_object()->set("armor_prop/" + item_owner()+ "_wrists", 1); 
652                                             } 
653                                             else 
654                                             { 
655                                                     this_object()->set("armor_prop/qh_pot",  
656                                                       5 * 2 + (query("qh_level") - 5)*4); 
657                                                     this_object()->set("armor_prop/qh_mar",  
658                                                       5 * 2 + (query("qh_level") - 5)*3); 
659                                                     // 設置擁有者 
660                                                     this_object()->set("armor_prop/" + item_owner()+ "_wrists", 1); 
661                                             } 
662                                             /* 每個鑲嵌額外提升 
663                                             每個鑲嵌物可額外再提升經驗加成3% 
664                                             每個鑲嵌物可額外再提升2%的潛能加成 
665                                             每個鑲嵌物可額外提升1%的體會加成 
666                                             */ 
667                                             this_object()->add("armor_prop/qh_exp", enchase_number*3); 
668                                             this_object()->add("armor_prop/qh_pot", enchase_number*2); 
669                                             this_object()->add("armor_prop/qh_mar", enchase_number*1); 
670                                              
671                                     } 
672                             } 
673                     } 
674             } 


  /*
  if (find_player("rcwiz") && query("user") == "☆望天涯☆(rcwiz)" )
    tell_object(find_player("rcwiz"), HIR "\narmor_type = " + query("armor_type") + "\n" +
                                          "" NOR );
  */
  if (1 || query("armor_type") == "head") // 根據測試這個地方取不到armor_type
  {
    if (sizeof(key_objects))
    {
      this_object()->set("armor_prop/add_yanjiu", 0);
      this_object()->set("armor_prop/add_jiqu", 0);

      for (i = 0; i < sizeof(key_objects); i ++ )
      {
        // 提高研究效率
        if (enchase_objects[key_objects[i]]["spe_data"]["add_yanjiu"])
          this_object()->add("armor_prop/add_yanjiu",
                             enchase_objects[key_objects[i]]["spe_data"]["add_yanjiu"]);
        // 提高汲取效率
        if (enchase_objects[key_objects[i]]["spe_data"]["add_jiqu"])
          this_object()->add("armor_prop/add_jiqu",
                             enchase_objects[key_objects[i]]["spe_data"]["add_jiqu"]);
      }
    }
  }

        return (d + p + enchase_points * 2) * 6 / 5;
}

// n_type = 0 : 福緣   n_type = 1 ： 氣運
int f_enchase_points(int n_type)
{
        int i, enchase_points, enchase_number;
        mixed enchase_objects;
        string* key_objects;

        enchase_objects = query("enchase");
  enchase_points = 0;

        if (! enchase_objects || ! sizeof(enchase_objects))
  {
    enchase_points = 0;
  }
  else
  {
    key_objects = keys(enchase_objects);
                enchase_number = sizeof(key_objects);
                for (i = 0; i < enchase_number; i ++)
                {
                  if (n_type)
                    enchase_points += enchase_objects[key_objects[i]]["qy"];
                  else
                    enchase_points += enchase_objects[key_objects[i]]["fy"];
    }
        }

        return enchase_points;

}

// 進行保存數據的接口函數
mixed save_dbase_data()
{
        mapping data;
        object  user;

        data = ([ "combat" : query("combat"),
                  "owner"  : query("owner"),
                  "magic"  : query("magic"),
                  "consistence" : query("consistence"),
                  "bless"       : query("bless"),
                  "stable"      : query("stable"),
      "enchase"     : query("enchase"),
                  "enchase_all" : query("enchase_all"),
                  "enchase_all_last" : query("enchase_all_last"),// 非會員失效的時候孔的數量
                  //"new_long"         : query("new_long"),             // 可以更改long描述
                  //"new_wear_msg"     : query("new_wear_msg"),         // 可以更改裝備時的描述
                  //"new_remove_msg"   : query("new_remove_msg"),       // 可以更改取消裝備時的描述
                  "taozhuang"   : query("taozhuang"), // 套裝等級
754                       "qh_level"    : query("qh_level"), // 強化等級 
755                       "suc_points_add" : query("suc_points_add"), // 強化成功率增加 
756                       "no_reduce_level": query("no_reduce_level"), // 強化失敗不掉等級                 

                  ]);

        if (! (user = environment()))
                data += ([ "user" : query("user") ]);
        else
        if (playerp(user))
                data += ([ "user" : user->name(1) + "(" + user->query("id") + ")" ]);

        return data;
}

// 接受存盤數據的接口函數
int receive_dbase_data(mixed data)
{

        if (! mapp(data))
                return 0;
/*
  // 可以再完成自造兵器後更改long,wear_msg, remove_msg等描述
        if (stringp(data["new_long"]))
                set("new_long", data["new_long"]);
        if (stringp(data["new_wear_msg"]))
                set("new_wear_msg", data["new_wear_msg"]);
        if (stringp(data["new_remove_msg"]))
                set("new_remove_msg", data["new_remove_msg"]);
*/
        if (mapp(data["combat"]))
                set("combat", data["combat"]);

        if (mapp(data["owner"]))
                set("owner", data["owner"]);

        if (mapp(data["magic"]))
                set("magic", data["magic"]);

        if (stringp(data["user"]))
                set("user", data["user"]);

        if (! undefinedp(data["consistence"]))
                set("consistence", data["consistence"]);

        if (intp(data["bless"]))
                set("bless", data["bless"]);

        // 套裝
        if (intp(data["taozhuang"]))
                set("taozhuang", data["taozhuang"]);
805             // 強化等級 
806             if (intp(data["qh_level"])) 
807                     set("qh_level", data["qh_level"]);       
808             // 強化增加成功率 
809             if (intp(data["suc_points_add"])) 
810                     set("suc_points_add", data["suc_points_add"]); 
811             // 強化失敗不掉等級 
812             if (intp(data["no_reduce_level"])) 
813                     set("no_reduce_level", data["no_reduce_level"]); 
814      

        if (intp(data["stable"]))
                set("stable", data["stable"]);

        if (mapp(data["enchase"]))
                set("enchase", data["enchase"]);

        if (intp(data["enchase_all"]))
    set("enchase_all", data["enchase_all"]);

        if (intp(data["enchase_all_last"]))
    set("enchase_all_last", data["enchase_all_last"]);
}

// 讀取存盤的數據
int restore()
{
        int r;

        if (base_name(this_object()) + ".c" == __FILE__)
                return 0;

        r = ::restore();
        set("no_sell", 1);
        set("stable", query("stable"));
        set("bless", query("bless"));
  set("enchaes", query("enchase"));
  set("enchase_all", query("enchase_all"));
  set("taozhuang", query("taozhuang")); // 套裝
843             set("qh_level", query("qh_level")); // 強化等級 
844             set("suc_points_add", query("suc_points_add")); // 強化成功率增加 
845             set("no_reduce_level", query("no_reduce_level")); // 強化不掉等級        

/*
  // 設置新long描述
  if (stringp(query("new_long")) && sizeof(query("new_long")) > 0)
  {
    set("long", query("new_long") + "\n");
  }
  else
  {
    set("long", query("long"));
  }
  // 設置新的wear_msg描述
  // 要對兵器進行判斷，query(skill_type)為兵器，用wield_msg
  //                   query(armor_type)為防具，用wear_msg
  if (stringp(query("new_wear_msg")) && sizeof(query("new_wear_msg")) > 0)
  {
    if (stringp(query("skill_type")))
    {
      set("wield_msg", query("new_wear_msg") + "\n");
    }
    else
    {
      set("wear_msg", query("new_wear_msg") + "\n");
    }
  }
  else
  {
    if (query("skill_type"))
    {
      set("wield_msg", query("wield_msg") + "\n");
    }
    else
    {
      set("wear_msg", query("wear_msg") + "\n");
    }

  }

  // 設置新的remove_msg描述
  // 要對兵器進行判斷，query(skill_type)為兵器，用wield_msg
  //                   query(armor_type)為防具，用wear_msg
  if (stringp(query("new_remove_msg")) && sizeof(query("new_remove_msg")) > 0)
  {
    if (query("skill_type"))
    {
      set("unwield_msg", query("new_remove_msg") + "\n");
    }
    else
    {
      set("remove_msg", query("new_remove_msg") + "\n");
    }

  }
  else
  {
    if (query("skill_type"))
    {
      set("unwield_msg", query("unwield_msg") + "\n");
    }
    else
    {
      set("remove_msg", query("remove_msg") + "\n");
    }
  }

*/
  if (query("enchase_all") >= 11)
  {
    log_file("srb_bug", base_name(this_object()) + "\n");
  }

  if (! MEMBER_D->is_valib_member(item_owner()) && query("enchase_all") > 4 )
  {
    set("enchase_all_last", query("enchase_all"));
    set("enchase_all", 4);
  }
  if (MEMBER_D->is_valib_member(item_owner()))
  {
    if (query("enchase_all_last") > query("enchase_all"))
      set("enchase_all", query("enchase_all_last"));
  }

        return r;
}

// 保存數據
int save()
{
  int res;

        if (base_name(this_object()) + ".c" == __FILE__)
                return 0;

  return ::save();
}

// 9/10級兵器攻擊對手
mixed weapon_hit_ob(object me, object victim, int damage_bonus)
{
        int ap;
        int dp;
        int damage;

        if (attack_lvl < MAX_LEVEL ||
      query("owner/" + me->query("id")) < MAX_LEVEL * 80)
                return;

        if (attack_lvl >= ULTRA_LEVEL &&
            mapp(query("magic")))
        {
                return ITEM_D->weapon10lv_hit_ob(me, victim, this_object(), damage_bonus);
        }

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
        if (! is_weapon() && ! is_unarmed_weapon())
        {
                write("你無法追尋" + name() + "。\n");
                return 0;
        }

        if (attack_lvl < ULTRA_LEVEL)
        {
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
        if (attack_lvl != ULTRA_LEVEL)
                return notify_fail("你摸了半天，好像沒什麼反應。\n");

        return ITEM_D->do_touch(me, this_object());
}

// 聖化
int do_san(object me)
{
        if ((is_weapon() || is_unarmed_weapon()) &&
            attack_lvl < MAX_LEVEL)
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

int query_autoload() { return (query("equipped") ? query("equipped") : "kept"); }

void autoload(string parameter)
{
    if (this_object()->query("enchase_all") >= 10)
    {
      log_file("srb_bug", base_name(this_object()) + "\n");
    }

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
