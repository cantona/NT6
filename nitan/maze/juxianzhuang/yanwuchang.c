// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "演武場");
        set("long",  @LONG
遊氏雙雄身為一方豪富，卻不失武林中人的本色，宅邸之中的演武場
修葺得尤為廣闊，場中旌旗蔽空，檣帆林立，場邊的兵器架上擺放着
刀、槍、劍、戟、錘等十八般兵器，被家丁們擦拭得寒光閃閃。遊氏
雙雄嗜武成痴，時常邀請武林中的前輩耆宿、後起之秀來莊中比試切
磋。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  __DIR__"neitang",
                "east"  :  __DIR__"huayuan",
                "south" :  __DIR__"changlang4",
                "north" :  __DIR__"changlang3",
        ]));
        /*
        set("objects",([
                __DIR__"npc/haojie" : 1,
                __DIR__"npc/sengren" : 1,
                __DIR__"npc/qigai"  : 1,
        ]));
        */
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
