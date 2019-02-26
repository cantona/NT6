// tyroad11.c 桃園小路
// by Marz 

inherit ROOM;
#include "feng.h"
string* npcs = ({
        "little_monkey",
        "monkey",
        "little_monkey",
        "little_bee",
        "bee",
        "little_bee",
});
                                
void do_tao();
int do_zhai(string arg);
void create()
{
        int i = random(sizeof(npcs));
            
        set("short", "榔梅園");
        set("long", @LONG
眼前豁然開朗，你輕鬆地走在榔梅園的小路上。兩邊是桃樹林(t
ree)，樹上盛開着粉紅的桃花，紅雲一片，望不到邊。不時有蜜蜂「
嗡嗡」地飛過，消失在在花叢中；幾隻猴子在樹上互相追逐着，嘰嘰
喳喳地爭搶桃子。遠處是高高的天柱峯(feng)。
LONG );
        set("outdoors", "wudang");

        set("exits", ([
                "east" : "/d/wudang/lameigt",
        ]));
        
        set("item_desc", ([
                "feng" : (:look_feng:),
                "tree" : 
"這是一片桃林，上面結滿了水蜜桃，引得人哈喇子都掉下來了。\n"
         ]));
        set("objects", ([
                 CLASS_D("wudang") + "/shouyuan" : 1,
                "/d/wudang/npc/"+npcs[i] : 1
        ]));
        set("taocount",2);
//        set("no_clean_up", 0);
        setup();
}
void init()
{
        add_action("look_feng", "look");
        add_action("do_zhai","zhai");
}

int do_zhai(string arg)
{       object tao;
         if( !arg || arg=="" ) {
message_vision("你想摘什麼？\n", this_player());
return 1;
}
        if( arg=="tao"||arg=="taozi" ) {
            if(query("taocount") > 0){
                message_vision(
       "$N桃樹上摘下一個熟透的水蜜桃。\n"
                        , this_player());
                tao = new("/d/wudang/obj/mitao");
                tao->move(this_player());
                addn("taocount",-1);
                return 1;
                }else
        message_vision(
        "你這麼着急呀？桃還沒熟呢。\n" , this_player());
        remove_call_out("do_tao");
        call_out("do_tao",60);
        return 1;             
                }
        return 0;
}
void do_tao()
{
        set("taocount",2);
}