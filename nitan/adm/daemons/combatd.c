// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// combatd.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_DBASE;

#define NCH_CHANNEL(x) CHANNEL_D->channel_broadcast("nch", "戰鬥精靈："+(string)x) 

#define DEFAULT_MAX_PK_PERDAY   8
#define DEFAULT_MAX_PK_PERMAN   3
#define EXP_LIMIT       50000000000

#define ATTACK          0
#define DODGE           1
#define PARRY           2
#define DAMAGE          3
#define FORCE2          4

#define USE_SKILLS_COMBAT       1

#undef REDUCE_PVP_DAMAGE

#define PVP_DAMAGE_SCALE        40;  // 玩家對玩家時傷害（當前值）下降為 40%
#define PVP_WOUND_SCALE         30;  // 玩家對玩家時傷害（最大值）下降為 30%

mapping limb_damage = ([
// 人類身體部位
        "頭部"  :   100,
        "頸部"  :   90,
        "胸口"  :   90,
        "後心"  :   80,
        "左肩"  :   50,
        "右肩"  :   55,
        "左臂"  :   40,
        "右臂"  :   45,
        "左手"  :   20,
        "右手"  :   30,
        "腰間"  :   60,
        "小腹"  :   70,
        "左腿"  :   40,
        "右腿"  :   50,
        "左腳"  :   35,
        "右腳"  :   40,
//  動物身體部位
        "身體"  :   80,
        "前腳"  :   40,
        "後腳"  :   50,
        "腿部"  :   40,
        "尾巴"  :   10,
        "翅膀"  :   50,
        "爪子"  :   40,
]);

nosave string *danger_limbs = ({
        "頭部", "頸部", "胸口", "後心","小腹",
});

string *head_damage_me_msg = ({
        append_color(HIR "你覺得頭有一點發暈。\n" NOR, HIR),
        append_color(HIB "你覺得一陣暈眩，身體晃了一下。\n" NOR, HIB),
        append_color(BLU "你只得眼冒金星，渾身發飄。\n" NOR, BLU),
});

string *body_damage_me_msg = ({
        append_color(HIR "你只覺$l隱隱作痛，體內真氣受到一點振盪。\n" NOR, HIR),
        append_color(HIB "你只覺$l生疼，體內真氣一陣亂竄。\n" NOR, HIB),
        append_color(BLU "你只覺得$l處劇痛，連帶著體內真氣一陣外泄。\n" NOR, BLU),
});

string *guard_msg = ({
        append_color(CYN "$N注視著$n的行動，企圖尋找機會出手。\n" NOR, CYN),
        append_color(CYN "$N正盯著$n的一舉一動，隨時準備發動攻勢。\n" NOR, CYN),
        append_color(CYN "$N緩緩地移動腳步，想要找出$n的破綻。\n" NOR, CYN),
        append_color(CYN "$N目不轉睛地盯著$n的動作，尋找進攻的最佳時機。\n" NOR, CYN),
        append_color(CYN "$N慢慢地移動著腳步，伺機出手。\n" NOR, CYN),
});

string *catch_hunt_human_msg = ({
        append_color(HIW "$N和$n仇人相見份外眼紅，立刻打了起來！\n" NOR, HIW),
        append_color(HIW "$N對著$n大喝：「可惡，又是你！」\n" NOR, HIW),
        append_color(HIW "$N和$n一碰面，二話不說就打了起來！\n" NOR, HIW),
        append_color(HIW "$N一眼瞥見$n，「哼」的一聲沖了過來！\n" NOR, HIW),
        append_color(HIW "$N一見到$n，愣了一愣，大叫：「我宰了你！」\n" NOR, HIW),
        append_color(HIW "$N喝道：「$n，我們的帳還沒算完，看招！」\n" NOR, HIW),
        append_color(HIW "$N喝道：「$n，看招！」\n" NOR, HIW),
});

string *catch_hunt_beast_msg = ({
        append_color(HIW "$N怒吼一聲，撲了過來攻擊$n！\n" NOR, HIW),
        append_color(HIW "$N對著$n大吼，想殺死$n！\n" NOR, HIW),
        append_color(HIW "$N發出連串低吼，突然暴起攻擊$n！\n" NOR, HIW),
});

string *catch_hunt_bird_msg = ({
        append_color(HIW "$N對著$n一聲怒鳴，飛沖了過來！\n" NOR, HIW),
        append_color(HIW "$N怒鳴幾聲，突然暴起攻擊$n！\n" NOR, HIW),
        append_color(HIW "$N一聲銳鳴，猛然向$n發動攻擊！\n" NOR, HIW),
});

string *catch_hunt_msg = ({
        append_color(HIW "$N和$n仇人相見分外眼紅，立刻打了起來！\n" NOR, HIW),
        append_color(HIW "$N對著$n大喝：「可惡，又是你！」\n" NOR, HIW),
        append_color(HIW "$N和$n一碰面，二話不說就打了起來！\n" NOR, HIW),
        append_color(HIW "$N一眼瞥見$n，「哼」的一聲沖了過來！\n" NOR, HIW),
        append_color(HIW "$N一見到$n，愣了一愣，大叫：「我宰了你！」\n" NOR, HIW),
        append_color(HIW "$N喝道：「$n，我們的帳還沒算完，看招！」\n" NOR, HIW),
        append_color(HIW "$N喝道：「$n，看招！」\n" NOR, HIW),
});

string *winner_msg = ({
        append_color(CYN "\n$N哈哈大笑，說道：承讓了！\n\n" NOR, CYN),
        append_color(CYN "\n$N雙手一拱，笑著說道：承讓！\n\n" NOR, CYN),
        append_color(CYN "\n$N勝了這招，向後躍開三尺，笑道：承讓！\n\n" NOR, CYN),
        append_color(CYN "\n$N雙手一拱，笑著說道：知道我的利害了吧！\n\n" NOR, CYN),
        append_color(CYN "\n$N勝了這招，向後躍開三尺，嘆道：真是拔劍四顧心茫然！\n\n" NOR, CYN),
        append_color(CYN "\n$n向後退了幾步，說道：這場比試算我輸了，下回看我怎麼收拾你！\n\n" NOR, CYN),
        append_color(CYN "\n$n向後一縱，恨恨地說道：君子報仇，十年不晚！\n\n" NOR, CYN),
        append_color(CYN "\n$n臉色一寒，說道：算了算了，就當是我讓你吧！\n\n" NOR, CYN),
        append_color(CYN "\n$n縱聲而笑，叫道：“你運氣好！你運氣好！”一面身子向後跳開。\n\n" NOR, CYN),
        append_color(CYN "\n$n臉色微變，說道：佩服，佩服！\n\n" NOR, CYN),
        append_color(CYN "\n$n向後退了幾步，說道：這場比試算我輸了，佩服，佩服！\n\n" NOR, CYN),
        append_color(CYN "\n$n向後一縱，躬身做揖說道：閣下武藝不凡，果然高明！\n\n" NOR, CYN),
});

string *weapon_parry_throwing = ({
        append_color(HIR "$n手中$v一揮，將$w打飛。\n" NOR, HIR),
        append_color(HIR "$n將$v在身前一橫，$w打在$v上，$n手上覺得一陣酸麻。\n" NOR, HIR),
        append_color(HIR "$n猛力揮動手中$v，將$w打得無影無蹤。\n" NOR, HIY),
});

string *unarm_parry_throwing = ({
        append_color(HIR "$n長袖一卷，將$w收入囊中。\n" NOR, HIY),
        append_color(HIR "$n伸出兩個手指輕輕一夾，便將$w接在手中。\n" NOR, HIY),
        append_color(HIR "$n脫下一只鞋子對準$w一撈，$w掉入$n的鞋中。\n" NOR, HIY),
});

string *weapon_parry_sixmai = ({
        append_color(HIR "$n舞動$v，將自身罩在一道光幕之中，擋住了$N六脈神劍的攻勢。\n" NOR, HIY),
        append_color(HIR "$n揮動$v，接住了$N六脈神劍的無形劍氣。\n" NOR, HIY),
        append_color(HIR "$n揮舞$v，六脈神劍的無形劍氣盡數打在$v上。\n" NOR, HIY),
});

string *unarm_parry_sixmai = ({
        append_color(HIR "$n運起內力，衣袖鼓風而前，接住了$N的六脈神劍，袖子卻被無形劍氣切下一片。\n" NOR, HIY),
        append_color(HIR "$n在身前布起一道氣牆，只聽「嗤」，「嗤」之聲，$N的劍氣盡數打在氣牆上。\n" NOR, HIY),
        append_color(HIR "$n將內力盡數布在$l處，接下了$N的六脈神劍，但$l處的表皮卻已燒焦。\n" NOR, HIY),
});

string *star_move_weapon = ({
        append_color(HIR "只見$n長袖在$N的$w上一帶一送，$w在空中硬生生轉了個灣，奔向$P自己的$l。\n" NOR, HIY),
        append_color(HIR "$n使一招鬥轉星移，$N的$w竟然倒轉過來，奔向$P自己的$l。\n" NOR, HIY),
});

string *star_move_unarm = ({
        append_color(HIR "$n運用鬥轉星移，暗中將$N的內力盡數送了回去，$N只覺得$l處一陣劇疼。\n" NOR, HIY),
        append_color(HIR "$n的長袖一帶一送，$N的這一招竟然打到了自己身上。\n" NOR, HIY),
});

string *qiankun_move_weapon = ({
        append_color(HIR "只見$n長袖在$N的$w上一帶一送，$w在空中硬生生轉了個灣，奔向$P自己的$l。\n" NOR, HIY),
        append_color(HIR "$n使一招乾坤大挪移，$N的$w竟然倒轉過來，奔向$P自己的$l。\n" NOR, HIY),
});

string *qiankun_move_unarm = ({
        append_color(HIR "$n運用乾坤大挪移，暗中將$N的內力盡數送了回去，$N只覺得$l處一陣劇疼。\n" NOR, HIY),
        append_color(HIR "$n的長袖一帶一送，$N的這一招竟然打到了自己身上。\n" NOR, HIY),
});

string *counter_msg = ({
        append_color(HIR "$N全然不顧$n的攻擊，以快制快。\n" NOR, HIR),
        append_color(HIR "$N不求自保，奮力搶攻而上。\n" NOR, HIR),
});

// message after damage info
nosave string foo_before_hit = 0;
nosave string foo_after_hit = 0;
string query_bhinfo() { return foo_before_hit; }
string query_ahinfo() { return foo_after_hit; }
void clear_bhinfo() { foo_before_hit = 0; }
void clear_ahinfo() { foo_after_hit = 0; }
protected void quest_kill(object killer, object victim);

void create()
{
        int pd, pm;

        seteuid(getuid());
        set("channel_id", "戰鬥精靈");

        if( undefinedp(pd = CONFIG_D->query_int("max pk perday")) )
                pd = DEFAULT_MAX_PK_PERDAY;

        if( undefinedp(pm = CONFIG_D->query_int("max pk perman")) )
                pm = DEFAULT_MAX_PK_PERMAN;

        set("pk_perday", pd);
        set("pk_perman", pm);
}

void set_bhinfo(string msg)
{
        if( !foo_before_hit ) {
                foo_before_hit = msg;
                return;
        }
        foo_before_hit += msg;
}

void set_ahinfo(string msg)
{
        if( !foo_after_hit ) {
                foo_after_hit = msg;
                return;
        }
        foo_after_hit += msg;
}

string damage_msg(int damage, string type)
{
        string str;

        if( damage == 0 )
                return "結果沒有造成任何傷害。\n";

        switch( type )
        {
        case "擦傷":
        case "拉傷":
        case "割傷":
                if( damage < 100 ) return "結果只是輕輕地劃破$p的皮肉。\n"; else
                if( damage < 200 ) return "結果在$p$l劃出一道細長的血痕。\n"; else
                if( damage < 400 ) return "結果「嗤」地一聲，$w已在$p$l劃出一道傷口！\n"; else
                if( damage < 600 ) return "結果「嗤」地一聲，$w已在$p$l劃出一道血淋淋的傷口！\n"; else
                if( damage < 1000 )return "結果「嗤」地一聲，$w已在$p$l劃出一道又長又深的傷口，濺得$N滿臉鮮血！\n"; else
                                   return "結果只聽見$n一聲慘嚎，$w已在$p$l劃出一道深及見骨的可怕傷口！\n";
                break;
        case "刺傷":
                if( damage < 100 ) return "結果只是輕輕地刺破$p的皮肉。\n"; else
                if( damage < 200 ) return "結果在$p$l刺出一個創口。\n"; else
                if( damage < 400 ) return "結果「噗」地一聲，$w已刺入了$n$l寸許！\n"; else
                if( damage < 800 ) return "結果「噗」地一聲，$w已刺進$n的$l，使$p不由自主地退了幾步！\n"; else
                if( damage < 1000 )return "結果「噗嗤」地一聲，$w已在$p$l刺出一個血肉□糊的血窟窿！\n"; else
                                   return "結果只聽見$n一聲慘嚎，$w已在$p的$l對穿而出，鮮血濺得滿地！\n";
                break;
        case "踢傷":
                if( damage < 50 )  return  "結果只是輕輕地踢到，比拍蒼蠅稍微重了點。\n";else
                if( damage < 100 ) return "結果在$n的$l造成一處瘀青。\n";else
                if( damage < 200 ) return "結果一踢命中，$n的$l登時腫了一塊老高！\n";else
                if( damage < 400 ) return "結果一踢命中，$n悶哼了一聲顯然吃了不小的虧！\n";else
                if( damage < 600 ) return "結果「砰」地一聲，$n退了兩步！\n";else
                if( damage < 800 ) return "結果這一下「砰」地一聲踢得$n連退了好幾步，差一點摔倒！\n";else
                if( damage < 1000 )return "結果重重地踢中，$n「哇」地一聲吐出一口鮮血！\n";else
                                   return "結果只聽見「砰」地一聲巨響，$n像一捆稻草般飛了出去！！\n";
                break;
        case "瘀傷":
        case "震傷":
                if( damage < 50 )  return "結果只是輕輕地碰到，比拍蒼蠅稍微重了點。\n"; else
                if( damage < 100 ) return "結果在$p的$l造成一處瘀青。\n"; else
                if( damage < 200 ) return "結果一擊命中，$n的$l登時腫了一塊老高！\n"; else
                if( damage < 400 ) return "結果一擊命中，$n悶哼了一聲顯然吃了不小的虧！\n"; else
                if( damage < 600 ) return "結果「砰」地一聲，$n退了兩步！\n"; else
                if( damage < 800 ) return "結果這一下「砰」地一聲打得$n連退了好幾步，差一點摔倒！\n"; else
                if( damage < 1000 )return "結果重重地擊中，$n「哇」地一聲吐出一口鮮血！\n"; else
                                   return "結果只聽見「砰」地一聲巨響，$n像一捆稻草般飛了出去！\n";
                break;
        case "抓傷":
                if( damage < 50 )  return "結果只是輕輕地抓到，比抓癢稍微重了點。\n";else
                if( damage < 100 ) return "結果在$p的$l抓出幾條血痕。\n";else
                if( damage < 200 ) return "結果一抓命中，$n的$l被抓得鮮血飛濺！\n";else
                if( damage < 400 ) return "結果「嗤」地一聲，$l被抓得深可見骨！！\n";else
                if( damage < 600 ) return "結果一抓命中，$n的$l被抓得血肉橫飛！！！\n";else
                if( damage < 800 ) return "結果這一下「嗤」地一聲抓得$n連晃好幾下，差一點摔倒！\n";else
                if( damage < 1000 )return "結果$n哀號一聲，$l被抓得筋斷骨折！！\n";else
                                   return "結果只聽見$n一聲慘嚎，$l被抓出五個血窟窿！鮮血濺得滿地！！\n";
                break;
        case "內傷":
                if( damage < 50 )  return "結果只是把$n打得退了半步，毫發無損。\n"; else
                if( damage < 100 ) return "結果$n痛哼一聲，在$p的$l造成一處瘀傷。\n"; else
                if( damage < 200 ) return "結果一擊命中，把$n打得痛得彎下腰去！\n"; else
                if( damage < 400 ) return "結果$n悶哼了一聲，臉上一陣青一陣白，顯然受了點內傷！\n"; else
                if( damage < 600 ) return "結果$n臉色一下變得慘白，昏昏沉沉接連退了好幾步！\n"; else
                if( damage < 800 ) return "結果重重地擊中，$n「哇」地一聲吐出一口鮮血！\n"; else
                if( damage < 1000 )return "結果「轟」地一聲，$n全身氣血倒流，口中鮮血狂噴而出！\n"; else
                                   return "結果只聽見幾聲喀喀輕響，$n一聲慘叫，像灘軟泥般塌了下去！\n";
                break;
        case "點穴":
                if( damage < 60 )  return "結果只是輕輕的碰到$n的$l，根本沒有點到穴道。\n"; else
                if( damage < 100 ) return "結果$n痛哼一聲，在$p的$l造成一處淤青。\n"; else
                if( damage < 200 ) return "結果一擊命中，$N點中了$n$l上的穴道，$n只覺一陣麻木！\n"; else
                if( damage < 400 ) return "結果$n悶哼了一聲，臉上一陣青一陣白，登時覺得$l麻木！\n"; else
                if( damage < 800 ) return "結果$n臉色一下變得慘白，被$N點中$l的穴道,一陣疼痛遍布整個$l！\n"; else
                if( damage < 1000 )return "結果$n一聲大叫，$l的穴道被點中,疼痛直入心肺！\n"; else
                                   return "結果只聽見$n一聲慘叫，一陣劇痛夾雜著麻癢遊遍全身，跟著直挺挺的倒了下去！\n";
                break;
        case "抽傷":
        case "鞭傷":
                if( damage < 50 )  return "結果只是在$n的皮肉上碰了碰，好象只蹭破點皮。\n"; else
                if( damage < 100 ) return "結果在$n$l抽出一道輕微的紫痕。\n"; else
                if( damage < 200 ) return "結果「啪」地一聲在$n$l抽出一道長長的血痕！\n"; else
                if( damage < 400 ) return "結果只聽「啪」地一聲，$n連晃好幾下，差一點摔倒！\n"; else
                if (damage < 600)  return "結果$p的$l上被抽了一道血淋淋的創口！\n"; else
                if( damage < 800 ) return "結果只聽「啪」地一聲，$n的$l被抽得皮開肉綻，痛得$p咬牙切齒！\n"; else
                if( damage < 1000 )return "結果「啪」地一聲爆響！這一下好厲害，只抽得$n皮開肉綻，血花飛濺！\n"; else
                                   return "結果只聽見$n一聲慘嚎，$w重重地抽上了$p的$l，$n頓時血肉橫飛，十命斷了九條！\n";
                break;
        case "反震傷":
        case "反彈傷":
                if( damage < 50 )  return "結果$N受到$n的內力反震，悶哼一聲。\n"; else
                if( damage < 100 ) return "結果$N被$n的反震得氣血翻騰，大驚失色。\n"; else
                if( damage < 200 ) return "結果$N被$n的反震得站立不穩，搖搖晃晃。\n"; else
                if( damage < 400 ) return "結果$N被$n以內力反震，「嘿」地一聲退了兩步。\n"; else
                if( damage < 600 ) return "結果$N被$n的震得反彈回來的力量震得半身發麻。\n"; else
                if( damage < 800 ) return "結果$N被$n的內力反震，胸口有如受到一記重擊，連退了五六步！\n"; else
                if( damage < 1000 )return "結果$N被$n內力反震，眼前一黑，身子向後飛出丈許！\n"; else
                                   return "結果$N被$n內力反震，眼前一黑，狂吐鮮血，身子象斷了線的風箏向後飛去！\n";
                break;
        case "砸傷":
        case "挫傷":
                if( damage < 50 )  return "結果只是輕輕地碰到，像是給$n搔了一下癢。\n"; else
                if( damage < 100 ) return "結果在$n的$l砸出一個小臌包。\n"; else
                if( damage < 200 ) return "結果$N這一下砸個正著，$n的$l登時腫了一塊老高！\n"; else
                if( damage < 400 ) return "結果$N這一下砸個正著，$n悶哼一聲顯然吃了不小的虧！\n"; else
                if( damage < 600 ) return "結果只聽「砰」地一聲，$n疼得連腰都彎了下來！\n"; else
                if( damage < 800 ) return "結果這一下「轟」地一聲砸得$n眼冒金星，差一點摔倒！\n"; else
                if( damage < 1000 )return "結果重重地砸中，$n眼前一黑，「哇」地一聲吐出一口鮮血！\n"; else
                                   return "結果只聽見「轟」地一聲巨響，$n被砸得血肉模糊，慘不忍睹！\n";
                break;
        case "咬傷":
                if( damage < 100 ) return "結果只是輕輕地蹭了一下$p的皮肉。\n";else
                if( damage < 200 ) return "結果在$p$l咬出一排牙印。\n";else
                if( damage < 400 ) return "結果$p被咬下一片肉來！\n";else
                if( damage < 800 ) return "結果$p連皮帶肉被咬下一大塊！\n";else
                if( damage < 1000 )return "結果在$p的身上咬下來血肉模糊的一大塊$l肉！\n";else
                                   return "結果只聽見$n一聲慘嚎，$p的$l上的肉被一口咬掉，露出骨頭！！\n";
                break;
        case "灼傷":
        case "燒傷":
                if( damage < 100 ) return "結果只是把$p的$l燙了一下。\n";else
                if( damage < 200 ) return "結果$p的$l被$w灼炙得起了個小皰。\n";else
                if( damage < 400 ) return "結果$p的$l被$w燒得紅腫疼痛，痛得不住冒汗咬牙！\n";else
                if( damage < 800 ) return "結果「嗤」一聲輕響，$p祗覺$l上一片熱痛，已被$w燒成了暗紅色，猶如焦炭！\n";else
                if( damage < 1000 )return "結果「嗤嗤」一陣聲響過去，$n神色痛楚難當，$l被$w燒得一片焦黑，青煙直冒！\n";else
                                   return "結果只聽見$n長聲慘呼，在地上不住打滾，$l已被$w燒得皮肉盡爛，焦臭四溢！！\n";
                break;
        case "凍傷":
                if( damage < 100 ) return "結果$p祗是覺得$l有些冷颼颼地，還挺涼快的。\n";else
                if( damage < 200 ) return "結果$p的$l被凍得有些麻木。\n";else
                if( damage < 400 ) return "結果$p機伶伶地打了個寒顫！\n";else
                if( damage < 800 ) return "結果$p臉色一變，神情有些僵硬，身子也冷得瑟瑟發抖！\n";else
                if( damage < 1000 )return "結果$p身子打顫，臉色蒼白，嘴唇凍得發紫，牙關格格直響！\n";else
                                   return "結果祗聽見$n聲音一啞，臉上慘白得沒半分血色，顫抖不休，渾身血液似乎都結成了冰！！\n";
                break;
        default:
                if( !type) type = "傷害";
                if( damage < 50 )  str = "結果只是勉強造成一處輕微"; else
                if( damage < 100 ) str = "結果造成輕微的"; else
                if( damage < 200 ) str = "結果造成一處"; else
                if( damage < 400 ) str = "造成一處嚴重"; else
                if( damage < 500 ) str = "結果造成頗為嚴重的"; else
                if( damage < 600 ) str = "結果造成相當嚴重的"; else
                if( damage < 800 ) str = "結果造成十分嚴重的"; else
                if( damage < 1000 )str = "結果造成極其嚴重的"; else
                                   str = "結果造成非常可怕的嚴重";
                return str + type + "！\n";
        }
}

