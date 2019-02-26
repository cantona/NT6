
#include <ansi.h>

inherit ROOM;
void create()
{
        set("short",HIR"["+HIY+"深田恭子麻將館"+HIR+"]"NOR);
        set("long", @LONG
這是一間專門讓玩家們休息的娛樂場所，當你在為你的角色
辛苦鍛  時，別忘了休息是為了走更長遠的路，找叁五好友一同
來打個幾圈吧，不過可別沉迷在賭博中喔～～～～詳細的規則請
看看布告欄（ｂｏａｒｄ）
LONG
);

        set("no_fight", 1);
        set("no_magic", 1);
      
        set("exits",([
                "west": "/d/city/tree2",
        ]));
        set("objects",([
                "/clone/game/mjlady3":1,
        ]));
        
        set("item_desc",([
                "board":"
 一般基本的操作：：  每種牌都有其代碼　例：一萬－＞1w 七索－＞7s
 加入牌局   ："HIY"addin"NOR"        開始牌局   ："HIY"start"NOR" 
 摸牌       ："HIY"mo"NOR"           重開牌局   ："HIY"restart"NOR" 
 看玩家1的牌："HIY"-1"NOR"           看玩家2的牌："HIY"-2"NOR" 
 看玩家3的牌："HIY"-3 "NOR"          看玩家4的牌："HIY"-4"NOR" 
 看自己的牌 ："HIY"-"NOR"            看所有玩家的牌："HIY"-0"NOR" 
 丟牌       ："HIY"dump xx"NOR"      吃         ："HIY"eat xx xx "NOR"        
 碰         ："HIY"pon"NOR"          槓         ："HIY"gon "NOR"              
 胡         ："HIY"hu"NOR"           聽         ："HIY"tin xx  "NOR"          
 xx為代碼 例："HIY"eat 2w 3w"NOR" 
",
        ]));
        setup();
}
