// map.c
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( HIC "『天下旅遊圖』" NOR, ({ "luyou tu", "tu" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", @TEXT
                 『天下旅遊圖』
                                                                         天池
                                                                     長白山●/
                                                              赫圖阿拉⊙ ▲ /
                                                                            /
                             ◎                                     ｏ寧遠  /
 靈鷲峯                     靈州  黃  河                      山海關  _/-\ /
  ∧∧ 天山山脈                  ≈≈≈≈         八達嶺    凸凸凹  _/   |/
   ∧∧∧ｏ∧∧  ∷嘉峪關≈≈≈ ≈      §          凹凸凸凸凹    _/  ～ ～
星宿海§ 伊犁  ∷∷凹凸凸凸   ≈         §   凹凸凸凸 京城   ___/ ～ ～ ¤ ～
         ∷∷∷∷∷∷∷∷∷ 凹凸凸凸     凹凸凸凸平定州 ⊙ ♀/ ～ ～～神龍島～
白駝山  ∷∷大∷∷∷∷漠∷∷∷∷   凹凸凸凸§  △  ｏ    塘沽\___ ～ ～～ ～
  △  ∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷       §黑木崖 ▲恆山   ≈≈\_/---+__
∷∷∷∷∷∷∷∷∷     ｏ        ◎  華山村§             ≈≈ 泰山    __/
 ∷∷∷∷∷∷∷       蘭州      永登   ｏ▲§中條山▲ ≈≈≈    ▲   _/   ～
∧∧  昆 侖 山 脈           長安◎      華山≈≈≈≈≈  汝州       _/ ～ ～
    ∧∧∧ ∧∧∧ ∧∧           ▲終南山                ｏ        |__  ～～
                             漢中ｏ ｏ         ▲嵩山       揚州    \_  ～
                                  函谷關            ｏ南陽   ◎ ≈蘇州\_～
  青   藏   高   原                         ▲    ◎      無錫◎≈◎≈|_～
                    ∧                    武當山 襄陽       ≈≈   嘉興♀| ～～ 
∧                   ∧   青城山  成都     荊州ｏ≈      ≈≈  杭州◎--_『～¤ 
  _∧∧             大雪山   ▲     ◎       ≈≈  ≈≈≈≈        ●   / 桃花島
   \___∧∧           ∧       峨嵋山     ≈≈ 長      江         西湖  | ～
       \____∧∧       ∧≈      ▲    ≈≈                            _/ ～
  ＊註釋   \_ ∧ ∧       §        ≈≈         衡山         ∧       |  ～
             -__--\        ≈    ≈≈   △        ▲     武夷∧ ｏ 福州| ～
  ⊙  首都         | 大理   ≈≈≈   摩天崖      ｏ衡陽 山脈∧ 延平 ◎/  ～
  ◎  城市       _/ ▲◎ ●滇池                                      /～台灣_
  ｏ  小鎮       |_蒼山 ｏ喜州                南嶺∧∧ ∧∧  泉州♀_/～～ / |
  ∧  山川         |_   無量山                        佛山       _/～¤～/  |
△▲  高山           \_   △  ___                      ◎       / ～澎湖～\/
§≈  江河             |_  _--  \__                 漁村♀___---  ～ ～  ～
  ～  大海               \_|       \__              ___---  ～ ～～ ～～～～
  ∷  沙漠                            \__--\  ___--- ～ ～～～ ～～ ～～
  ♀  港口                            / ～ | /  ～～ ～～～  ～ ～～ ～～
  ¤  島嶼                            | ～  \| ～～～  ～～ ～ ～～～ ～～～
  凹  長城                           / ～ ～__--_～ ～ 俠客島～～～ ～ ～～～
  ●  湖泊                           | ～  /    /～～ ¤～ ～～～ ～ ～～～～
                                    /   ～ --__-  ～ ～～～ ～～～～ ～～～
TEXT);
                set("value", 50);
                set("material", "paper");
        }
        setup();
}