varargs string eff_status_msg(int ratio, int dam_type) 
{
        if( !dam_type ) dam_type = 1;
        if( ratio==100 ) return HIG "看來身上並無絲毫傷痕。" NOR;
        if( ratio > 95 ) return HIG "似乎只受了點輕傷，但無傷大體。" NOR;
        if( ratio > 90 ) {
                if (dam_type == 3)
                        return HIY "看來有些萎靡，好像精力受損。" NOR;
                else if (dam_type == 2)
                        return HIY "精神似乎受了些損傷，表情有點僵硬。" NOR;
                else    return HIY "可能受了幾處皮肉傷。" NOR;
        }
        if( ratio > 80 ) return HIY "受了幾處創傷，似乎並不礙事。" NOR;
        if( ratio > 60 ) {
                if (dam_type == 3)
                        return HIY "骨軟筋麻，涕淚交流。" NOR;
                else if (dam_type == 2)
                        return HIY "神情慘然，耳鼻中竟然有鮮血滲出。" NOR;
                else    return HIY "身上受傷不輕，正在流著血。" NOR;
        }
        if( ratio > 40 ) {
                if (dam_type == 3)
                        return HIY "面部抽搐不止，已經不能自己。" NOR;
                else    return HIR "流血不止，動作散亂，已經在走下坡路了。" NOR;
        }
        if( ratio > 30 ) return HIR "傷痕累累，正在勉力支撐著不倒下去。" NOR;
        if( ratio > 20 ) return HIR "遍體鱗傷，只剩下最後一口氣了。" NOR;
        if( ratio > 10 ) return RED "渾身浴血，就要倒在地上。" NOR;
        if( ratio > 5  ) return RED "瞳孔放大，已經奄奄一息，命在旦夕了。" NOR;
        return RED "如風中殘燭，隨時都可能斷氣。" NOR;
}

varargs string status_msg(int ratio, int dam_type) 
{
        if( !dam_type ) dam_type = 1;
        if( ratio==100 ) return HIG "精力充沛，神完氣足，" NOR;
        if( ratio > 95 ) return HIG "似乎有些疲憊，但是仍然十分有活力，" NOR;
        if( ratio > 90 ) return HIY "看起來可能有些不濟，" NOR;
        if( ratio > 80 ) {
                if (dam_type == 3)
                        return HIY "精力有點不足，但仍攻守從容，" NOR;
                else if (dam_type == 2)
                        return HIY "神情有些恍惚，但仍應付自如，" NOR;
                else    return HIY "動作有點不太靈光，但仍有條不紊，" NOR;
        }
        if( ratio > 60 ) {
                if (dam_type == 3)
                        return HIY "行動雖然無礙，精力明顯跟不上了，" NOR;
                else if (dam_type == 2)
                        return HIY "反應開始遲緩，雙目無神，" NOR;
                else    return HIY "氣喘噓噓，臉色慘白，" NOR;
        }
        if( ratio > 40 ) {
                if (dam_type == 3)
                        return HIR "精力渙散，似乎對痛癢都失去知覺，" NOR;
                else if (dam_type == 2)
                        return HIR "眼光迷離，六神無主，" NOR;
                else    return HIR "似乎十分疲憊，看來需要好好休息了，" NOR;
        }
        if( ratio > 30 ) return HIR "頭重腳輕，正在勉力支撐著不倒下去，" NOR;
        if( ratio > 20 ) {
                if (dam_type == 3)
                        return HIR "看來已經麻木不仁了，" NOR;
                else if (dam_type == 2)
                        return HIR "看起來已經魂不守舍了，" NOR;
                else    return HIR "看起來已經力不從心了，" NOR;
        }
        if( ratio > 10 ) return RED "搖頭晃腦、歪歪斜斜，瀕于暈倒，" NOR;
        return RED "已經陷入半昏迷狀態，神智全失，" NOR;
}

varargs mixed report_status(object ob, int effective)
{
        int eff_ratio = 100;
        int ratio = 100;
        int k_stat, g_stat, s_stat;
        int d_type = 1;
        int e_type = 1;
        string *msg = ({RED,HIR,HIY,HIG,HIG});
        string str;
 
        if( !ob || !query("max_qi", ob) || !query("max_jing", ob) ) return;
               
        k_stat = (int) query("qi", ob) * 100 / (int)query("max_qi", ob);
        //s_stat = (int) query("sen", ob) * 100 / (int)query("max_sen", ob);
        g_stat = (int) query("jing", ob) * 100 / (int)query("max_jing", ob);
               
        if (ratio > k_stat ) {
                ratio =  k_stat;
        }
        /*
        if (ratio > s_stat ) {
                ratio =  s_stat;
                d_type = 2;
        }
        */
        if (ratio > g_stat ) {
                ratio =  g_stat;
                d_type = 3;
        }
        
        k_stat = (int) query("eff_qi", ob) * 100 / (int)query("max_qi", ob);
        //s_stat = (int) query("eff_sen", ob) * 100 / (int)query("max_sen", ob);
        g_stat = (int) query("eff_jing", ob) * 100 / (int)query("max_jing", ob);
        
        if (eff_ratio > k_stat ) {
                eff_ratio =  k_stat;
        }
        /*
        if (eff_ratio > s_stat ) {
                eff_ratio =  s_stat;
                e_type = 2;
        }
        */
        if (eff_ratio > g_stat ) {
                eff_ratio =  g_stat;
                e_type = 3;
        }
        
        str = "( $N" + status_msg(ratio, d_type) + eff_status_msg(eff_ratio, e_type) + " )\n";
        if( !effective )
                message_vision(str, ob);
        else
                return str;
}

#ifdef REDUCE_PVP_DAMAGE
int reduce_damage(object attacker, object victim, int damage)
{
        if( objectp(attacker) && objectp(victim) &&
            playerp(attacker) && playerp(victim) ) {
                damage = damage * PVP_DAMAGE_SCALE / 100;
        }

        return damage;
}

int reduce_wound(object attacker, object victim, int wound)
{
        if( objectp(attacker) && objectp(victim) &&
            playerp(attacker) && playerp(victim) ) {
                wound = wound * PVP_WOUND_SCALE / 100;
        }

        return wound;
}
#endif

int valid_power(object ob, int combat_exp)
{
        int t;
        
        t = query("reborn/times", ob);

        if( t >= 1 )
                combat_exp += 10000000000/2;
        
        if( t >= 2 )
                combat_exp += 20000000000/2;
        
        if( t >= 3 )
                combat_exp += 50000000000/2;
                
        return combat_exp/1000;
}

