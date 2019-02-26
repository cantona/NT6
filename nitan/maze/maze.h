#include <ansi.h>
mapping *mazes = ({ 
              ([      "name":         HIG"原始森林"NOR,
                                 "code":         "forest",
                "len":               10,     
                "lvl":                      1,
                "outdoor":            1,
                "time":               3600,
        ]),
        ([      "name":         HIW"神祕冰窟"NOR,
                                "code":         "icecave",
                "len":               6,
                "lvl":                      2,
                "outdoor":            0,
                "time":               900,
        ]),
        ([      "name":         CYN"詭異洞穴"NOR,
                                "code":         "darkhole",
                "len":               6,
                "lvl":                      3,
                "outdoor":            0,
                "time":               1200,
        ]),
        ([      "name":         WHT"無盡大漠"NOR,
                                "code":         "desert",
                "len":               6,
                "lvl":                      4,
                "outdoor":            1,
                "time":               1200,
        ]),
        ([      "name":         HIY"失落神廟"NOR,
                                "code":         "temple",
                "len":               6,
                "lvl":                      5,
                "outdoor":            0,
                "time":               1500,
        ]),
        ([      "name":         RED"墓園"NOR,
                                "code":         "necropolis",
                "len":               7,
                "lvl":                      6,
                "outdoor":            1,
                "time":               5400,
        ]),
});
mapping maze_desc = ([
"forest" :
"原始森林樹葉蒼黑如蓋，遮天蔽日，林中瀰漫着枯葉腐爛
和樹脂混合的味道，地上的苔鮮落葉踩上去軟綿綿的，上面還
佈滿野獸的痕跡，四周濃密的山霧，讓人難以分辨方向。",
"icecave" :
"冰窟內温度極低，四面都是厚厚的冰層，地面很滑，雖然
沒有任何陽光透入，但冰筍，冰牆反射的出的寒光讓冰窟裏的
東西一清二楚，再往裏面走，即便不遇上什麼怪物，寒冷的空
氣足可以把任何人凍僵。",
"darkhole" :
"洞穴很暗，幾乎伸手不見五指，地上很滑，偶爾有些小動
物的叫聲，蝙蝠突然掠過，你總覺得四周有一雙詭異的眼睛盯
着你，一股股寒意從心裏冒出，你總想往身後看，但卻十分害
怕，只能不斷的往前走。",
"desert" :
"一望無際的大漠，烈日、風沙、苦寒、酷熱，無時不在折
磨着每一個人，在這裏，如果你沒有飲水，很有可能就會被曬
死，沙子滾燙，足以把腳燙爛，一到晚上，卻又冰冷得透骨。",
"temple" :
"神廟很大，柱子上雕刻着千奇百怪的動物，有的人身上卻
長着一顆狼頭，人身上生出一雙翅膀，怪異的怪首的雕刻讓人
歎為觀止，廟頂成八角，屋脊曲線柔美,泥塑,剪黏,木雕,彩繪
皆為上品。",
"necropolis" :
"墓園裏沒有一點生氣，地上到處是枯枝敗葉，偶爾看到一些
乾枯的動物屍骸，讓人不寒而慄，到處散發着一股屍首腐爛的
味道，看不到一絲活物存在。",
]);


