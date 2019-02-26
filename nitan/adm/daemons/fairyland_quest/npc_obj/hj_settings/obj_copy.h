// This file for hj_wiztools.c and hj_npc_quest.c(the no.1 , seller)
// 現有兩個文件包含本文件：hj_wiztools.c 及 hj_npc_quest.c 。
// 實際上，兩份文件所用是不同的。統一在這裏，是為了方便更改。



// ###########################################################
// ################# 下面是巫師用的複製列表 ##################
// ###########################################################

string *can_copy=({"
    \n"HIY"工具類"NOR"\n",
"dx定向水晶","fx飛翔之石","tl脱離水晶","hg迴歸之鏡",
"qd祈禱之石","zh召喚之盒","fd發呆之旗","qz驅逐之旗",
"xr尋人水晶","kt窺探水晶","dw定位之儀",

    "\n"HIY"其他類"NOR"\n",
"wmg無名果","xrg仙人果","tqg淘氣果","dlg毒龍果","ysg野生果實",
"hbs紅色寶石","lvbs綠色寶石","lbs藍色寶石","slg試煉之果",


    "\n"HIY"武器類"NOR"\n",
"qtj青銅之劍","lqj靈氣之劍","byj白銀之劍","ydj盈動之劍",
"hjj黃金之劍","nlj耐力之劍","xyj迅隱之劍","dhj奪魂之劍","bsj必勝之劍",
"kfsj狂風水晶","bysj暴雨水晶","llsj落雷水晶","ydsj引電水晶","gssj滾石水晶",
"fhsj飛火水晶","dhsj奪魂水晶",

    "\n"HIY"迷題物品類"NOR"\n",
"hfzs呼風之石","hyzs喚雨之石","llzs落雷之石","ydzs引電之石",
"gszs滾石之石","fhs飛火之石","dhzs奪魂之石","fhzs復活之石",

    "\n"HIY"特殊物品類(不可購買)"NOR"\n",
"srl神人令（5分鐘效能）", "box寶箱",
});


mapping all=([

"dx":"定向水晶","fx":"飛翔之石","tl":"脱離水晶","hg":"迴歸之鏡","qd":"祈禱之石",
"zh":"召喚之盒","fd":"發呆之旗","qz":"驅逐之旗","xr":"尋人水晶","kt":"窺探水晶",
"dw":"定位之儀",

"wmg":"無名果","xrg":"仙人果","tqg":"淘氣果","dlg":"毒龍果","ysg":"野生果實",
"hbs":"紅色寶石","lvbs":"綠色寶石","lbs":"藍色寶石","slg":"試煉之果",


"qtj":"青銅之劍","lqj":"靈氣之劍","byj":"白銀之劍","ydj":"盈動之劍",
"hjj":"黃金之劍","nlj":"耐力之劍","xyj":"迅隱之劍","dhj":"奪魂之劍","bsj":"必勝之劍",


"kfsj":"狂風水晶","bysj":"暴雨水晶","llsj":"落雷水晶","ydsj":"引電水晶",
"gssj":"滾石水晶","fhsj":"飛火水晶","dhsj":"奪魂水晶",

"hfzs":"呼風之石","hyzs":"喚雨之石","llzs":"落雷之石","ydzs":"引電之石",
"gszs":"滾石之石","fhs":"飛火之石","dhzs":"奪魂之石","fhzs":"復活之石",

"srl":"神人令(5分鐘的)", "box":"寶箱",

    ]);