// This function calculates the combined skill/combat_exp power of a certain
// skill. This value is used for A/(A+B) probability use.
varargs mixed skill_power(object ob, string skill, int usage, int delta)
{
        int level, power;
        mapping dbase;
        mapping temp;
        mapping fight;
        mapping apply;
        int percent = 0;
        int bonus,buff;
        int ratio = 0;
        string martial_skill = ob->query_skill_mapped(skill);

        if( !living(ob) ) return 0; // 暈倒時 power 永遠等于零
        if( ob->over_encumbranced() )    return 0; // 負重小于零時 power 永遠等于零
        
        if( userp(ob) && ob->is_ghost() )
                return 0;  // 鬼魂的 power 永遠等于零
                
        level = ob->query_skill(skill);

        dbase = ob->query_entire_dbase();
        temp = ob->query_entire_temp_dbase();
        if( temp ) 
        {
                apply = temp["apply"];
                fight = temp["fight"];
        }

        switch( usage ) {
        case SKILL_USAGE_ATTACK:
                if( apply )  {
                        level += apply[skill];
                        level += apply["attack"];
                }
                if( query("jingmai/finish", ob) )
                        buff = ZHOUTIAN_D->query_jingmai_effect("attack"); // 經脈沖穴效果 1640
                else
                        buff = query("jingmai/attack", ob);     
                //bonus = query_temp("bonus/attack", ob);         // This bonus is ONE_SHOT_BONUS.
                //set_temp("bonus/attack", 0, ob);                // after this calculation, release bonus.s
                break;
        case SKILL_USAGE_DEFENSE:
                if( apply ) {
                        level += apply[skill];
                        level += apply["defense"];
                }
                if( query("jingmai/finish", ob) )
                        buff = ZHOUTIAN_D->query_jingmai_effect("defense"); // 經脈沖穴效果 1140
                else
                        buff = query("jingmai/defense", ob);     
                //bonus = query_temp("bonus/defense", ob);        // This bonus is ONE_SHOT_BONUS.
                //set_temp("bonus/defense", 0, ob);               // after this calculation, release bonus.s
                break;
        case SKILL_USAGE_ABSORB:
                level += apply["iron-cloth"];
                //bonus = query_temp("bonus/iron-cloth", ob);        // This bonus is ONE_SHOT_BONUS.
                //set_temp("bonus/iron-cloth", 0, ob);               // after this calculation, release bonus.s
                if( !level )
                        return 0;
                break;
        }
        if( delta ) level += delta;

        if( !level || level < 1 ) 
        {
                power = valid_power(ob, query("combat_exp", ob)) / 2;

                if( ob->is_weak() ) power /= 2; // 虛弱 power 減半
                return  power;
        }

        power = level * level * level / 100;
        //power+= bonus * bonus * bonus / 100;
        power+= buff * buff * buff / 100;

        if( usage == SKILL_USAGE_ATTACK ) 
        {
                power = power / 30 * dbase["str"];
                if( fight && ob->is_fighting() )
                         power += power / 100 * fight["attack"];
        } 
        else 
        {
                power = power / 30 * dbase["dex"];
                if( fight && ob->is_fighting() )
                         power += power / 100 * fight[skill];
        }
        
        power += valid_power(ob, dbase["combat_exp"]);
        
        
        // 逍遙遊提高命中及回避
        if( ob->query_skill("xiaoyao-you", 1) >= 100 )
        {
                percent = ob->query_skill("xiaoyao-you", 1) / 100; // 每100級提升一個百分點
                if( ratio < percent ) ratio = percent;
        }

        // 昆侖無極提高命中
        if( usage == SKILL_USAGE_ATTACK && ob->query_skill("kunlun-wuji", 1) >= 50 && 
            skill == "sword" && martial_skill == "qiankun-jian" )
        {
                percent = ob->query_skill("kunlun-wuji", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        // 奇門玄術提高命中
        if( usage == SKILL_USAGE_ATTACK && ob->query_skill("qimen-xuanshu", 1) >= 50 &&
            skill == "finger" && martial_skill == "tanzhi-shentong" )
        {
                percent = ob->query_skill("qimen-xuanshu", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        // 血影大法提高命中
        if( usage == SKILL_USAGE_ATTACK && ob->query_skill("xueying-dafa", 1) >= 50 && 
            skill == "blade" && martial_skill == "xuedao-daofa" )
        {
                percent = ob->query_skill("xueying-dafa", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        // 靜心提高命中
        if( usage == SKILL_USAGE_ATTACK && ob->query_skill("jingxin", 1) >= 50 && 
            ((skill == "sword" && martial_skill == "huifeng-jian")
                || (skill == "strike" && martial_skill == "piaoxue-zhang")) )
        {
                percent = ob->query_skill("jingxin", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        // 劍意提高命中
        if( usage == SKILL_USAGE_ATTACK && ob->query_skill("jianyi", 1) >= 50 &&
            skill == "sword" && (martial_skill == "huashan-sword" || martial_skill == "lonely-sword") )
        {
                percent = ob->query_skill("jianyi", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        // 劍意提高防御
        if( usage == SKILL_USAGE_DEFENSE && ob->query_skill("jianyi", 1) >= 50 )
        {
                percent = ob->query_skill("jianyi", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        // 天威正氣命中
        if( usage == SKILL_USAGE_ATTACK && ob->query_skill("tianwei-zhengqi", 1) >= 50 &&
            ((skill == "sword" && martial_skill == "taiji-jian")
                || (skill == "cuff" && martial_skill == "taiji-quan")) )
        {
                percent = ob->query_skill("tianwei-zhengqi", 1) / 50;
                if( ratio < percent ) ratio = percent;
        }

        power += power * ratio / 100;      
        
        // 陣法防御效果
        if( (usage == SKILL_USAGE_DEFENSE) && ob->in_array() ) 
        {
                int n;
        
                if( (n =  ob->query_array_level()/100) )
                {
                        power += power * n / 100;
                }
        }

        // 移形換位提升戰鬥回避率15%
        if( usage == SKILL_USAGE_DEFENSE && query("special_skill/yixing", ob) )
                power += power * 15 / 100;

        // 逆轉乾坤提升10%命中
        if( usage == SKILL_USAGE_ATTACK && query("special_skill/nizhuan", ob) )
                power += power * 10 / 100;

        // 流星慧眼提升30%命中
        if( usage == SKILL_USAGE_ATTACK && query("special_skill/huiyan", ob) )
                power += power * 30 / 100;
        
        // 元神提升
        if( query("yuanshen/status", ob))
                power += power * query("yuanshen/status", ob) / 100;
	
        // 虛弱狀況減半
        if( ob->is_weak() ) power /= 2;
        
        // 手部受傷，使用unarmed，減半
        /*
        if( (skill == "unarmed") && (ob->query_limb_wound("右手") || 
            ob->query_limb_wound("左手")) ) 
                power /= 2;
        */
        return power;
}

varargs mapping query_action(object me, int flag)
{
        mixed act,l_act;
        
        //me->reset_action();
        act = query("actions", me); // 此人的右手 action
        if( functionp(act) ) act = evaluate(act, me);
        if( !mapp(act) )
        {
                me->reset_action();
                act = query("actions", me);
                if( functionp(act) ) act = evaluate(act, me);
                if( !mapp(act) ) 
                {
                        CHANNEL_D->do_channel( this_object(), "sys",
                                        sprintf("%s(%s): bad action = %O",
                                        me->name(1), me->query_id(1), 
                                        query("actions", me)));
                        return 0;
                }
        }
        
        if( flag && flag == 1 ) // 指定右手
        {
                set_temp("hand_flag", 0, me);
                return act;
        }
                
        l_act = query("second_actions", me); // 此人的左手 action 
        if( functionp(l_act) ) l_act = evaluate(l_act, me);
        if( !mapp(l_act) || !sizeof(l_act) )
        {
                set_temp("hand_flag", 0, me);
                return act;
        }

        if( flag && flag == 2 ) // 指定左手
        {
                set_temp("hand_flag", 1, me);
                return l_act;
        }

        // 什麼因素決定此人用左手攻擊還是用右手攻擊? 目前沒有,暫用隨機數決定.
        if( random(100) < 55 ) // 右手的可能性大一些.
        {
                set_temp("hand_flag", 0, me);
                return act;
        }
        else
        {
                set_temp("hand_flag", 1, me);
                return l_act;
        }
}

// do_attack()
//
// Perform an attack action. This function is called by fight() or as an
// interface for some special utilize in quests.
//
varargs int do_attack(object me, object victim, object weapon, int attack_type, int flag)
{
        mapping my, your;
        mapping my_temp, your_temp;
        mapping fight;
        mapping prepare, action;
        string limb, *limbs;
        string attack_skill, martial_skill, force_skill, defense_skill;
        string parry_msg;
        mixed foo;

        int has_weapon;
        int delta;
        int ap, dp, pp;
        int damage, damage_bonus;
        int armor;
        int wounded;
        int array_flag;
        int attack;
        int avoid;

        object second_weapon;
        object weapon2; // weapon of victim
        object ob;

        string result;
        string damage_info;
        string *att, *def;
        int hjs;

        if( !me || !victim ) return 1;
        if( !living(me) ) return 1;
        if( (userp(me) && me->is_ghost()) || (userp(victim) && victim->is_ghost()) ) return 1;
        
        // 葵花魔功 分身化影
        if( query_temp("hiding_kuihua", victim) ) return 1;
        if( query("no_fight", environment(me))){
                message_vision("$N和$n各自退了一步，收住了招。\n",
                               me, victim);
                me->remove_enemy(victim);
                victim->remove_enemy(me);
                return 0;
        }

        if( environment(me) != environment(victim) ) {
                me->remove_enemy(victim);
                victim->remove_enemy(me);
                return 0;
        }

        hjs = me->query_skill("huajia-su", 1);
        my = copy(me->query_entire_dbase());
        your = copy(victim->query_entire_dbase());
        if( !(my_temp = copy(me->query_entire_temp_dbase())) )
                my_temp = allocate_mapping(5);
        if( !(your_temp = copy(victim->query_entire_temp_dbase())) )
                your_temp = allocate_mapping(5);
        //
        // (0) Choose skills.
        //
        prepare = me->query_skill_prepare();
        if( !prepare ) prepare = ([]);
        
        if( !objectp(weapon) ) weapon = query_temp("weapon", me); // 右手
        second_weapon = query_temp("secondary_weapon", me); // 左手
        
        if( objectp(weapon) ) attack_skill = query("skill_type", weapon);
        else if(  sizeof(prepare) == 0) attack_skill = "unarmed";
        else if(  sizeof(prepare) == 1) attack_skill = (keys(prepare))[0];
        else if(  sizeof(prepare) == 2) attack_skill = (keys(prepare))[query_temp("action_flag", me)];

        if( attack_skill == "pin" )
                attack_skill = "sword";

        //
        // (1) Find out what action the offenser will take.
        //
        action = query_action(me, flag); // 選擇左手還是右手攻擊
        if( !action ) return 0;

        if( query_temp("hand_flag", me) )  // 調整'當前兵器' weapon
                weapon = second_weapon;

        has_weapon = objectp(weapon) || objectp(query_temp("armor/hands", me)) || objectp(query_temp("armor/finger", me));
        
        if( stringp(query_temp("action_msg", me))){
                result="\n"+query_temp("action_msg", me)+action["action"]+"！\n";
                delete_temp("action_msg", me);
        } else if( query_temp("action_flag", me) == 0){
                result = "\n" + action["action"] + "！\n";
        } else
                result = WHT "\n$N攻勢凌厲無匹，瞬間又已攻出一招。\n" NOR + action["action"] + "！\n";
        //
        // (2) Prepare AP, DP for checking if hit.
        //
        if( martial_skill = me->query_skill_mapped(attack_skill) )
                limb = SKILL_D(martial_skill)->query_attack_limb(me, victim);
        else
                martial_skill = attack_skill;
                
        if( !limb ) {
                limbs=query("limbs", victim);
                if( !arrayp(limbs) ) {
                        limbs = ({ "身體" });
                        set("limbs", limbs, victim);
                }
                limb = limbs[random(sizeof(limbs))];
        }

        // 陣法防御
        if( victim->in_array() && victim->query_array_status() &&
            (random(100) < (victim->query_array_level() / 100 + 60))) {
                if( ((your["qi"] < your["max_qi"] * 2 / 5) ||
                    (your["jing"] < your["max_jing"] * 2 / 5)) &&
                    !ob->is_busy() && objectp(ob = victim->query_array_obstructor()) ) {
                        result = replace_string(result, "$l", limb);
                        if( objectp(weapon) )
                                result = replace_string(result, "$w", weapon->name());
                        else if( stringp(action["weapon"]) )
                                result = replace_string(result, "$w", action["weapon"]);
                        else if( attack_skill == "finger" || attack_skill == "hand" )
                                result = replace_string(result, "$w", "手指" );
                        else if( attack_skill == "strike" || attack_skill == "claw" )
                                result = replace_string(result, "$w", "手掌" );
                        else    result = replace_string(result, "$w", "拳頭" );

                        message_combatd(result, me, victim);
                        message_combatd(HIC BWHT "$N飛身移步，擋在了$n的身前。\n" NOR, ob, victim);
                        result = "";

                        victim = ob;
                        your = copy(ob->query_entire_dbase());
                        array_flag = 1;
                        attack_type = TYPE_QUICK;
                }
        }
        /*
         * 兩套技能系統，第一套是採用skill對應combat中數據，則skill中的dodge,parry為影響自己的防御數值
         * 第二套採用skill技能本身的寫法數據，則skill中的dodge,parry為影響對手防御的數值
         * 如果#define USE_SKILLS_COMBAT則為採用第一套，否則視為採用第二套，本遊戲採用第一套
         */
        fight = ([]);
#ifdef USE_SKILLS_COMBAT
        // 第一套
        if( att = SKILLS_D->skill_query_power(martial_skill) ) { // combat 數值
                fight["attack"] = to_int(att[ATTACK]);      // 攻擊時候增加自己的命中
                my_temp["fight"] = copy(fight);        
        } else {
#endif
        // 第二套
                if( intp(action["attack"]) )
                        fight["attack"] = action["attack"]; // 攻擊時候增加自己的命中
                my_temp["fight"] = copy(fight);
                fight = ([]);
                if( intp(action["dodge"]) )
                        fight["dodge"] = action["dodge"];   // 攻擊時候影響對手的躲閃
                if( intp(action["parry"]) )
                        fight["parry"] = action["parry"];   // 攻擊時候影響對手的招架
                your_temp["fight"] = copy(fight);
#ifdef USE_SKILLS_COMBAT
        }
#endif

        ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK, 0);
        if( ap < 1) ap = 1;

        if( sizeof(me->query_enemy()) > 1 )  // 敵人越多，命中降低
                ap = ap * 9 / (8 + sizeof(victim->query_enemy()));
        if( !me->visible(victim) ) ap /= 10;
        if( member_array(limb, danger_limbs) != -1 ) // 攻擊危險部位命中降低
                ap -= ap / 10;
        if( my["character"] == "陰險姦詐" )
                ap += ap * 20 / 100;

        if( victim->in_array() ) ap /= 2; // 陣法降低命中
        
        if( array_flag || query_temp("freeze", victim) ) dp = 0;          // 替人擋招只能招架或者在冰凍狀態躲閃為0
        else {
                defense_skill = victim->query_skill_mapped("dodge");
                                
#ifdef USE_SKILLS_COMBAT
                if( defense_skill && (def = SKILLS_D->skill_query_power(defense_skill)) ) { // combat 數值
                        fight = ([]);
                        fight["dodge"] = to_int(def[DODGE]);  // 防御時候的躲閃
                        your_temp["fight"] = copy(fight);
                }
#endif                
                dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE, 0);
                if( dp < 1 ) dp = 1;

                if( stringp(defense_skill) )
                        dp += dp / 100 * SKILL_D(defense_skill)->query_effect_dodge(me, victim);
                if( sizeof(victim->query_enemy()) > 1 )
                        dp = dp * 9 / (8 + sizeof(victim->query_enemy()));
                if( !victim->visible(me) ) dp /= 10;
                if( victim->is_busy() ) dp /= 3;
        }

        //
        // (3) Fight!
        //     Give us a chance of AP/(AP+DP) to "hit" our opponent. Since both
        //     AP and DP are greater than zero, so we always have chance to hit
        //     or be hit.
        //
        damage = 0;
        wounded = 0;
        damage_info = "";

        if( random(ap + dp) < dp ) {
                // Does the victim dodge this hit?
#if INSTALL_COMBAT_TEST
                if( wizardp(me) && query("env/combat_test", me) )
                        tell_object(me, HIY "【戰鬥精靈】：己方 AP：" + ap +
                                    "，DP：" + dp + "。\n" NOR);
                if( wizardp(victim) && query("env/combat_test", victim) )
                        tell_object(victim, HIC "【戰鬥精靈】：對方 AP：" + ap +
                                    "，DP：" + dp + "。\n" NOR);
#endif
                if( !defense_skill ) defense_skill = "dodge";
                result += SKILL_D(defense_skill)->query_dodge_msg(limb, victim);

                damage = RESULT_DODGE;
        } else {
        //
        //  (4) Check if the victim can parry this attack.
        //
                delta = 0;
                if( weapon2 = your_temp["weapon"] ) {
                        if( !weapon ) delta = 100;
                } else {
                        if( weapon ) delta = -100;
                }
                
                if( query_temp("freeze", victim) ) pp = 0;  // 冰凍狀態招架為0
                else {
                        defense_skill = victim->query_skill_mapped("parry");
                                                
#ifdef USE_SKILLS_COMBAT
                        if( defense_skill && (def = SKILLS_D->skill_query_power(defense_skill)) ) { // combat 數值
                                fight = ([]);
                                fight["parry"] = to_int(def[PARRY]);  // 防御時候的招架
                                your_temp["fight"] = copy(fight);
                        }
#endif                             
                        pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE, delta);
                        if( stringp(defense_skill) )
                                pp += pp / 100 * SKILL_D(defense_skill)->query_effect_parry(me, victim);
                        if( pp < 1 ) pp = 1;
                        if( sizeof(victim->query_enemy()) > 1 )
                                pp = pp * 9 / (8 + sizeof(victim->query_enemy()));
                        if( victim->is_busy() ) pp /= 3;
                }
                
                if( random(ap + pp) < pp ) {
#if INSTALL_COMBAT_TEST
                        if( wizardp(me) && query("env/combat_test", me) )
                                tell_object(me, HIY "【戰鬥精靈】：己方 AP：" + ap +
                                            "，PP：" + pp + "。\n" NOR);
                        if( wizardp(victim) && query("env/combat_test", victim) )
                                tell_object(victim, HIC "【戰鬥精靈】：對方 AP：" + ap +
                                            "，PP：" + pp + "。\n" NOR);
#endif
                        if( !defense_skill) defense_skill = "parry";
                        if( attack_skill == "throwing" && your["race"] ==  "人類" ) {
                                if( weapon2 )
                                        parry_msg = weapon_parry_throwing[random(sizeof(weapon_parry_throwing))];
                                else {
                                        parry_msg = unarm_parry_throwing[random(sizeof(unarm_parry_throwing))];
                                }
                        } else if( martial_skill == "six-finger" ) {
                                if( random(me->query_skill("six-finger", 1)) > victim->query_skill("force", 1)/2 ) {
                                        if( weapon2 ) {
                                                parry_msg = weapon_parry_sixmai[random(sizeof(weapon_parry_sixmai))];
                                                if( my["jiali"] > weapon2->weight() ) {
                                                        parry_msg = replace_string(parry_msg, "$v", weapon2->name());
                                                        weapon2->unequip();
                                                        weapon2->move(environment(victim));
                                                        set("consistence", 0, weapon2);
                                                        if( weapon2->is_item_make() ) {
                                                                parry_msg += HIW "$n" HIW "只覺得虎口劇震，兵器脫手而出！。\n" NOR;
                                                        } else {
                                                                parry_msg += HIW "只聽見「啪」地一聲，$n" HIW "手中的" + weapon2->name() +
                                                                             HIW "已被$N" HIW "的無形劍氣震為數截！\n" NOR;
                                                                set("name", "斷掉的"+query("name", weapon2), weapon2);
                                                                set("value", 0, weapon2);
                                                                set("weapon_prop", 0, weapon2);
                                                        }
                                                        victim->reset_action();
                                                }
                                        } else parry_msg = unarm_parry_sixmai[random(sizeof(unarm_parry_sixmai))];
                                } else  parry_msg = SKILL_D(defense_skill)->query_parry_msg(weapon2, victim);

                        } else if( defense_skill == "douzhuan-xingyi" || defense_skill == "qiankun-danuoyi" ) {
                                if( random(victim->query_skill(defense_skill, 1)) > me->query_skill("force", 1)/2 ) {
                                        if( weapon) {
                                                if( defense_skill == "douzhuan-xingyi" )
                                                        parry_msg = star_move_weapon[random(sizeof(star_move_weapon))];
                                                else
                                                        parry_msg = qiankun_move_weapon[random(sizeof(qiankun_move_weapon))];

                                                damage=query_temp("apply/damage", me);
                                        } else {
                                                if( defense_skill == "douzhuan-xingyi" )
                                                        parry_msg = star_move_unarm[random(sizeof(star_move_unarm))];
                                                else
                                                        parry_msg = qiankun_move_unarm[random(sizeof(qiankun_move_unarm))];

                                                damage=query_temp("apply/unarmed_damage", me);
                                        }

                                        damage+=query_temp("apply/damage1", me);   // 裝備附加傷害
                                        if( query("jingmai/finish", me) )
                                                damage+= ZHOUTIAN_D->query_jingmai_effect("damage");
                                        damage+=query("jingmai/damage", me);       // 經脈附加傷害

                                        damage += (int)me->query_skill(attack_skill, 1);
                                        damage+=query("jiali", me);
                                        damage = (damage + random(damage)) / 2;
#ifdef USE_SKILLS_COMBAT
                                        if( arrayp(att) && sizeof(att) )
                                                damage += (int)att[DAMAGE] * damage / 100;
                                        else
#endif
                                        if( action["damage"] )
                                                damage += action["damage"] * damage / 100;
                                        
                                        damage_bonus = me->query_str();
#ifdef USE_SKILLS_COMBAT
                                        if( arrayp(att) && sizeof(att) )
                                                damage_bonus += (int)att[FORCE2] * damage_bonus / 100;
                                        else
#endif
                                        if( action["force"] )
                                                damage_bonus += action["force"] * damage_bonus / 100;
                                        // calculate the damage
                                        if( damage_bonus > 0 )
                                                damage += (damage_bonus + random(damage_bonus)) / 2;

                                        me->receive_damage("qi", damage, victim);
                                        armor=query_temp("apply/armor", me);
                                        armor+=query_temp("apply/armor1", me);
                                        if( query("jingmai/finish", me) )
                                                armor+= ZHOUTIAN_D->query_jingmai_effect("armor");
                                        armor+=query("jingmai/armor", me);
                                        if( damage > armor + 2 )
                                                me->receive_wound("qi", (damage - armor)/2, victim);

                                        foo = damage_msg(damage, action["damage_type"]);
                                        foo = replace_string(foo, "$n", "$N");
                                        foo = replace_string(foo, "$p", "$P");
                                        
                                        /*
                                        foo += "( $N" +
                                                status_msg(query("qi", me)*100/
                                                (query("max_qi", me)?query("max_qi", me):100))+")\n";
                                        */
                                        foo += report_status(me, 1);
                                        parry_msg += foo;
                                } else
                                        parry_msg = SKILL_D(defense_skill)->query_parry_msg(weapon2, victim);
                        } else {
                                // change to SKILL_D(defense_skill) after added parry msg to those
                                // martial arts that can parry.
                                parry_msg = SKILL_D(defense_skill)->query_parry_msg(weapon2, victim);
                        }

                        if( !stringp(parry_msg) )
                                parry_msg = SKILL_D("parry")->query_parry_msg(weapon2, victim);

                        if( stringp(parry_msg) )
                                result += parry_msg;

                        damage = RESULT_PARRY;
                } else {
        //
        //  (5) We hit the victim and the victim failed to parry
        //
                        attack = 1;

                        if( weapon )
                                damage=query_temp("apply/damage", me);
                        else
                                damage=query_temp("apply/unarmed_damage", me);

                        damage+=query_temp("apply/damage1", me);
                        if( query("jingmai/finish", me) )
                                damage+= ZHOUTIAN_D->query_jingmai_effect("damage");
                        damage+=query("jingmai/damage", me);    // 經脈附加傷害

                        damage = damage + me->query_skill(attack_skill, 1);

                        damage+=query("jiali", me);

#ifdef USE_SKILLS_COMBAT
                        if( arrayp(att) && sizeof(att) )
                                damage += (int)att[DAMAGE] * damage / 100;
                        else
#endif
                        if( action["damage"] )
                                damage += action["damage"] * damage / 100;


                        // 先天技能浩然正氣對邪氣類效果加倍
                        if( query("special/haoran") && victim->query("shen") < 0 )
                                damage *= 2;
                        else
                        // 先天技能九幽魔氣對正氣類效果加倍
                        if( query("special/jiuyou") && victim->query("shen") > 0 )
                                damage *= 2;

                        // 昆侖無極的影響
                        if( martial_skill == "qiankun-jian" && me->query_skill("kunlun-wuji", 1) >= 100 )
                                damage += me->query_skill("kunlun-wuji", 1);

                        // 血影大法的影響
                        if( martial_skill == "xuedao-daofa" && me->query_skill("xueying-dafa", 1) >= 100 )
                                damage += me->query_skill("xueying-dafa", 1) * 2;

                        // 臂力的影響
                        damage_bonus = me->query_str();
                        if( my["jianu"] ) {
                                // does angry bonus
                                damage_bonus += me->cost_craze(my["jianu"]);
                                if( me->query_craze() > 1000 &&
                                    random(my["jianu"] + 200) > 200 ) {
                                        damage_info += random(2) ? HIR "$N" HIR "大喝一聲，雙目圓睜，一股凌厲的殺氣油然而起！\n" NOR
                                                                 : HIR "$N" HIR "奮不顧身的撲上前來，招招緊逼$n" HIR "，毫不容情。\n" NOR;
                                        me->cost_craze(200 + random(300));
                                        damage_bonus += my["jianu"] * 2;
                                }
                        }

                        // Clear the special message info after damage info
                        foo_before_hit = 0;
                        foo_after_hit = 0;

                        // Let force skill take effect.
                        if( my["jiali"] && (my["neili"] > my["jiali"]) ) {
                                if( force_skill = me->query_skill_mapped("force") ) {
                                        // 鑲嵌有天地日月靈珠的護甲加力傷害減半
                                        if( objectp(ob = query_temp("armor/armor", victim)) && ob->query_magic_item() == "天地日月靈珠" )
                                                delta = 2;
                                        else
                                                delta = 1;

                                        foo = SKILL_D(force_skill)->hit_ob(me, victim, damage_bonus,
                                                my["jiali"] / delta);

                                        if( stringp(foo) ) damage_info += foo; else
                                        if( intp(foo) ) damage_bonus += foo; else
                                        if( mapp(foo) ) {
                                                damage_info += foo["msg"];
                                                damage_bonus += foo["damage"];
                                        }
                                }
                        }
#ifdef USE_SKILLS_COMBAT
                        if( arrayp(att) && sizeof(att) )
                                damage_bonus += (int)att[FORCE2] * damage_bonus / 100;
                        else
#endif
                        if( action["force"] )
                                damage_bonus += action["force"] * damage_bonus / 100;

                        // calculate the damage
                        if( damage_bonus > 0 )
                                damage += (damage_bonus + random(damage_bonus)) / 2;

                        // 根據攻擊的部位影響傷害
                        if( !undefinedp(limb_damage[limb]) )
                                damage = (damage * limb_damage[limb] / 100);

                        // Let's attack & parry skill, weapon & armor do effect
                        while( damage > 0)
                        {
                                if( my["not_living"] || your["not_living"] )
                                        break;

                                if( !living(me) || !living(victim) ) break;
                                if( damage < 1 ) break;

                                if( objectp(ob = query_temp("armor/surcoat", me)) && ob->query_magic_item() == "真武寶石" )
                                        damage_info += HIY "$N" HIY "的真武寶石發出一道耀眼的光芒，另所有人無法辨別眼前事物 ……\n" NOR;
                                else {
                                        delta = 0;
                                        if( attack_skill == "unarmed" && me->query_skill_prepared("unarmed") == "xiantian-gong"
                                        ||  martial_skill == "quanzhen-jian" )
                                                delta = 1;

                                        // Let parry skill take its special effort.
                                        avoid=query_temp("apply/avoid_dodge", me);
                                        if( random(100) >= avoid &&
                                            stringp(defense_skill = victim->query_skill_mapped("dodge")) ) {
                                                foo = SKILL_D(defense_skill)->valid_damage(me, victim, damage, weapon);
                                                if( stringp(foo) ) damage_info += foo; else
                                                if( intp(foo) ) {
                                                        // 發揮化甲術的特效
                                                        if( delta )
                                                                foo = foo - foo / 100 * (hjs / 50);
                                                        else
                                                                foo = foo - foo / 100 * (hjs / 100);
                                                        damage += foo;
                                                } else
                                                if( mapp(foo) ) {
                                                        damage_info += foo["msg"];
                                                        // 發揮化甲術的特效
                                                        if( delta )
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 50);
                                                        else
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 100);
                                                        damage += foo["damage"];
                                                }
                                                if( damage < 1 ) break;
                                        }

                                        avoid=query_temp("apply/avoid_parry", me);
                                        if( random(100) >= avoid &&
                                            stringp(defense_skill = victim->query_skill_mapped("parry")) ) {
                                                foo = SKILL_D(defense_skill)->valid_damage(me, victim, damage, weapon);
                                                if( stringp(foo) ) damage_info += foo; else
                                                if( intp(foo) ) {
                                                        // 發揮化甲術的特效
                                                        if( delta )
                                                                foo = foo - foo / 100 * (hjs / 50);
                                                        else
                                                                foo = foo - foo / 100 * (hjs / 100);
                                                        damage += foo;
                                                } else
                                                if( mapp(foo) ) {
                                                        damage_info += foo["msg"];
                                                        // 發揮化甲術的特效
                                                        if( delta )
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 50);
                                                        else
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 100);
                                                        damage += foo["damage"];
                                                }
                                                if( damage < 1 ) break;
                                        }

                                        // Let armor/cloth take its special effort
                                        if( mapp(your_temp["armor"]) && objectp(ob = your_temp["armor"]["armor"]) ) {
                                                foo = ob->valid_damage(me, victim, damage, weapon);
                                                if( stringp(foo) ) damage_info += foo; else
                                                if( intp(foo) ) {
                                                        // 發揮化甲術的特效
                                                        if( delta )
                                                                foo = foo - foo / 100 * (hjs / 50);
                                                        else
                                                                foo = foo - foo / 100 * (hjs / 100);
                                                        damage += foo;
                                                } else
                                                if( mapp(foo) ) {
                                                        damage_info += foo["msg"];
                                                        // 發揮化甲術的特效
                                                        if( delta )
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 50);
                                                        else
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 100);
                                                        damage += foo["damage"];
                                                }
                                        } else if( mapp(your_temp["armor"]) && objectp(ob = your_temp["armor"]["cloth"]) ) {
                                                foo = ob->valid_damage(me, victim, damage, weapon);
                                                if( stringp(foo) ) damage_info += foo; else
                                                if( intp(foo) ) {
                                                        // 發揮化甲術的特效
                                                        if( delta )
                                                                foo = foo - foo / 100 * (hjs / 50);
                                                        else
                                                                foo = foo - foo / 100 * (hjs / 100);
                                                        damage += foo;
                                                } else
                                                if( mapp(foo) ) {
                                                        damage_info += foo["msg"];
                                                        // 發揮化甲術的特效
                                                        if( delta )
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 50);
                                                        else
                                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * (hjs / 100);
                                                        damage += foo["damage"];
                                                }
                                        }
                                        if( damage < 1 ) break;
                                        
                                        /*
                                        // 兵器有透甲能力。如透甲錐之類的暗器
                                        if(objectp(weapon) && weapon->through_armor())
                                                return 0;       // 硬功的防護作用。armor_vs_force
                                        absp = skill_power(victim, "iron-cloth", SKILL_USAGE_ABSORB);
                                        if(absp)
                                        {
                                                defense_skill = victim->query_skill_mapped("iron-cloth");
                                                if(!defense_skill) defense_skill = "iron-cloth";

                                                if(!mute_flag)
                                                        result += SKILL_D(defense_skill)->query_absorb_msg();
                                                foo = SKILL_D(defense_skill)->absorb_ob(victim, me, damage, absp);
                                                if(stringp(foo))
                                                {
                                                        if(!mute_flag)
                                                        result += foo;
                                                }
                                                else if(intp(foo)) damage += foo;
                                        }                       
                                        */
                                }
                                // Let attack skill take its special effort.
                                avoid=query_temp("apply/avoid_attack", victim);
                                if( random(100) >= avoid && stringp(martial_skill) ) {
                                        foo = SKILL_D(martial_skill)->hit_ob(me, victim, damage);
                                        if( stringp(foo) ) damage_info += foo; else
                                        if( intp(foo) ) damage += foo; else
                                        if( mapp(foo) ) {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                        if( damage < 1 ) break;
                                }

                                // Let weapon or living have their special damage.
                                if( weapon ) {
                                        foo = weapon->hit_ob(me, victim, damage);
                                        if( stringp(foo) ) damage_info += foo; else
                                        if( intp(foo) ) damage += foo; else
                                        if( mapp(foo) ) {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                } else {
                                        foo = me->hit_ob(me, victim, damage);
                                        if( stringp(foo) ) damage_info += foo; else
                                        if( intp(foo) ) damage += foo; else
                                        if( mapp(foo) ) {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                }

                                if( damage < 1 ) break;

                                if( mapp(my_temp["apply"]) && my_temp["apply"]["double_damage"] > 0 ) {
                                        if( random(100) < my_temp["apply"]["double_damage"] ) {
                                                int damage2, scale;
                                                damage2 = random(damage);
                                                scale = 100 + damage2 * 10 / damage * 10;
                                                damage += damage2;
                                                damage_info += HIY "$N" HIY "福至心靈，有如神助，一擊之中竟產生多重傷害，給予$n" HIY "造成「" + scale + "%」的傷害！\n" NOR;
                                        }
                                }

                                // finish
                                break;
                        }
        //
        //  (6) Inflict the damage.
        //

                        if( victim->query_skill_mapped("dodge") == "lingbo-weibu" &&
                            query_temp("immortal", victim) && random(100) < 90 )
                        {
                                damage = 0;
                                damage_info += HIY "$n" HIY "施展凌波微步逆天絕招「神光離合」，一道耀眼的光芒環繞全身，頓時讓所有的攻擊落空 ……\n" NOR;
                        }

                        if( damage > 0 ) {
                                /*
                                int def_exp;

                                // Let combat exp take effect
                                def_exp = your["combat_exp"];
                                while( random(def_exp) > my["combat_exp"] ) {
                                        damage -= damage / 4;
                                        def_exp /= 2;
                                }
                                */

                                if( my["character"] == "心狠手辣" )
                                        damage += damage * 20 / 100;

                                if( my["breakup"] ) damage += damage * 10 / 100;

                                // 元神
                                if( query("yuanshen/status", me) )
                                        damage += damage * query("yuanshen/status", me) / 100;

                                if( objectp(ob = query_temp("armor/surcoat", victim)) && ob->query_magic_item() == "流行趕月" )
                                        damage -= damage * 5 / 100;

                                // calculate wounded
                                wounded = damage;
                                armor=query_temp("apply/armor", victim);
                                armor+=query_temp("apply/armor1", victim);
                                if( query("jingmai/finish", victim) )
                                        armor += ZHOUTIAN_D->query_jingmai_effect("armor");
                                armor+=query("jingmai/armor",victim);

                                // 發揮化甲術的特效
                                if( attack_skill == "unarmed" && me->query_skill_prepared("unarmed") == "xiantian-gong"
                                ||  martial_skill == "quanzhen-jian" )
                                        armor -= armor / 100 * hjs / 50;
                                else
                                        armor -= armor / 100 * hjs / 100;

                                //if( mapp(your_temp["apply"]) && your_temp["apply"]["armor"] > 0 )
                                //        wounded -= random(your_temp["apply"]["armor"]);
                                if( random(100) >= query_temp("apply/through_armor", me) )
                                        wounded -= random(armor);

                                // 昆侖無極的穿透作用
                                if( martial_skill == "qiankun-jian" && me->query_skill("kunlun-wuji", 1) >= 125 )
                                        wounded += me->query_skill("kunlun-wuji", 1) / 125 * 100;

                                // 發揮披風--赤煉龍膽的特效
                                if( objectp(ob = query_temp("armor/surcoat", me)) && ob->query_magic_item() == "赤煉龍膽" )
                                {
                                        damage_info += HIR "\n$N" HIR "的赤煉龍膽寶石發出一道奇異的光芒，一條發光的"
                                                       "的赤龍張牙舞爪般的撲向$n" HIR "。\n" NOR;
                                        damage += damage / 2;
                                }

                                // 發揮披風--孔 雀 石的效果
                                if( objectp(ob = query_temp("armor/surcoat", victim)) && ob->query_magic_item() == "孔雀石" )
                                {
                                        result += HIG + victim->name() + HIG "的孔雀石發出一道奇異的光芒，數道青光將" + victim->name() +
                                                  HIG "籠罩，但見一只發光的孔雀\n跳躍飛舞，卻不讓任何人靠近。\n" NOR;

                                        // 發揮披風--真武寶石的效果
                                        if( objectp(ob = query_temp("armor/surcoat", me)) && ob->query_magic_item() == "真武寶石" )
                                                result += HIY "可是" + me->name() + HIY "的真武寶石發出一道亮光，"
                                                          "那發光的孔雀頓時消失不見。\n" NOR;
                                        else
                                        {
                                                message_combatd(result, me, victim);
                                                return 1;
                                        }
                                }

                                // 發揮勛章--碧海殘□的作用
                                if( objectp(ob = query_temp("armor/charm", me)) && ob->query_magic_item() == "碧海殘□" )
                                {
                                        damage_info += HIC "$N" HIC "的碧海殘□青光一閃，「碧海蒼穹」呈現，發出震耳般的海嘯聲 ……\n" NOR;
                                        damage += damage / 2;
                                        if( !victim->is_busy() )
                                                victim->start_busy(3);
                                }

                                else
                                // 發揮勛章--麒麟火的作用
                                if( objectp(ob = query_temp("armor/charm", me)) && ob->query_magic_item() == "麒麟火" )
                                {
                                        damage_info += HIR "$N" HIR "的麒麟火發閃出火紅般的光芒，「麒麟聖火」長久不熄，令人難以喘息 ……\n" NOR;
                                        damage += damage / 2;
                                        if( query("neili", victim) >= 300 )
                                        {
                                                addn("neili", -300, victim);
                                                addn("neili", 300, me);
                                        }
                                }
                                /*
                                if( wounded > 400 )
                                        wounded = (wounded - 400) / 4 + 300;
                                else if( wounded > 200 )
                                        wounded = (wounded - 200) / 2 + 200;
                                else if( wounded < 1 )
                                        wounded = 0;

                                // recalculate damage
                                if( damage > 400 )
                                        damage = (damage - 400) / 4 + 300;
                                else if( damage > 200 )
                                        damage = (damage - 200) / 2 + 200;
                                */
                                if( your["character"] == "光明磊落" )
                                        wounded -= wounded * 20 / 100;

#ifdef REDUCE_PVP_DAMAGE
                                damage = COMBAT_D->reduce_damage(me, victim, damage);
#endif
                                damage = victim->receive_damage("qi", damage, me);
                                if( damage < 1 )
                                        damage_info += BLU "$n" BLU "神奇的化解了$N" BLU "這一擊的所有傷害！\n" NOR;

                                if( wounded > 0 &&
                                    // ((me->is_killing(your["id"]) && random(3) == 1) ||
                                    (has_weapon ||
                                     random(3) == 1) ) {
                                        // We are sure that damage is greater than victim's armor here.
#ifdef REDUCE_PVP_DAMAGE
                                        wounded = COMBAT_D->reduce_wound(me, victim, wounded);
#endif
                                        wounded = victim->receive_wound("qi", wounded, me);
                                } else  wounded = 0;

                                // add message before hit in victim
                                if( foo_before_hit )
                                        result += foo_before_hit;

                                result += damage_msg(damage, action["damage_type"]);
                                damage_info += "( $n" +
                                        status_msg(query("qi", victim)*100/
                                        (query("max_qi", victim)?query("max_qi", victim):100))+")\n";
                                /*
                                damage_info += replace_string(report_status(victim, 1), "$N", "$n");
                                */
                                // 奇門玄術的反傷效果
                                if( victim->query_skill("qimen-xuanshu", 1) >= 100 )
                                {
                                        if( random(victim->query_skill("qimen-xuanshu", 1)) > 100 && random(3) == 1 )
                                        {
                                                damage_info += HIG "$n" HIG "施展出「奇門玄術」的反傷效果，使得$N" HIG "自身同時也受到損傷。\n" NOR;
                                                me->receive_damage("qi", damage * victim->query_skill("qimen-xuanshu", 1) / 5000, victim);
                                                me->receive_wound("qi", wounded * victim->query_skill("qimen-xuanshu", 1) / 5000, victim);

                                                if( query("eff_qi", victim) + wounded * victim->query_skill("qimen-xuanshu", 1) / 5000 <
                                                    query("max_qi", victim) )
                                                        addn("eff_qi", wounded * victim->query_skill("qimen-xuanshu", 1) / 5000, victim);
                                                else
                                                        set("eff_qi", query("max_qi", victim), victim);

                                                if( query("qi", victim) + damage * victim->query_skill("qimen-xuanshu", 1) / 5000 <
                                                    query("eff_qi", victim) )
                                                        addn("qi", damage * victim->query_skill("qimen-xuanshu", 1) / 5000, victim);
                                                else
                                                       set("qi", query("eff_qi", victim), victim);
                                                
                                                /*
                                                damage_info += "( $N" +
                                                        status_msg(query("qi", me)*100/
                                                        (query("max_qi", me)?query("max_qi", me):100))+")\n";
                                                */
                                                damage_info += report_status(me, 1);
                                        }
                                }

                                // 血影大法傷內力效果
                                if( martial_skill == "xuedao-daofa" && me->query_skill("xueying-dafa", 1) >= 1 )
                                {
                                        addn("neili", -1 * (me->query_skill("xueying-dafa", 1) + me->query_skill("xuedao-daofa", 1)) / 12, victim);
                                        if( query("neili", victim) < 0 )
                                                set("neili", 0, victim);
                                }

                                // 極品防具傷害反射效果
                                avoid=query_temp("apply/counter_damage", victim);
                                if( random(100) < avoid && random(3) == 1 ) {
                                        /*
                                        if( objectp(ob=query_temp("armor/armor", victim)) &&
                                            query("enchase/apply_prop/counter_damage", ob) )
                                                damage_info += BLINK + HIM + ob->name() + BLINK + HIM "發出一道奇異眩目的紅光襲向$N！\n" NOR;
                                        else
                                        if( objectp(ob=query_temp("armor/cloth", victim)) &&
                                            query("enchase/apply_prop/counter_damage", ob) )
                                                damage_info += BLINK + HIM + ob->name() + BLINK + HIM "發出一道奇異眩目的紅光襲向$N！\n" NOR;
                                        else
                                        */
                                                damage_info += BLINK + HIM "$n" BLINK + HIM "周身發出一道奇異眩目的紅光襲向$N！\n" NOR;

                                        me->receive_damage("qi", damage/5, victim);
                                        me->receive_wound("qi", wounded/5, victim);
                                        /*
                                        damage_info += "( $N" +
                                                status_msg(query("qi", me)*100/
                                                (query("max_qi", me)?query("max_qi", me):100))+")\n";
                                        */
                                        damage_info += report_status(me, 1);
                                }
                        }

                        if( foo_after_hit )
                                damage_info += foo_after_hit;
        //
        //  (7) Give experience
        //
                        /*
                        if( victim->is_boss() && query("fight_boss", victim) &&
                            my["level"] < your["level"]*2 )
                                addn("combat_exp", me->query_int()/10, me);

                        if( your["combat_exp"] > my["combat_exp"] &&
                            (random(my["jing"]*100/my["max_jing"] + me->query_int()) > 50) ) {
                                if( my["combat_exp"] > EXP_LIMIT )
                                        addn("combat_exp", me->query_int()/60, me);
                                else
                                        addn("combat_exp", me->query_int()/15, me);
                                me->improve_skill(attack_skill, random(me->query_int()));
                                if( my["potential"] - my["learned_points"] < 10*me->query_int() )
                                        addn("potential", 1, me);

                        }
                        */
                }
        }

        result = replace_string(result, "$l", limb);
        if( objectp(weapon2=query_temp("weapon", victim)) )
                result = replace_string(result, "$v", weapon2->name());
        if( objectp(weapon) )
                result = replace_string(result, "$w", weapon->name());
        else if( stringp(action["weapon"]) )
                result = replace_string(result, "$w", action["weapon"]);
        else if( attack_skill == "finger" || attack_skill == "hand" )
                result = replace_string(result, "$w", "手指" );
        else if( attack_skill == "strike" || attack_skill == "claw" )
                result = replace_string(result, "$w", "手掌" );
        else    result = replace_string(result, "$w", "拳頭" );

        message_combatd(result, me, victim, damage_info);

        if( damage > 0 ) {
#if INSTALL_COMBAT_TEST
                if( userp(me)/* && query("env/combat_test", me)*/ )
                        tell_object(me, HIW "( 你對" +
                                        query("name", victim)+HIW"造成"+
                                        damage + "點傷害，" +
                                        wounded + "點創傷。)\n" NOR);
                if( userp(victim)/* && query("env/combat_test", victim)*/ )
                        tell_object(victim, HIG "( 你受到" +
                                        query("name", me)+HIG+damage+"點傷害，"+
                                        wounded + "點創傷。)\n" NOR);
#endif
                if( attack == 1 ) {
                        switch( limb ) {
                        // 頭、頸受傷會傷一些神。
                        case "頭部":
                        case "頸部":
                                damage /= 4;
                                if( damage < 1 )
                                        damage = 1;
                                if( damage > 8000 )
                                        damage = 8000;
                                victim->receive_damage("jing", damage, me );
                                delta=query("jing", victim)*100/query("max_jing", victim);
                                if( delta <= 30 )
                                        tell_object(victim, head_damage_me_msg[2]);
                                else if( delta <= 70 )
                                        tell_object(victim, head_damage_me_msg[1]);
                                else
                                        tell_object(victim, head_damage_me_msg[0]);
                                break;
                        // 擊中這些部位真氣會受到振盪。
                        case "胸口":
                        case "後心":
                        case "小腹":
                                if( query("max_neili", victim) && query("neili", victim)){
                                        damage /= 4;
                                        if( damage < 1 )
                                                damage = 1;
                                        if( damage > 10000 )
                                                damage = 10000;
                                        if( query("neili", victim) <= damage )
                                                set("neili", 0, victim);
                                        else
                                                addn("neili", -damage, victim);
                                        if( damage <= 500 )
                                                foo = body_damage_me_msg[0];
                                        else if( damage <= 1000 )
                                                foo = body_damage_me_msg[1];
                                        else
                                                foo = body_damage_me_msg[2];
                                        foo = replace_string(foo, "$l", limb);
                                        tell_object(victim, foo);
                                }
                                break;
                        }
                        victim->receive_limbs_wound(limb, damage);
                }

                // 顯示玩家精氣、氣血
                /*
                if( query("env/verbose", me) )
                {
                        tell_object(me, SAVEC);
                        tell_object(me, SETDISPLAY(21,49)+DELLINE);
                        tell_object(me, SETDISPLAY(22,49)+DELLINE);
                        tell_object(me, SETDISPLAY(23,49)+DELLINE);
                        tell_object(me, SETDISPLAY(21,50)+HIY"□□□□□□□□□□□□□□□");
                        tell_object(me, SETDISPLAY(22,50)+HIY"□");
                        tell_object(me, SETDISPLAY(22,52)+HIG"精："HIR+query("jing",me)+"/"+query("eff_jing",me));
                        tell_object(me, SETDISPLAY(22,65)+HIG"氣："HIR+query("qi",me)+"/"+query("eff_qi",me));
                        tell_object(me, SETDISPLAY(22,78)+HIY"□");
                        tell_object(me, SETDISPLAY(23,50)+HIY"□□□□□□□□□□□□□□□"NOR);
                        tell_object(me, REST);
                }
                */

                if( query("special_skill/monster", victim) && random(5) == 1){
                        message_vision(HIG "$N" HIG "施展出「天妖臨世」，$n" HIG "自身同時也受到損傷。\n" NOR, victim, me);
                        me->receive_damage("qi", damage, victim);
                        if( random(2) == 1 ) me->receive_wound("qi", wounded, victim);
                        //damage_info = "(" + me->name() + status_msg(query("qi", me) * 100 / query("max_qi", me)) + ")\n";
                        damage_info = report_status(me, 1);
                        message_vision(damage_info, me);
                }

                if( query("special_skill/demon", victim) && random(5) == 1 )
                        message_vision(HIW "$N" HIW "強提一口丹田之氣，真氣運轉之下，力保心脈不死！\n" NOR, victim, me);
                        victim->receive_curing("qi", victim->query("max_qi") / 3);

                if( victim->is_busy() ) {
                        victim->interrupt_me(me, 60 + random(10));
                        message_vision(HIW "$N行動微覺受制，急忙默運真氣，移開了周身要穴！\n" NOR, victim);
                }

                if( victim->query_condition("no_perform") && !random(6) ) {
                        message_vision(HIY"$N發現自己氣血運行不暢，急忙默運真氣，硬是壓下了翻騰不已的氣血！\n"NOR, victim);
                        victim->clear_condition("no_perform");
                }

                if( me->query_condition("no_exert") && !random(6) ) {
                        message_vision(HIC"$N發現自己內息不勻，急忙默運真氣，調理內息！\n"NOR, victim);
                        victim->clear_condition("no_exert");
                }
                
                if( (!me->is_killing(your["id"])) &&
                    (!victim->is_killing(my["id"])) &&
                    !query("not_living", victim) &&
                    your["qi"] * 2 <= your["max_qi"] ) {
                        me->remove_enemy(victim);
                        victim->remove_enemy(me);
                        if( query("can_speak", me) && query("can_speak", victim) )
                                message_vision(winner_msg[random(sizeof(winner_msg))],
                                               me, victim);
                        if( me == victim->query_competitor() ) {
                                me->win();
                                victim->lost();
                        }
                }
                // if(me->query("special_skill/tianmo") && random(5) == 1) {
                //         message_vision(HIR"$N腦中浮現出天魔解體時所領會的武學精華，以敵血補己氣，攻勢更顯凌厲！\n" NOR, me, victim);
                //         me->receive_curing("qi", (me->query("max_qi")*(int)me->query("special_skill/tianmo",1)*2/100));
                //         do_attack(me, victim, weapon, 3);
                // }
                //
                
        }
        if( functionp(action["post_action"]) ) // 技能特效
                evaluate( action["post_action"], me, victim, weapon, damage);
        else
                WEAPON_D->bash_weapon(me, victim, weapon, damage);

        // See if the victim can make a riposte.
        if( attack_type == TYPE_REGULAR &&
            damage < 1 &&
            your_temp["guarding"] ) {
                your_temp["guarding"];
                if( random(my["dex"]) < 5 ) {
                        message_combatd("$N一擊不中，露出了破綻！\n",
                                        me, 0, "");
                        do_attack(victim, me, your["weapon"],
                                  TYPE_QUICK);
                } else {
                        message_combatd("$N見$n攻擊失誤，趁機發動攻擊！\n",
                                        victim, me, "");
                        do_attack(victim, me, your_temp["weapon"],
                                  TYPE_RIPOSTE);
                }
        }
}

// do damage when perform
// I will consider the damage of the weapon
// what is final: final may be a function with result type string,
// or a single string.
// The syntax of the final string is info:damage_type@limb or info only,
// If the limb if ?, the system will auto select limb of
// target, if the final is a single string, the system will
// treat as damage infomation.
varargs string do_damage(object me, object target, mixed type,
                         int damage, int percent, mixed final)
{
        mapping my;
        object weapon;
        object cloth;
        object ob;
        int apply;
        int armor;
        int wound;
        int jiali;
        int bonus;
        mixed foo;
        string msg;
        string skill;
        string *limbs;
        string limb;
        string damage_type;
        string result;
        int str;
        int damage_bonus;
        mapping prepare;
        string attack_skill;
        int avoid;
        int def_exp, att_exp;
        int hjs;

        if( damage < 0 ) return "";
        if( (userp(me) && me->is_ghost()) || (userp(target) && target->is_ghost()) ) return "";
        if( environment(me) != environment(target) ) {
                me->remove_enemy(target);
                target->remove_enemy(me);
                return "";
        }

        hjs = me->query_skill("huajia-su", 1);

        // Am I use weapon
        if( type == WEAPON_ATTACK ) {
                apply=query_temp("apply/damage", me);
                apply+=query_temp("apply/damage1", me);
                weapon=query_temp("weapon", me);
        } else if( type == UNARMED_ATTACK ) {
                apply=query_temp("apply/unarmed_damage", me);
                apply+=query_temp("apply/damage1", me);
                weapon = 0;
        } else if( type == REMOTE_ATTACK ) {
                apply  = 0;
                weapon = 0;
        } else {
                if( query_temp("weapon", me)){
                        apply=query_temp("apply/damage", me);
                        weapon=query_temp("weapon", me);
                } else {
                        apply=query_temp("apply/unarmed_damage", me);
                        weapon = 0;
                }
                apply+=query_temp("apply/damage1", me);
        }

        prepare = me->query_skill_prepare();
        if( !prepare ) prepare = ([]);

        if( type == REMOTE_ATTACK )
                skill = "force";
        else if( weapon )
                skill=query("skill_type", weapon);
        else {
                switch( sizeof(prepare) ) {
                case 0: skill = "unarmed"; break;
                case 1:
                case 2: skill = (keys(prepare))[0]; break;
                }
        }

        if( skill == "pin" ) skill = "sword";

        attack_skill = me->query_skill_mapped(skill);

        // Check the target's armor
        armor=query_temp("apply/armor", target);
        armor+=query_temp("apply/armor1", target);
        if( query("jingmai/finish", target) )
                armor += ZHOUTIAN_D->query_jingmai_effect("armor");
        armor+=query("jingmai/armor", target);

        damage += apply;
        if( query("jingmai/finish", me) )
                damage += ZHOUTIAN_D->query_jingmai_effect("damage");
        damage += query("jingmai/damage",me);

        // 發揮昆侖無極的威力
        if( me->query_skill("kunlun-wuji", 1) >= 100 )
                damage += me->query_skill("kunlun-wuji", 1);

        msg = "";
        foo_after_hit = 0;

        while (type == UNARMED_ATTACK || type == WEAPON_ATTACK )
        {
                if( !living(target) ) break;

                if( random(100) < 20 &&
                   (attack_skill == "six-finger" ||
                    attack_skill == "dragon-strike" ||
                    attack_skill == "moon-blade" ||
                    attack_skill == "lonely-sword") )
                        break;

                if( objectp(ob = query_temp("armor/surcoat", me)) && ob->query_magic_item() == "真武寶石" )
                        msg += HIY "$N" HIY "的真武寶石發出一道耀眼的光芒，另所有人無法辨別眼前事物 ……\n" NOR;
                else
                {
                        avoid=query_temp("apply/avoid_parry", me);
                        skill = target->query_skill_mapped("parry");

                        // Let parry skill take its special effort
                        if( stringp(skill) && (skill == "qiankun-danuoyi" ||
                            skill == "douzhuan-xingyi") ) {
                                foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                                if( stringp(foo) ) msg += foo; else
                                if( intp(foo) ) damage += foo; else
                                if( mapp(foo) ) {
                                        msg += foo["msg"];
                                        damage += foo["damage"];
                                }
                        } else if( random(100) >= avoid && stringp(skill) ) {
                                foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                                if( stringp(foo) ) msg += foo; else
                                if( intp(foo) ) {
                                        // 發揮化甲術的特效
                                        if( hjs > 100 )
                                                foo = foo - foo / 100 * hjs / 100;
                                        damage += foo;
                                } else
                                if( mapp(foo) ) {
                                        msg += foo["msg"];
                                        // 發揮化甲術的特效
                                        if( hjs > 100 )
                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * hjs / 100;
                                        damage += foo["damage"];
                                }
                        }

                        if( damage < 1 ) break;

                        avoid=query_temp("apply/avoid_dodge", me);
                        skill = target->query_skill_mapped("dodge");

                        // Let dodge skill take its special effort
                        if( stringp(skill) && skill == "lingbo-weibu") {
                                foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                                if( stringp(foo) ) msg += foo; else
                                if( intp(foo) ) damage += foo; else
                                if( mapp(foo) ) {
                                        msg += foo["msg"];
                                        damage += foo["damage"];
                                }
                        } else if( random(100) > avoid && stringp(skill) ) {
                                foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                                if( stringp(foo) ) msg += foo; else
                                if( intp(foo) ) {
                                        // 發揮化甲術的特效
                                        if( hjs > 100 )
                                                foo = foo - foo / 100 * hjs / 100;
                                        damage += foo;
                                } else
                                if( mapp(foo) ) {
                                        msg += foo["msg"];
                                        // 發揮化甲術的特效
                                        if( hjs > 100 )
                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * hjs / 100;
                                        damage += foo["damage"];
                                }
                        }

                        if( damage < 1) break;

                        // Let cloth & armor take its special effort
                        if( cloth=query_temp("armor/armor", target)){
                                foo = cloth->valid_damage(me, target, damage, weapon);
                                if( stringp(foo) ) msg += foo; else
                                if( intp(foo) ) {
                                        // 發揮化甲術的特效
                                        if( hjs > 100 )
                                                foo = foo - foo / 100 * hjs / 100;
                                        damage += foo;
                                } else
                                if( mapp(foo) ) {
                                        msg += foo["msg"];
                                        // 發揮化甲術的特效
                                        if( hjs > 100 )
                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * hjs / 100;
                                        damage += foo["damage"];
                                }
                        }else if( cloth=query_temp("armor/cloth", target)){
                                foo = cloth->valid_damage(me, target, damage, weapon);
                                if( stringp(foo) ) msg += foo; else
                                if( intp(foo) ) {
                                        // 發揮化甲術的特效
                                        if( hjs > 100 )
                                                foo = foo - foo / 100 * hjs / 100;
                                        damage += foo;
                                } else
                                if( mapp(foo) ) {
                                        msg += foo["msg"];
                                        // 發揮化甲術的特效
                                        if( hjs > 100 )
                                                foo["damage"] = foo["damage"] - foo["damage"] / 100 * hjs / 100;
                                        damage += foo["damage"];
                                }
                        }
                }
                // Finish
                break;
        }

        if( target->query_skill_mapped("dodge") == "lingbo-weibu" &&
            query_temp("immortal", target) && random(100) < 90 )
        {
                damage = 0;
                msg += HIY "$n" HIY "施展凌波微步逆天絕招「神光離合」，一道耀眼的光芒環繞全身，頓時化去所有的傷害 ……\n" NOR;
        }

        /*
        // Let combat exp take effect
        if( damage > 0 )
        {
                def_exp=query("combat_exp", target);
                att_exp=query("combat_exp", me);
                while( random(def_exp) > att_exp ) {
                        damage -= damage / 4;
                        def_exp /= 2;
                }
        }
        */

        while (damage > 0)
        {
                if( target->is_busy() ) target->interrupt_me(target, 60 + random(10));

                // Let weapon/unarmed attack take its special effort
                if( type == WEAPON_ATTACK && objectp(weapon) )
                        // weapon attack
                        foo = weapon->hit_ob(me, target, damage);
                else if( type == UNARMED_ATTACK )
                        // unarmed attack
                        foo = me->hit_ob(me, target, damage);
                else if( type == SPECIAL_ATTACK ) {
                        if( objectp(weapon) )
                                foo = weapon->hit_ob(me, target, damage);
                        else
                                foo = me->hit_ob(me, target, damage);
                } else if( objectp(type) )
                        // special item attack
                        foo = type->hit_ob(me, target, damage);

                if( stringp(foo) ) msg += foo; else
                if( intp(foo) ) damage += foo; else
                if( mapp(foo) ) {
                        msg += foo["msg"];
                        damage += foo["damage"];
                }

                // do enforce effect
                my = me->query_entire_dbase();
                if( (jiali = my["jiali"]) > 0 && my["neili"] >= jiali ) {
                        // eforced
                        my["neili"] -= jiali;

                        if( objectp(ob = query_temp("armor/armor", target)) && ob->query_magic_item() == "天地日月靈珠" )
                                jiali /= 2;

                        if( type == REMOTE_ATTACK || type == SPECIAL_ATTACK ) {
                                damage_bonus = SKILLS_D->enforce_power(me, jiali);
                        } else {
                                damage_bonus = SKILLS_D->enforce_power(me, jiali);

                                if( !living(target) ) break;
                                // check special force effort
                                skill = target->query_skill_mapped("force");
                                if( stringp(skill) && (!objectp(ob = query_temp("armor/surcoat", me)) || ob->query_magic_item() != "真武寶石") ) {
                                        foo = SKILL_D(skill)->valid_damage(me, target, damage_bonus);
                                        if( stringp(foo) ) msg += foo; else
                                        if( intp(foo) ) damage_bonus += foo; else
                                        if( mapp(foo) ) {
                                                msg += foo["msg"];
                                                damage_bonus += foo["damage"];
                                        }
                                }
                        }
                        damage += damage_bonus;
                }

                if( damage < 1 ) break;

                if( query("breakup", me) ) damage += damage * 10 / 100;

                // 元神
                if( query("yuanshen/status", me) )
                        damage += damage * query("yuanshen/status", me) / 100;

                if( objectp(ob = query_temp("armor/surcoat", target)) && ob->query_magic_item() == "流行趕月" )
                        damage -= damage * 5 / 100;

                // 發揮披風--赤煉龍膽的特效
                if( objectp(ob = query_temp("armor/surcoat", me)) && ob->query_magic_item() == "赤煉龍膽" )
                {
                        msg += HIR "\n$N" HIR "的赤煉龍膽寶石發出一道奇異的光芒，一條發光的"
                               "的赤龍張牙舞爪般的撲向$n" HIR "。\n" NOR;
                        damage += damage / 2;
                }

                // 發揮勛章--碧海殘□的作用
                if( objectp(ob = query_temp("armor/charm", me)) && ob->query_magic_item() == "碧海殘□" )
                {
                        msg += HIC "$N" HIC "的碧海殘□青光一閃，「碧海蒼穹」呈現，發出震耳般的海嘯聲 ……\n" NOR;
                        damage += damage / 2;
                        if( !target->is_busy() )
                                target->start_busy(3);
                }

                else
                // 發揮勛章--麒麟火的作用
                if( objectp(ob = query_temp("armor/charm", me)) && ob->query_magic_item() == "麒麟火" )
                {
                        msg += HIR "$N" HIR "的麒麟火發閃出火紅般的光芒，「麒麟聖火」長久不熄，令人難以喘息 ……\n" NOR;
                        damage += damage / 2;
                        if( query("neili", target) >= 300 )
                        {
                                addn("neili", -300, target);
                                addn("neili", 300, me);
                        }
                }

                // 發揮披風--孔 雀 石的效果
                if( objectp(ob = query_temp("armor/surcoat", target)) && ob->query_magic_item() == "孔雀石" )
                {
                        msg += HIG + target->name() + HIG "的孔雀石發出一道奇異的光芒，數道青光將" +
                               target->name() +  HIG "籠罩，但見一只發光的孔\n雀跳躍飛舞，卻不讓任何人靠近。\n" NOR;

                        // 發揮披風--真武寶石的效果
                        if( objectp(ob = query_temp("armor/surcoat", me)) && ob->query_magic_item() == "真武寶石" )
                        {
                                msg += HIY "可是" + me->name() + HIY "的真武寶石發出一道亮光，那發光"
                                       "的孔雀頓時消失不見。\n" NOR;

                        }
                        else
                                return msg;
                }

                if( query_temp("apply/double_damage", me)>0){
                        if( random(100)<query_temp("apply/double_damage", me)){
                                int damage2, scale;
                                damage2 = random(damage);
                                scale = 100 + damage2 * 10 / damage * 10;
                                damage += damage2;
                                msg += HIY "$N" HIY "福至心靈，有如神助，一擊之中竟產生多重傷害，給予$n" HIY "造成「" + scale + "%」的傷害！\n" NOR;
                        }
                }

                // do str effect
                str=me->query_str()+query_temp("str", me);
                if( query("jingmai/finish", me) )
                        str += ZHOUTIAN_D->query_jingmai_effect("str");
                str += query("jingmai/str", me);
                if( str < 20 )
                        damage += damage * str / 50;
                else if( str < 40 )
                        damage += damage * ((str - 20) / 2 + 20) / 50;
                else
                        damage += damage / 50 * ((str - 40) / 4 + 30);

                // recalculate damage
                if( damage > 1500 )
                        damage = (damage - 1500) / 4 + 1000;
                else if( damage > 500 )
                        damage = (damage - 500) / 2 + 500;

                // do damage
#ifdef REDUCE_PVP_DAMAGE
                damage = COMBAT_D->reduce_damage(me, target, damage);
#endif
                // 發揮化甲術的特效
                if( hjs > 100 )
                        armor = armor - armor / 100 * hjs / 100;

                if( random(100) >= query_temp("apply/through_armor", me) )
                        wound = (damage - random(armor)) * percent / 100;
                else
                        wound = damage * percent / 100;

                if( me->query_skill("kunlun-wuji", 1) >= 125 )
                        wound += wound + me->query_skill("kunlun-wuji", 1) / 125 * 100;

                // 血影大法傷內力效果
                if( me->query_skill("xueying-dafa", 1) >= 100 )
                {
                        addn("neili", -1 * (me->query_skill("xueying-dafa", 1) + me->query_skill("xuedao-daofa", 1)) / 12, target);
                        if( query("neili", target) < 0 )
                                set("neili", 0, target);
                }

                damage = target->receive_damage("qi", damage, me);
                if( damage < 1 )
                        msg += BLU "$n" BLU "神奇的化解了$N" BLU "這一擊的所有傷害！\n" NOR;

                if( wound > 0 ) {
#ifdef REDUCE_PVP_DAMAGE
                        wound = COMBAT_D->reduce_wound(me, target, wound);
#endif
                        wound = target->receive_wound("qi", wound, me);
                }
                else wound = 0;

                if( functionp(final) ) final = evaluate(final);
                if( stringp(final) ) {
                        if( sscanf(final, "%s@%s", final, limb) == 2 ) {
                                if( sscanf(final, "%s:%s", result, damage_type) != 2 ) {
                                        result = HIR "這招打了個正中！";
                                        damage_type = final;
                                }
                                if( sscanf(limb, "?%*s") ) {
                                        // auto select limb
                                        limbs=query("limbs", target);
                                        if( !arrayp(limbs) ) {
                                                limbs = ({ "身體" });
                                                set("limbs", limbs, target);
                                        }
                                        limb = limbs[random(sizeof(limbs))];
                                }

                                // indicate damage type & limb
                                final = replace_string(damage_msg(damage, damage_type), "$l", limb);
                                final = replace_string(final, "$n", "$n" HIR);
                                final = replace_string(final, "$N", "$N" HIR);
                                final = replace_string(final, "$p", "$p" HIR);
                                final = replace_string(final, "$P", "$P" HIR);
                                if( weapon )
                                        final = replace_string(final, "$w", weapon->name() + HIR);
                                final = result + HIR + final + NOR;
                        }
                        msg += final;
                        /*
                        msg +="($n"+status_msg(query("qi", target)*100/(query("max_qi", target)?
                                                   query("max_qi", target):100))+")\n";
                        */
                        msg += replace_string(report_status(target, 1), "$N", "$n");
                }
#if INSTALL_COMBAT_TEST
                msg += HIW "( $N" HIW "對$n" HIW "造成" + damage + "點傷害，" + wound + "點創傷。)\n" NOR;
#endif

                // 奇門玄術的反傷效果
                if( target->query_skill("qimen-xuanshu", 1) >= 100 )
                {
                        if( random(target->query_skill("qimen-xuanshu", 1)) > 100 && random(3) == 1 )
                        {
                                msg += HIG "$n" HIG "施展出「奇門玄術」的反傷效果，使得$N" HIG "自身同時也受到損傷。\n" NOR;
                                // 反傷
                                me->receive_damage("qi", damage * target->query_skill("qimen-xuanshu", 1) / 5000, target);
                                me->receive_wound("qi", wound * target->query_skill("qimen-xuanshu", 1) / 5000, target);

                                if( query("eff_qi", target) + wound * target->query_skill("qimen-xuanshu", 1) / 5000 <
                                    query("max_qi", target) )
                                        addn("eff_qi", wound * target->query_skill("qimen-xuanshu", 1) / 5000, target);
                                else
                                        set("eff_qi", query("max_qi", target), target);

                                if( query("qi", target) + damage * target->query_skill("qimen-xuanshu", 1) / 5000 <
                                    query("eff_qi", target) )
                                        addn("qi", damage * target->query_skill("qimen-xuanshu", 1) / 5000, target);
                                else
                                       set("qi", query("eff_qi", target), target);
                                
                                /*
                                msg += "( $N" +
                                        status_msg(query("qi", me)*100/
                                        (query("max_qi", me)?query("max_qi", me):100))+")\n";
                                */
                                msg += report_status(me, 1);
                        }
                }

                // 極品防具反噬效果
                avoid=query_temp("apply/counter_damage", target);
                if( random(100) < avoid && random(5) == 1 ) {
                        /*
                        if( objectp(cloth=query_temp("armor/armor", target)) &&
                            query("enchase/apply_prop/counter_damage", cloth) )
                                msg += BLINK + HIM + cloth->name() + BLINK + HIM "發出一道奇異眩目的紅光襲向$N！\n" NOR;
                        else
                        if( objectp(cloth=query_temp("armor/cloth", target)) &&
                            query("enchase/apply_prop/counter_damage", cloth) )
                                msg += BLINK + HIM + cloth->name() + BLINK + HIM "發出一道奇異眩目的紅光襲向$N！\n" NOR;
                        else
                        */
                                msg += BLINK + HIM "$n" BLINK + HIM "周身發出一道奇異眩目的紅光襲向$N！\n" NOR;

                        me->receive_damage("qi", damage/5, target);
                        me->receive_wound("qi", wound/5, target);
                        /*
                        msg += "( $N" +
                                status_msg(query("qi", me)*100/
                                (query("max_qi", me)?query("max_qi", me):100))+")\n";
                        */
                        msg += report_status(me, 1);
                }
                if( query("special_skill/monster", target) && random(5) == 1){
                        message_vision(HIG "$N" HIG "施展出「天妖臨世」，$n" HIG "自身同時也受到損傷。\n" NOR, target, me);
                        me->receive_damage("qi", damage, target);
                        if( random(2) == 1 ) me->receive_wound("qi", wound, target);
                        /*
                        msg += "( $N" +
                                status_msg(query("qi", me)*100/
                                (query("max_qi", me)?query("max_qi", me):100))+")\n";
                        */
                        msg += report_status(me, 1);
                }
                break;
        }

        if( foo_after_hit ) msg += foo_after_hit;
        if( foo_before_hit ) msg = foo_before_hit + msg;
        // Clear the special message info after damage info
        foo_before_hit = 0;
        foo_after_hit = 0;

        return msg;
}

//  auto_perform()
int auto_perform(object me, object target, string skill)
{
        int l;
        string dir;
        string file;
        mixed *all_file;

        if( !stringp(dir = SKILL_D(skill) + "/") ||
            file_size(dir) != -2 )
                return 0;

        if( file_size(dir + "perform/") == -2 ) {
                all_file = get_dir(dir + "perform/");
                if( !sizeof(all_file) )
                        all_file = get_dir(dir);
                else
                        dir += "perform/";
        } else
                all_file = get_dir(dir);

        if( !sizeof(all_file) )
                return 0;

        all_file = filter_array(all_file, (: is_c_file($1) :));
        if( !sizeof(all_file) )
                return 0;

        file = all_file[random(sizeof(all_file))];
        l = strlen(file);
        file = dir + file[0..l-3];
        return (int)call_other(file, "perform", me, target);
}

//  fight()
//
//  This is called in the attack() defined in F_ATTACK, which handles fighting
//  in the heart_beat() of all livings. Be sure to optimize it carefully.
//
void fight(object me, object victim)
{
        object ob;
        string skill_name;
        object weapon, weapon2;
        string attack_skill;
        int double_attack;
        mapping prepare;
        string result;
        mapping my_temp;
        int i, auto_pf, pf_flag;
        string pf_skill, pf_skill1, pf_skill2;

        if( !living(me) || me->is_busy() ) return;
        if( !me->visible(victim)) return;
        if( environment(me)!=environment(victim) ) return;

        if( !mapp(my_temp = me->query_entire_temp_dbase()) )
                my_temp = ([ ]);

        auto_pf = 0;
        if( query("auto_perform", me))auto_pf=query("auto_perform", me);
        else            auto_pf = me->query_auto_perform();
        if( auto_pf < 0 ) auto_pf = 0;
        if( auto_pf > 10 ) auto_pf = 10;

        prepare = me->query_skill_prepare();
        if( sizeof(prepare) && stringp(attack_skill = (keys(prepare))[0]) ) {
                if( !query_temp("weapon", me) && (attack_skill == "sword" ||
                    attack_skill == "blade" || attack_skill == "hammer" || attack_skill == "whip") ) {
                        for (i=0; i<sizeof(keys(prepare)); i++)
                                me->prepare_skill((keys(prepare))[i]);
                        tell_object(me, HIY "你現在採用" HIR "空手技能" HIY "進行攻擊，"
                                        HIY "取消所備" HIR "兵器技能" HIY "攻擊。\n" NOR);
                }
        }

        if( weapon = my_temp["weapon"] )
                attack_skill=query("skill_type", weapon);
        else if( !prepare || sizeof(prepare) == 0 ) attack_skill = "unarmed";
        else if( sizeof(prepare) ) attack_skill = (keys(prepare))[0];
        if( attack_skill == "pin" ) attack_skill = "sword";

        attack_skill = me->query_skill_mapped(attack_skill);

        if( auto_pf == 1 || (random(auto_pf) == 1) ) {
                pf_flag = 0;
                if( attack_skill ) {
                        pf_skill1 = attack_skill;
                        pf_flag = 1;
                }
                if( !weapon && prepare && sizeof(prepare) > 1 )
                        pf_skill2 = me->query_skill_mapped((keys(prepare))[1]);
                if( pf_skill2 ) pf_flag = 2;
                if( pf_flag == 1 )
                        auto_perform(me, victim, pf_skill1);
                else if( pf_flag == 2 ) {
                        if( random(2) ) pf_skill = pf_skill1;
                        else pf_skill = pf_skill2;
                        if( !auto_perform(me, victim, pf_skill) )
                                auto_perform(me, victim, (pf_skill == pf_skill1) ?
                                                        pf_skill2 : pf_skill1);
                }
        }

        if( !objectp(me) || !objectp(victim) ) return;
        if( me->is_busy() ) return;

        if( attack_skill && random(me->query_dex()) >= 8 )
                double_attack = (sizeof(prepare) >= 2 && !weapon) ||
                        SKILL_D(attack_skill)->double_attack();

        // If victim is busy or unconcious, always take the chance to make an attack.
        if( victim->is_busy() || !living(victim) ) {
                set_temp("guarding", 0, me);
                if( !victim->is_fighting(me) ) victim->fight_ob(me);
                do_attack(me,victim,query_temp("weapon", me),TYPE_QUICK);

                if( me->is_fighting(victim) && victim->is_fighting(me) ) {
                        if( double_attack ) {
                                set_temp("action_flag", 1, me);
                                do_attack(me, victim, my_temp["weapon"], TYPE_QUICK);
                                set_temp("action_flag", 0, me);
                        } else // 兵器互備
                        if( objectp(weapon) &&
                            objectp(weapon2=query_temp("secondary_weapon", me)) &&
                            sizeof(me->query_skill_prepare()) > 1 &&
                            me->query_skill_prepared(query("skill_type", weapon)) &&
                            me->query_skill_prepared(query("skill_type", weapon2))) {
                                if( query_temp("hand_flag", me) ) // 上次使用的是左手
                                        do_attack(me, victim, weapon, TYPE_QUICK, 1);
                                else
                                        do_attack(me, victim, weapon2, TYPE_QUICK, 2);
                        }
                }
                /*
                if( living(victim) ) {
                        if( stringp(attack_skill) ) {
                                set_temp("action_flag", 1, me);
                                SKILL_D(attack_skill)->do_interlink(me, victim);
                                set_temp("action_flag", 0, me);
                        }
                }
                */
        // Else, see if we are brave enough to make an aggressive action.
        } else if( me->query_str() > random(victim->query_str() * 3 / 4) ) {
                set_temp("guarding", 0, me);
                if( !victim->is_fighting(me) ) victim->fight_ob(me);
                do_attack(me, victim, my_temp["weapon"], TYPE_REGULAR);

                if( me->is_fighting(victim) && victim->is_fighting(me) ) {
                        if( double_attack ) {
                                set_temp("action_flag", 1, me);
                                do_attack(me, victim, my_temp["weapon"], TYPE_REGULAR);
                                set_temp("action_flag", 0, me);
                        } else // 兵器互備
                        if( objectp(weapon) &&
                            objectp(weapon2=query_temp("secondary_weapon", me)) &&
                            sizeof(me->query_skill_prepare()) > 1 &&
                            me->query_skill_prepared(query("skill_type", weapon)) &&
                            me->query_skill_prepared(query("skill_type", weapon2))) {
                                if( query_temp("hand_flag", me) ) // 上次使用的是左手
                                        do_attack(me, victim, weapon, TYPE_REGULAR, 1);
                                else
                                        do_attack(me, victim, weapon2, TYPE_REGULAR, 2);
                        }
                }
                /*
                if( stringp(attack_skill) ) {
                        set_temp("action_flag", 1, me);
                        SKILL_D(attack_skill)->do_interlink(me, victim);
                        set_temp("action_flag", 0, me);
                }
                */

        // Else, we just start guarding.
        }else if( !query_temp("guarding", me)){
                set_temp("guarding", 1, me);
                message_combatd( guard_msg[random(sizeof(guard_msg))], me, victim, "");
                return;
        } else return;
}

//  auto_fight()
//
//  This function is to start an automatically fight. Currently this is
//  used in "aggressive", "vendetta", "hatred", "berserk" fight.
//
void auto_fight(object me, object obj, string type)
{
        // Don't let NPC autofight NPC.
        if( !playerp(me) && !playerp(obj) ) return;

        if( query_temp("owner", me) == obj ||
            obj->quety_temp("owner") == me )
                return;

        // Because most of the cases that we cannot start a fight cannot be checked
        // before we really call the kill_ob(), so we just make sure we have no
        // aggressive callout wating here.
        if( query_temp("looking_for_trouble", me))return ;
        set_temp("looking_for_trouble", 1, me);

        // This call_out gives victim a chance to slip trough the fierce guys.
        call_out("start_" + type, 0, me, obj);
}

void start_berserk(object me, object obj)
{
        int shen, sb_shen;

        if( !me || !obj ) return;               // Are we still exist( not becoming a corpse )?
        set_temp("looking_for_trouble", 0, me);

        if( me->is_fighting(obj)                // Are we busy fighting?
        ||  !living(me)                         // Are we capable for a fight?
        ||  environment(me)!=environment(obj)   // Are we still in the same room?
         || query("no_fight", environment(me))//Areweinapeaceroom?
        )   return;

        message_vision("$N用一種異樣的眼神掃視著在場的每一個人。\n", me);
        if( (shen < -50000 || sb_shen>100000) && me->query_per()>random(obj->query_per())*2 &&  !wizardp(obj) ) {
                message_vision("$N對著$n喝道：" + RANK_D->query_self_rude(me)
                        + "看你實在很不順眼，去死吧。\n", me, obj);
                me->want_kill(obj);
                me->kill_ob(obj);
                obj->fight_ob(me);
        } else {
                message_vision("$N對著$n喝道：喂！" + RANK_D->query_rude(obj)
                        + "，" + RANK_D->query_self_rude(me) + "正想找人打架，陪我玩兩手吧！\n",me, obj);
                me->fight_ob(obj);
                obj->fight_ob(me);
        }
}

void start_hatred(object me, object obj)
{
        if( !me || !obj ) return;               // Are we still exist( not becoming a corpse )?
        set_temp("looking_for_trouble", 0, me);

        if( me->is_fighting(obj)                // Are we busy fighting?
        ||  !living(me)                         // Are we capable for a fight?
        ||  environment(me)!=environment(obj)   // Are we still in the same room?
         || (query("no_fight", environment(me))//Areweinapeaceroom?
        &&  !me->is_demogorgon() && !obj->is_demogorgon())
        )   return;

        if( query_temp("owner", me) == query("id", obj) ||
            query_temp("owner", obj) == query("id", me) )
                return;

        // We found our hatred!Charge!
        message_vision( catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);
        me->want_kill(obj);
        me->kill_ob(obj);
        obj->fight_ob(me);

        if( !playerp(me) && me->is_busy() && !intp(me->query_busy()) )
                me->interrupt_me(me);
}

void start_vendetta(object me, object obj)
{
        if( !me || !obj ) return;               // Are we still exist( not becoming a corpse )?
        set_temp("looking_for_trouble", 0, me);

        if( me->is_fighting(obj)                // Are we busy fighting?
        ||  !living(me)                         // Are we capable for a fight?
        ||  environment(me)!=environment(obj)   // Are we still in the same room?
         || query("no_fight", environment(me))//Areweinapeaceroom?
        )   return;

        // We found our vendetta opponent!Charge!
        me->want_kill(obj);
        me->kill_ob(obj);
        obj->fight_ob(me);
}

void start_aggressive(object me, object obj)
{
        if( !me || !obj ) return;               // Are we still exist( not becoming a corpse )?
        set_temp("looking_for_trouble", 0, me);

        if( me->is_fighting(obj)                // Are we busy fighting?
        ||  !living(me)                         // Are we capable for a fight?
        ||  environment(me)!=environment(obj)   // Are we still in the same room?
         || query("no_fight", environment(me))//Areweinapeaceroom?
        )   return;

        // We got a nice victim!Kill him/her/it!!!
        me->want_kill(obj);
        me->kill_ob(obj);
        obj->fight_ob(me);
}

int player_escape(object killer, object ob)
{
        object iob;
        string msg;

        if( !objectp(ob) ) return 0;
        if( !playerp(ob) ) return 0;

        if( query("combat/which_day", ob) == time()/86400 &&
            query("total_count", ob)>0 )
                return 0;

        if( !killer ) killer = ob->query_defeated_by();
        if( !killer)killer=query("query_last_damage", ob);
        if( !killer || !playerp(killer) ||
            !killer->is_want_kill(query("id", ob)) )
                return 0;

        if( query("no_newbie", ob) ||
            query("combat/WPK", ob) ||
            (query("age", ob) >= 20 &&
            query("combat_exp", ob) >= 20000000) )
                return 0;

        switch( random(7) )
        {
        case 0:
                msg = "突然只聽幽幽一聲長嘆，一掌輕輕按來。$N大吃一驚，不及"
                      "多加思索，只是抬手一格。匆忙之間只怕對手過于厲害，難"
                      "以招架，急忙向後躍開。卻見來人並不追擊，只是一伸手拎"
                      "起$n，轉身飄然而去，仙蹤渺然。\n";
                break;

        case 1:
                msg = "$N將$n打翻在地，“哈哈”一聲笑聲尚未落下，只聽有人冷"
                      "哼一聲，忽然間掌風襲體，$N頓感呼吸不暢，幾欲窒息，慌"
                      "忙中急忙退後，待得立穩腳跟，卻見$n早已無影無蹤。\n";
                break;

        case 2:
                msg = "一人忽然掠至，喝道：“豈有此理？我龍島主最恨此欺善怕"
                      "惡之輩，休走！”說罷一掌擊來，$N奮力招架，一招之下幾"
                      "欲吐血！只見來人輕輕提起$n，冷笑兩聲，轉身離去，$N驚"
                      "駭之下，竟然說不出一句話來。\n";
                break;

        case 3:
                msg = "突然一人喝道：“且慢！”只見一道黑影掠到，飛起一腳將"
                      "$N踢了個跟頭，左手拎起$n，冷冷對$N道：“今日所幸尚未"
                      "傷人命，你作惡不甚，饒你去吧！”$N捂胸運氣，不住喘息"
                      "，眼睜睜的看著來人去了。\n";
                break;

        case 4:
                msg = "$N跨前一步，忽然看到面前已多了兩人，一胖一瘦，一喜一"
                      "怒，不由暗生疑竇。一人手中亮出一面銅牌，笑道：“這位" +
                      RANK_D->quert_respect(killer)+ "，這面罰惡銅牌你收下可"
                      "好？”$N聽了大吃一驚，手只是一軟，哪裡還敢搭半句話？"
                      "那瘦子冷冷看了過來，目光如電，$N訕訕笑了兩聲，目送兩"
                      "人帶了$n逍遙而去。\n";

        case 5:
                msg = "恰在此時，正逢一老者路過，只見他微一顰眉，喝道：“兀"
                      "那" + RANK_D->query_rude(killer)+ "，傷人做甚？”$N大"
                      "怒道：“你是何人，如此囂張？”老者大怒，一掌拍落，$N"
                      "向上只是一格，“噗嚕”一下雙腿陷入土中，足有半尺。老"
                      "者森然道：“我乃俠客島木島主是也，如有不服，恭候大駕"
                      "！”此時$N內息如狂，連句場面話也說不出來，只能眼看$n"
                      "被那木島主帶了離去。\n";
                break;

        default:
                msg = "忽聽“哈哈”一陣長笑，一人道：“龍兄，想不到我們三十"
                      "年不履中土，這些武林高手卻是越來越不長進了！”另一人"
                      "道：“正是，看來賞善罰惡，漫漫無期，終無盡頭。”$N聽"
                      "得大汗涔涔而下，環顧四方卻無一人，轉回頭來，更是大吃"
                      "一驚！連$n也不見了。\n";
                break;
        }

        if( (environment(killer) == environment(ob)) &&
            killer->is_fighting(ob) ) {
                msg = replace_string(msg, "$n", ob->name());
                message_sort(msg, killer);
        } else {
                msg = "正逢一老者路過，見了" + ob->name() + "暈倒在地，嘆口"
                      "氣，將他扶起帶走了。\n";
                message("vision", msg, environment(ob));
        }

        /*
        foreach (iob in all_inventory(ob))
                if( !query("money_id", iob) &&
                    !query("equipped", iob) )
                        iob->move(environment(ob));
        */

        // 初始化玩家的狀態
        ob->clear_condition();
        ob->remove_killer(killer);
        killer->remove_killer(ob);

        // 通緝傷人兇手
        if( !killer->query_condition("killer") ) {
                msg = "聽說官府發下海捕文書，緝拿傷人兇手" +
                             killer->name(1) + "。";
                killer->apply_condition("killer", 500);
        } else {
                msg = "聽說官府加緊捉拿累次傷人的暴徒" +
                             killer->name(1) + "。";
                killer->apply_condition("killer", 800 +
                        (int)killer->query_condition("killer"));
        }
        CHANNEL_D->do_channel(this_object(), "rumor", msg);

        ob->move("/d/xiakedao/shiroom24");
        set("startroom", "/d/xiakedao/shiroom24", ob);
        ob->revive();
        set("eff_qi",query("max_qi",  ob), ob);
        set("eff_jing",query("max_jing",  ob), ob);
        set("qi", 0, ob);
        set("jing", 0, ob);

        if( intp(ob->query_busy()) )
                ob->start_busy(30);

        tell_object(ob, "你睜開眼來，看到兩位老者正在靜坐修煉。\n"
                    HIG "龍島主告訴你：" + RANK_D->query_respect(ob) +
                        "，你要想離島不妨和我說一聲(ask long about 離島)。\n" NOR);
        return 1;
}

// This function is to announce the special events of the combat.
// This should be moved to another daemon in the future.
void announce(object ob, string event)
{
        object *target;
        int i;

        switch( event ) {
        case "dead":
                message_vision(NOR "\n$N撲在地上掙紮了幾下，腿一伸，口中噴出幾口"
                               HIR "鮮血" NOR "，死了！\n\n" NOR, ob);
                if( environment(ob) && playerp(environment(ob)) && living(environment(ob)) )
                        tell_object(environment(ob),NOR "\n" + ob->name() + "撲騰了幾下，腿一伸，口中噴出幾口"
                               HIR "鮮血" NOR "，死了！\n\n" NOR);
                break;
        case "unconcious":
                message_vision("\n$N腳下一個不穩，跌在地上一動也不動了。\n\n", ob);
                player_escape(0, ob);
                break;
        case "revive":
                message_vision("\n$N慢慢睜開眼睛，清醒了過來。\n\n", ob);
                break;
        }
}

void winner_reward(object winner, object victim)
{
        object owner;
        int temp;
        int td;
        mapping today;

        owner=query_temp("owner", winner);
        if( objectp(owner) )
                winner = owner;

        winner->defeated_enemy(victim);

        if( !playerp(winner) || wizardp(victim) && 0 )
                return;

        if( !winner->is_want_kill(query("id", victim)) )
                // only if I want kill ob, I will record it.
                return;

        addn("combat/DPS", 1, winner);
        if( victim->is_not_bad())  addn("combat/DPS_NOTBAD", 1, winner);
        if( victim->is_not_good()) addn("combat/DPS_NOTGOOD", 1, winner);
        if( victim->is_bad())      addn("combat/DPS_BAD", 1, winner);
        if( victim->is_good())     addn("combat/DPS_GOOD", 1, winner);

        if( victim->query_condition("killer") )
                return;

        log_file("static/killrecord",
                 sprintf("%s %s defeat %s\n",
                         log_time(), log_id(winner), log_id(victim)));

        td = time() / 86400;
        today=query("combat/today", winner);
        if( !mapp(today) || today["which_day"] != td ) {
                today = ([ "which_day" : td,
                           "total_count" : 1,
                           query("id", victim):1,]);
        } else {
                // count how many times that winner hit the victim to unconcious
                temp=++today[query("id", victim)];
                if( query("newbie", victim)){
                        today[query("id", victim)] = temp + 1;
                        temp = today[query("id", victim)];
                }

                if( temp == query("pk_perman") ) {
                        // reach limit
                        tell_object(winner, BLINK HIR "\n今天你已經打暈" +
                                    victim->name() + chinese_number(temp) +
                                    "次了，手下留"
                                    "情吧，否則麻煩可要找上門了。\n" NOR);
                } else if( temp > query("pk_perman") )
                        // too many times
                        set("combat/need_punish", "這廝逼人太甚，真是豈有此理！", winner);

                // count how many users that winner hit to unconcious
                temp = ++today["total_count"];
                if( query("newbie", victim)){
                        today["total_count"] = temp + 5;
                        temp = today["total_count"];
                }

                if( temp == query("pk_perday") ) {
                        // reach limit
                        tell_object(winner, BLINK HIR "\n今天你已經打暈" +
                                    chinese_number(temp) + "次玩家了，手下留"
                                    "情吧，否則麻煩可要找上門了。\n" NOR);
                } else if( temp > query("pk_perday") )
                        // too many users
                        set("combat/need_punish", "喪盡天良，大肆屠戮，罪無可恕！", winner);
        }
        set("combat/today", today, winner);
}

void family_kill(object killer, object victim)
{
        // 以下為門派功績處理
        if( !objectp(killer) || !playerp(killer) ||
            !objectp(victim) ||
            !stringp(query("family/family_name", killer)) )
                return;

        if( query("family/family_name", killer) !=
            query("family/family_name", victim) )
                return;

        // quest 任務
        if( stringp(query("quest/id", killer)) &&
            query("quest/id", killer) == query("id", victim) )
                return;

        // free 任務
        if( !playerp(victim) && query_temp("quest_ob", victim) )
                return;

        // ultra 任務
        if( !playerp(victim) && stringp(query_temp("quester", victim)) &&
            query_temp("quester", victim) == query("id", killer) )
                return;

        // ultra 任務
        if( !playerp(victim) && (query("quest_dg", killer) ||
            query("quest_hs", killer) || query("quest_sn", killer) ||
            query("quest_kh", killer)) )
                return;

        if( playerp(victim) ) {
                addn("family/gongji", -500, killer);
                tell_object(killer, sprintf("由于你殘害同門弟子，師門功績下降 %d 點。\n", 500));
        } else {
                if( killer->is_apprentice_of(victim) ) {
                        addn("family/gongji", -1000, killer);
                        tell_object(killer,sprintf("由于欺師滅組的行為，師門功績下降 %d 點。\n", 1000));
                }
                else if( query("family/generation", killer)>query("family/generation", victim)){
                        addn("family/gongji", -600, killer);
                        tell_object(killer,sprintf("由于你殘害同門尊長，師門功績下降 %d 點。\n", 600));
                }
                else {
                        addn("family/gongji", -300, killer);
                        tell_object(killer,sprintf("由于你殘害同門，師門功績下降 %d 點。\n", 300));
                }
        }
        if( query("family/gongji", killer)<0 )
                delete("family/gongji", killer);
}

void killer_reward(object killer, object victim)
{
        object owner, charm;
        string vmark;
        string msg = "莫名其妙地死了";
        string follow_msg = 0;
        object weapon;
        mapping actions, quest, bonus;
        int shen_delta,exp_damage;
        mixed exp_lost;
        mapping ks, vs, kcombat;
        int flag, no_loss = 0;
        int exp, pot, score;
        int kill_bonus;

        if( !objectp(victim) )
                return;

        if( objectp(killer) ) {
                owner=query_temp("owner", killer);
                if( objectp(owner) )
                        killer = owner;
        }

        // This while is only to enable "break"
        vs = victim->query_entire_dbase();
        while( 1 )
        {
                if( !objectp(killer) )
                        break;

                // call the killer's override function
                killer->killed_enemy(victim);

                if( !objectp(killer) || !playerp(killer) )
                        break;

                // assure the killer's dbase
                ks = killer->query_entire_dbase();
                if( !mapp(kcombat = ks["combat"]) ) {
                        kcombat = ([ ]);
                        ks["combat"] = kcombat;
                }

                if( ks["combat_exp"]/2 < vs["combat_exp"] ) {
                        if( ks["combat_exp"] >= 100000 &&
                            ks["combat_exp"] >= vs["combat_exp"] * 2 / 3 ) {
                                // adjust experience
                                if( !ks["experience"] )
                                        ks["experience"] = 0;
                                killer->improve_experience(1 + random(5));
                        }

                        // adjust shen
                        shen_delta = -vs["shen"] / 2;
                        if( shen_delta > 100 ) {
                                // 非線性校正獲得的正神
                                shen_delta = (shen_delta - 100) / 3 + 100;

                                if( shen_delta > 200 )
                                        shen_delta = (shen_delta - 200) / 3 + 200;

                                if( shen_delta > 300 )
                                        shen_delta = (shen_delta - 300) / 3 + 300;
                        } else
                        if( shen_delta < -100 ) {
                                // 非線性校正獲得的負神
                                shen_delta = (shen_delta + 100) / 3 - 100;

                                if( shen_delta < -200 )
                                        shen_delta = (shen_delta + 200) / 3 - 200;

                                if( shen_delta < -300 )
                                        shen_delta = (shen_delta + 300) / 3 - 300;
                        }

                        ks["shen"] += shen_delta;
                }

                // weapon get the bonus
                if( weapon=query_temp("weapon", killer) )
                        weapon->killer_reward(killer, victim);

                if( weapon=query_temp("armor/finger", killer) )
                        weapon->killer_reward(killer, victim);

                if( weapon=query_temp("armor/hands", killer) )
                        weapon->killer_reward(killer, victim);

                if( weapon=query_temp("secondary_weapon", killer) )
                        weapon->killer_reward(killer, victim);

                if( weapon=query_temp("handing", killer) )
                        weapon->killer_reward(killer, victim);

                // record the user's killing
                if( playerp(victim) ) {
                        if( !intp(kcombat["PKS"]) )
                                kcombat["PKS"] = 1;
                        else
                                kcombat["PKS"]++;

                        //killer->set("pktime", (int)killer->query("mud_age"));
                        set("combat/pktime", time(), killer);

                        // do family action
                        FAMILY_D->family_kill(killer, victim);

                        // do league action
                        LEAGUE_D->league_kill(killer, victim);

                        // do bunch action
                        BUNCH_D->bunch_kill(killer, victim);

                        //if( victim->query_condition("killer") ) {
                        if( query("pk_score", victim)>0){
                                // 獎勵設置
                                if( query("combat/today/"+query("id", killer), victim) )
                                        addn("pk_score", -1, victim);
                                else {
                                        kill_bonus=query("combat_exp", victim)/100;
                                        if( kill_bonus > 1000000 ) kill_bonus = 1000000;
                                        addn("combat_exp", kill_bonus, killer);
                                        tell_object(killer, "你獲得了" + kill_bonus + "點經驗獎勵。\n");
                                }

                                set("combat/punish", time(), victim);
                                follow_msg = "聽說殺人兇手" + victim->name(1) +
                                             "被" + killer->name(1) + "在" +
                                             environment(victim)->short() + HIM
                                             "就地正法了。";
                                break;
                        }

                        if( playerp(killer) && killer->in_array() && killer->query_array_status() ) {
                                follow_msg = sprintf("%s(%s)被%s(%s)帶領的『%s』做掉啦！！\n",
                                                victim->name(1),
                                                capitalize(query("id", victim)),
                                                killer->query_array_master()->name(1),
                                                capitalize(query("id", killer->query_array_master())),
                                                killer->query_array_name());
                        }

                       if( playerp(killer) && killer->in_team() && objectp(killer->query_team_leader()) ) {
                                follow_msg = sprintf("%s(%s)被%s(%s)帶領的隊伍做掉啦！！\n",
                                                victim->name(1),
                                                capitalize(query("id", victim)),
                                                killer->query_team_leader()->name(1),
                                                capitalize(query("id", killer->query_team_leader())));
                        }

                        if( !killer->is_want_kill(vs["id"]) )
                                break;

                        if( !intp(kcombat["WPK"]) )
                                kcombat["WPK"] = 1;
                        else
                                kcombat["WPK"]++;

                        if( !killer->query_condition("killer") ) {
                                follow_msg = "聽說官府發下海捕文書，緝拿殺人兇手" +
                                             killer->name(1) + "。";
                                killer->apply_condition("killer", 500);
                        } else {
                                follow_msg = "聽說官府加緊捉拿累犯重案的暴徒" +
                                             killer->name(1) + "。";
                                killer->apply_condition("killer", 800 +
                                        (int)killer->query_condition("killer"));
                        }

                        addn("pk_score", 1, killer);
                        set("pk_score_time", time(), killer);
                        
                        HISTORY_D->add_history("PK_SCORE", query("id", killer), sprintf("殺死玩家 %s(%s)，年齡 %d、等級 %d，對手等級 %d\n", 
                                query("name", victim), query("id", victim), query("age", killer), query("level", killer), query("level", victim)));     
                        // be killed
                        HISTORY_D->add_history("BK_SCORE", query("id", victim), sprintf("被玩家 %s(%s)殺死，年齡 %d、等級 %d，對手等級 %d\n", 
                                query("name", killer), query("id", killer), query("age", victim), query("level", victim), query("level", killer))); 
                                   
                        // assure data of kcombat
                        if( !intp(kcombat["WPK_NOTBAD"]) ) kcombat["WPK_NOTBAD"] = 0;
                        if( !intp(kcombat["WPK_NOTGOOD"]) ) kcombat["WPK_NOTGOOD"] = 0;
                        if( !intp(kcombat["WPK_GOOD"]) ) kcombat["WPK_GOOD"] = 0;
                        if( !intp(kcombat["WPK_BAD"]) ) kcombat["WPK_BAD"] = 0;

                        // record the combat info.
                        if( victim->is_not_bad() )  kcombat["WPK_NOTBAD"]++;
                        if( victim->is_not_good() ) kcombat["WPK_NOTGOOD"]++;
                        if( victim->is_good() )     kcombat["WPK_GOOD"]++;
                        if( victim->is_bad() )      kcombat["WPK_BAD"]++;
                        break;
                } else {
                        if( mapp(query("drops", victim)) )
                                EQUIPMENT_D->killer_reward(killer,victim,query("drops", victim));

                        // 任務
                }

                if( vs["can_speak"] )
                        if( !intp(kcombat["MKS"]) )
                                kcombat["MKS"] = 1;
                        else
                                kcombat["MKS"]++;

                family_kill(killer, victim);
                quest_kill(killer, victim);

                break;
        }

        // die penalty & message of victim
        if( playerp(victim) ) {
                // clear punish info.
                delete("combat/need_punish", victim);

                // remove vendetta
                map_delete(vs, "vendetta");

                // 有tianshi charm且不被通緝死亡無損失
                if( objectp(charm = present("tianshi charm", victim)) /*&& !victim->query_condition("killer")*/ )
                {
                        set_temp("tianshi_charm", 1, victim);
                        no_loss = 1;
                }

                // 被玩家殺死且自己受到保護死亡無損失
                else
                if( objectp(killer) && playerp(killer) &&
                    (query("age", victim)<20 ||
                    query("combat_exp", victim)<20000000) &&
                    !query("no_newbie", victim) &&
                    !query("combat/WPK", victim) )
                        no_loss = 1;

                // 被玩家殺死且殺手年紀小于20歲或經驗小于2000萬死亡無損失
                else
                if( objectp(killer) && playerp(killer) &&
                    (query("age", killer)<20 ||
                    query("combat_exp", killer)<20000000) )
                        no_loss = 1;

                // clear all condition
                victim->clear_condition();

                if( !no_loss ) {
                        // adjust shen
                        vs["shen"] -= vs["shen"] / 10;
                        if( vs["max_neili"] >= 20 )
                                vs["max_neili"] -= 20;
                        else
                                vs["max_neili"] = 0;

                        // adjust combat exp.
                        if( !mapp(vs["combat"]) ) exp_damage = 1;
                        else exp_damage = vs["combat"]["WPK"];
                        if( exp_damage < 1 ) exp_damage = 1;
                        if( exp_damage > 5 ) exp_damage = 5;

                        // pk紅名懲罰
                        if( vs["pk_score"] > 3 )
                                exp_damage += 5;
                        else if( vs["pk_score"] >= 1 )
                                exp_damage += 2;

                        exp_lost = vs["combat_exp"] * exp_damage / 5000;
                        vs["combat_exp"] -= exp_lost;

                        if( killer )
                                addn("combat/WPKEXP", exp_lost, killer);
                        addn("combat/dieexp", exp_lost, victim);
                        set("combat/last_dieexp", exp_lost, victim);

                        // adjust weiwang
                        vs["weiwang"] -= vs["weiwang"] / 10;
                        // adjust score
                        vs["score"] -= vs["score"] / 10;


                        // lost half of potential
                        if( vs["potential"] > vs["learned_points"])
                                vs["potential"] += (vs["learned_points"] - vs["potential"]) / 100;

                        // lost half of experience
                        if( vs["experience"] > vs["learned_experience"] )
                                 vs["experience"] += (vs["learned_experience"] - vs["experience"]) / 100;

                        if( !query("death", victim))flag=100;//生死玄關
                        else if( query("special_skill/zhuque", victim) && random(100) < 60 ) flag=0; 
                        else {
                                // 按照實戰經驗修正掉技能幾率
                                if( query("combat_exp", victim) >= 200000000)flag=20;
                                else if( query("combat_exp", victim) >= 80000000)flag=30;
                                else if( query("combat_exp", victim) >= 50000000)flag=40;
                                else if( query("combat_exp", victim) >= 30000000)flag=50;
                                else if( query("combat_exp", victim) >= 15000000)flag=55;
                                else if( query("combat_exp", victim) >= 8000000)flag=60;
                                else if( query("combat_exp", victim) >= 5000000)flag=65;
                                else                                               flag = 70;
                        }
                        if( random(100) < flag ) victim->skill_death_penalty();
                }

                if( objectp(charm) && no_loss )
                        destruct(charm);

                // generate message of die reason
                if( objectp(killer) && killer->is_character() ) {
                        msg = "被" + filter_color(killer->name(1));

                        if( query("race", killer) == "野獸"
                         || query("race", killer) == "蛇類"
                         || query("race", killer) == "遊魚"
                         || query("race", killer) == "昆蟲")msg+="咬死了";
                        else if( query("race", killer) == "家畜")msg+="踩死了";
                        else if( query("race", killer) == "飛禽")msg+="啄死了";
                        else {
                                if( query_temp("hand_flag", killer) )
                                        actions = query("second_actions", killer);
                                else
                                        actions = query("actions", killer);
                                switch (mapp(actions) ? actions["damage_type"] : "殺傷") {
                                case "擦傷":
                                case "割傷":
                                        msg+="砍死了";
                                        break;
                                case "刺傷":
                                        msg+="刺死了";
                                        break;
                                case "震傷":
                                case "瘀傷":
                                        msg+="擊死了";
                                        break;
                                case "內傷":
                                        msg+="震死了";
                                        break;
                                default:
                                        msg+="殺死了";
                                }
                        }
                }

                if( stringp(query_temp("die_reason", victim)) )
                        msg=filter_color(query_temp("die_reason", victim));

                delete_temp("die_reason", victim);
                CHANNEL_D->channel_broadcast("combat",
                        sprintf("聽說%s" HIR + msg + "。", victim->name(1)));

                // show the follow msg after victim die
                if( follow_msg )
                        CHANNEL_D->channel_broadcast("rumor",
                                              follow_msg);

                set("combat/last_die", filter_color(msg), victim);
                if( objectp(killer) && playerp(killer) && playerp(victim) ) {
                        string cname;
                        object couple;

                        log_file("static/killrecord",
                                 sprintf("%s %s killed %s\n",
                                         log_time(),
                                         log_id(killer), log_id(victim)));

                        killer->remove_killer(victim);

                        // check sadly
                        cname=query("couple/couple_id", victim);
                        if( cname &&
                            query("gender", victim) == "女性" &&
                            query("combat_exp", victim) >= 970000 &&
                            objectp(couple = find_player(cname)) &&
                            couple != killer &&
                            query("couple/married", couple) <= 1 &&
                            query("couple/married", victim) <= 1){
                                addn("static/sadly", 1, couple);
                                tell_object(couple, "你的妻子死在了" +
                                            killer->name(1) + "的手下" +
                                            "，你感到了一陣深深的哀傷。\n");
                        }
                }
        }

        if( stringp(vmark=query("vendetta_mark", victim)) && objectp(killer) )
                addn("vendetta/"+vmark, 1, killer);
}

// me hit victim with poison in ob
void hit_with_poison(object me, object victim, object ob)
{
        mapping p, ap;
        string msg;
        string poison_type;

        if( !mapp(p=query_temp("daub/poison", ob)) )
                return;

        if( !stringp(poison_type=query_temp("daub/poison_type", ob)) )
                return;

        if( !p["remain"] )
                return;

        // affect parameter
        ap = allocate_mapping(4);
        if( ob == me )
                ap["level"] = p["level"] * 9 / 10 + 1;
        else
                ap["level"] = p["level"] * 8 / 10 + 1;

        ap["id"]       = p["id"];
        ap["name"]     = p["name"];
        ap["duration"] = 1;

        if( p["remain"] > p["level"] ) {
                // decrase the remain poison
                p["remain"] -= p["level"];
        } else {
                // the poison has run out
                delete_temp("daub", ob);
        }

        msg = HIG "突然$n覺得受傷的地方有一些麻癢";
        if( p["id"] == query("id", victim)){
                if( !query_temp("has_announce/defense1", victim)){
                        set_temp("has_announce/defense1", 1, victim);
                        victim->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", victim :), victim), 15);
                        msg += "。\n" NOR HIC "$n默一運功，冷笑兩聲：“好你個" +
                               RANK_D->query_rude(me) + "，居然在我面前賣弄" +
                               RANK_D->query_self_rude(victim) +
                               "毒藥！真是假李鬼碰上真李逵了！”\n" NOR;
                } else
                        msg += "，不過$n並沒有在意。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if( p["level"] < victim->query_skill("poison", 1) ) {
                if( !query_temp("has_announce/defense2", victim)){
                        set_temp("has_announce/defense2", 1, victim);
                        victim->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", victim :), victim), 15);
                        msg += "。\n" NOR HIC "$n呼吸數次，嘿然冷笑道："
                               "“米粒之珠，也放光華？”\n" NOR;
                } else
                        msg += "，不過$n顯然並沒有把它放在心上。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if( p["level"] < victim->query_skill("force") / 2 ) {
                if( !query_temp("has_announce/defense3", victim)){
                        set_temp("has_announce/defense3", 1, victim);
                        victim->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", victim :), victim), 15);
                        msg += "。\n" NOR HIC "$n深吸一口氣，哈哈長笑道：“好家伙，居然" +
                               (ob == me ? "在身上淬毒" : "使用淬毒兵器") +
                               "，你這些下三濫的手段也敢到我面前賣弄？”\n" NOR;
                } else
                        msg += "，不過$n看起來似乎並無大礙。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        victim->affect_by(poison_type, ap);

        msg += "，大概是中毒了。\n" NOR;
        if( p["level"] < victim->query_skill("force") ) {
                msg += HIG "$n深深吸一了口氣，面目凝重，手中的攻勢陡然一緊。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        msg += HIR "$n悶哼一聲，攻勢頓緩，神情甚是痛苦。\n" NOR;
        if( !victim->is_busy() )
                victim->start_busy(1 + random(2));
        set_ahinfo(msg);
        return;
}

// me hit victim, but poison by victim in ob
void hit_poison(object me, object victim, object ob)
{
        mapping p, ap;
        string msg;
        string poison_type;

        if( !mapp(p=query_temp("daub/poison", ob)) )
                return;

        if( !stringp(poison_type=query_temp("daub/poison_type", ob)) )
                return;

        if( !p["remain"] )
                return;

        if( query_temp("armor/hands", me) )
                return;

        // affect parameter
        ap = allocate_mapping(4);
        ap["level"]    = p["level"] * 7 / 10 + 1;

        ap["id"]       = p["id"];
        ap["name"]     = p["name"];
        ap["duration"] = 1;

        if( p["remain"] > p["level"] ) {
                // decrase the remain poison
                p["remain"] -= p["level"];
        } else {
                // the poison has run out
                delete_temp("daub", ob);
        }

        msg = HIG "突然$N覺得渾身有些麻癢";
        if( p["id"] == query("id", me)){
                if( !query_temp("has_announce/defense1", me)){
                        set_temp("has_announce/defense1", 1, me);
                        me->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", me :), me), 15);
                        msg += "。\n" NOR HIC "$N默一運功，冷笑兩聲：“好你個" +
                               RANK_D->query_rude(victim) + "，居然在我面前賣弄" +
                               RANK_D->query_self_rude(victim) +
                               "的毒藥！把你衣服上的毒藥都還給我！”\n" NOR;
                } else
                        msg += "，不過$N並沒有在意。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if( p["level"] < me->query_skill("poison", 1) ) {
                if( !query_temp("has_announce/defense2", me)){
                        set_temp("has_announce/defense2", 1, me);
                        me->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", me :), me), 15);
                        msg += "。\n" NOR HIC "$N呼吸數次，嘿然冷笑道：“米粒之珠，也"
                               "放光華？你在衣衫上淬毒我就怕你了？”\n" NOR;
                } else
                        msg += "，不過$N顯然並沒有把它放在心上。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if( p["level"] < me->query_skill("force") / 2 ) {
                if( !query_temp("has_announce/defense3", me)){
                        set_temp("has_announce/defense3", 1, me);
                        me->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", me :), me), 15);
                        msg += "。\n" NOR HIC "$N深吸一口氣，哈哈長笑道：“你居然在衣衫上"
                               "淬毒，這些下三濫的手段也敢到我面前賣弄？”\n" NOR;
                } else
                        msg += "，不過$N看起來似乎並無大礙。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        me->affect_by(poison_type, ap);

        msg += "，看來有些不妙。\n" NOR;
        if( p["level"] < me->query_skill("force") ) {
                msg += HIG "$N深深吸一了口氣，面目凝重，手中的攻勢陡然一緊。\n" NOR;
                set_ahinfo(msg);
                return;
        }

        msg += HIR "$N腳步一個蹌踉，攻勢頓緩，神色難看之極。\n" NOR;
        me->start_busy(1 + random(2));
        set_ahinfo(msg);
        return;
}

void clear_announce(object me)
{
        if( !objectp(me) )
                return;

        delete_temp("has_announce", me);
}

protected void quest_kill(object killer, object victim)
{
        mapping quest,b;
        int level,i,n,exp,pot,score,weiwang,mar,quest_count,all_quest;
        mixed special = 0;
        mixed money = 0;
        object ob,*all_killer,obj;
        object tongren;

        // 以下是NPC幫派任務的獎勵
        // 如果是追殺任務
        if( !playerp(victim) && query("bunch_quest", victim)){
                quest=query("bunch_quest", victim);
                if( quest["type"] == "追殺" &&
                    ((quest["bunch_type"] == "good" && good_bunch(killer) && query("shen", killer) >= 0) ||
                    (quest["bunch_type"] == "bad" && bad_bunch(killer) && query("shen", killer) <= 0)) &&
                    query("combat_exp", killer)<5000000000){
                        exp = quest["bonus"];
                        exp += 120;
                        exp += random(exp/2);
                        pot = exp/(2 + random(2));
                        score = 25 + random(20);
                        weiwang = 25 + random(20);

                        b = ([ "exp" : exp,
                               "pot" : pot,
                               "score" : score,
                               "weiwang" : weiwang,
                               "prompt": "在追殺" + victim->name() + HIG "的過程中，經過鍛煉"
                        ]);

                        GIFT_D->delay_bonus(killer, b);
                }
                return;
        }

        // 如果是鏟除外敵任務
        if( query("bunch_quest", killer) &&
            query("bunch_quest", killer)["type"] == "鏟除外敵" &&
            query("bunch_quest", killer)["ob"] == victim){
                quest=query("bunch_quest", killer);

                exp = quest["bonus"];
                exp += 120;
                exp += random(exp/2);
                pot = exp/(2 + random(2));
                score = 25 + random(20);
                weiwang = 25 + random(20);

                b = ([ "exp" : exp,
                       "pot" : pot,
                       "score" : score,
                       "weiwang" : weiwang,
                       "prompt": "在鏟除外來敵人" + victim->name() + HIG "的過程中，經過鍛煉"
                ]);

                GIFT_D->delay_bonus(killer, b);

                delete("bunch_quest", killer);
                addn_temp("finish_bunch_times", 1, killer);
                return;
        }

        // 以下是組隊任務的獎勵
        if( !playerp(victim) && query("my_type", victim)){
                /*
                if( objectp(victim->query_defeated_by()) &&
                    playerp(victim->query_defeated_by()) )
                    killer = victim->query_defeated_by();
                */
                switch(query("my_type", victim) )
                {
                case "外敵":
                        GROUP_QUEST_D->be_killed(1);
                        GROUP_QUEST_D->add_killer(killer);
                        exp=query("bonus", victim);
                        pot = exp;
                        score = random(exp);
                        weiwang = exp + random(exp);
                        mar = random(exp/2);
                        if( GROUP_QUEST_D->query_drop() < 2 && random(10) == 1 ) {
                                GROUP_QUEST_D->add_drop(1);
                                tongren = new("/clone/tongren/tongren"+(1+random(2)));
                                message_vision(HIR "叮~~一聲，從$N" HIR "掉出一樣東西，$n" HIR
                                               "趕緊揀了起來。\n" NOR, victim, killer);
                                tell_object(killer, BLINK + HIG "你得到了" + tongren->name() + BLINK + HIG "。\n" NOR);
                                tongren->move(killer, 1);
                        }
                        GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                 "weiwang" : weiwang, "score" : score ]), 1);
                        if( GROUP_QUEST_D->query_enemy() == 0 ) {
                                tongren = new("/clone/tongren/tongren"+(1+random(2)));
                                message_vision(HIR "叮~~一聲，從$N" HIR "掉出一樣東西，$n" HIR
                                               "趕緊揀了起來。\n" NOR, victim, killer);
                                tell_object(killer, BLINK + HIG "你得到了" + tongren->name() + BLINK + HIG "。\n" NOR);
                                tongren->move(killer, 1);

                                all_killer = GROUP_QUEST_D->query_killer();
                                n = sizeof(all_killer);
                                exp = 2000+20*n;
                                pot = exp;
                                score = 1000;
                                weiwang = 3000;
                                mar = 500;
                                foreach (ob in all_killer)
                                {
                                        if( !objectp(ob) || !playerp(ob) )
                                                continue;

                                        tell_object(ob, HIW "所有入侵的敵人都給打退了，由于你也參與了戰鬥，" +
                                                            "因此現在你也一起分享勝利果實！\n" NOR);
                                        GIFT_D->bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                             "weiwang" : weiwang, "score" : score ]), 1);
                                }
                        }
                        break;
                case "門派":
                        GROUP_QUEST_D->be_killed(1);
                        if( query("門派", victim) == query("family/family_name", killer)){
                                GROUP_QUEST_D->add_killer(killer);
                                exp=query("bonus", victim);
                                pot = exp;
                                score = random(exp);
                                weiwang = exp + random(exp);
                                mar = random(exp/2);
                        if( GROUP_QUEST_D->query_drop() < 2 && random(10) == 1 ) {
                                GROUP_QUEST_D->add_drop(1);
                                tongren = new("/clone/tongren/tongren"+(1+random(2)));
                                message_vision(HIR "叮~~一聲，從$N" HIR "掉出一樣東西，$n" HIR
                                               "趕緊揀了起來。\n" NOR, victim, killer);
                                tell_object(killer, BLINK + HIG "你得到了" + tongren->name() + BLINK + HIG "。\n" NOR);
                                tongren->move(killer, 1);
                                }
                                GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                         "gongxian" : weiwang, "score" : score, "weiwang" : weiwang ]), 1);
                        }
                        if( GROUP_QUEST_D->query_enemy() == 0 ) {
                                tongren = new("/clone/tongren/tongren"+(1+random(2)));
                                message_vision(HIR "叮~~一聲，從$N" HIR "掉出一樣東西，$n" HIR
                                               "趕緊揀了起來。\n" NOR, victim, killer);
                                tell_object(killer, BLINK + HIG "你得到了" + tongren->name() + BLINK + HIG "。\n" NOR);
                                tongren->move(killer, 1);
                                all_killer = GROUP_QUEST_D->query_killer();
                                n = sizeof(all_killer);
                                exp = 2000+20*n;
                                pot = exp;
                                score = 1000;
                                weiwang = 30000;
                                mar = 500;
                                foreach (ob in all_killer)
                                {
                                        if( !objectp(ob) || !playerp(ob))
                                                continue;

                                        tell_object(ob, HIW "所有入侵的敵人都給打退了，由于你也參與了戰鬥，" +
                                                            "因此現在你也一起分享勝利果實！\n" NOR);
                                        GIFT_D->bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                             "gongxian" : weiwang, "score" : score, "weiwang" : weiwang ]), 1);
                                }
                        }
                        break;
                case "幫派":
                        GROUP_QUEST_D->be_killed(1);
                        if( query("幫派", victim) == query("bunch/bunch_name", killer)){
                                GROUP_QUEST_D->add_killer(killer);
                                exp=query("bonus", victim);
                                pot = exp;
                                score = random(exp);
                                weiwang = exp + random(exp);
                                mar = random(exp/2);
                                if( GROUP_QUEST_D->query_drop() < 2 && random(10) == 1 ) {
                                GROUP_QUEST_D->add_drop(1);
                                tongren = new("/clone/tongren/tongren"+(1+random(2)));
                                message_vision(HIR "叮~~一聲，從$N" HIR "掉出一樣東西，$n" HIR
                                               "趕緊揀了起來。\n" NOR, victim, killer);
                                tell_object(killer, BLINK + HIG "你得到了" + tongren->name() + BLINK + HIG "。\n" NOR);
                                tongren->move(killer, 1);
                                }
                                GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                   "weiwang" : weiwang, "score" : score ]), 1);
                        }
                        if( GROUP_QUEST_D->query_enemy() == 0 ) {
                                tongren = new("/clone/tongren/tongren"+(1+random(2)));
                                message_vision(HIR "叮~~一聲，從$N" HIR "掉出一樣東西，$n" HIR
                                               "趕緊揀了起來。\n" NOR, victim, killer);
                                tell_object(killer, BLINK + HIG "你得到了" + tongren->name() + BLINK + HIG "。\n" NOR);
                                tongren->move(killer, 1);
                                BUNCH_D->add_bunch_honors(query("幫派", victim), 200);
                                all_killer = GROUP_QUEST_D->query_killer();
                                n = sizeof(all_killer);
                                exp = 2000+20*n;
                                pot = exp;
                                score = 1000;
                                weiwang = 3000;
                                mar = 500;
                                foreach (ob in all_killer)
                                {
                                        if( !objectp(ob) || !playerp(ob) )
                                                continue;

                                        tell_object(ob, HIW "所有入侵的敵人都給打退了，由于你也參與了戰鬥，" +
                                                            "因此現在你也一起分享勝利果實！\n" NOR);
                                        GIFT_D->bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                             "weiwang" : weiwang, "score" : score ]), 1);
                                }
                        }
                        break;
                }
                return;
        }

        // 以下是宗師任務的獎勵
        if( mapp(quest=query("quest_kh", killer)) && quest["desc"] == "滅"){//葵花太監
                if( (quest["name"] == "男子" && query("gender", victim) == "男性") ||
                    (quest["name"] == "女子" && query("gender", victim) == "女性") ||
                    (quest["type"] == "地點" && (domain_file(base_name(victim)) == quest["dir"] ||
                    (stringp(query("startroom", victim)) && (domain_file(query("startroom", victim)) == quest["dir"])) ||
                     base_dir(victim) == quest["dir1"])) ) {
                        if( (quest["time"]-time()) < 0 ) {
                                delete("quest_kh", killer);
                                return ;
                        }
                        else if( query("race", victim) == "野獸")return ;
                        else {
                                level = (quest["level"]+1)*(70+random(20));
                                exp = level;
                                pot = exp/(2+random(2));
                                score = random(exp/20);
                                weiwang = random(exp/15);
                                if( query("questkh_times", killer)+1>200 )
                                        mar=exp/5+random(query("questkh_times", killer));
                                else mar = 20 + random(20);
                                if( mar > 1000 ) mar = 1000;

                                GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                         "weiwang" : weiwang, "score" : score ]), 1);

                                return ;
                        }
                }
        }

        if( mapp(quest=query("quest_dg", killer))){//獨孤求敗
                if( quest["type"] == "殺" && victim->name(1) == quest["name"] ) {
                        if( (i=query("questdg_times", killer))<8 )
                                i = 15-i;
                        else
                                i = 1;
                        level = quest["level"]+1;
                        exp = level*105 + quest["bonus"]*3;
                        exp += random(exp/2);
                        exp = exp/i;
                        /*
                        if( level == 9 )
                                exp+=query("questdg_times", killer);
                        if( level == 9)
                                pot = exp*(2+random(2));
                        else
                        */
                                pot = exp/(2+random(2));
                        score = random(exp/20);
                        weiwang = random(exp/15);

                        if( query("questdg_times", killer)+1>200 )
                                mar=exp/5+random(query("questdg_times", killer));
                        else mar = 20 + random(20);
                        if( mar > 1000 ) mar = 1000;

                        GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                 "weiwang" : weiwang, "score" : score ]), 1);

                        addn("questdg_times", 1, killer);

                        quest_count=query("questdg_times", killer)%500;
                        if( quest_count == 50 )
                                special = 1;
                        else if( quest_count == 100)
                                special = "/clone/gift/puti-zi";
                        else if( quest_count == 150)
                                money = 1;
                        else if( quest_count == 200)
                                money = 1;
                        else if( quest_count == 250)
                                money = 1;
                        else if( quest_count == 300)
                                special = "/clone/gift/tianxiang";
                        else if( quest_count == 350)
                                special = "/clone/gift/tianxiang";
                        else if( quest_count == 400)
                                special = "/clone/gift/jiuzhuan";
                        else if( quest_count == 450)
                                special = "/clone/gift/jiuzhuan";
                        else if( quest_count == 0)
                                special = "/clone/gift/jiuzhuan";

                        if( special ) GIFT_D->special_bonus(victim, killer, special);
                        if( money ) QUEST_D->money_bonus(victim, killer, money);

                        addn("total_hatred", -5, killer);
                        if( query("total_hatred", killer) < 0 ) set("total_hatred", 0, killer);
                        delete("quest_dg", killer);

