/*************************************************

本遊戲移動時，無須作任何改動，可直接放置任何目錄內。

*************************************************/


/**********************************************************************
各物品詳細説明：

_qxd_.c  玩家主判斷物品，包括進入遊戲、退出遊戲、遊戲內指令、
                   遊戲內迷題及其他相關資訊，必不可少
hj_wiztools.c      巫師工具，功能有：可複製遊戲內物件等（隨時添加）


hj_box.c 寶箱，打開時隨機發放人物或物品     標記為  "hj_game/obj","box"

hj_npc_kill.c  殺戮型NPC，亦被作為攜帶各族寶物之NPC使用
               標記為 "hj_game/npc","kill"
hj_npc_quest.c 迷題型NPC，其部分資料需要正常遊戲途徑獲得的 _qxd_.c 支持
               標記為 "hj_game/npc","quest"
hj_npc_other.c 其他類型NPC，包括教授技能、恢復體力、提升最大HP、尋求寶物（有獎勵）等
               標記為 "hj_game/npc","other"

hj_obj_weapon.c   兵器類物品，包括各式劍及魔法水晶（皆限用次數）
                  標記為 "hj_game/obj","sword" 或 "hj_game/obj","magic"
hj_obj_quest.c    領會技能型物品，文件名不合真實含義。可學懂遊戲內技能。
                  標記為 "hj_game/obj","quest"
hj_obj_other.c    補給類物品，文件名不合真實含義。各類補充HP的物品。
                  標記為 "hj_game/obj","other"
hj_obj_tools.c    遊戲工具型物品，例如定向水晶可獲得較為準確的當前房間標記號等。
                  標記為 "hj_game/obj","tools"
hj_obj_gem.c      不記入obj_list.h，本物品作為玩家尋求寶物時的附加條件使用。
                  標記為 "hj_game/obj","the_gem"
hj_obj_gem_qz.c   同上，另一個任務的附加條件。


feng_npc.c yu_npc.c lei_npc.c dian_npc.c 及 fyld_npc.h
       四個國度的NPC，攜帶玩家需要尋求的寶物的最重要之組成部分
feng_obj.c yu_obj.c lei_obj.c dian_objc. 及 fyld_obj.h
       四個國度的OBJ,此物品將通過嚴格處理出現

以上國度的NPC或OBJ物件，都將執行判斷隸屬玩家情況而決定是否自毀的函數。


hj_npc_ashman.c    清道夫（小矮人），將負責清除各類玩家丟下的垃圾。
                   標記為 "hj_game/npc","ashman"


迷題型物品    獎勵型物品   （遊戲工具型物品）
*************************************************************************/


// HJ_DIR 在此定義。

#include "get_hj_dir.h"

string *obj_list_all=({

    HJ_DIR + "npc_obj/hj_box",
    HJ_DIR + "npc_obj/hj_box",        // 寶箱概率增加。
    HJ_DIR + "npc_obj/hj_npc_kill",
    HJ_DIR + "npc_obj/hj_npc_kill",   // 殺戮型怪物概率增加。
    HJ_DIR + "npc_obj/hj_npc_quest",
    HJ_DIR + "npc_obj/hj_npc_quest",  // 其他型NPC概率增加。
    HJ_DIR + "npc_obj/hj_npc_other",
    HJ_DIR + "npc_obj/hj_obj_tools",
    HJ_DIR + "npc_obj/hj_obj_quest",
    HJ_DIR + "npc_obj/hj_obj_other",
    HJ_DIR + "npc_obj/hj_obj_weapon",
});

string *obj_list_obj=({
    HJ_DIR + "npc_obj/hj_obj_tools",
    HJ_DIR + "npc_obj/hj_obj_quest",
    HJ_DIR + "npc_obj/hj_obj_other",
    HJ_DIR + "npc_obj/hj_obj_other",   // 補充HP類果品多加一個機會取得。
    HJ_DIR + "npc_obj/hj_obj_weapon",
});

string *obj_list_npc=({
    HJ_DIR + "npc_obj/hj_npc_kill",
    HJ_DIR + "npc_obj/hj_npc_quest",
    HJ_DIR + "npc_obj/hj_npc_other",
});

// 下面是各個國度的寶物組成部分。

string *obj_list_feng=({
    HJ_DIR + "npc_obj/feng_obj",
    HJ_DIR + "npc_obj/feng_npc",
});

string *obj_list_yu=({
    HJ_DIR + "npc_obj/yu_obj",
    HJ_DIR + "npc_obj/yu_npc",
});

string *obj_list_lei=({
    HJ_DIR + "npc_obj/lei_obj",
    HJ_DIR + "npc_obj/lei_npc",
});

string *obj_list_dian=({
    HJ_DIR + "npc_obj/dian_obj",
    HJ_DIR + "npc_obj/dian_npc",
});
