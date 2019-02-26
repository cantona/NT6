// 這是為新任務所做的房子
// add by chhu
// Modified by haiyan

inherit ROOM;
#include <ansi.h> 
#include <room.h> 

void create()
{
     set("short", "峭壁");
        set("long", @LONG
這是位於終南山的一處峭壁，遠處傳來洶湧的流水聲，周圍是陰
暗的叢林。一面光滑的大石(stone)上面似乎密密麻麻地刻着些字。
LONG );
     set("exits", ([ /* sizeof() == 1 */ 
         "south" : "/d/changan/zhongnan.c",
     ])); 

     set("objects", ([ 
         "/d/wudang/quest/tianshi" : 1,
     ]));

     set("coor/x", -320);
        set("coor/y", 10);
        set("coor/z", 0);
        setup(); 
}

void init() 
{ 
    add_action("do_look","look"); 
} 

int do_look(string arg) 
{ 
    string msg; 
    if (!arg || arg != "stone")  return 0; 
    msg  = HIC "----------------------------------------------------------\n"NOR; 
    msg += WHT BBLU "                        捉鬼任務簡介                      \n"NOR; 
    msg += HIC "----------------------------------------------------------\n"NOR; 
    msg += "    武當派和全真教弟子身為道士，自然會降妖驅魔的本事。可以\n";
    msg += "向李天師打聽任務。降妖驅魔需要兩件寶物，一是"HIY"符紙"NOR"，二是"HIM"桃木\n";
    msg += "劍"NOR"。領取任務時，李天師會給你"HIY"符紙"NOR"，而"HIM"桃木劍"NOR"則需要自己想辦法\n";
    msg += "了。:)\n";
    msg += "    這項工作有一定的難度，妖魔一般都是隱身看不見的，你只能\n";
    msg += "夠感覺它的存在，並利用"HIY"符紙"NOR"使其現身。當你感覺到妖魔存在時，\n";
    msg += "只可使用"HIC"shoufu"NOR"指令，不能kill它。但妖魔一般都比較厲害，你最\n";
    msg += "好做足充分的準備。完成任務後，將"HIY"符紙"NOR"交還給李天師，即可得到\n";
    msg += "獎勵。\n";
    this_player()->start_more(msg); 
    return 1; 
} 