#ifdef DB_SAVE
                        if( MEMBER_D->is_valid_member(query("id", killer))){
                                if( query("special_skill/sophistry", killer)){
                                        if( query("questdg_times", killer) >= 5000 )
                                                set("questdg_times", 0, killer);
                                } else {
                                        if( query("questdg_times", killer) >= 2000 )
                                                set("questdg_times", 0, killer);
                                }
                        } else {
#endif
                                if( query("questdg_times", killer) >= 1000 )
                                        set("questdg_times", 0, killer);
#ifdef DB_SAVE
                        }
#endif
                        all_quest=query("all_quest_dg", killer);
                        if( !all_quest ) all_quest = 0;
                        all_quest += 1;
                        if( all_quest == 1000 ) {
                                obj = new("/clone/gift/xuanhuang");
                                tell_object(killer,"由于你已經累計完成了一千個任務，因此你得到了一個" +
                                                query("name", obj)+"作為獎勵\n");
                                if( !obj->move(killer) )
                                        obj->move(environment(killer));
                                set("all_quest_dg", 0, killer);
                        } else
                                set("all_quest_dg", all_quest, killer);
                        return ;
                }
        }

        if( mapp(quest=query("quest_hs", killer))){//黃裳
                if( quest["type"]=="殺"&&quest["name"]==victim->name(1) ) {
                        tell_object(killer,"恭喜你！你又為綠林立了一功！\n");
                        if( (i=query("quesths_times", killer))<15 )
                                i = 15-i;
                        else
                                i = 1;
                        level = quest["level"]+1;
                        exp = level*80 + quest["bonus"]*3;
                        exp += random(exp/2);
                        exp = exp/i;
                        if( level > 4 && i > 5 )
                                exp /= 2;
                        if( level == 9 )
                                exp+=query("quesths_times", killer);
                        /*
                        if( level == 9 )
                                pot = exp*(2+random(2));
                        else
                        */
                                pot = exp/(2+random(2));
                        score = random(exp/20);
                        weiwang = random(exp/15);
                        if( query("quesths_times", killer)+1>200 )
                                mar=exp/5+random(query("quesths_times", killer));
                        else mar = 20 + random(20);
                        if( mar > 1000 ) mar = 1000;

                        GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                 "weiwang" : weiwang, "score" : score ]), 1);

                        addn("quesths_times", 1, killer);
                        quest_count=query("quesths_times", killer)%500;
                        if( quest_count == 50)
                                special = 1;
                        else if( quest_count == 100 )
                                special = "/clone/gift/puti-zi";
                        else if( quest_count == 150 )
                                money = 1;
                        else if( quest_count == 200 )
                                money = 1;
                        else if( quest_count == 250 )
                                money = 1;
                        else if( quest_count == 300 )
                                special = "/clone/gift/tianxiang";
                        else if( quest_count == 350 )
                                special = "/clone/gift/tianxiang";
                        else if( quest_count == 400 )
                                special = "/clone/gift/jiuzhuan";
                        else if( quest_count == 450 )
                                special = "/clone/gift/jiuzhuan";
                        else if( quest_count == 0 )
                                special = "/clone/gift/jiuzhuan";

                        if( special ) GIFT_D->special_bonus(victim, killer, special);
                        if( money ) QUEST_D->money_bonus(victim, killer, money);

                        addn("total_hatred", -5, killer);
                        if( query("total_hatred", killer) < 0 ) set("total_hatred", 0, killer);
                        delete("quest_hs", killer);
                        set_temp("hs_giveup", 0, killer);

