//                標準描述長度示例                                   |
// 幻境內物品  武器類型（包括魔法水晶）
// by naihe  2002-10-25  於茂名
// naihe 05-9-7 9:34 V1.7 繼續更新

#include <ansi.h>

inherit ITEM;


string *names=({
    GRN"青銅之劍"NOR,
    HIW"靈氣之劍"NOR,
    HIW"白銀之劍"NOR,
    HIM"盈動之劍"NOR,
    HIY"黃金之劍"NOR,
    HIY"耐力之劍"NOR,
    HIW"迅隱之劍"NOR,
    HIB"奪魂之劍"NOR,
    HIR"必勝之劍"NOR,
    HIW"狂風水晶"NOR,
    MAG"暴雨水晶"NOR,
    HIC"落雷水晶"NOR,
    HIG"引電水晶"NOR,
    YEL"滾石水晶"NOR,
    RED"飛火水晶"NOR,
    BLU"奪魂水晶"NOR,

// 這幾個出來的概率大些
    YEL"滾石水晶"NOR,
    RED"飛火水晶"NOR,

    GRN"青銅之劍"NOR,
    HIW"靈氣之劍"NOR,
    HIW"白銀之劍"NOR,
    HIM"盈動之劍"NOR,
    HIY"黃金之劍"NOR,
    HIY"耐力之劍"NOR,
});

string *ids=({
    "qt jian",
    "lq jian",
    "by jian",
    "yd jian",
    "hj jian",
    "nl jian",
    "xy jian",
    "dh jian",
    "bs jian",
    "kf sj",
    "by sj",
    "ll sj",
    "yd sj",
    "gs sj",
    "fh sj",
    "dh sj",

    "gs sj",
    "fh sj",

    "qt jian",
    "lq jian",
    "by jian",
    "yd jian",
    "hj jian",
    "nl jian",
});

string *ids2=({
    "jian",
    "jian",
    "jian",
    "jian",
    "jian",
    "jian",
    "jian",
    "jian",
    "jian",
    "sj",
    "sj",
    "sj",
    "sj",
    "sj",
    "sj",
    "sj",

    "sj",
    "sj",

    "jian",
    "jian",
    "jian",
    "jian",
    "jian",
    "jian",
});

string *longs=({
    "這是一柄最普通的劍，似是青銅打造。\n",
    "這是一柄“靈氣之劍”，劍身似有氣息流動一般。\n",
    "這是一柄相當普通的劍，似由白銀打造，要比青銅打造的好一點。\n",
    "這是一柄“盈動之劍”，劍身上隱隱有各色光華流淌閃耀，十分美麗。\n",
    "這是一柄以黃金打造的劍，揮動時將有十分大氣的感覺。\n",
    "這是一柄名為“耐力”的劍，以耐用著稱。\n",
    "這柄劍輕飄飄的不知是什麼質地鑄成，劍體似有時隱時現一般，甚為神祕。\n",
    "這柄劍看似普普通通，卻隱隱散發陰森殺氣，看來是件邪物。\n",
    "這柄劍不見得有什麼特別之處，劍身劍柄皆以普通精鐵鑄就，劍柄上刻有兩個小字：“必勝”。\n",
    "這是一顆狂風水晶，似乎可以召喚魔法。\n",
    "這是一顆暴雨水晶，似乎可以召喚魔法。\n",
    "這是一顆落雷水晶，似乎可以召喚魔法。\n",
    "這是一顆引電水晶，似乎可以召喚魔法。\n",
    "這是一顆滾石水晶，似乎可以召喚魔法。\n",
    "這是一顆飛火水晶，似乎可以召喚魔法。\n",
    "這是一顆奪魂水晶，似乎可以召喚魔法。\n",

    "這是一顆滾石水晶，似乎可以召喚魔法。\n",
    "這是一顆飛火水晶，似乎可以召喚魔法。\n",

    "這是一柄最普通的劍，似是青銅打造。\n",
    "這是一柄“靈氣之劍”，劍身似有氣息流動一般。\n",
    "這是一柄相當普通的劍，似由白銀打造，要比青銅打造的好一點。\n",
    "這是一柄“盈動之劍”，劍身上隱隱有各色光華流淌閃耀，十分美麗。\n",
    "這是一柄以黃金打造的劍，揮動時將有十分大氣的感覺。\n",
    "這是一柄名為“耐力”的劍，以耐用著稱。\n",
});