mapping all_dir=([

"dx":"hj_obj_tools","fx":"hj_obj_tools","tl":"hj_obj_tools","hg":"hj_obj_tools",
"qd":"hj_obj_tools","zh":"hj_obj_tools","fd":"hj_obj_tools","qz":"hj_obj_tools",
"xr":"hj_obj_tools","kt":"hj_obj_tools","dw":"hj_obj_tools",

"wmg":"hj_obj_other","xrg":"hj_obj_other","tqg":"hj_obj_other",
"dlg":"hj_obj_other","ysg":"hj_obj_other","hbs":"hj_obj_other",
"lvbs":"hj_obj_other","lbs":"hj_obj_other","slg":"hj_obj_other",

"qtj":"hj_obj_weapon","lqj":"hj_obj_weapon","byj":"hj_obj_weapon","ydj":"hj_obj_weapon",
"hjj":"hj_obj_weapon","nlj":"hj_obj_weapon","xyj":"hj_obj_weapon","dhj":"hj_obj_weapon",
"bsj":"hj_obj_weapon","kfsj":"hj_obj_weapon","bysj":"hj_obj_weapon",
"llsj":"hj_obj_weapon","ydsj":"hj_obj_weapon","gssj":"hj_obj_weapon",
"fhsj":"hj_obj_weapon","dhsj":"hj_obj_weapon",

"hfzs":"hj_obj_quest","hyzs":"hj_obj_quest","llzs":"hj_obj_quest","ydzs":"hj_obj_quest",
"gszs":"hj_obj_quest","fhs":"hj_obj_quest","dhzs":"hj_obj_quest","fhzs":"hj_obj_quest",
"srl":"shenren_ling","box":"hj_box",
    ]);

mapping all_set=([

"dx":111,"fx":1,"tl":2,"hg":3,"qd":4,"zh":5,"fd":6,"qz":7,"xr":8,"kt":9, "dw":10,

"wmg":111,"xrg":1,"tqg":2,"dlg":3,"ysg":4,
"hbs":5,"lvbs":6,"lbs":7,"slg":8,

"qtj":111,"lqj":1,"byj":2,"ydj":3,
"hjj":4,"nlj":5,"xyj":6,"dhj":7,"bsj":8,

"kfsj":9,"bysj":10,"llsj":11,"ydsj":12,
"gssj":13,"fhsj":14,"dhsj":15,

"hfzs":111,"hyzs":1,"llzs":2,"ydzs":3,"gszs":4,"fhs":5,"dhzs":6,"fhzs":7,
"srl":1024, "box":1024,
// 這個 srl(神人令) 的 set 的方法已更改，這裏的數值毫無意義了。
    ]);

// 在隨後的時候學懂了 mapping 的用法，發現 hj_wiz_tools.c 裏的
// list方案寫得有夠愚笨的哎……


// ###########################################################
// ################# 下面是玩家用的銷售列表 ##################
// ###########################################################

mapping can_sell_tools=([   // 奇特

"dx":"定向水晶","fx":"飛翔之石","tl":"脱離水晶","hg":"迴歸之鏡","test":"測試啦",
"qd":"祈禱之石","zh":"召喚之盒","fd":"發呆之旗","qz":"驅逐之旗","xr":"尋人水晶",
"kt":"窺探水晶","dw":"定位之儀",
    ]);

mapping can_sell_other=([   // 果品類

"wmg":"無名果","xrg":"仙人果","tqg":"淘氣果","dlg":"毒龍果",
"ysg":"野生果實","slg":"試煉之果"
    ]);

mapping can_sell_weapon=([   // 兵器類

"qtj":"青銅之劍","lqj":"靈氣之劍","byj":"白銀之劍","ydj":"盈動之劍",
"hjj":"黃金之劍","nlj":"耐力之劍","xyj":"迅隱之劍","dhj":"奪魂之劍","bsj":"必勝之劍",
"kfsj":"狂風水晶","bysj":"暴雨水晶","llsj":"落雷水晶","ydsj":"引電水晶","gssj":"滾石水晶",
"fhsj":"飛火水晶","dhsj":"奪魂水晶"
    ]);

mapping can_sell_quest=([    // 神祕

"hfzs":"呼風之石","hyzs":"喚雨之石","llzs":"落雷之石","ydzs":"引電之石",
"gszs":"滾石之石","fhs":"飛火之石","dhzs":"奪魂之石","fhzs":"復活之石"
    ]);


// 此文件內記錄各道具的價格
#include "obj_values.h"