#ifdef DB_SAVE
                        if( MEMBER_D->is_valid_member(query("id", killer))){
                                if( query("special_skill/sophistry", killer)){
                                        if( query("quesths_times", killer) >= 5000 )
                                                set("quesths_times", 0, killer);
                                } else {
                                        if( query("quesths_times", killer) >= 2000 )
                                                set("quesths_times", 0, killer);
                                }
                        } else {
#endif
                                if( query("quesths_times", killer) >= 1000 )
                                        set("quesths_times", 0, killer);
#ifdef DB_SAVE
                        }
#endif

                        all_quest = (int)query("all_quest_hs", killer);
                        if( !all_quest ) all_quest = 0;
                        all_quest += 1;
                        if( all_quest == 1000 ) {
                                obj = new("/clone/gift/xuanhuang");
                                tell_object(killer,"由于你已經累計完成了一千個任務，因此你得到了一個" +
                                                query("name", obj)+"作為獎勵\n");
                                if( !obj->move(killer) )
                                        obj->move(environment(killer));
                                set("all_quest_hs", 0, killer);
                        } else
                                set("all_quest_hs", all_quest, killer);
                        return ;
                }
        }

        if( mapp(quest=query("quest_sn", killer))){//南海神尼
                if( quest["type"]=="殺"&&quest["name"]==victim->name(1) ) {
                        tell_object(killer,"恭喜你！你又為南海神尼立了一功！\n");
                        if( (i=query("questsn_times", killer))<15 )
                                i = 15-i;
                        else i = 1;
                        level = quest["level"]+1;
                        exp = level*80 + quest["bonus"]*3;
                        exp += random(exp/2);
                        exp = exp/i;
                        if( level > 4 && i > 5 )
                                exp /= 2;
                        if( level == 9 )
                                exp+=query("questsn_times", killer);
                        /*
                        if( level == 9 )
                                pot = exp*(2+random(2));
                        else
                        */
                                pot = exp/(2+random(2));
                        score = random(exp/20);
                        weiwang = random(exp/15);
                        if( query("questsn_times", killer)+1>200 )
                                mar=exp/5+random(query("questsn_times", killer));
                        else mar = 20 + random(20);
                        if( mar > 1000 ) mar = 1000;

                        GIFT_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                 "weiwang" : weiwang, "score" : score ]), 1);

                        addn("questsn_times", 1, killer);
                        quest_count=query("questsn_times", killer)%500;
                        if( quest_count == 50 )
                                special = 1;
                        else if( quest_count == 100 )
                                special = "/clone/gift/puti-zi";
                        else if( quest_count == 150 )
                                money = 1;
                        else if( quest_count == 200 )
                                money = 1;
                        else if( quest_count == 250 )
                                money = 1;
                        else if( quest_count == 300 )
                                special = "/clone/gift/tianxiang";
                        else if( quest_count == 350 )
                                special = "/clone/gift/tianxiang";
                        else if( quest_count == 400 )
                                special = "/clone/gift/jiuzhuan";
                        else if( quest_count == 450 )
                                special = "/clone/gift/jiuzhuan";
                        else if( quest_count == 0 )
                                special = "/clone/gift/jiuzhuan";

                        if( special ) GIFT_D->special_bonus(victim, killer, special);
                        if( money ) QUEST_D->money_bonus(victim, killer, money);

                        addn("total_hatred", -5, killer);
                        if( query("total_hatred", killer) < 0 ) set("total_hatred", 0, killer);
                        delete("quest_sn", killer);
                        set_temp("sn_giveup", 0, killer);

#ifdef DB_SAVE
                        if( MEMBER_D->is_valid_member(query("id", killer))){
                                if( query("special_skill/sophistry", killer)){
                                        if( query("questsn_times", killer) >= 5000 )
                                                set("questsn_times", 0, killer);
                                } else {
                                        if( query("questsn_times", killer) >= 2000 )
                                                set("questsn_times", 0, killer);
                                }
                        } else {
#endif
                                if( query("questsn_times", killer) >= 1000 )
                                        set("questsn_times", 0, killer);
#ifdef DB_SAVE
                        }
#endif

                        all_quest = (int)query("all_quest_sn", killer);
                        if( !all_quest ) all_quest = 0;
                        all_quest += 1;
                        if( all_quest == 1000 ) {
                                obj = new("/clone/gift/xuanhuang");
                                tell_object(killer,"由于你已經累計完成了一千個任務，因此你得到了一個" +
                                                query("name", obj)+"作為獎勵\n");
                                if( !obj->move(killer) )
                                        obj->move(environment(killer));
                                set("all_quest_sn", 0, killer);
                        } else
                                set("all_quest_sn", all_quest, killer);
                        return ;
                }
        }
}