// 全面提升武器攻擊力
int *power=({
    10,
    10+random(11),
    15,
    20,
    30,
    20,
    30,
    88,
    128,
    20,
    20,
    20,
    20,
    10+random(6),
    10+random(6),
    88,

    10+random(6),
    10+random(6),

    10,
    10+random(11),
    15,
    20,
    30,
    20,
});

int *times=({
    10,
    10,
    10,
    10+random(6),
    15,
    30,
    5+random(6),    // 增強迅隱之劍
    5,
    3+random(3),
    5,
    5,
    5,
    5,
    5,
    5,
    3+random(3),

    5,
    5,

    10,
    10,
    10,
    10+random(6),
    15,
    30,
});

int *busys=({
    1,
    1,
    2,
    1+random(2),
    2,
    2,
    888,  //  無忙時！！！
    2,
    2,
    2,
    2,
    2,
    2,
    1,
    1,
    2,

    1,
    1,

    1,
    1,
    2,
    1+random(2),
    2,
    2,
});


/*   本函數未使用。由於手頭上的 劍 的圖片都是COPY別人的，
     用了感覺也不好；而且一旦加上劍的圖片，必然要加水晶的——
     水晶的圖片倒是可以用我自己畫的那張(漂亮哦……)，但又會和
     "redaygo" 那個地點的水晶圖片形成雷同。而且其他的道具，例
     如什麼石頭什麼旗子也要加，羅嗦之極，暫時不予考慮罷。

void hjset_long()
{
    string long_pic, id = query("id");
    switch( id )
    {
        case "qt jian": long_pic = GRN"
         />_________________________________
[########[]_________________________________ >
         \\>\n\n"NOR;
            break;
        case "by jian": long_pic = HIW"
         />_________________________________
[########[]_________________________________ >
         \\>\n\n"NOR;
            break;
        case "hj jian": long_pic = HIY"
         />_________________________________
[########[]_________________________________ >
         \\>\n\n"NOR;
            break;


    }

    set( "long", long_pic + query("long") );
}
*/


void setme( int iii )
{
    if( iii == 99 ) iii = random( sizeof(names) );
    set( "iii", iii );

    set_name(names[ iii ], ({ids[ iii ],ids2[ iii ]}));
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);

    set("long", longs[ iii ]);
    if( iii  < 9 || iii > 17 )
    {
        set("unit", "柄");
        set("hj_game/obj","sword");
        set("msg","你只覺得眼睛一花，地上多了一件兵器。\n");
    }

    else
    {
        set("unit","顆");
        set("hj_game/obj","magic");
        set("msg","你只覺得眼睛一花，地上多了一顆水晶。\n");
        switch( iii )
        {
            case 9:    set("type","風之國度");
                set("att_msg","不知何處忽地刮來一陣旋風");
                break;
            case 10:set("type","雨之國度");
                set("att_msg","不知何處忽地潑下一陣寒雨");
                break;
            case 11:set("type","雷之國度");
                set("att_msg","半空中忽地炸響一聲驚雷");
                break;
            case 12:set("type","電之國度");
                set("att_msg","半空中忽地打來一道閃電");
                break;
            case 13: case 16: set("type","迷失之國");
                set("att_msg","不知何處忽地滾落一顆大石");
                break;
            case 14: case 17: set("type","迷失之國");
                set("att_msg","不知何處忽地飛來一團猛烈之火");
                break;
            case 15:set("type","迷失之國");
                set("att_msg","不知何處忽地響起一陣淒厲之音");
                break;
        }
    }

    set("use_times",times[ iii ] );
    set("power",power[ iii ] );
    set("real_use_times", times[iii] );
    set("real_power", power[iii] );
    // 由於新加入的 鑄劍師 需要核對使用次數，所以設置一個不變的值
    // 1:18 03-11-5 naihe

    set("busy",busys[ iii ] );
    set("value", 1);  // 該物件扔下後不會消失。
    set("no_refresh",1); // 不會被房間更新。
}

void create()
{
    setme( 99 );
    setup();
}

void delete_me()
{
    message_vision(query("name", this_object())+"靈氣已盡，「嘭」的一聲消失不見了。\n",this_object());
    destruct(this_object());
}
