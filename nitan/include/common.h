// common.h

// 普通物品列表

// weapon : 武器
// sword　: 劍
// knife　: 匕首
// axe　　: 斧頭
// mace　 : 杖
// club　 : 棍
// bow　　: 弓
// javelin: 標槍
// spear　: 矛
// hammer : 錘

// equip　: 裝備
// helmet : 頭盔
// armor　: 護甲
// shield : 盾
// gloves : 手套
// boots　: 靴子
// belt　 : 腰帶
// ring　 : 戒指
// amulet : 護符
// charm　: 飾物 - 特大, 大型, 小型
// other　: 其他

mapping common_list = ([
        "weapon" : ([   "sword" : ([ "short sword": "短劍", "scimitar" : "彎刀",
　　　　　　　　　　　　　　　　　 "sabre"　　　: "馬刀", "fachion"　: "伶月刀",
　　　　　　　　　　　　　　　　　 "long sword" : "長劍", "war sword": "戰劍",
　　　　　　　　　　　　　　　　　 "crystal sword"　: "水晶劍", "broad sword"　: "闊劍",
　　　　　　　　　　　　　　　　　 "two-hand sword" : "雙手劍", "claymore"　　 : "雙刃刀",
　　　　　　　　　　　　　　　　　 "giant sword"　　: "巨劍",　 "bastard sword": "奇行劍",
　　　　　　　　　　　　　　　　　 "flamberge"　　　: "火燄劍", "great sword"　: "巨人劍", ]),

                        "knife" : ([ "dagger" : "短劍",　 "dirk"　: "匕首",
　　　　　　　　　　　　　　　　　 "kris"　 : "蛇刃劍", "blade" : "刀",
　　　　　　　　　　　　　　　　　 "throwing knife" : "投擲刀", "balanced knife" : "平衡刀", ]),

                        "axe"　 : ([ "hand exe"　 : "手斧",　 "axe"　　　　　 : "斧", 
　　　　　　　　　　　　　　　　　 "double exe" : "雙刃斧", "military pick" : "戰鎬",
　　　　　　　　　　　　　　　　　 "war axe"　　: "戰斧",　 "large axe"　　 : "大斧",
　　　　　　　　　　　　　　　　　 "broad axe"　: "寬斧",　 "battle axe"　　: "戰斧",
　　　　　　　　　　　　　　　　　 "great axe"　: "巨斧",　 "giant axe"　　 : "巨斧", ]),

                        "mace"　: ([ "mace" : "杖", "morning star" : "晨星杖", "flail" : "連枷", ]),
　　　　　　　　　　　
                        "club"　: ([ "club" : "棍", "spiked club"　: "釘棍", ]),
　　　　　　　　　　　
                        "bow"　 : ([ "short bow" : "短弓", "hunter's bow"　: "獵弓",
                        "long bow"　: "長弓", "composite bow" : "復合弓",
　　　　　　　　　　　　　　　　　 "short battle bow" : "短戰弓", "long battle bow" : "長戰弓",
　　　　　　　　　　　　　　　　　 "short war bow"　　: "短戰弓", "long war bow"　　: "長戰弓", ]),

                        "javelin" : ([ "javelin"　　　　: "標槍", "pilum"　: "重標槍",
　　　　　　　　　　　　　　　　　　 "short spear"　　: "短矛", "glaive" : "戈",
　　　　　　　　　　　　　　　　　　 "throwing spear" : "擲矛", ]),

                        "spear"　 : ([ "spear"　　　 : "矛",　 "trident" : "三叉戟",
　　　　　　　　　　　　　　　　　　 "brandistock" : "長矛", "spetum"　: "長矛",
　　　　　　　　　　　　　　　　　　 "pike"　　　　: "長槍", ]), ]),

        "helmet" : ([ "cap"　　　 : "帽子",　 "skull cap"　: "頭盔", "helm"　: "頭盔", 
　　　　　　　        "full helm" : "全頭盔", "great helm" : "巨盔", "crown" : "冠",
　　　　　　　　　　  "mask"　　　: "面具",　 "bone helm"　: "骨盔", ]),

　　　  "armor"　: ([ "quilted armor"　　　: "軟甲",　 "leather armor" : "皮甲",
　　　　　　　　　    "hard leather armor" : "硬皮甲", "studded armor" : "釘甲",
　　　　　　　　　　  "ring mail"　　　　　: "環甲",　 "scale mail"　　: "鱗甲",
　　　　　　　　　　  "chain mail"　　　　 : "鎖子甲", "breast plate"　: "胸甲",
　　　　　　　　　    "splint mail"　　　　: "籐甲",　 "plate mail"　　: "鋼板甲",
　　　　　　　　　　  "field plate"　　　　: "片甲",　 "gothic plate"　: "哥特甲",
　　　　　　　　　　  "full plate mail"　　: "全身甲", "ancient armor" : "舊甲",
　　　　　　　　　　  "light plate"　　　　: "輕甲", ]),

        "shield" : ([ "buckler"　　　: "小園盾", "small shield"　: "小盾",
　　　　　　　　　　  "large shield" : "大盾",　 "kite shield"　 : "長盾",
　　　　　　　　　　  "tower shield" : "平盾",　 "gothic shield" : "哥特盾",
　　　　　　　　　　  "bone shield"　: "骨盾",　 "spiked shield" : "釘盾", ]),

        "gloves" : ([ "leather gloves" : "皮手套", "heavy gloves"　　: "重手套",
　　　　　　　　　　  "chain gloves"　 : "鏈手套", "light gauntlets" : "輕鐵護手",
　　　　　　　　　　  "gauntlets"　　　: "鐵護手", ]),

        "boots"　: ([ "boots"　　　 : "靴子",　 "heavy boots"　　　　: "重靴",
　　　　　　　　　　  "chain boots" : "鎖子靴", "light plated boots" : "輕鐵靴",
　　　　　　　　　　  "greaves"　　 : "護脛甲", ]),

        "belt"　 : ([ "sash" : "腰帶", "light belt" : "輕腰帶",
　　　　　　　　　　  "belt" : "腰帶", "heavy belt" : "重腰帶",
　　　　　　　　　　  "plated belt" : "鐵腰帶", ]),

        "ring"　 : "戒指",
        "amulet" : "護身符",

        "charm"　: ([ "grand charm" : "豪華飾物", "large charm" : "大飾物",
　　　　　　　　　　  "small charm" : "小飾物", ]),

        "potion" : ([ "healing"　: ([ "minor healing potion"　 : "小生命瓶",
　　　　　　　　　　　　　　　　　　  "light healing potion"　 : "輕生命瓶",
　　　　　　　　　　　　　　　　　　  "healing potion"　　　　 : "輕生命瓶",
　　　　　　　　　　　　　　　　　　  "greater healing potion" : "大生命瓶",
　　　　　　　　　　　　　　　　　　  "super healing potion"　 : "特級生命瓶", ]),
　　　　　　　　　　  "mana"　　 : ([ "minor mana potion"　 : "小魔法瓶",
　　　　　　　　　　　　　　　　　　  "light mana potion"　 : "輕魔法瓶",
　　　　　　　　　　　　　　　　　　  "mana potion"　　　　 : "輕魔法瓶",
　　　　　　　　　　　　　　　　　　  "greater mana potion" : "大魔法瓶",
　　　　　　　　　　　　　　　　　　  "super mana potion"　 : "特級魔法瓶", ]),
　　　　　　　　　　  "antidote potion" : "解毒劑",
　　　　　　　　　　  "thawing potion"　: "解凍劑", ]),

        "key"　 : "鑰匙",
        "jewel" : "珠寶",
]);

// 物品出現的幾率
array common_rate_table = ({ "weapon", "potion", "armor", "helmet", "shield",
　　　　　　　　　　　　　　　 "key", "gloves", "boots", "belt", "ring", "amulet",
　　　　　　　　　　　　　　　 "charm", "jewel", });

static int max_rate;

int *common_rate_list = ({ 120, 100, 100, 80, 80, 70, 60, 60, 60, 20, 20, 20, 10, });
