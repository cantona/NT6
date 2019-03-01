// map.c 峨嵋地圖
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( HIC "『長白山旅遊圖』" NOR, ({ "luyou tu","tu","map"}) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long",
"\n                 『長白山導遊圖』\n\n"
"　　　【地圖一】　　　　　　　　　   ＾\n"
"                                     ｜\n"
"                                     ＾\n"
"\n"
"\n"
"\n"
"                                                                     白\n"
" 大                                                                  雲\n"
" 門                                                  雞              峯\n"
" 坎＼二                                        鐵    冠    鹿      ／  ＼\n"
" 子  門    滿                                  壁 —    — 鳴＼玉／  天  ＼龍\n"
"     坎 — 天  谷    白    密    黑    夾      崖    砬    峯  柱          門\n"
"           星＼草 —    —    — 風 — 心      ｜    子        峯＼  池  ／峯\n"
"               垛    河    林    口    子      長                  ＼  ／\n"
"                                       ｜      白                    梯\n"
"                                       二＼半／瀑                    雲\n"
"                                       龍  拉  布                    峯\n"
"                                       鬥  瓢\n"
"\n"
"\n"
"　　　【地圖二】\n"
"\n"
"                                        山神廟\n"
"                                       ／\n"
"                                    荒路          船廠 — 冰面 — 大門坎子\n"
"                                   ／              ｜\n"
"                小巷 — 北城    荒路        雪地—雪地\n"
"               ／        ｜      ｜        ／\n"
"          小土屋        集市 — 東城 — 雪地\n"
"                         ｜      ｜\n"
"              香肉館 — 南城    土窯館\n"
"                         ｜\n"
"                        木橋\n"
"                         ｜\n"
"                        大道\n"
"                         ｜\n"
"                        大道\n"
"                      ／\n"
"                   大道\n"
"                    ｜\n"
"                   寧遠\n"
"                  ／\n"
"               官道\n"
"              ／\n"
"           官道\n"
"          ／\n"
"     山海關\n"
"          ＼\n"
"           老龍頭\n"
"\n");
                set("value", 50);
                set("material", "paper");
        }
        setup();
}